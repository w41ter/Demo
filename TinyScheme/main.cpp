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

namespace StringTable
{
    /* string table */
    /* the BKDR hash funcion */
    static unsigned int BKDRHash(const char *str) 
    {
        unsigned int seed = 131; // 31 131 1313 13131 131313 etc..    
        unsigned int hash = 0;

        while (*str) 
        {
            hash = hash * seed + (*str++);
        }

        return (hash & 0x7FFFFFFF);
    }

    const int MAX_BUCKET = 2048;

    static map<unsigned, const char*> *Buckets() 
    {
        static map<unsigned, const char*> buckets[MAX_BUCKET];
        return buckets;
    }

    void Clear() 
    {
        map<unsigned, const char*> *bucket = Buckets();
        for (int i = 0; i < MAX_BUCKET; ++i) 
        {
            for (auto j : bucket[i])
                delete j.second;
            bucket[i].clear();
        }
    }

    void Create() 
    {
        Clear();
    }

    const char *Insert(const char *str) 
    {
        map<unsigned, const char*> *bucket = Buckets();
        unsigned int hash = BKDRHash(str), pos = hash % MAX_BUCKET;
        if (bucket[pos].count(hash) == 0) 
        {
            char *tmp = new char[strlen(str) + 1];
            strcpy(tmp, str);
            bucket[pos][hash] = tmp;
        }
        return bucket[pos][hash];
    }

    const char *Lookup(const char *str) 
    {
        map<unsigned, const char*> *bucket = Buckets();
        unsigned int hash = BKDRHash(str), pos = hash % MAX_BUCKET;
        if (bucket[pos].count(hash) == 0) 
        {
            return nullptr;
        }
        return bucket[pos][hash];
    }

    /* end string table */
}

/* runtime */

// Object Tags
// Primary Pointer Tags
//const unsigned int FixnumTag  = 0;      // 00
//const unsigned int FixnumBits = 30;
//const unsigned int FixnumMask = 3;      // 11
//
//const unsigned int ObjectBits = 29; 
//const unsigned int ObjectMask = 8;      // 111
//const unsigned int PairTag    = 1;      // 001
//const unsigned int ClosureTag = 2;      // 010
//const unsigned int SymbolTag  = 3;      // 011
//const unsigned int VectorTag  = 5;      // 101
//const unsigned int StringTag  = 6;      // 110
//const unsigned int OtherTag   = 7;      // 111
//
//// Immediates Objects
//const unsigned int ImmediatesBits = 24;
//const unsigned int ImmediatesMask = 0xff;   // 1111 1111
//const unsigned int CharTag        = 0x0f;   // 0000 1111
//const unsigned int FalseTag       = 0x2f;   // 0010 1111
//const unsigned int TrueTag        = 0x3f;   // 0011 1111
//const unsigned int NilTag         = 0x4f;   // 0100 1111
//const unsigned int EOFTag         = 0x5f;   // 0101 1111
//const unsigned int VOIDTag        = 0x6f;   // 0110 1111
//const unsigned int UNBOUNDTag     = 0x7f;   // 0111 1111
//
//// Extended Object Tags
//const unsigned int CODETag          = 7;    // 0000 0111
//const unsigned int STACKTag         = 0x17; // 0001 0111
//const unsigned int SymbolTableTag   = 0x27; // 0010 0111
//const unsigned int HashTableTag     = 0x37; // 0011 0111
//const unsigned int ExactBigumTag    = 0x87; // 1000 0111
//const unsigned int ExactTatnumTag   = 0x97; // 1001 0111
//const unsigned int ExactTextnumTag  = 0xa7; // 1010 0111
//const unsigned int INEXACTTag       = 0xb7; // 1100 0111

typedef int32_t Pointer;

enum class Tag {
    TAG_NOT = 0,
    TAG_FIXNUM = 1,
    TAG_SPEC   = 3, // #t #f ()

    TAG_SPEC_MASK = 0xf,

    TAG_CHAR   = 3,
    TAG_FALSE  = 7,
    TAG_TRUE   = 0xf,
    TAG_NIL    = 11,

    TAG_SHIFT  = 2,
    TAG_MASK   = 3,
};

