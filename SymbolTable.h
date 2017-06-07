#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define HASHMAX 200

typedef enum {GLOBAL, ARGV, LOCAL_SCOPE, LIB_FUNCT, PROG_FUNCT} TYPE;

typedef enum scopespace {
    programm_vars = 0,
    function_arguments = 1,
    function_locals = 2
} Scopespace;

typedef struct symbolTable{
    int visible;
    int funct;
    int table;
    char* name;
    TYPE type;
    int scope;
    int line;
    int totallocals;
    int offset;
    int taddress;
    Scopespace scopespace;
    struct symbolTable* argv;
    struct symbolTable* nextScope;
    struct symbolTable* nextInScope;
    struct symbolTable* next;
} symbolTable;

typedef struct functionStack{
    char* name;
    struct functionStack* prev;
}   functionStack;

typedef struct ValuesStack {
    int value;
    int toJump;
    struct ValuesStack* prev;
} ValuesStack;

typedef struct loop_stack {
    ValuesStack* stack;
    struct loop_stack* prev;
} loop_stack;

typedef struct for_pre {
    int toExpr;
    int enter;
} for_pre;

typedef struct funcF {
    int value;
    struct funcF* prev;
} funcF;


void initHashTable();
void insert(int funct, char* name, int scope,int line);
int lookup(char* name, int scope);
void hide(int scope);
void insertArgv(symbolTable* s, int funct, char* name, int scope,int line);
int hashCode(char* name);
void printHash();
symbolTable* findNode(char* name, int scope);

int Cscope = 0;
int error = 0;
symbolTable* functionNode;
int anonymous_FCounter = 0;
int found_error = 0;
int ret = 0;
int is_function = 0;
int c;
int globalscope = 0;
int found_local = 0;
int rightSideValue = 0;
char* funcname_string;
int loopcounter = 0;
int toJumpexpr = -1;
int isFuncBlock = 0;
int isRelatioNal = 0;
int functionLocalsToSym;
int funcJumpToPatch = 0;
int isIndexed = 0;
