/**
 Edw tha graftoun oi sinartiseis gia tin paragwgi tou telikoy kwdika
**/

#include "quads.h"



int  funcEndforJump = 0;




typedef void (*generator_func_t)(quad*);

#define NL \n
#define PRINT(x) printf("%d:\t%s(%d)\t%d(%d)\t%d(%d)\t%d(%d)\t%d\n"\
                            , x.srcLine\
                            , typeVM[x.opcode]\
                            , x.opcode\
                            , x.result->type\
                            , x.result->val\
                            , x.arg1->type\
                            , x.arg1->val\
                            , x.arg2->type\
                            , x.arg2->val\
                            , x.label);





void initialize_Strings(){
    stringConsts = (char**)malloc(500*sizeof(char*));
    totalStringConsts = 0;
    return;
}

void initialize_Numbers(){
    numConsts = malloc(200*sizeof(double));
    totalNumConsts = 0;
    return;
}

void initialize_Userfucs(){
    userFuncs = (userfunc*)malloc(100*sizeof(userfunc));
    totalUserFuncs = 0;
    return;
}

void initialize_Libfuncs(){
    namedLibfuncs = (char**)malloc(100*sizeof(char*));
    totalNamedLibFuncs = 0;
    return;
}


void initialize_Arrays(){

    initialize_Strings();
    initialize_Numbers();
    initialize_Userfucs();
    initialize_Libfuncs();

}

void printArraysTofile(FILE *fp){
    int i;
    fprintf(fp ,"%d Strings\n" , totalStringConsts);
    for( i = 0; i < 500; i++){
        if(stringConsts[i] != NULL){
            fprintf(fp ,"%d %s\n" , i , stringConsts[i]);
        }
    }

    fprintf(fp ,"%d Nums\n" , totalNumConsts);
    for( i = 0; i < totalNumConsts; i++){
        fprintf(fp ,"%d %f\n" , i , numConsts[i]);
    }

    fprintf(fp ,"%d Userfuncs\n" , totalUserFuncs);
    for( i = 0; i < 100; i++){
        if(userFuncs[i].id != NULL){
            fprintf(fp , "%d %d %d %s\n" ,i ,userFuncs[i].address, userFuncs[i].localSize,  userFuncs[i].id);
        }
    }


    fprintf(fp ,"%d Libfuncs\n" , totalNamedLibFuncs);
    for( i = 0; i < 100; i++){
        if(namedLibfuncs[i] != NULL){
            fprintf(fp ,"%d %s\n" , i ,namedLibfuncs[i]);
        }
    }
}

void printArrays(){
    int i;
    printf("%d Strings\n" , totalStringConsts);
    for( i = 0; i < 100; i++){
        if(stringConsts[i] != NULL){
            printf("%d:  %s\n" , i , stringConsts[i]);
        }
    }

    printf("%d Nums\n" , totalNumConsts);
    for( i = 0; i < totalNumConsts; i++){
        printf("%d: %f\n" , i , numConsts[i]);
    }

    printf("%d Userfuncs\n" , totalUserFuncs);
    for( i = 0; i < 100; i++){
        if(userFuncs[i].id != NULL){
            printf( "%d %d %d %s\n" ,i ,userFuncs[i].address, userFuncs[i].localSize,  userFuncs[i].id);
        }
    }


    printf("%d Libfuncs\n" , totalNamedLibFuncs);
    for( i = 0; i < 100; i++){
        if(namedLibfuncs[i] != NULL){
            printf("%d: %s\n" , i ,namedLibfuncs[i]);
        }
    }

    printf("%d code\n" , currInst);

}


unsigned consts_newstring (char* s) {
    int i;
    for(i = 0; i < totalStringConsts; i++){
        if(strcmp(stringConsts[i] , s) == 0){
            return i;
        }
    }
    stringConsts[totalStringConsts]  = strdup(s);
    return totalStringConsts++;
}

unsigned consts_newnumber (double n){ 
    int i;
    for(i = 0; i < totalNumConsts; i++){
        if(numConsts[i] == n){
            return i;
        }
    }
    numConsts[totalNumConsts] = n;
    return totalNumConsts++; 
}