bool IsTagging(Pointer p)
{
    return (p & (Pointer)Tag::TAG_MASK);
}

bool IsFixnum(Pointer p)
{
    return (p & (Pointer)Tag::TAG_MASK) == (Pointer)Tag::TAG_FIXNUM;
}

int GetFixnum(Pointer p)
{
    return (p >> (Pointer)Tag::TAG_SHIFT);
}

Pointer MakeFixnum(int value)
{
    return ((value << (Pointer)Tag::TAG_SHIFT) | (Pointer)Tag::TAG_FIXNUM);
}

bool IsSpecal(Pointer p)
{
    return (p & (Pointer)Tag::TAG_MASK) == (Pointer)Tag::TAG_SPEC;
}

bool IsBoolean(Pointer p)
{
    return (p & (Pointer)Tag::TAG_MASK) == (Pointer)Tag::TAG_SPEC_MASK;
}

bool GetBoolean(Pointer p)
{
    return (p & (Pointer)Tag::TAG_TRUE) >> 3;
}

Pointer SetBoolean(bool s)
{
    return s ? (Pointer)Tag::TAG_TRUE : (Pointer)Tag::TAG_FALSE;
}

bool IsChar(Pointer p)
{
    return (p & (Pointer)Tag::TAG_SPEC_MASK) == (Pointer)Tag::TAG_CHAR;
}

Pointer SetChar(char c)
{
    return ((Pointer)c << (Pointer)Tag::TAG_SPEC_MASK) | (Pointer)Tag::TAG_CHAR;
}

char GetChar(Pointer p)
{
    return (p >> (Pointer)Tag::TAG_SPEC_MASK);
}

bool IsNil(Pointer p)
{
    return (p & (Pointer)Tag::TAG_SPEC_MASK) == (Pointer)Tag::TAG_NIL;
}

Pointer Nil()
{
    return (Pointer)Tag::TAG_NIL;
}

// 8bits
enum class Type {
    TYPE_PAIR = 0,
    TYPE_STRING = 1,
};

// common property of heap object, gcMark_ for garbage collector 
// obType_ is the type of object
#define HEAP_OBJECT_HEAD    \
    int8_t gcMark_;         \
    int8_t obType_;         \
    int8_t resv1_;          \
    int8_t resv2_         

typedef struct {
    HEAP_OBJECT_HEAD;
    Pointer car, cdr;
} Pair;

// make pair from alloced memory.
Pointer MakePair(Pointer self, Pointer car, Pointer cdr)
{
    ((Pair *)self)->gcMark_ = 0;
    ((Pair *)self)->obType_ = (int8_t)Type::TYPE_PAIR;
    ((Pair *)self)->car = car;
    ((Pair *)self)->cdr = cdr;
    return (self & (Pointer)Tag::TAG_NOT);
}

bool IsPair(Pointer p)
{
    return (!IsTagging(p) || ((Pair *)p)->obType_ == (Pointer)Type::TYPE_PAIR);
}

Pointer *Car(Pointer self)
{
    return &((Pair *)self)->car;
}

Pointer *Cdr(Pointer self)
{
    return &((Pair *)self)->cdr;
}

/* end of runtime */

/* garbage collector */

typedef void*(*Alloc)(size_t);
typedef void*(*Realloc)(void *, size_t);
typedef void(*Free)(void *);

namespace GC
{
    struct Scheme;

    struct Semispace 
    {
        Pointer _bottom;
        Pointer _top;
        Pointer _end;
    };

    /* 方便GC */
    size_t Ceil(size_t size)
    {
        int c = size % sizeof(Pointer);
        if (c != 0) c = sizeof(Pointer) - c;
        return size + c;
    }

    void InitSemispace(Scheme *scheme, Semispace *ptr, size_t size)
    {
        size_t space_size = Ceil(size);
        ptr->_bottom = (Pointer)scheme->malloc(space_size);
        ptr->_end = ptr->_bottom + space_size;
        ptr->_top = ptr->_bottom;
    }

    void DestroySemispace(Scheme *scheme, Semispace *ptr)
    {
        scheme->free((void*)ptr->_bottom);
        ptr->_bottom = ptr->_end = ptr->_top = NULL;
    }

