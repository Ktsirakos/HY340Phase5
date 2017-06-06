#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "colors.h"

typedef struct userfunc_t {
    unsigned address;
    unsigned localSize;
    char*    id;
} userfunc;


typedef enum vmarg {
    label_a,
    global_a,
    formal_a,
    local_a,
    number_a,
    string_a,
    bool_a,
    nil_a,
    userfunc_a,
    libfunc_a,
    retval_a
} vmarg_t;

typedef struct vmarg_t { 
    vmarg_t type;  unsigned val; 
} vmarg;

typedef  enum vmopcode_t {
    assign_v,               add_v,          sub_v,
    mul_v,                  div_v,          mod_v,
    uminus_v,               and_v,          or_v,
    not_v,                  jeq_v,          jne_v,
    jle_v,                  jge_v,          jlt_v,
    jgt_v,                  call_v,         pusharg_v,
    funcenter_v,            funcexit_v,     newtable_v,
    tablegetelem_v,         tablesetelem_v, nop_v , jump_v,
    ret_v , grv_v
} vmopcode;

typedef struct instruction {
    vmopcode opcode;
    vmarg*    result;
    vmarg*    arg1;
    vmarg*   arg2;
    unsigned label;
    unsigned srcLine;

} Instruction;

#define EXPAND_SIZE 1024
#define CURR_INST_SIZE  (totalInst*sizeof(Instruction))
#define NEW_INST_SIZE   (EXPAND_SIZE*sizeof(Instruction) + CURR_INST_SIZE)


unsigned int totalInst = 0;
unsigned int currInst  = 0;


char** strings = NULL;
int totalStrings = 0;

double* numbers = NULL;
int totalNums = 0;


char** Libfuncs = NULL;
int totalLibFuncs;

userfunc* userFuncs = NULL;
int totalUserFuncs;


int doneWithArrays = 0;


#include "phaseE.h"

/*============================*/

void initializeStrings(int counter){
    int i;
    strings = (char**)malloc(counter*sizeof(char*));
    for(i = 0; i < counter; i++){
        strings[i] = NULL;
    }
}

void initializeNumbers(int counter){
    int i;
    numbers = (double*)malloc(counter*sizeof(double));
}

void initializeUserFuncs(int counter){
    userFuncs = (userfunc*)malloc(counter*sizeof(userfunc));
}

void initializeLibFuncs(int counter){
    int i;
    Libfuncs = (char**)malloc(counter*sizeof(char*));
    for(i = 0; i < counter; i++){
        Libfuncs[i] = NULL;
    }
}


void addToNumbers(double num , int index){
    numbers[index] = num;
}
void addToString(char *s , int index){
    strings[index] = strdup(s);
}

void addToUserfunc(int address , int localsize , char* name , int index){
    userFuncs[index].address    = address;
    userFuncs[index].localSize  = localsize;
    userFuncs[index].id         = strdup(name);
    
}

void addToLibFuncs(char* data , int index){
    Libfuncs[index] = strdup(data);
}


char* removeQuotes(char* s){
    int len = strlen(s);
    int i,j=1;
    for(i = 0; i < len - 1; i++){
        if(s[i+1] == '\\'){
            switch(s[i+2]){
                case 'n': s[i] = '\n';    break;
                case 't': s[i] = '\t';    break;
                case 'b': s[i] = '\b';    break;
                case 'a': s[i] = '\a';    break;
                case 'f': s[i] = '\f';    break;
                case 'r': s[i] = '\r';    break;
                case 'v': s[i] = '\v';    break;
                case '\\': s[i] = '\\';    break;
                case '\'': s[i] = '\'';    break;
                case '\"': s[i] = '\"';    break;
                case '?': s[i] = '?';    break;
                default:    s[i] = '\\';    j--; break;
            }
            j++;
        }else{
            s[i] = s[i+j];
        }
    }
    s[len - 2 - j] = '\0';
    return s;
}


void expand_Instruction(void){
    assert(totalInst == currInst);
    Instruction* i = (Instruction*) malloc(NEW_INST_SIZE);

    if(code){
        memcpy(i ,  code , CURR_INST_SIZE);
        free(code);
    }

    code = i;
    totalInst += EXPAND_SIZE;
}


void emit_instruction(Instruction* i){
    if(currInst == totalInst) expand_Instruction();

    Instruction* q = code + currInst++;
    q->opcode = i->opcode;
    q->result = i->result;
    q->arg1 = i->arg1;
    q->arg2 = i->arg2;
    q->srcLine = i->srcLine;
    q->label = i->label - 1;
}

