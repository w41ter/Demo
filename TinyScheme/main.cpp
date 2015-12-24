#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <functional>
#include <iterator>
#include <sstream>
#include <memory>
#include <queue>
#include <map>
#include <stack>
#include <list>

using namespace std;

/* string table */
/* the BKDR hash funcion */
static unsigned int BKDRHash(const char *str) {
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..    
    unsigned int hash = 0;

    while (*str) {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

const int MAX_BUCKET = 2048;

static map<unsigned, const char*> *Buckets() {
    static map<unsigned, const char*> buckets[MAX_BUCKET];
    return buckets;
}

void st_clear() {
    map<unsigned, const char*> *bucket = Buckets();
    for (int i = 0; i < MAX_BUCKET; ++i) {
        for (auto j : bucket[i])
            delete j.second;
        bucket[i].clear();
    }
}

void st_create() {
    st_clear();
}

const char *st_insert(const char *str) {
    map<unsigned, const char*> *bucket = Buckets();
    unsigned int hash = BKDRHash(str), pos = hash % MAX_BUCKET;
    if (bucket[pos].count(hash) == 0) {
        char *tmp = new char[strlen(str) + 1];
        strcpy(tmp, str);
        bucket[pos][hash] = tmp;
    }
    return bucket[pos][hash];
}

const char *st_lookup(const char *str) {
    map<unsigned, const char*> *bucket = Buckets();
    unsigned int hash = BKDRHash(str), pos = hash % MAX_BUCKET;
    if (bucket[pos].count(hash) == 0) {
        return nullptr;
    }
    return bucket[pos][hash];
}

/* end string table */


typedef intptr_t RtsPtr;  // 所有Scheme的值都是pointer

// 定义 pointer tagging 的相关常数。这些 type 会以 tagging 的形式存在 pointer 的值上
enum {
    kNotTag = 0,
    kFixnumTag = 1,  // integer用1来进行tag
    //kPairTag = 2,  // pair用2来进行tag
    kStringTag = 2,  // string用2来进行tag
    kSpecTag = 3,  // 特殊的值（#t, #f, '()之类的）用3来进行tag

    kTagShift = 2,  // tag的宽度是2
    kTagMask = 3   // 用于检查pointer tag
};

// 定义其他的 type。这些 type 会存在 obType 里
enum {
    kPairTag = 1,
    kNativeProc = 2,
    kBytecode = 3,
    kBytecodeProc = 4,
    kListTag = 5,
};

// 定义heap object共有的一些property，用于GC以及其他runtime的操作
// gcMark是garbage collector所使用的，用于存储gc过程中对object进行的标记
// obType表示该object的类型（如果该object不是一个tagged pointer的话）
#define HEAP_OBJECT_HEAD \
    int8_t gcMark;       \
    int8_t obType

bool isTagging(RtsPtr row) {
    return (row & kTagMask);
}

// 将C里面的int转换成Scheme里面的int（即fixnum）
RtsPtr makeFixnum(intptr_t rawInt) {
    return kFixnumTag + (rawInt << kTagShift);
}

// 检查一个Scheme的值是不是fixnum
bool isFixnum(RtsPtr maybeInt) {
    return (maybeInt & kTagMask) == kFixnumTag;
}

// tag 通用的
intptr_t getValue(RtsPtr val) {
    return val >> kTagShift;
}

// 判断是否特殊标记
bool isSpec(RtsPtr val) {
    return (val & kTagMask) == kSpecTag;
}

RtsPtr makeSpec(intptr_t val) {
    return kSpecTag + (val << kTagShift);
}

// String
RtsPtr makeString(intptr_t rawInt) {
    return kStringTag + (rawInt << kTagShift);
}

bool isString(RtsPtr maybeStr) {
    return (maybeStr & kTagMask) == kStringTag;
}

size_t stringLength(RtsPtr str) {
    return strlen((const char*)(str >> kTagShift));
}

bool toBoolean(RtsPtr value) {
    if (isSpec(value)) {
        return getValue(value);
    }
    return true;
}

// 定义Scheme里面的pair
typedef struct {
    HEAP_OBJECT_HEAD;
    RtsPtr car, cdr;
} Pair;

// 将一块已分配好的内存初始化为一个pair，并且返回这个pair
RtsPtr makePair(RtsPtr self, RtsPtr car, RtsPtr cdr) {
    // 我们可以在 obType 里记录这是一个 pair
    // 也可以用 pointer tagging 的方式 (见下面的注释) 来记录。
    // 这里我选择用 pointer tagging

    ((Pair *)self)->gcMark = 0;
    ((Pair *)self)->car = car;
    ((Pair *)self)->cdr = cdr;
    ((Pair *)self)->obType = kPairTag;
    // 记录这是一个 pair，只不过是用 pointer tagging 的方式。
    // pointer tagging 由于是将 tag 存在 pointer 的值里，检查的时候不需要
    // 访问内存，理论上来说比检查内存里的 obType 来得更快一些。当然了，这样会在其他地方
    // 带来一个速度的降低 (检查一个 pointer 的类型的时候需要先检查 tag，再检查 obType).
    // 所以解释器/编译器很多的时候都要根据实际使用情况以及测试结果来做一个取舍。
    // 这里还有另一个隐含的约定：这个 pair pointer 一定是 align 在
    // word boundary 上的，所以最低的 2-3 个 bit 一定是 0。正因为如此，我们才能挤出
    // 这几个 bit 来存储 type 方面的信息。
    //return self + kPairTag;
    return self;
}

// 检查一个Scheme的值是不是pair
bool isPair(RtsPtr maybePair) {
    return ((Pair *)maybePair)->obType == kPairTag;
}

// 一个pair的car的地址
RtsPtr *getCar(RtsPtr self) {
    return &((Pair *)(self))->car;
}

// 同上
RtsPtr *getCdr(RtsPtr self) {
    return &((Pair *)(self))->cdr;
}

size_t SizeOfObject(RtsPtr self) {
    return sizeof(self);
}


//////////////////////////////////////////////////////////////////////////
// GC 部分
//////////////////////////////////////////////////////////////////////////

struct Semispace {
    RtsPtr _bottom;
    RtsPtr _top;
    RtsPtr _end;
};

typedef void*(*Alloc)(size_t);
typedef void*(*Realloc)(void *, size_t);
typedef void(*Free)(void *);

struct Scheme {
    Alloc malloc;
    Free free;
    
    struct {
        Semispace *_from_space;
        Semispace *_to_space;
        size_t size;
        size_t space_size;
        intptr_t forward;
    };

    map<const char*, RtsPtr> global_variable;
};

/* 方便GC */
size_t Ceil(size_t size) {
    int c = size % sizeof(RtsPtr);
    if (c != 0) c = sizeof(RtsPtr) - c;
    return size + c;
}

void InitSemispace(Scheme *scheme, Semispace *ptr, size_t size) {
    size_t space_size = Ceil(size);
    ptr->_bottom = (RtsPtr)scheme->malloc(space_size);
    ptr->_end = ptr->_bottom + space_size;
    ptr->_top = ptr->_bottom;
}

void DestroySemispace(Scheme *scheme, Semispace *ptr) {
    scheme->free((void*)ptr->_bottom);
    ptr->_bottom = ptr->_end = ptr->_top = NULL;
}

bool Contains(Semispace *ptr, RtsPtr obj) {
    return (ptr->_bottom <= obj && obj < ptr->_end);
}

RtsPtr AllocateMemory(Semispace *space, size_t size) {
    size_t space_size = Ceil(size);
    if (space->_top + space_size <= space->_end) {
        RtsPtr obj = space->_top;
        space->_top += space_size;
        return obj;
    }
    else {
        return NULL;
    }
}

void Reset(Semispace *space) {
    space->_top = space->_bottom;
}

void InitSchemeAllocate(Scheme *scheme, size_t size) {
    scheme->size = size;
    scheme->space_size = Ceil(size) >> 2;
    scheme->_from_space = (Semispace*)scheme->malloc(sizeof(Semispace));
    scheme->_to_space = (Semispace*)scheme->malloc(sizeof(Semispace));
    InitSemispace(scheme, scheme->_from_space, scheme->space_size);
    InitSemispace(scheme, scheme->_to_space, scheme->space_size);
}

void DestroySchemeAllocate(Scheme *scheme) {
    DestroySemispace(scheme, scheme->_from_space);
    DestroySemispace(scheme, scheme->_to_space);
    scheme->free((void*)scheme->_from_space);
    scheme->free((void*)scheme->_to_space);
    scheme->_from_space = scheme->_to_space = NULL;
}

void SwapSpace(Scheme *scheme) {
    Semispace* temp = scheme->_from_space;
    scheme->_from_space = scheme->_to_space;
    scheme->_to_space = temp;

    // After swapping, the to-space is assumed to be empty.
    // Reset its allocation pointer.
    Reset(scheme->_to_space);
}

bool IsForwarded(Scheme *scheme, RtsPtr obj) {
    size_t offset = obj - scheme->_from_space->_bottom;
    int *forward = (int*)scheme->forward;
    return (forward[offset >> 2] != NULL);
}

void ForwardTo(Scheme *scheme, RtsPtr obj, RtsPtr new_addr) {
    size_t offset = obj - scheme->_from_space->_bottom;
    int *forward = (int*)scheme->forward;
    forward[offset >> 2] = new_addr;
}

RtsPtr Forwardee(Scheme *scheme, RtsPtr obj) {
    size_t offset = obj - scheme->_from_space->_bottom;
    int *forward = (int*)scheme->forward;
    return forward[offset >> 2];
}

RtsPtr Swap(Scheme *scheme, RtsPtr obj, size_t size) {
    RtsPtr dest = AllocateMemory(scheme->_to_space, size);
    memcpy((void*)dest, (void*)obj, size);
    return dest;
}

void ProcessReference(Scheme *scheme, RtsPtr *slot) {
    size_t szie = SizeOfObject(*slot);
    RtsPtr obj = *slot;
    if (obj == NULL) return;

    if (Contains(scheme->_from_space, obj)) {
        if (IsForwarded(scheme, obj)) {
            *slot = Forwardee(scheme, obj);
        }
        else {
            RtsPtr new_obj = Swap(scheme, obj, sizeof(Pair));
            ForwardTo(scheme, obj, new_obj);
            *slot = new_obj;
        }
    }

    //if (!isTagging(obj)) {
    //    if (Contains(scheme->_from_space, obj)) {
    //        if (IsForwarded(scheme, obj)) {
    //            *slot = Forwardee(scheme, obj);
    //        }
    //        else {
    //            RtsPtr new_obj = Swap(scheme, obj, sizeof(Pair));
    //            ForwardTo(scheme, obj, new_obj);
    //        }
    //    }
    //}
}

void GarbageCollect(Scheme *scheme, RtsPtr *address) {
    scheme->forward = (RtsPtr)scheme->malloc(Ceil(scheme->space_size));
    memset((void*)scheme->forward, 0, Ceil(scheme->space_size));

    // 隐式队列
    RtsPtr scanned = scheme->_to_space->_bottom;

    for (int i = 0; i < 9; ++i) {
        cout << ((int*)scheme->forward)[i] << endl;
        ProcessReference(scheme, &address[i]);
    }

    // breadth-first scanning of object graph
    while (scanned < scheme->_to_space->_top) {
        RtsPtr parent_obj = scanned;
        ProcessReference(scheme, &parent_obj);
        scanned += SizeOfObject(parent_obj);
    }

    // Now all live objects will have been evacuated into the to-space,
    // and we don't need the data in the from-space anymore.
    SwapSpace(scheme);

    scheme->free((void*)scheme->forward);
    scheme->forward = NULL;
}

RtsPtr Allocate(Scheme *scheme, size_t size) {
    RtsPtr address = AllocateMemory(scheme->_from_space, size);
    if (address == NULL) {
        //GarbageCollect(scheme);
        address = AllocateMemory(scheme->_from_space, size);
        if (address == NULL) {
            // error
        }
        else {
            return address;
        }
    } 
    else {
        return address;
    }
}

/* end of garbage collect */

/* begin visual machine */

enum Instruction {
    OP_SHUTDOWN,

    /* 栈上操作 */
    OP_PUSH, 
    OP_POP, 
    OP_LOAD,
    OP_STORE,
    OP_SET,
    OP_GET,
    OP_EXTEND,

    /* 调用操作 */
    OP_CALL,
    OP_RET,
    OP_JMP,
    OP_JL,
    OP_JG,
    
    /* 运算 */
    OP_ADD, 
    OP_SUB, 
    OP_MUL, 
    OP_DIV, 
    OP_MOD,

    /* debug 相关 */
    OP_SHOW, 
    OP_INSERT,
};

#define MAX_LENGTH 2048

struct Instructions {
    Instruction instr;
    RtsPtr imuniate;
};

struct CallStack {
    RtsPtr pc;
    RtsPtr *stacks;
    size_t top;
    size_t length;
    CallStack *parent;
};

struct VMstate {
    Instructions instructions[MAX_LENGTH];
    map<const char*, RtsPtr> global_variable;

    CallStack *global_stacks;
    CallStack *cur_stacks;

    Alloc malloc;
    Realloc realloc;
    Free free;
};

void InitVMstate(VMstate *vm) {
    vm->global_stacks = (CallStack*)vm->malloc(sizeof(CallStack));
    vm->cur_stacks = vm->global_stacks;
    vm->cur_stacks->stacks = (RtsPtr*)vm->malloc(sizeof(RtsPtr) * 1024);
    vm->cur_stacks->length = 1024;
    vm->cur_stacks->parent = NULL;
    vm->cur_stacks->top = vm->cur_stacks->pc = 0;
}

void DestoryVMstate(VMstate *vm) {
    while (vm->cur_stacks != NULL) {
        CallStack *stacks = vm->cur_stacks;
        vm->cur_stacks = vm->cur_stacks->parent;
        vm->free(stacks->stacks);
        vm->free(stacks);
    }
    vm->cur_stacks = vm->global_stacks = NULL;
}

RtsPtr StackTop(VMstate *vm, size_t pos = 0) {
    return vm->cur_stacks->stacks[vm->cur_stacks->top - pos];
}

RtsPtr StackPop(VMstate *vm, size_t size = 1) {
    RtsPtr res = NULL;
    while (size--) {
        res = vm->cur_stacks->stacks[vm->cur_stacks->top--];
    }
    return res;
}

void StackPush(VMstate *vm, RtsPtr value) {
    if (vm->cur_stacks->length == vm->cur_stacks->top) {
        vm->cur_stacks->stacks = (RtsPtr*)vm->realloc(
            vm->cur_stacks->stacks, 
            sizeof(RtsPtr) * vm->cur_stacks->length * 2
            );
    }
    ++vm->cur_stacks->top;
    vm->cur_stacks->stacks[vm->cur_stacks->top] = value;
}

void StackLoad(VMstate *vm, const char *name) {
    StackPush(vm, vm->global_variable[name]);
}

RtsPtr StackStore(VMstate *vm, const char *name) {
    return vm->global_variable[name] = StackPop(vm);
}

void StackSet(VMstate *vm, size_t pos) {
    vm->cur_stacks->stacks[pos] = StackPop(vm);
}

void StackGet(VMstate *vm, size_t pos) {
    StackPush(vm, vm->cur_stacks->stacks[pos]);
}

void CallFunction(VMstate *vm, size_t size) {
    CallStack *func = (CallStack*)vm->malloc(sizeof(CallStack));
    func->stacks = (RtsPtr*)vm->malloc(sizeof(RtsPtr) * 1024);
    func->length = 1024;
    func->parent = vm->cur_stacks;
    //func->stacks[0] = vm->cur_stacks->pc + 1;   /* 返回CALL 下一条指令 */
    func->pc = StackPop(vm);
    func->top = size - 1;
    for (size_t pos = 0; pos < size; ++pos) {
        func->stacks[pos] = StackPop(vm);
    }
    vm->cur_stacks = func;
}

void Return(VMstate *vm) {
    CallStack *func = vm->cur_stacks;
    vm->cur_stacks = vm->cur_stacks->parent;
    StackPush(vm, func->stacks[func->top]);
}

#define OPCODE(code) case OP_##code:

void Run(VMstate *vm) {
    while (true) {
    Begin:
        Instructions instr = vm->instructions[vm->cur_stacks->pc];
        switch (instr.instr)
        {
        OPCODE(SHUTDOWN) {
            return;
        }
        OPCODE(PUSH) {
            StackPush(vm, instr.imuniate);
            break;
        }
        OPCODE(POP) {
            StackPop(vm, instr.imuniate);
            break;
        }
        OPCODE(LOAD) {
            StackLoad(vm, (const char*)instr.imuniate);
            break;
        }
        OPCODE(STORE) {
            vm->global_variable[(const char*)instr.imuniate] = 
                StackStore(vm, (const char*)instr.imuniate);
            break;
        }
        OPCODE(SET) {
            StackSet(vm, instr.imuniate);
            break;
        }
        OPCODE(GET) {
            StackGet(vm, instr.imuniate);
            break;
        }
        OPCODE(EXTEND) {
            vm->cur_stacks->top += instr.imuniate;
            break;
        }
        OPCODE(CALL) {
            CallFunction(vm, instr.imuniate);
            goto Begin;
        }
        OPCODE(RET) {
            Return(vm);
            break;
            // 这里需要指向下一条
        }
        OPCODE(JMP) {
            vm->cur_stacks->pc += instr.imuniate;
            break;
        }
        OPCODE(JG) {
            RtsPtr op1 = StackPop(vm), op2 = StackPop(vm);
            if (op1 > op2) {
                vm->cur_stacks->pc += instr.imuniate;
                goto Begin;
            }
            break;
        }
        OPCODE(JL) {
            RtsPtr op1 = StackPop(vm), op2 = StackPop(vm);
            if (op1 < op2) {
                vm->cur_stacks->pc += instr.imuniate;
                goto Begin;
            }
            break;
        }
        OPCODE(MUL) {
            RtsPtr op1 = StackPop(vm), op2 = StackPop(vm);
            StackPush(vm, op1 * op2);
            break;
        }
        OPCODE(ADD) {
            RtsPtr op1 = StackPop(vm), op2 = StackPop(vm);
            StackPush(vm, op1 + op2);
            break;
        }
        OPCODE(SUB) {
            RtsPtr op1 = StackPop(vm), op2 = StackPop(vm);
            StackPush(vm, op1 - op2);
            break;
        }
        OPCODE(DIV) {
            RtsPtr op1 = StackPop(vm), op2 = StackPop(vm);
            StackPush(vm, op1 / op2);
            break;
        }
        OPCODE(MOD) {
            RtsPtr op1 = StackPop(vm), op2 = StackPop(vm);
            StackPush(vm, op1 % op2);
            break;
        }
        OPCODE(SHOW) {
            cout << StackPop(vm);
            break;
        }
        OPCODE(INSERT) {
            RtsPtr ptr;
            cin >> ptr;
            StackPush(vm, ptr);
            break;
        }
        default:
            break;
        }
        vm->cur_stacks->pc++;
    }
    
}

/* end visual machine */

int test() {
    Scheme scheme;
    scheme.malloc = malloc;
    scheme.free = free;
    InitSchemeAllocate(&scheme, sizeof(RtsPtr) * 1024);

    const char * buff[] = {
        "1", "2", "3", "4", "5", "6",
        "7", "8", "9", "10"
    };
    RtsPtr address[10];
    for (int i = 0; i < 10; ++i) {
        address[i] = Allocate(&scheme, sizeof(RtsPtr));
    }

    for (int i = 0; i < 10; ++i) {
        RtsPtr ptr = address[i];
        *((int*)ptr) = i;
    }

    for (int i = 0; i < 10; ++i) {
        RtsPtr ptr = address[i];
        cout << buff[i] << " address is " << ptr << " , var is " << *((int*)ptr) << endl;
    }
        
    cout << "\n\nBegin GC" << endl;

    GarbageCollect(&scheme, &address[1]);
    for (int i = 0; i < 10; ++i) {
        RtsPtr ptr = address[i];
        cout << buff[i] << " address is " << ptr << " , var is " << *((int*)ptr) << endl;
    }

    DestroySchemeAllocate(&scheme);
    return 0;
}

void test_vm() {
    char *str[] = {
        "vara",
        "varb",
        "varc",
    };
    VMstate state;
    state.malloc = malloc;
    state.realloc = realloc;
    state.free = free;
    InitVMstate(&state);
    /* A + B = C */
    state.instructions[0] = { OP_INSERT, NULL };
    state.instructions[1] = { OP_STORE, (RtsPtr)"vara" };
    state.instructions[2] = { OP_INSERT, NULL };
    state.instructions[3] = { OP_STORE, (RtsPtr)"varb" };
    state.instructions[4] = { OP_LOAD, (RtsPtr)"vara" };
    state.instructions[5] = { OP_LOAD, (RtsPtr)"varb" };
    state.instructions[6] = { OP_PUSH, 10 };
    state.instructions[7] = { OP_CALL, 2 };
    state.instructions[8] = { OP_SHOW, NULL };
    state.instructions[9] = { OP_SHUTDOWN, NULL };

    // FUNCTION
    state.instructions[10] = { OP_GET, 0 };
    state.instructions[11] = { OP_GET, 1 };
    state.instructions[11] = { OP_ADD, NULL };
    state.instructions[12] = { OP_RET, NULL };
    Run(&state);
    DestoryVMstate(&state);
}
//

struct Object
{
    virtual ~Object() = 0 {}
    virtual string ToString() = 0;
    virtual bool ToBool() = 0;
    virtual long ToInt() = 0;
};

struct Number : public Object 
{
    virtual ~Number() {}
    long value;
    Number(long value) : value(value) {}

    virtual string ToString() 
    {
        stringstream strs;
        strs << value;
        string str;
        strs >> str;
        return str;
    }

    virtual bool ToBool() { return value; }
    virtual long ToInt() { return value; };
};

struct String : public Object
{
    virtual ~String() {}
    const char *value;
    
    virtual string ToString() { return value; };
    virtual bool ToBool() { return true; }
    virtual long ToInt() { return 0; };
};

struct Bool : public Object
{   
    virtual ~Bool() {}
    bool value;
    virtual string ToString() { return value ? "True" : "False"; }
    virtual bool ToBool() { return value; }
    virtual long ToInt() { return value ? 1 : 0; };
};

struct List : public Object
{
    virtual ~List() {}

    list<Object*> value;

    virtual string ToString()
    {
        string tmp = "(list";
        for (auto i : value)
        {
            tmp += " " + i->ToString();
        }
        tmp += ")";
        return tmp;
    }

    virtual bool ToBool() { return 1; }
    virtual long ToInt() { return 1 ? 1 : 0; };
};

struct Scope;

using BuildInFunction = function<RtsPtr(vector<RtsPtr>&, Scope*)>;

struct Scope
{
    Scope *parent;
    map<string, RtsPtr> variableTable;

    static vector<void*> gc;
    static map<string, BuildInFunction> builtinFunctions;

    static map<string, BuildInFunction> &BuildIn(string name, BuildInFunction func) {
        builtinFunctions.insert(pair<string, BuildInFunction>(name, func));
        return builtinFunctions;
    }

    static void GC() {
        for (auto i : gc) {
            delete i;
        }
        gc.clear();
    }

    Scope(Scope *parent = nullptr) : parent(parent) {}

    RtsPtr Find(const string &name)
    {
        Scope *current = this;
        while (current != nullptr) {
            if (current->variableTable.count(name) != 0)
                return current->variableTable[name];
            current = current->parent;
        }
        //throw name + " is not defined.";
        return 0;
    }

    RtsPtr Define(const string &name, RtsPtr value)
    {
        variableTable.insert(pair<string, RtsPtr>(name, value));
        return value;
    }

    Scope * SpawnScopeWith(vector<string> &names, vector<RtsPtr> &values) {
        if (names.size() < values.size())
            throw ("Too many arguments.");

        Scope *scope = new Scope(this);
        for (int i = 0; i < values.size(); i++) {
            scope->variableTable.insert(pair<string, RtsPtr>(names[i], values[i]));
        }
        return scope;
    }

    RtsPtr FindInTop(string &name) {
        if (variableTable.count(name)) {
            return variableTable[name];
        }
        return 0;
    }
};

vector<void*> Scope::gc;
map<string, BuildInFunction> Scope::builtinFunctions;

struct Expression {
    const char *value;
    Expression *parent;
    vector<Expression*> children;

    Expression(const char *val, Expression *parent = nullptr) : value(val), parent(parent) {}

    RtsPtr Evaluate(Scope *scope);

    string ToString()
    {
        if (value == "(") {
            string res = "( ";
            for (auto &i : children)
            {
                res += " " + i->ToString();
            }

            res += " )";
            return res;
        }
        else {
            return value;
        }
    }
};

struct Function : public Object {
    Expression *body;
    vector<string> parameters;
    Scope *scope;

    Function(Expression *e, vector<string> &s, Scope *sc) : body(e), parameters(s), scope(sc) {}

    bool IsPartial()
    {
        int filledParameters = ComputeFilledParametersLength();
        return (filledParameters < parameters.size());
    }

    RtsPtr Evaluate()
    {
        int filledParameters = ComputeFilledParametersLength();
        if (filledParameters < parameters.size())
            return (RtsPtr)this;
        else
            return body->Evaluate(scope);
    }

    int ComputeFilledParametersLength() {
        int ans = 0;
        for (auto &i : parameters)
        {
            if (scope->Find(i))
                ans++;
        }
        return ans;
    }

    Function *Updata(vector<RtsPtr> arguments) {
        vector<RtsPtr> ans;
        for (auto &i : parameters)
        {
            auto p = scope->FindInTop(i);
            if (p) ans.push_back(p);
        }
        for (auto i : arguments) {
            ans.push_back(i);
        }
        Scope *newScope = scope->parent->SpawnScopeWith(parameters, ans);
        Scope::gc.push_back(new Function(body, parameters, newScope));
        return (Function*)Scope::gc.back();
    }

    virtual string ToString() { 
        string ans = "(func ( ";
        for (auto &i : parameters) {
            ans += i;
            auto p = scope->FindInTop(i);
            if (p) ans += ":" + ((Object*)p)->ToString();
            ans += " ";
        }
        ans += ") ";
        ans += body->ToString();
        return ans;
    }
    virtual bool ToBool() { return 1; }
    virtual long ToInt() { return 1 ? 1 : 0; };
};

bool StringToInt(const char *str, long &i)
{
    char *pos; 
    i = strtol(str, &pos, 10);
    if (pos == str)
        return 0;
    else
        return 1;
}

RtsPtr Expression::Evaluate(Scope *scope) {
    Expression *current = this;
    while (true) {
        if (current->children.size() == 0) {
            long number = 0;
            if (StringToInt(current->value, number)) {
                return makeFixnum(number);
            }
            else if (current->value[0] == '"') {
                return makeString((intptr_t)current->value);
            }
            else {
                RtsPtr obj = scope->Find(current->value);
                if (!obj) throw string("没有找到") + current->value;
                return obj;
            }
        }
        else {
            Expression *first = current->children[0];

            if (first->value == st_lookup("if")) {
                bool condition = toBoolean(current->children[1]->Evaluate(scope));
                current = condition ? current->children[2] : current->children[3];
            }
            else if (first->value == st_lookup("let")) {
                return scope->Define(current->children[1]->value, current->children[2]->Evaluate(new Scope(scope)));
            }
            else if (first->value == st_lookup("begin")) {
                RtsPtr result = 0;
                for (auto i : current->children) {
                    result = i->Evaluate(scope);
                }
                return result;
            }
            else if (first->value == st_lookup("lambda")) {
                Expression *body = current->children[2];
                vector<string> parameters;
                for (auto i : current->children[1]->children) {
                    parameters.push_back(i->value);
                }

                Scope *newScope = new Scope(scope);
                Scope::gc.push_back(new Function(body, parameters, newScope));
                return (RtsPtr)Scope::gc.back();
            }
            else if (first->value == st_lookup("list")) {
                RtsPtr cur;
                Pair p;
                cur = (RtsPtr)&p;
                for (int i = 1; i < current->children.size(); ++i) {
                    *getCdr(cur) = (RtsPtr) new Pair;
                    cur = *getCdr(cur);
                    makePair(cur, current->children[i]->Evaluate(scope), 0);
                    Scope::gc.push_back((void*)cur);
                }
                return cur;
            }
            else if (Scope::builtinFunctions.count(first->value)) {
                vector<RtsPtr> arguments;
                for (int i = 1; i < current->children.size(); ++i) {
                    arguments.push_back(current->children[i]->Evaluate(scope));
                }
                return Scope::builtinFunctions[first->value](arguments, scope);
            }
            else {
                Function *function = first->value == st_lookup("(") ? (Function*)first->Evaluate(scope) : (Function*)scope->Find(first->value);
                vector<RtsPtr> arguments;
                for (int i = 1; i < current->children.size(); ++i) {
                    arguments.push_back(current->children[i]->Evaluate(scope));
                }
                Function *newFunction = function->Updata(arguments);
                if (newFunction->IsPartial()) {
                    return newFunction->Evaluate();
                }
                else {
                    current = newFunction->body;
                    scope = newFunction->scope;
                }
            }
        }
    }
}

void DeleteExpression(Expression *exp) {
    if (exp == nullptr) return;
    for (auto i = exp->children.begin(); i != exp->children.end(); ++i)
        DeleteExpression(*i);
    delete exp;
}

vector<string> split(const string& src, string separate_character) {
    vector<string> strs;
    int separate_characterLen = separate_character.size();
    int lastPosition = 0, index = -1;
    while (string::npos != (index = src.find(separate_character, lastPosition)))
    {
        string tmp = src.substr(lastPosition, index - lastPosition);
        if (!tmp.empty())
            strs.push_back(tmp);
        lastPosition = index + separate_characterLen;
    }
    string lastString = src.substr(lastPosition);
    if (!lastString.empty())
        strs.push_back(lastString);
    return strs;
}

string replace_all(const string& str, const string& old_value, const string& new_value) {
    string tmp = str;
    string::size_type pos = 0;
    while (true) 
    {
        if ((pos = tmp.find(old_value, pos)) != string::npos) 
        {
            tmp.replace(pos, old_value.length(), new_value);
            pos += new_value.length();
        }
        else 
        {
            break;
        }
    }
    return tmp;
}

inline bool issparater(int ch) { return isspace(ch) || ch == '(' || ch == ')'; }

void tokenizer(string &str, vector<const char*> &token) {
    char tmp[2048];

    for (string::iterator i = str.begin(); i != str.end(); ++i) {
        while (i != str.end() && issparater(*i)) {
            if (*i == '(') {
                token.push_back(st_insert("("));
                goto scan_continue;
            }
            else if (*i == ')') {
                token.push_back(st_insert(")"));
                goto scan_continue;
            }
            ++i;
        }
        if (i == str.end()) break;

        if (*i == '"') {
            int j = 1; ++i; tmp[0] = '"';
            while (i != str.end() && *i != '"') tmp[j++] = *i++;
            if (i == str.end()) throw string("引号没有结束");
            tmp[j++] = '"'; tmp[j] = '\0';
            token.push_back(st_insert(tmp));
        }
        else {
            int j = 0;
            while (i != str.end() && !issparater(*i)) {
                tmp[j + 1] = 0;
                tmp[j++] = *i++;
            }
            token.push_back(st_insert(tmp));
            if (i == str.end()) break;
            --i;    // ( )
        }

    scan_continue: ;
    }
}

vector<string> tokenizer(string &str) {
    str = replace_all(str, ")", " ) ");
    str = replace_all(str, "(", " ( ");
    return split(str, " ");
}

Expression *ParseAsIScheme(string &code) {
    Expression *program = new Expression(st_lookup("")), *current = program;
    //vector<string> token = tokenizer(code);
    vector<const char*> token;
    tokenizer(code, token);
    for (auto i : token) {
        if (i == st_lookup("(")) {
            current->children.push_back(new Expression(st_lookup("("), current));
            current = current->children.back();
        }
        else if (i == st_lookup(")")) {
            current = current->parent;
        }
        else {
            current->children.push_back(new Expression(i, current));
        }
    }
    if (current->parent != nullptr) throw string("括号不匹配！");
    return program;
}

void Init() {
    const char *str[] = {
        "(", ")", "+", "-", "*", "/", "%", "set!",
        "list", "define", "let", "first", "append",
        "if", "begin", "lambda", "rest", nullptr,
    };
    for (int i = 0; str[i] != nullptr; ++i)
        st_insert(str[i]);

    Scope::BuildIn("+", [](vector<RtsPtr>& argument, Scope *scope) -> RtsPtr {
        int ans = 0;
        for (auto i : argument) {
            ans += getValue(i);
        }
        return makeFixnum(ans);
    });
    Scope::BuildIn("-", [](vector<RtsPtr>& argument, Scope *scope) -> RtsPtr {
        int ans = getValue(argument[0]);
        if (argument.size() != 1) {
            for (int i = 1; i < argument.size(); ++i) {
                ans -= getValue(argument[i]);
            }
        }
        else
            ans = -ans;
        return makeFixnum(ans);
    });
    Scope::BuildIn("*", [](vector<RtsPtr>& argument, Scope *scope) -> RtsPtr {
        return makeFixnum(getValue(argument[0]) * getValue(argument[1]));
    });
    Scope::BuildIn("=", [](vector<RtsPtr>& argument, Scope *scope) -> RtsPtr {
        return makeSpec(getValue(argument[0]) == getValue(argument[1]));
    });
    Scope::BuildIn("and", [](vector<RtsPtr>& argument, Scope *scope) -> RtsPtr {
        return makeSpec(getValue(argument[0]) && getValue(argument[1]));
    });
    Scope::BuildIn("or", [](vector<RtsPtr>& argument, Scope *scope) -> RtsPtr {
        return makeSpec(getValue(argument[0]) || getValue(argument[1]));
    });
    Scope::BuildIn("not", [](vector<RtsPtr>& argument, Scope *scope) -> RtsPtr {
        return makeSpec(!getValue(argument[0]));
    });
    Scope::BuildIn("first", [](vector<RtsPtr>& argument, Scope *scope) -> RtsPtr {
        return *getCar(argument[0]);
    });
    Scope::BuildIn("rest", [](vector<RtsPtr>& argument, Scope *scope) -> RtsPtr {
        return *getCdr(argument[0]);
    });
    Scope::BuildIn("append", [](vector<RtsPtr>& argument, Scope *scope) -> RtsPtr {
        RtsPtr p = argument[0];
        while (*getCdr(p)) {
            
        }
        return p;
    });
    Scope::BuildIn("empty?", [](vector<RtsPtr>& argument, Scope *scope) -> RtsPtr {
        return makeSpec(1);
    });
}

void Display(RtsPtr val) {
    if (isTagging(val)) {
        if (isFixnum(val)) cout << getValue(val);
        else if (isString(val)) cout << (const char*)getValue(val);
        else cout << (getValue(val) ? "#t" : "#f");
    }
    else {
        cout << "(";
        Display(*getCar(val));
        cout << " . ";
        Display(*getCdr(val));
        cout << ")";
    }
}

int main() {
    test_vm();
    //test();
    //string str, ans;
    //Init();
    //Scope scope;
    //vector<Expression*> prog;
    //cout << "TinyScheme v0.0000000001\n>> ";
    //while (getline(cin, str)) {
    //    ans += str;
    //    int sum = 0;
    //    for (auto i : ans) {
    //        if (i == '(') sum++;
    //        else if (i == ')') sum--;
    //    }
    //    if (sum != 0) continue;

    //    Expression *program = nullptr;
    //    try {
    //        program = ParseAsIScheme(ans);
    //        Display(program->children[0]->Evaluate(&scope));
    //    }
    //    catch (string &e) {
    //        cout << e;
    //    }
    //    prog.push_back(program);
    //    cout << "\n>> ";
    //    ans.clear();
    //}
    //for (auto i : prog) DeleteExpression(i);
    //Scope::GC();
    return 0;
}