    bool Contains(Semispace *ptr, Pointer obj)
    {
        return (ptr->_bottom <= obj && obj < ptr->_end);
    }

    Pointer AllocateMemory(Semispace *space, size_t size)
    {
        size_t space_size = Ceil(size);
        if (space->_top + space_size > space->_end)
            return (Pointer)nullptr;
        Pointer obj = space->_top;
        space->_top += space_size;
        return obj;
    }

    void Reset(Semispace *space)
    {
        space->_top = space->_bottom;
    }

    struct Scheme 
    {
        Alloc malloc;
        Free free;

        struct 
        {
            Semispace *_from_space;
            Semispace *_to_space;
            size_t size;
            size_t space_size;
            intptr_t forward;
        };

        map<const char*, Pointer> global_variable;
    };

    void InitSchemeAllocate(Scheme *scheme, size_t size) 
    {
        scheme->size = size;
        scheme->space_size = Ceil(size) >> 2;
        scheme->_from_space = (Semispace*)scheme->malloc(sizeof(Semispace));
        scheme->_to_space = (Semispace*)scheme->malloc(sizeof(Semispace));
        InitSemispace(scheme, scheme->_from_space, scheme->space_size);
        InitSemispace(scheme, scheme->_to_space, scheme->space_size);
    }

    void DestroySchemeAllocate(Scheme *scheme) 
    {
        DestroySemispace(scheme, scheme->_from_space);
        DestroySemispace(scheme, scheme->_to_space);
        scheme->free((void*)scheme->_from_space);
        scheme->free((void*)scheme->_to_space);
        scheme->_from_space = scheme->_to_space = NULL;
    }

    void SwapSpace(Scheme *scheme) 
    {
        Semispace* temp = scheme->_from_space;
        scheme->_from_space = scheme->_to_space;
        scheme->_to_space = temp;

        // After swapping, the to-space is assumed to be empty.
        // Reset its allocation pointer.
        Reset(scheme->_to_space);
    }

    // offset / 4 is the index of obj's forward.
    bool IsForwarded(Scheme *scheme, Pointer obj) 
    {
        size_t offset = obj - scheme->_from_space->_bottom;
        int *forward = (int*)scheme->forward;
        return (forward[offset >> 2] != NULL);
    }

    // set the obj's forward to new addr.
    void ForwardTo(Scheme *scheme, Pointer obj, Pointer new_addr) 
    {
        size_t offset = obj - scheme->_from_space->_bottom;
        int *forward = (int*)scheme->forward;
        forward[offset >> 2] = new_addr;
    }

    // get the new addr of obj.
    Pointer Forwardee(Scheme *scheme, Pointer obj) 
    {
        size_t offset = obj - scheme->_from_space->_bottom;
        int *forward = (int*)scheme->forward;
        return forward[offset >> 2];
    }

    // copy object to to_space.
    Pointer Swap(Scheme *scheme, Pointer obj, size_t size) 
    {
        Pointer dest = AllocateMemory(scheme->_to_space, size);
        memcpy((void*)dest, (void*)obj, size);
        return dest;
    }

    void ProcessTaggingReference(Scheme *scheme, Pointer *slot)
    {

    }

    void ProcessReference(Scheme *scheme, Pointer *slot) 
    {
        size_t size = SizeOfObject(*slot);
        Pointer obj = *slot;
        if (obj == NULL) return;

        if (Contains(scheme->_from_space, obj)) 
        {
            if (!IsForwarded(scheme, obj)) 
            {
                Pointer new_obj = Swap(scheme, obj, size);
                ForwardTo(scheme, obj, new_obj);
                *slot = new_obj;

                if (!IsTagging(obj)) 
                    ProcessTaggingReference(scheme, slot);
            }
            else 
            {
                *slot = Forwardee(scheme, obj);
            }
        }
    }

