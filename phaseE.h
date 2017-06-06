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
    char* s;
    for(int i=0; i<AVM_TABLE_HASHSIZE; i++){
        avm_table_bucket* temp = table[i];
        while(temp != NULL){
            switch(temp->key.type){
                case number_m:{
                    switch(temp->value.type){
                        case number_m:{
                            sprintf(s,"\t%f:%f\n",temp->key.data.numVal, temp->value.data.numVal);
                            break;
                        }
                        case string_m:{
                            sprintf(s,"\t%f:%s\n",temp->key.data.numVal, temp->value.data.strVal);
                            break;
                        }
                        case bool_m:{
                            sprintf(s,"\t%f:%d\n",temp->key.data.numVal, temp->value.data.boolVal);
                            break;
                        }
                        case table_m:{
                            s = table_tostring(&(temp->value));
                            break;
                        }
                        case userfunc_m:{
                            sprintf(s,"\t%f:%s\n",temp->key.data.numVal, userFuncs[temp->value.data.funcVal].id);
                            break;
                        }
                        case libfunc_m:{
                            sprintf(s,"\t%f:%s\n",temp->key.data.numVal, temp->value.data.libfuncVal);
                            break;
                        }
                        case nil_m:{
                            sprintf(s,"\t%f:(null)\n",temp->key.data.numVal);
                            break;
                        }
                        case undef_m:{
                            sprintf(s,"\t%f:(undefined)\n",temp->key.data.numVal);
                            break;
                        }
                        default: CP(_tableTostring) assert(0);
                    }   break;
                }
                case string_m:{
                    switch(temp->value.type){
                        case number_m:{
                            sprintf(s,"\t%s:%f\n",temp->key.data.strVal, temp->value.data.numVal);
                            break;
                        }
                        case string_m:{
                            sprintf(s,"\t%s:%s\n",temp->key.data.strVal, temp->value.data.strVal);
                            break;
                        }
                        case bool_m:{
                            sprintf(s,"\t%s:%d\n",temp->key.data.strVal, temp->value.data.boolVal);
                            break;
                        }
                        case table_m:{
                            s = table_tostring(&(temp->value));
                            break;
                        }
                        case userfunc_m:{
                            sprintf(s,"\t%s:%s\n",temp->key.data.strVal, userFuncs[temp->value.data.funcVal].id);
                            break;
                        }
                        case libfunc_m:{
                            sprintf(s,"\t%s:%s\n",temp->key.data.strVal, temp->value.data.libfuncVal);
                            break;
                        }
                        case nil_m:{
                            sprintf(s,"\t%s:(null)\n",temp->key.data.strVal);
                            break;
                        }
                        case undef_m:{
                            sprintf(s,"\t%s:(undefined)\n",temp->key.data.strVal);
                            break;
                        }
                        default: CP(_tableTostring) assert(0);
                    }
                }   break;
                default:    CP(_tableTostring) assert(0);
            }
            temp = temp->next;
        }
    }
    return s;
}
char* userfunc_tostring  (avm_memcell* a){CP(_userfuncToString) assert(0);}
char* libfunc_tostring   (avm_memcell* a){CP(_libfuncToString)  assert(0);}
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

void libfunc_input(){
    unsigned n = avm_totalactuals();
    if(n!=0){
        char errorMessage[100];
        sprintf(errorMessage , "0 argument (not %d) expected in 'input'",n);
        avm_error(errorMessage);
    }else{
        avm_memcellclear(&retval);
        retval.type = number_m;
        scanf("%lf\n",&(retval.data.numVal));
    }
}

void libfunc_typeof(){
    unsigned n = avm_totalactuals();
    if(n!=1){
        char errorMessage[100];
        sprintf(errorMessage , "one argument (not %d) expected in 'typeof'",n);
        avm_error(errorMessage);
    }else{
        avm_memcellclear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}

void avm_initialize(){
    avm_initstack();
    //avm_registerlibfunc("print",libfunc_print);
    //avm_registerlibfunc("typeof", libfunc_typeof);
}

void libfunc_totalarguments(){
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);
    if(!p_topsp){
        avm_error("'totalarguments' called outside a function");
        retval.type = nil_m;
    }else{
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(p_topsp + AVM_SAVEDTOPSP_OFFSET);
    }
}

//void avm_registerlibfunc(char* id ,library_func_t addr ){}