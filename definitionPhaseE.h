#define AVM_STACKENV_SIZE 4
#define AVM_MAX_INSTRUCTIONS (unsigned) jump_v
#define AVM_TABLE_HASHSIZE 211
#define AVM_STACKSIZE 4096
#define N 4096
#define AVM_WIPEOUT(m)  memset(&(m) , 0  , sizeof(m))
#define AVM_ENDING_PC  codeSize
#define AVM_NUMACTUALS_OFFSET +4
#define AVM_SAVEDPC_OFFSET    +3
#define AVM_SAVEDTOP_OFFSET   +2
#define AVM_SAVEDTOPSP_OFFSET +1
#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic
int mycounter = 0;
#define CP(x) printf("Checkpoint %s\n" , #x);
#define PI(a,x) printf("Variable: %d\n" , x);

char* typeStrings[]={
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"
};

typedef enum avm_memcell_type {
    number_m,
    string_m,
    bool_m,
    table_m,
    userfunc_m,
    libfunc_m,
    nil_m,
    undef_m
} avm_memcell_t;

typedef struct avm_table_t avm_table;
typedef struct avm_table_bucket avm_table_bucket;

typedef struct avm_memcell_struct {
    avm_memcell_t type;
    union {
        double numVal;
        char*  strVal;
        unsigned char boolVal;
        avm_table*    tableVal;
        unsigned funcVal;
        char* libfuncVal;
    } data;
} avm_memcell;

struct avm_table_bucket{
    avm_memcell key;
    avm_memcell value;
    struct avm_table_bucket* next;
};

struct avm_table_t {
    unsigned        refCounter;
    avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];

    avm_table_bucket* libIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* boolIndexed[2];
    avm_table_bucket* userfIndexed[AVM_TABLE_HASHSIZE];
    unsigned total;
};

avm_memcell stack[AVM_STACKSIZE];

avm_memcell ax , bx , cx;
avm_memcell retval; 
unsigned top = 100, topsp = 100;

unsigned char executionFinished = 0;
unsigned      pc = 0 , oldPC = 0;
unsigned      currLine = 0;
unsigned      codeSize = 0;
Instruction*  code = (Instruction*) 0;

unsigned totalActuals = 0;

void    execute_assign         (Instruction *i);
void    execute_add            (Instruction *i);
void    execute_sub            (Instruction *i);
void    execute_mul            (Instruction *i);
void    execute_div            (Instruction *i);
void    execute_mod            (Instruction *i);
void    execute_uminus         (Instruction *i);
void    execute_and            (Instruction *i);
void    execute_or             (Instruction *i);
void    execute_not            (Instruction *i);
void    execute_jeq            (Instruction *i);
void    execute_jne            (Instruction *i);
void    execute_jle            (Instruction *i);
void    execute_jge            (Instruction *i);
void    execute_jlt            (Instruction *i);
void    execute_jgt            (Instruction *i);
void    execute_call           (Instruction *i);
void    execute_pusharg        (Instruction *i);
void    execute_funcenter      (Instruction *i);
void    execute_funcexit       (Instruction *i);
void    execute_newtable       (Instruction *i);
void    execute_tablegetelem   (Instruction *i);
void    execute_tablesetelem   (Instruction *i);
void    execute_nop            (Instruction *i);
void    execute_jump           (Instruction *i);

typedef void (*execute_func_t)(Instruction*);
execute_func_t executeFuncs[] = {
    execute_assign,   
    execute_add,   
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_uminus,
    execute_and,  
    execute_or,
    execute_not,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_call,
    execute_pusharg,
    execute_funcenter,
    execute_funcexit,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_nop,
    execute_jump
};
void execute_cycle(void);

char * number_tostring      (avm_memcell*);   
char * string_tostring      (avm_memcell*);    
char * bool_tostring        (avm_memcell*);
char * table_tostring       (avm_memcell*);    
char * userfunc_tostring    (avm_memcell*);    
char * libfunc_tostring     (avm_memcell*);
char * nil_tostring         (avm_memcell*);
char * undef_tostring       (avm_memcell*);

typedef char* (*tostring_func_t)(avm_memcell*);
tostring_func_t tostringFuncs[] = {
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring
};
char* avm_tostring(avm_memcell*);

unsigned char number_tobool(avm_memcell*);
unsigned char string_tobool(avm_memcell*);
unsigned char bool_tobool(avm_memcell*);
unsigned char table_tobool(avm_memcell*);
unsigned char userfunc_tobool(avm_memcell*);
unsigned char libfunc_tobool(avm_memcell*);
unsigned char nil_tobool(avm_memcell*);
unsigned char undef_tobool(avm_memcell*);

typedef unsigned char (*tobool_func_t)(avm_memcell*);
tobool_func_t toboolFuncs[]={
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool
};
unsigned char avm_tobool(avm_memcell*);

void memclear_string(avm_memcell*);
void memclear_table(avm_memcell*);

typedef void (*memclear_func_t)(avm_memcell*);
memclear_func_t memclearFuncs[] = {
    0,
    memclear_string,
    0,
    memclear_table,
    0,
    0,
    0,
    0
};
void avm_memcellclear(avm_memcell*);

void libfunc_print(void);
void libfunc_typeof(void);
void libfunc_totalarguments(void);
void libfunc_input();
typedef void (*library_func_t)(void);
library_func_t libraryFuncs[] = {
    libfunc_print,
    libfunc_typeof,
    libfunc_totalarguments,
    libfunc_input
};

//void avm_registerlibfunc(char*,library_func_t);
library_func_t avm_getlibraryfunc(char*);

double consts_getnumber(unsigned index);
char*  consts_getstring(unsigned index);
char*  libfunc_getused(unsigned index);
static void avm_initstack();
avm_memcell* avm_translate_operand(vmarg*, avm_memcell*);
int avm_error(char*);
void avm_initialize();
void avm_warning(char* format, ...);
void avm_assign(avm_memcell*, avm_memcell*);
void avm_tablebucketsinit(avm_table_bucket**);
avm_table* avm_tablenew();
void avm_tabledestroy(avm_table*);
void avm_tableincrefcounter(avm_table*);
void avm_tabledecrefcounter(avm_table*);
void avm_tablebucketsdestroy(avm_table_bucket**);
avm_memcell* avm_tablegetelem(avm_table*, avm_memcell*);
void avm_tablesetelem(avm_table*, avm_memcell*, avm_memcell*);

double add_impl(double, double);
double sub_impl(double, double);
double mul_impl(double, double);
double div_impl(double, double);
double mod_impl(double, double);

void avm_dec_top();
void avm_push_envvalue();
void avm_callsaveenviroment();
userfunc* avm_getfuncinfo(unsigned address);
unsigned avm_get_envvalue(unsigned i);
void avm_calllibfunc(char* id);
unsigned avm_totalactuals(void);
avm_memcell* avm_getactual(unsigned);

int mull(int, int);
int hashCodeString(char*);
int hashCodeNumber(int);

void FunctorCall(avm_table* t); //------------