unsigned consts_newused   (symbolTable* sym) { 
    int i;
    for(i = 0; i < totalUserFuncs; i++){
        if(strcmp(userFuncs[i].id , sym->name) == 0){
            return i;
        }
    }
    userFuncs[totalUserFuncs].id = strdup(sym->name);
    userFuncs[totalUserFuncs].address = sym->taddress + 1;
    userFuncs[totalUserFuncs].localSize = sym->totallocals;
    return totalUserFuncs++; 
}

unsigned libfuncs_newused (char *s) {
    int i;
    for(i = 0; i < totalNamedLibFuncs; i++){
        if(strcmp(namedLibfuncs[i] , s) == 0){
            return i;
        }
    }
    namedLibfuncs[totalNamedLibFuncs] = strdup(s);
    return totalNamedLibFuncs++;
}

#define CURR_INST_SIZE  (total*sizeof(Instruction))
#define NEW_INST_SIZE   (EXPAND_SIZE*sizeof(Instruction) + CURR_INST_SIZE)


typedef struct incomplete_jump {
    unsigned instrNo;
    unsigned iaddress;
    struct incomplete_jump* next;
} Incomplete_jump;

Incomplete_jump* jumps_to_patch = NULL;


void expand_Instruction(void){
    assert(totalInst == currInst);
    Instruction* i = (Instruction*) malloc(NEW_INST_SIZE);

    if(instructions){
        memcpy(i ,  instructions , CURR_INST_SIZE);
        free(instructions);
    }

    instructions = i;
    totalInst += EXPAND_SIZE;
}


void emit_instruction(Instruction* i){
    if(currInst == totalInst) expand_Instruction();

    Instruction* q = instructions + currInst++;
    q->opcode = i->opcode;
    q->result = i->result;
    q->arg1 = i->arg1;
    q->arg2 = i->arg2;
    q->srcLine = i->srcLine;
    q->label = i->label - 1;

    PRINT(instructions[currInst - 1])
}

void printInst(){
    int i;
    printf("Line\tInst\t\tresult\targ1\targ2\tlabel\n");
    for(i=0;i<currInst;i++){
        PRINT(instructions[i])
    }
}

void add_incomplete_jump(unsigned instrNo , unsigned iaddress){
    assert(instrNo >= currProsQuad);
    Incomplete_jump* node = malloc(sizeof(Incomplete_jump));
    node->instrNo = instrNo;
    node->iaddress = iaddress;
    node->next = jumps_to_patch;
    jumps_to_patch = node;
    return;
}


void patch_incomplete_jumps(){
    Incomplete_jump* temp = jumps_to_patch;
    int i;
    while(temp != NULL){
        if(temp->iaddress == currQuad-1){
            instructions[temp->instrNo].result->val = currInst-1;
        }else {
            i = quads[temp->iaddress - 1].taddress;
            instructions[temp->instrNo].result->val = i;
        }
        temp = temp->next;
    }
}


void make_operand(expr* e , vmarg* arg){
    if(e == NULL){
        arg->val = -1;
        return;
    }
    switch(e->type){
        case var_e:
        case tableitem_e:
        case arithexpr_e:
        case boolexpr_e:
        case newtable_e: 
        case assignexpr_e: {
            arg->val = e->sym->offset;
            switch(e->sym->scopespace){
                case  programm_vars :        arg->type = global_a; break;
                case  function_arguments : arg->type = formal_a; break;
                case  function_locals : arg->type = local_a;    break;
            }
            break;
        }
        case constbool_e: {
            arg->val = e->boolConst;
            arg->type = bool_a;
            break;
        }

        case conststring_e : {
            arg->val = consts_newstring(e->strConst);
            arg->type = string_a;
            break;
        }

        case constnum_e: {
            arg->val = consts_newnumber(e->numConst);
            arg->type = number_a;
            break;
        }

        case nil_e: arg->type = nil_a; break;

        case programfunc_e: {
            arg->type = userfunc_a;
            arg->val = consts_newused(e->sym);
            break;
        }

        case libraryfunc_e: {
            arg->type = libfunc_a;
            arg->val = libfuncs_newused(e->sym->name);
            break;
        }

        default: assert(0);
    }
}