    void GarbageCollect(Scheme *scheme, Pointer *address) 
    {
        scheme->forward = (Pointer)scheme->malloc(Ceil(scheme->space_size));
        memset((void*)scheme->forward, 0, Ceil(scheme->space_size));

        // queue
        Pointer scanned = scheme->_to_space->_bottom;

        for (int i = 0; i < 9; ++i) 
        {
            cout << ((int*)scheme->forward)[i] << endl;
            ProcessReference(scheme, &address[i]);
        }

        // breadth-first scanning of object graph
        while (scanned < scheme->_to_space->_top) 
        {
            Pointer parent_obj = scanned;
            ProcessReference(scheme, &parent_obj);
            scanned += SizeOfObject(parent_obj);
        }

        // Now all live objects will have been evacuated into the to-space,
        // and we don't need the data in the from-space anymore.
        SwapSpace(scheme);

        scheme->free((void*)scheme->forward);
        scheme->forward = NULL;
    }

    Pointer Allocate(Scheme *scheme, size_t size) 
    {
        Pointer address = AllocateMemory(scheme->_from_space, size);
        if (address == NULL) 
        {
            //GarbageCollect(scheme);
            address = AllocateMemory(scheme->_from_space, size);
            if (address == NULL) 
            {
                // error
            }
            else 
            {
                return address;
            }
        }
        else 
        {
            return address;
        }
    }
}
/* end of garbage collect */

/* begin visual machine */