void printArrays(){

    int i;
    printf("Strings....\n");
    for(i = 0; i < totalStrings; i++){
        printf("\t%d: %s\n" , i , strings[i]);
    }

    printf("Numbers...\n");
    for(i = 0; i < totalNums; i++){
        printf("\t%d: %f\n" , i , numbers[i]);
    }

    printf("LibFuncs...\n");
    for(i = 0; i < totalLibFuncs; i++){
        printf("\t%d: %s\n" , i , Libfuncs[i]);
    }

    printf("UserFuncs...\n");
    for(i = 0; i < totalUserFuncs; i++){
        printf("\t%d: %s\n" , i , userFuncs[i].id);
    }

}


int main(){

    avm_initialize();
    
    FILE *fp;

    fp = fopen("binary.abc" , "r");

    char line[256];
    char data[256];
    int globals;
    if(fp == NULL) {
        printf("Cant open file!\n");
        return 0;
    }

    int linecounter = 0;
    while (fgets(line, sizeof(line), fp)) {

        int counter ,i;
        char data[50];

        if(sscanf(line , "%d %s\n" , &counter , data) != 2){
            printf("Error While Parsing File!\n");
        }else{

            if(!doneWithArrays){
                if(strcmp(data , "Strings") == 0){
                    initializeStrings(counter);
                    totalStrings = counter;
                    int index;
                    for(i = 0; i < counter; i++){
                        if(fgets(line, sizeof(line) , fp)){
                            index = i;
                            int j;
                            for(j=0; line[j]!=' '; j++);
                            strcpy(data,removeQuotes(&line[j+1]));
                            addToString(data , index);
                        }
                    }
                }else if(strcmp(data , "Nums") == 0){
                    initializeNumbers(counter);
                    totalNums = counter;
                    int index;
                    float value;
                    for(i = 0; i < counter; i++){
                        if(fgets(line, sizeof(line) , fp)){
                            sscanf(line , "%d %f\n" , &index , &value);
                            addToNumbers(value , index);
                        }
                    }
                }else if(strcmp(data , "Libfuncs") == 0){
                    initializeLibFuncs(counter);
                    totalLibFuncs = counter;
                    int index;
                    for(i = 0; i < counter; i++){
                        if(fgets(line, sizeof(line) , fp)){
                            sscanf(line , "%d %s\n" , &index , data);
                            addToLibFuncs(data , index);
                        }
                    }
                }else if(strcmp(data , "Userfuncs") == 0){
                    initializeUserFuncs(counter);
                    totalUserFuncs = counter;
                    int index;
                    int taddress;
                    int locals;
                    for(i = 0; i < counter; i++){
                        if(fgets(line, sizeof(line) , fp)){
                            sscanf(line , "%d %d %d %s\n" , &index , &taddress , &locals ,data);
                            addToUserfunc(taddress , locals , data , index);
                        }
                    }
                }else if(strcmp(data , "code") == 0){
                    sscanf(line , "%d %s" , &codeSize , data);
                }else if(strcmp(data , "End") == 0){
                    doneWithArrays = 1;
                    continue;
                }else if(strcmp(data , "Globals") == 0){
                    sscanf(line , "%d %s\n" , &globals , data);
                }
            }else{
            int opcode , label;
        vmarg result , arg1 , arg2;    
        int type1,type2,type3;

        sscanf(line , "%d %d.%d %d.%d %d.%d %d\n" 
                        , &opcode 
                        , &type1
                        , &(result.val )
                        , &type2
                        , &(arg1.val )
                        , &type3
                        , &(arg2.val )
                        , &label);
        result.type = type1;
        arg1.type = type2;
        arg2.type = type3;

        Instruction* instr = malloc(sizeof(Instruction));
        instr->result = malloc(sizeof(vmarg));
        instr->arg1 = malloc(sizeof(vmarg));
        instr->arg2 = malloc(sizeof(vmarg));
        
        instr->opcode       = opcode;
        instr->result->type = result.type;
        instr->result->val  = result.val;
        instr->arg1->type =   arg1.type;
        instr->arg1->val  =   arg1.val;
        instr->arg2->type =   arg2.type;
        instr->arg2->val  =   arg2.val;
        instr->label      =   label;
        emit_instruction(instr);
        /*
        
        printf("%d %d.%d %d.%d %d.%d %d\n" 
                        , opcode 
                        , result.type
                        , result.val 
                        , arg1.type 
                        , arg1.val 
                        , arg2.type 
                        , arg2.val 
                        , label);
         */

            }

        }
    }

    printf("----------------ARRAYS----------------------\n");
    printArrays();
    printf("-------------PROGRAMM EXECUTING-------------\n");
    

    fclose(fp);


    top = AVM_STACKSIZE - 1 - globals;
    topsp = top;

    while(executionFinished != 1){
        execute_cycle();
    }
    return 0;

}