Instruction*  initialize_Instruction(){
    Instruction* temp = (Instruction*)malloc(sizeof(Instruction));
    temp->result = (vmarg*)malloc(sizeof(vmarg));
    temp->arg1   = (vmarg*)malloc(sizeof(vmarg));
    temp->arg2   = (vmarg*)malloc(sizeof(vmarg));
    temp->srcLine= 0;
    temp->label  = -1;
    return temp;
}


void gen(vmopcode op, quad* q){
    Instruction *temp = initialize_Instruction();
    temp->opcode  = op;
    make_operand(q->result , temp->result);
    make_operand(q->arg1   , temp->arg1);
    make_operand(q->arg2   , temp->arg2);
    temp->srcLine = currInst;
    temp->label   = q->label;
    q->taddress = currInst;
    emit_instruction(temp);
    currProsQuad++;
}

void gen_relop(vmopcode op, quad* q){
    Instruction *temp = initialize_Instruction();
    q->taddress = currInst;
    temp->opcode  = op;
    make_operand(q->arg1   , temp->arg1);
    make_operand(q->arg2   , temp->arg2);
    temp->result->type = label_a;
    if(q->label < currProsQuad){
        temp->result->val = quads[q->label-1].taddress;
    }else{
        add_incomplete_jump(currInst, q->label);
    }
    temp->srcLine = currInst;
    emit_instruction(temp);
    currProsQuad++;
}

void generate_ADD               (quad* q){gen(add_v,q);}
void generate_SUB               (quad* q){gen(sub_v,q);}
void generate_MUL               (quad* q){gen(mul_v,q);}
void generate_DIV               (quad* q){gen(div_v,q);}
void generate_MOD               (quad* q){gen(mod_v,q);}
void generate_ASSIGN            (quad* q){gen(assign_v,q);}
void generate_NEWTABLE          (quad* q){gen(newtable_v,q);}
void generate_TABLEGETELEM      (quad* q){gen(tablegetelem_v,q);}
void generate_TABLESETELEM      (quad* q){gen(tablesetelem_v,q);}
void generate_UNIMUS            (quad* q){return;}           
void generate_AND               (quad* q){return;}             
void generate_OR                (quad* q){return;}       
void generate_NOT               (quad* q){return;}             
void generate_JUMP              (quad* q){gen_relop(jump_v,q);}
void generate_IF_EQ             (quad* q){gen_relop(jeq_v,q);}
void generate_IF_NOTEQ          (quad* q){gen_relop(jne_v,q);}
void generate_IF_LESSEQ         (quad* q){gen_relop(jle_v,q);}
void generate_IF_GREATEREQ      (quad* q){gen_relop(jge_v,q);}
void generate_IF_LESS           (quad* q){gen_relop(jlt_v,q);}
void generate_IF_GREATER        (quad* q){gen_relop(jgt_v,q);}
void generate_NOP               (quad* q){
    Instruction *temp = initialize_Instruction();
    q->taddress = currInst;
    temp->opcode  = nop_v;
    temp->srcLine = currInst;
    emit_instruction(temp);
}
void generate_PARAM             (quad* q){
    Instruction *temp = initialize_Instruction();
    q->taddress = currInst;
    temp->opcode  = pusharg_v;
    make_operand(q->arg1,temp->arg1);
    temp->srcLine = currInst;
    temp->label = q->label;
    emit_instruction(temp);
    currProsQuad++;
}
void generate_CALL              (quad* q){
    Instruction *temp = initialize_Instruction();
    q->taddress = currInst;
    temp->opcode  = call_v; 
    make_operand(q->arg1,temp->arg1);
    make_operand(q->arg2,temp->arg2);
    make_operand(q->result,temp->result);

    temp->srcLine = currInst;
    temp->label = q->label;
    emit_instruction(temp);
    currProsQuad++;
}
void generate_GETRETVAL         (quad* q){
    Instruction *temp = initialize_Instruction();
    q->taddress = currInst;
    temp->opcode  = assign_v;
    make_operand(q->arg1,temp->result);
    temp->srcLine = currInst;
    temp->label = q->label;
    temp->arg1->type = retval_a;
    emit_instruction(temp);
    currProsQuad++;
}
void generate_FUNCTSTART        (quad* q){
    Instruction *temp = initialize_Instruction();
    symbolTable* s = q->arg1->sym;
    s->taddress = currInst;
    q->taddress = currInst;    
    //addToUserFuncs(userFuncs[totalUserFuncs++],f);
    funcStack = pushToFunc(funcStack,s);

    userfunc* f = funcStack;
    f->returnList = append(f->returnList,currInst);
    temp->opcode = jump_v;
    make_operand(NULL,temp->arg1);
    make_operand(NULL,temp->arg2);
    temp->srcLine = currInst;
    temp->result->type = forword_a;
    emit_instruction(temp);

    temp = initialize_Instruction();
    temp->opcode  = funcenter_v;
    make_operand(q->arg1,temp->result);
    temp->srcLine = currInst;
    temp->label = q->label;
    emit_instruction(temp);
    currProsQuad++;
}
void generate_FUNCEND           (quad* q){
    Instruction *temp = initialize_Instruction();
    q->taddress = currInst;
    userfunc* f = funcStack;
    funcStack = popFromFunc(funcStack);
    backpatchI(f->returnList,currInst);
    temp->opcode  = funcexit_v;
    make_operand(q->arg1,temp->result);
    temp->srcLine = currInst;
    temp->label = q->label;
    emit_instruction(temp);
    currProsQuad++;
}
void generate_RETURN            (quad* q){
    Instruction *temp = initialize_Instruction();
    q->taddress = currInst;
    temp->opcode  = assign_v;
    temp->result->type = retval_a;
    make_operand(q->arg1,temp->arg1);
    temp->srcLine = currInst;
    temp->label = q->label;
    emit_instruction(temp);

    userfunc* f = funcStack;
    f->returnList = append(f->returnList,currInst);

    temp = initialize_Instruction();
    temp->opcode = jump_v;
    make_operand(NULL,temp->arg1);
    make_operand(NULL,temp->arg2);
    temp->result->type = label_a;
    temp->srcLine = currInst;
    emit_instruction(temp);
    currProsQuad++;
}