namespace VM
{
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
        Pointer imuniate;
    };

    struct CallStack {
        Pointer pc;
        Pointer *stacks;
        size_t top;
        size_t length;
        CallStack *parent;
    };

    struct VMstate {
        Instructions instructions[MAX_LENGTH];
        map<const char*, Pointer> global_variable;

        CallStack *global_stacks;
        CallStack *cur_stacks;

        Alloc malloc;
        Realloc realloc;
        Free free;
    };

    void InitVMstate(VMstate *vm) {
        vm->global_stacks = (CallStack*)vm->malloc(sizeof(CallStack));
        vm->cur_stacks = vm->global_stacks;
        vm->cur_stacks->stacks = (Pointer*)vm->malloc(sizeof(Pointer) * 1024);
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

    Pointer StackTop(VMstate *vm, size_t pos = 0) {
        return vm->cur_stacks->stacks[vm->cur_stacks->top - pos];
    }

    Pointer StackPop(VMstate *vm, size_t size = 1) {
        Pointer res = NULL;
        while (size--) {
            res = vm->cur_stacks->stacks[vm->cur_stacks->top--];
        }
        return res;
    }

    void StackPush(VMstate *vm, Pointer value) {
        if (vm->cur_stacks->length == vm->cur_stacks->top) {
            vm->cur_stacks->stacks = (Pointer*)vm->realloc(
                vm->cur_stacks->stacks,
                sizeof(Pointer) * vm->cur_stacks->length * 2
                );
        }
        ++vm->cur_stacks->top;
        vm->cur_stacks->stacks[vm->cur_stacks->top] = value;
    }

    void StackLoad(VMstate *vm, const char *name) {
        StackPush(vm, vm->global_variable[name]);
    }

    Pointer StackStore(VMstate *vm, const char *name) {
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
        func->stacks = (Pointer*)vm->malloc(sizeof(Pointer) * 1024);
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
                    Pointer op1 = StackPop(vm), op2 = StackPop(vm);
                    if (op1 > op2) {
                        vm->cur_stacks->pc += instr.imuniate;
                        goto Begin;
                    }
                    break;
                }
                OPCODE(JL) {
                    Pointer op1 = StackPop(vm), op2 = StackPop(vm);
                    if (op1 < op2) {
                        vm->cur_stacks->pc += instr.imuniate;
                        goto Begin;
                    }
                    break;
                }
                OPCODE(MUL) {
                    Pointer op1 = StackPop(vm), op2 = StackPop(vm);
                    StackPush(vm, op1 * op2);
                    break;
                }
                OPCODE(ADD) {
                    Pointer op1 = StackPop(vm), op2 = StackPop(vm);
                    StackPush(vm, op1 + op2);
                    break;
                }
                OPCODE(SUB) {
                    Pointer op1 = StackPop(vm), op2 = StackPop(vm);
                    StackPush(vm, op1 - op2);
                    break;
                }
                OPCODE(DIV) {
                    Pointer op1 = StackPop(vm), op2 = StackPop(vm);
                    StackPush(vm, op1 / op2);
                    break;
                }
                OPCODE(MOD) {
                    Pointer op1 = StackPop(vm), op2 = StackPop(vm);
                    StackPush(vm, op1 % op2);
                    break;
                }
                OPCODE(SHOW) {
                    cout << StackPop(vm);
                    break;
                }
                OPCODE(INSERT) {
                    Pointer ptr;
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

}
/* end visual machine */

int test_gc() {
    Scheme scheme;
    scheme.malloc = malloc;
    scheme.free = free;
    InitSchemeAllocate(&scheme, sizeof(Pointer) * 1024);

    const char * buff[] = {
        "1", "2", "3", "4", "5", "6",
        "7", "8", "9", "10"
    };
    Pointer address[10];
    for (int i = 0; i < 10; ++i) {
        address[i] = Allocate(&scheme, sizeof(Pointer));
    }

    for (int i = 0; i < 10; ++i) {
        Pointer ptr = address[i];
        *((int*)ptr) = i;
    }

    for (int i = 0; i < 10; ++i) {
        Pointer ptr = address[i];
        cout << buff[i] << " address is " << ptr << " , var is " << *((int*)ptr) << endl;
    }
        
    cout << "\n\nBegin GC" << endl;

    GarbageCollect(&scheme, &address[1]);
    for (int i = 0; i < 10; ++i) {
        Pointer ptr = address[i];
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
    state.instructions[1] = { OP_STORE, (Pointer)"vara" };
    state.instructions[2] = { OP_INSERT, NULL };
    state.instructions[3] = { OP_STORE, (Pointer)"varb" };
    state.instructions[4] = { OP_LOAD, (Pointer)"vara" };
    state.instructions[5] = { OP_LOAD, (Pointer)"varb" };
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

using BuildInFunction = function<Pointer(vector<Pointer>&, Scope*)>;

struct Scope
{
    Scope *parent;
    map<string, Pointer> variableTable;

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

    Pointer Find(const string &name)
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

    Pointer Define(const string &name, Pointer value)
    {
        variableTable.insert(pair<string, Pointer>(name, value));
        return value;
    }

    Scope * SpawnScopeWith(vector<string> &names, vector<Pointer> &values) {
        if (names.size() < values.size())
            throw ("Too many arguments.");

        Scope *scope = new Scope(this);
        for (int i = 0; i < values.size(); i++) {
            scope->variableTable.insert(pair<string, Pointer>(names[i], values[i]));
        }
        return scope;
    }

    Pointer FindInTop(string &name) {
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

    Pointer Evaluate(Scope *scope);

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

    Pointer Evaluate()
    {
        int filledParameters = ComputeFilledParametersLength();
        if (filledParameters < parameters.size())
            return (Pointer)this;
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

    Function *Updata(vector<Pointer> arguments) {
        vector<Pointer> ans;
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

Pointer Expression::Evaluate(Scope *scope) 
{
    Expression *current = this;
    while (true) 
    {
        if (current->children.size() == 0) 
        {
            long number = 0;
            if (StringToInt(current->value, number)) 
            {
                return makeFixnum(number);
            }
            else if (current->value[0] == '"') 
            {
                return makeString((intptr_t)current->value);
            }
            else 
            {
                Pointer obj = scope->Find(current->value);
                if (!obj) throw string("没有找到") + current->value;
                return obj;
            }
        }
        else 
        {
            Expression *first = current->children[0];

            if (first->value == StringTable::Lookup("if")) 
            {
                bool condition = toBoolean(current->children[1]->Evaluate(scope));
                current = condition ? current->children[2] : current->children[3];
            }
            else if (first->value == StringTable::Lookup("let")) 
            {
                return scope->Define(current->children[1]->value, current->children[2]->Evaluate(new Scope(scope)));
            }
            else if (first->value == StringTable::Lookup("begin")) 
            {
                Pointer result = 0;
                for (auto i : current->children) 
                {
                    result = i->Evaluate(scope);
                }
                return result;
            }
            else if (first->value == StringTable::Lookup("lambda")) 
            {
                Expression *body = current->children[2];
                vector<string> parameters;
                for (auto i : current->children[1]->children) 
                {
                    parameters.push_back(i->value);
                }

                Scope *newScope = new Scope(scope);
                Scope::gc.push_back(new Function(body, parameters, newScope));
                return (Pointer)Scope::gc.back();
            }
            else if (first->value == StringTable::Lookup("list")) 
            {
                Pointer cur;
                Pair p;
                cur = (Pointer)&p;
                for (int i = 1; i < current->children.size(); ++i) 
                {
                    *getCdr(cur) = (Pointer) new Pair;
                    cur = *getCdr(cur);
                    makePair(cur, current->children[i]->Evaluate(scope), 0);
                    Scope::gc.push_back((void*)cur);
                }
                return cur;
            }
            else if (Scope::builtinFunctions.count(first->value)) 
            {
                vector<Pointer> arguments;
                for (int i = 1; i < current->children.size(); ++i) 
                {
                    arguments.push_back(current->children[i]->Evaluate(scope));
                }
                return Scope::builtinFunctions[first->value](arguments, scope);
            }
            else {
                Function *function = first->value == StringTable::Lookup("(") ? (Function*)first->Evaluate(scope) : (Function*)scope->Find(first->value);
                vector<Pointer> arguments;
                for (int i = 1; i < current->children.size(); ++i) 
                {
                    arguments.push_back(current->children[i]->Evaluate(scope));
                }
                Function *newFunction = function->Updata(arguments);
                if (newFunction->IsPartial()) 
                {
                    return newFunction->Evaluate();
                }
                else 
                {
                    current = newFunction->body;
                    scope = newFunction->scope;
                }
            }
        }
    }
}

void DeleteExpression(Expression *exp) 
{
    if (exp == nullptr) return;
    for (auto i = exp->children.begin(); i != exp->children.end(); ++i)
        DeleteExpression(*i);
    delete exp;
}

//vector<string> split(const string& src, string separate_character) {
//    vector<string> strs;
//    int separate_characterLen = separate_character.size();
//    int lastPosition = 0, index = -1;
//    while (string::npos != (index = src.find(separate_character, lastPosition)))
//    {
//        string tmp = src.substr(lastPosition, index - lastPosition);
//        if (!tmp.empty())
//            strs.push_back(tmp);
//        lastPosition = index + separate_characterLen;
//    }
//    string lastString = src.substr(lastPosition);
//    if (!lastString.empty())
//        strs.push_back(lastString);
//    return strs;
//}
//
//string replace_all(const string& str, const string& old_value, const string& new_value) {
//    string tmp = str;
//    string::size_type pos = 0;
//    while (true) 
//    {
//        if ((pos = tmp.find(old_value, pos)) != string::npos) 
//        {
//            tmp.replace(pos, old_value.length(), new_value);
//            pos += new_value.length();
//        }
//        else 
//        {
//            break;
//        }
//    }
//    return tmp;
//}

inline bool issparater(int ch) { return isspace(ch) || ch == '(' || ch == ')'; }

void Tokenizer(string &str, vector<const char*> &token) 
{
    char tmp[2048];

    for (string::iterator i = str.begin(); i != str.end(); ++i) 
    {
        while (i != str.end() && issparater(*i))
        {
            if (*i == '(') 
            {
                token.push_back(StringTable::Insert("("));
                goto scan_continue;
            }
            else if (*i == ')') 
            {
                token.push_back(StringTable::Insert(")"));
                goto scan_continue;
            }
            ++i;
        }
        if (i == str.end()) 
            break;

        if (*i == '"') 
        {
            int j = 1; ++i; tmp[0] = '"';
            while (i != str.end() && *i != '"') 
                tmp[j++] = *i++;
            if (i == str.end()) 
                throw std::runtime_error("unexcption end of find");
            tmp[j++] = '"'; tmp[j] = '\0';
            token.push_back(StringTable::Insert(tmp));
        }
        else 
        {
            int j = 0;
            while (i != str.end() && !issparater(*i)) 
            {
                tmp[j + 1] = 0;
                tmp[j++] = *i++;
            }
            token.push_back(StringTable::Insert(tmp));
            if (i == str.end()) 
                break;
            --i;    // ( )
        }

    scan_continue: ;
    }
}
//
//vector<string> Tokenizer(string &str) {
//    str = replace_all(str, ")", " ) ");
//    str = replace_all(str, "(", " ( ");
//    return split(str, " ");
//}

Expression *Parser(string &code) 
{
    Expression *program = new Expression(StringTable::Lookup("")), *current = program;

    vector<const char*> token;
    Tokenizer(code, token);
    for (auto i : token) 
    {
        if (i == StringTable::Lookup("("))
        {
            current->children.push_back(new Expression(StringTable::Lookup("("), current));
            current = current->children.back();
        }
        else if (i == StringTable::Lookup(")"))
        {
            if (current->parent == nullptr)
                throw std::runtime_error("unexception )");
            current = current->parent;
        }
        else 
        {
            current->children.push_back(new Expression(i, current));
        }
    }
    if (current->parent != nullptr) 
        throw std::runtime_error("exception )");
    return program;
}

void Init() {
    const char *str[] = {
        "(", ")", "+", "-", "*", "/", "%", "set!",
        "list", "define", "let", "first", "append",
        "if", "begin", "lambda", "rest", nullptr,
    };
    for (int i = 0; str[i] != nullptr; ++i)
        StringTable::Insert(str[i]);

    Scope::BuildIn("+", [](vector<Pointer>& argument, Scope *scope) -> Pointer {
        int ans = 0;
        for (auto i : argument) {
            ans += getValue(i);
        }
        return makeFixnum(ans);
    });
    Scope::BuildIn("-", [](vector<Pointer>& argument, Scope *scope) -> Pointer {
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
    Scope::BuildIn("*", [](vector<Pointer>& argument, Scope *scope) -> Pointer {
        return makeFixnum(getValue(argument[0]) * getValue(argument[1]));
    });
    Scope::BuildIn("=", [](vector<Pointer>& argument, Scope *scope) -> Pointer {
        return makeSpec(getValue(argument[0]) == getValue(argument[1]));
    });
    Scope::BuildIn("and", [](vector<Pointer>& argument, Scope *scope) -> Pointer {
        return makeSpec(getValue(argument[0]) && getValue(argument[1]));
    });
    Scope::BuildIn("or", [](vector<Pointer>& argument, Scope *scope) -> Pointer {
        return makeSpec(getValue(argument[0]) || getValue(argument[1]));
    });
    Scope::BuildIn("not", [](vector<Pointer>& argument, Scope *scope) -> Pointer {
        return makeSpec(!getValue(argument[0]));
    });
    Scope::BuildIn("first", [](vector<Pointer>& argument, Scope *scope) -> Pointer {
        return *getCar(argument[0]);
    });
    Scope::BuildIn("rest", [](vector<Pointer>& argument, Scope *scope) -> Pointer {
        return *getCdr(argument[0]);
    });
    Scope::BuildIn("append", [](vector<Pointer>& argument, Scope *scope) -> Pointer {
        Pointer p = argument[0];
        while (*getCdr(p)) {
            
        }
        return p;
    });
    Scope::BuildIn("empty?", [](vector<Pointer>& argument, Scope *scope) -> Pointer {
        return makeSpec(1);
    });
}

void Display(Pointer val) {
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

/*
    input port
*/
class InputPort
{
public:
    InputPort(istream &input) : input_(input) {}

    bool ReadLine(string &result)
    {
        result.erase();
        string tmp;
        while (getline(input_, tmp))
        {
            result += tmp;
            int sum = 0;
            for (auto i : result)
            {
                if (i == '(')
                    ++sum;
                else if (i == ')')
                    --sum;
            }
            if (sum == 0)
                return true;
        }
        return false;
    }
protected:
    istream &input_;
};

int main() 
{
    Init();
    Scope scope;
    vector<Expression*> prog;
    cout << "TinyScheme v0.0000000001\n>> ";
    InputPort in(cin);
    string str;
    while (in.ReadLine(str))
    {
        Expression *program = nullptr;
        try {
            program = Parser(str);
            Display(program->children[0]->Evaluate(&scope));
        }
        catch (string &e) {
            cout << e;
        }
        prog.push_back(program);
        cout << "\n>> ";
    }
    for (auto i : prog) DeleteExpression(i);
    Scope::GC();
    return 0;
}