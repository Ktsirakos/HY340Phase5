#include "definitionPhaseE.h"

char* number_tostring    (avm_memcell* a){
    char num[100];
    sprintf(num, "%f", a->data.numVal);
    return strdup(num);
}
char* string_tostring    (avm_memcell* a){
    char* toRet;
    toRet = strdup(a->data.strVal);
    return toRet;
}
char* bool_tostring      (avm_memcell* a){
    if(a->data.boolVal != 0){
        return "true";
    }else{
        return "false";
    }
}
char* table_tostring     (avm_memcell* a){
    avm_table_bucket** table = a->data.tableVal->numIndexed;
    char* s = (char*)malloc(10000*sizeof(char));
    char* toRet = (char*)malloc(10000*sizeof(char));
    strcpy(toRet,"Table\n");
    for(int i=0; i<AVM_TABLE_HASHSIZE; i++){
        avm_table_bucket* temp = table[i];
        while(temp != NULL){
            sprintf(s,"\t%s:%s\n",avm_tostring(&(temp->key)), avm_tostring(&(temp->value)));
            strcat(toRet,s);
            temp = temp->next;
        }
    }
    table = a->data.tableVal->strIndexed;
    for(int i=0; i<AVM_TABLE_HASHSIZE; i++){
        avm_table_bucket* temp = table[i];
        while(temp != NULL){
            sprintf(s,"\t%s:%s\n",avm_tostring(&(temp->key)), avm_tostring(&(temp->value)));
            strcat(toRet,s);
            temp = temp->next;
        }
    }
    return toRet;
}
char* userfunc_tostring  (avm_memcell* a){
    char* s;
    s = strdup(userFuncs[a->data.funcVal].id);
    return s;
}
char* libfunc_tostring   (avm_memcell* a){
    char* s;
    s = strdup(a->data.libfuncVal);
    return s;
}
char* nil_tostring       (avm_memcell* a){
    return "(null)";
}
char* undef_tostring     (avm_memcell* a){
    return "(undefined)";
}

char* avm_tostring(avm_memcell* m){
    assert(m->type >= 0 && m->type <= undef_m);
    return (*tostringFuncs[m->type])(m);
}

void memclear_string(avm_memcell* a){
    assert(a->data.strVal); 
    free(a->data.strVal);
}

void memclear_table(avm_memcell *a){
    assert(a->data.tableVal);
    avm_tabledecrefcounter(a->data.tableVal);
}

void avm_memcellclear(avm_memcell* m){
    if(m == NULL)   return;
    if(m->type != undef_m){
        memclear_func_t f = memclearFuncs[m->type];
        if(f){
            (*f)(m);
            m->type = undef_m;
        }
    }
}

double consts_getnumber(unsigned index){
    if(index > totalNums){
        printf("Segmentetion fault .|.");
        executionFinished = 1;
        return 0;
    }else{
        return numbers[index];
    }
}
char*  consts_getstring(unsigned index){
    if(index > totalStrings){
        printf("Segmentetion fault .|.");
        executionFinished = 1;
        return 0;
    }else{
        return strings[index];
    }
}
char*  libfuncs_getused(unsigned index){
    if(index > totalLibFuncs){
        printf("Segmentetion fault .|.");
        executionFinished = 1;
        return 0;
    }else{
        return Libfuncs[index];
    }
}

static void avm_initstack(void){
    int i;
    for(i = 0; i < AVM_STACKSIZE; i++){
        AVM_WIPEOUT(stack[i]); stack[i].type = undef_m;
    }
}

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){

    switch(arg->type){
        case global_a:  return &stack[AVM_STACKSIZE-1-arg->val];
        case local_a:   return &stack[topsp-arg->val];
        case formal_a:  return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];
    
        case retval_a:  return &retval;
    
        case number_a: {
            reg->type = number_m;
            reg->data.numVal = consts_getnumber(arg->val);
            return reg;
        }

        case string_a: {
            reg->type = string_m;
            reg->data.strVal = strdup(consts_getstring(arg->val));
            return reg;
        }

        case bool_a: {
            reg->type = bool_m;
            reg->data.boolVal = arg->val;
            return reg;
        }

        case nil_a: reg->type = nil_m; return reg;

        case userfunc_a: {
            reg->type = userfunc_m;
            reg->data.funcVal = arg->val;
            return reg;
        }

        case libfunc_a: {
            reg->type = libfunc_m;
            reg->data.libfuncVal = libfuncs_getused(arg->val);
            return reg;
        }

        default: assert(0);
    }
}


#include "phaseE_assign.h"
#include "phaseE_arithmetic.h"
#include "phaseE_calls_funcs.h"
#include "phaseE_relational.h"
#include "phaseE_tables_nop.h"
#include "library_functions.h"

int avm_error (char* yaccProvidedMessage){
    fprintf(stderr , RED"Runtime error" RESET " %s\n" , yaccProvidedMessage);
}

int mull(int x, int y){
    return x*y;
}

int hashCodeString(char* name){
    int Nname  = 0;
    char* c = name;
    int i = 1;
    while (*c != '\0'){
        Nname += mull(*c,i++);
        c++;
    }
    return Nname%AVM_TABLE_HASHSIZE;
}

int hashCodeNumber(int index){
    return index%AVM_TABLE_HASHSIZE;
}

void execute_cycle(void){
    if(executionFinished){
        return;
    }
    else
    if (pc == AVM_ENDING_PC) {
        executionFinished = 1;
        return;
    }
    else
    {
        assert(pc < AVM_ENDING_PC);
        Instruction *instr = code + pc;
        assert(
            instr->opcode >= 0 &&
            instr->opcode <= AVM_MAX_INSTRUCTIONS
        );

        if(instr->srcLine)
            currLine = instr->srcLine;
        unsigned oldPC = pc;
        (*executeFuncs[instr->opcode])(instr);
        if(pc == oldPC) {
            ++pc;
        }
    }
}

void avm_initialize(){
    avm_initstack();
    //avm_registerlibfunc("print",libfunc_print);
    //avm_registerlibfunc("typeof", libfunc_typeof);
}
//void avm_registerlibfunc(char* id ,library_func_t addr ){}