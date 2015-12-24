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

// common property of heap object
// obType_ is the type of object
#define HEAP_OBJECT_HEAD    \
    int8_t obType_;         \
    int8_t resv1_;          \
    int8_t resv2_;          \
    int8_t resv3_

typedef struct {
    HEAP_OBJECT_HEAD;
} CommonType;

typedef struct {
    HEAP_OBJECT_HEAD;
    Pointer car, cdr;
} Pair;

// make pair from alloced memory.
Pointer MakePair(Pointer self, Pointer car, Pointer cdr)
{
    ((Pair *)self)->obType_ = (int8_t)Type::TYPE_PAIR;
    ((Pair *)self)->car = car;
    ((Pair *)self)->cdr = cdr;
    return self;
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

typedef struct
{
    HEAP_OBJECT_HEAD;
    size_t length_;
    char str_[];
} String;

/* make string from exist str and memory. */
Pointer MakeString(Pointer self, const char *from, size_t length)
{
    ((String *)self)->obType_ = (Pointer)Type::TYPE_STRING;
    ((String *)self)->length_ = length;
    strncpy(((String *)self)->str_, from, length);
    return 0;
}

bool IsString(Pointer p)
{
    return (!IsTagging(p) || ((String *)p)->obType_ == (Pointer)Type::TYPE_STRING);
}

const char *GetString(Pointer p)
{
    return ((String *)p)->str_;
}

/* end of runtime */

/* garbage collector */



namespace GC
{
    struct Scheme;

    typedef void*(*Alloc)(size_t);
    typedef void*(*Realloc)(void *, size_t);
    typedef void(*Free)(void *);
    typedef size_t(*SizeOfObject)(void *);
    typedef void(*ProcessReference_)(Scheme*, Pointer*);
    typedef void(*GlobalVariables)(Scheme*, ProcessReference_);
    typedef void(*VariablesUse)(Scheme*, Pointer*, ProcessReference_);

    struct Semispace 
    {
        Pointer _bottom;
        Pointer _top;
        Pointer _end;
    };


    struct Scheme
    {
        Alloc malloc;
        Free free;
        SizeOfObject size_of_object;
        GlobalVariables global_variables;
        VariablesUse variable_use;

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

    /* end of semispace */

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

    void ProcessReference(Scheme *scheme, Pointer *slot) 
    {
        size_t size = scheme->size_of_object((void*)*slot);
        if (size <= 0)
            return;

        Pointer obj = *slot;
        if (obj == NULL) return;

        if (Contains(scheme->_from_space, obj)) 
        {
            if (!IsForwarded(scheme, obj)) 
            {
                Pointer new_obj = Swap(scheme, obj, size);
                ForwardTo(scheme, obj, new_obj);
                *slot = new_obj;
            }
            else 
            {
                *slot = Forwardee(scheme, obj);
            }
        }
    }

    void ProcessObjectReference(Scheme *scheme, Pointer *slot)
    {
        scheme->variable_use(scheme, slot, ProcessReference);
    }

    void GarbageCollect(Scheme *scheme) 
    {
        scheme->forward = (Pointer)scheme->malloc(Ceil(scheme->space_size));
        memset((void*)scheme->forward, 0, Ceil(scheme->space_size));

        // queue
        Pointer scanned = scheme->_to_space->_bottom;

        // copy all glboal variables
        scheme->global_variables(scheme, ProcessReference);

        // breadth-first scanning of object graph
        while (scanned < scheme->_to_space->_top) 
        {
            Pointer parent_obj = scanned;
            ProcessObjectReference(scheme, &parent_obj);
            scanned += scheme->size_of_object((void*)parent_obj);
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
            GarbageCollect(scheme);
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

        GC::Alloc malloc;
        GC::Realloc realloc;
        GC::Free free;
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

struct Scope 
{
    Scope *parent_;
    map<const char*, Pointer> records_;

    Scope(Scope *parent = nullptr) : parent_(parent) {}

    Pointer Lookup(const char *record)
    {
        if (records_.count(record) == 0)
        {
            if (parent_ != nullptr)
                return parent_->Lookup(record);
            else
                return (Pointer)nullptr;
        }
        else
        {
            return records_[record];
        }
    }

    Pointer Insert(const char *name, Pointer addr)
    {
        if (records_.count(name) != 0)
            throw std::runtime_error(string(name) + " redefined!");
        records_[name] = addr;
        return addr;
    }
};

struct Expression 
{
    const char *value;
    Expression *parent;
    vector<Expression*> children;

    Expression(const char *val, Expression *parent = nullptr) : value(val), parent(parent) {}

    Pointer Evaluate(GC::Scheme *scheme, Scope *scope);
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

Pointer SingleVariable(GC::Scheme *scheme, Expression *current, Scope *scope)
{
    long number = 0;
    if (StringToInt(current->value, number))
    {
        return MakeFixnum(number);
    }
    else if (current->value[0] == '"')
    {
        size_t length = strlen(current->value);
        Pointer pointer = GC::Allocate(scheme, sizeof(String) + length);
        return MakeString(pointer, current->value, length);
    }
    else
    {
        Pointer obj = scope->Lookup(current->value);
        if (!obj) throw std::runtime_error(string("没有找到") + current->value);
        return obj;
    }
}

Pointer Expression::Evaluate(GC::Scheme *scheme, Scope *scope) 
{
    Expression *current = this;
    while (true) 
    {
        if (current->children.size() != 0) 
        {
            Expression *first = current->children[0];

            if (first->value == StringTable::Lookup("if")) 
            {
                Pointer boolean = current->children[1]->Evaluate(scheme, scope);
                if (!IsBoolean(boolean))
                    throw std::runtime_error("condition need return boolean");
                current = GetBoolean(boolean)
                    ? current->children[2]
                    : current->children[3];
            }
            else if (first->value == StringTable::Lookup("let")) 
            {
                return scope->Insert(
                    current->children[1]->value, 
                    current->children[2]->Evaluate(
                        scheme, new Scope(scope)));
            }
            else if (first->value == StringTable::Lookup("begin")) 
            {
                Pointer result = 0;
                for (auto i : current->children) 
                {
                    result = i->Evaluate(scheme, scope);
                }
                return result;
            }
            /*else if (first->value == StringTable::Lookup("lambda")) 
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
            }*/
            else if (first->value == StringTable::Lookup("list")) 
            {
                Pair p;
                Pointer cur = (Pointer)&p;
                for (int i = 1; i < current->children.size(); ++i) 
                {
                    *Cdr(cur) = GC::Allocate(scheme, sizeof(Pair));
                    cur = MakePair(*Cdr(cur), current->children[i]->Evaluate(scheme, scope), 0);
                }
                return p.cdr;
            }/*
            else if (Scope::builtinFunctions.count(first->value)) 
            {
                vector<Pointer> arguments;
                for (int i = 1; i < current->children.size(); ++i) 
                {
                    arguments.push_back(current->children[i]->Evaluate(scope));
                }
                return Scope::builtinFunctions[first->value](arguments, scope);
            }
            else 
            {
                Function *function = first->value == StringTable::Lookup("(") 
                    ? (Function*)first->Evaluate(scope) 
                    : (Function*)scope->Find(first->value);
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
            }*/

        }
        else
        {
            return SingleVariable(scheme, current, scope);
        }
    }
}

/* tokenizer */

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

/* end of tokenizer */

/* parser */

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

/* end of parser */

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

size_t SizeOfObject(void *slot)
{
    Pointer self = (Pointer)slot;

    // ever tagging pointer didn't nedd trans.
    if (IsTagging(self))
        return 0;

    switch (((CommonType*)self)->obType_)
    {
    case (int)Type::TYPE_PAIR:
        return sizeof(Pair);
    case (int)Type::TYPE_STRING:
        return sizeof(String) + ((String*)self)->length_;
    default:
        return 0;
        break;
    }
}

void GlobalVariables(GC::Scheme *scheme, GC::ProcessReference_ callback)
{

}

void VariablesUse(
    GC::Scheme *scheme, 
    Pointer *slot, 
    GC::ProcessReference_ callback
    )
{
    if (IsTagging(*slot))
        return;

    switch (((CommonType*)*slot)->obType_)
    {
    case (int)Type::TYPE_PAIR:
        callback(scheme, &((Pair*)*slot)->car);
        callback(scheme, &((Pair*)*slot)->cdr);
        break;
    }
}

int main() 
{
    cout << "TinyScheme v0.0000000001\n>> ";
    InputPort in(cin);

    /* gc */
    GC::Scheme scheme;
    scheme.global_variables = GlobalVariables;
    scheme.variable_use     = VariablesUse;
    scheme.size_of_object   = SizeOfObject;
    GC::InitSchemeAllocate(&scheme, 4 * 1024 * 1024);
    while (true)
    {
        string str;
        if (!in.ReadLine(str))
            break;

        Expression *program = nullptr;
        try {
            program = Parser(str);
        }
        catch (string &e) {
            cout << e;
        }
        cout << "\n>> ";
    }
    GC::DestroySchemeAllocate(&scheme);

    return 0;
}