generator_func_t generators[] = {
    generate_ASSIGN,   
    generate_ADD,   
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UNIMUS,
    generate_AND,  
    generate_OR,
    generate_NOT,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCTSTART,
    generate_FUNCEND,
    generate_NEWTABLE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_JUMP,
    generate_NOP
};



void generate ( void ){
    int i;
    for(i = 0; i < currQuad; ++i){
        (*generators[quads[i].op])(quads+i);
    }
    patch_incomplete_jumps();
}


void printInstructionTofile(FILE *fp){

    int globals = 0;
    symbolTable* p;
    int i;
    for(i=0;i<HASHMAX;i++){
        p = symT[i];
        while(p != NULL){
            if(p->scope == 0) globals++;
            p = p->next;
        }
    }

    fprintf(fp ,"%d Globals\n" , globals);

    fprintf(fp , "%d code\n" , currInst);
    fprintf(fp , "-1 End\n");
    for(i=0;i<currInst;i++){
        fprintf(fp , "%d %d.%d %d.%d %d.%d %d\n"
                            , instructions[i].opcode
                            , instructions[i].result->type
                            , instructions[i].result->val
                            , instructions[i].arg1->type
                            , instructions[i].arg1->val
                            , instructions[i].arg2->type
                            , instructions[i].arg2->val
                            , instructions[i].label
                );
    }
}


void writeBinaryFile(){
    FILE *fp;
    fp = fopen("binary.abc", "w");
    if(fp == NULL){
        printf("Error Opening File\n");
    }else{
        fprintf(fp , "%d magic\n" , 340200501);
        printArraysTofile(fp);
        printInstructionTofile(fp);
    }
}
