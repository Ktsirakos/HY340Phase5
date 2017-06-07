#include "phase2.h"

typedef enum  iopcode {
    assign,         add,            sub,
    mul,            div_code,            mod,
    uminus,         and,            or,
    not,            if_eq,          if_noteq,
    if_lesseq,      if_greatereq,   if_less,
    if_greater,     call,           param,  
    ret_code,       getretval,      functstart,
    functend,       tablecreate,    tablegetelem, 
    tablesetelem,   jump,           program_end
    
}iopcode;


char* typeStr[] = {
    "assign      ",         
    "add         ",            
    "sub         ",
    "mul         ",            
    "div_code    ",       
    "mod         ",
    "uminus      ",         
    "and         ",            
    "or          ",
    "not         ",            
    "if_eq       ",          
    "if_noteq    ",
    "if_lesseq   ",      
    "if_greatereq",   
    "if_less     ",
    "if_greater  ",     
    "call        ",           
    "param       ",  
    "ret_code    ",       
    "getretval   ",      
    "functstart  ",
    "funcend     ",        
    "tablecreate ",    
    "tablegetelem", 
    "tablesetelem",   
    "jump        ",
    "program_end"
};


char * typeVM[] = {
    "assign_v",           
    "add_v",          
    "sub_v",
    "mul_v",           
    "div_v",          
    "mod_v",
    "uminus_v",       
    "and_v",          
    "or_v",
    "not_v",          
    "jeq_v",          
    "jne_v",
    "jle_v",          
    "jge_v",          
    "jlt_v",
    "jgt_v",          
    "call_v",         
    "pusharg_v",
    "funcenter_v",    
    "funcexit_v",     
    "newtable_v",
    "tablegetelem_v", 
    "tablesetelem_v", 
    "nop_v" , 
    "jump_v",
    "ret_v" , 
    "grv_v"
};
/*---------------------------------------------*/

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
    retval_a,
    forword_a
} vmarg_t;

typedef struct vmarg_t { 
    vmarg_t type;  unsigned val; 
} vmarg;

typedef struct instruction {
    vmopcode opcode;
    vmarg*    result;
    vmarg*    arg1;
    vmarg*   arg2;
    unsigned label;
    unsigned srcLine;

} Instruction;

typedef struct userfunc_t {
    unsigned address;
    unsigned localSize;
    char*    id;
    ValuesStack* returnList;
    struct userfunc_t* prev;
} userfunc;

double*    numConsts;
unsigned   totalNumConsts = 0;

char**     stringConsts;
unsigned   totalStringConsts = 0;

char**     namedLibfuncs;
unsigned   totalNamedLibFuncs = 0;

userfunc*  funcStack;
userfunc*  userFuncs;
unsigned   totalUserFuncs = 0;
unsigned int currProsQuad = 0;
/*---------------------------------*/
typedef enum {
    var_e,
    tableitem_e,
    programfunc_e,
    libraryfunc_e,
    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,
    constnum_e,
    constbool_e,
    conststring_e,
    nil_e
}expr_t;

typedef struct expr_type{
    expr_t                  type;
    symbolTable*            sym;
    struct expr_type*       index;
    double                  numConst;
    char*                   strConst;
    unsigned char           boolConst;

    struct expr_type*       table;

    ValuesStack* truelist;
    ValuesStack* falselist;

    struct expr_type*       next;
} expr;

typedef struct  quad_t {
    iopcode     op;
    expr*       result;
    expr*       arg1;
    expr*       arg2;

    unsigned    taddress;
    unsigned    label;
    unsigned    line;
} quad;

quad*           quads = (quad*) 0;
unsigned        total = 0;
unsigned int    currQuad = 0; 

int tempfunccounter = 0;
int tempcounter = 0;

Instruction* instructions = (Instruction*) 0;
unsigned int totalInst = 0;
unsigned int currInst  = 0;

    expr* currentUsingTable;


#define EXPAND_SIZE 1024
#define CURR_SIZE   (total*sizeof(quad))
#define NEW_SIZE    (EXPAND_SIZE*sizeof(quad) + CURR_SIZE)

void expand(void){
    assert(total == currQuad);
    quad* p = (quad*) malloc(NEW_SIZE);
    
    if(quads){
        memcpy(p ,  quads , CURR_SIZE);
        free(quads);
    }

    quads = p;
    total += EXPAND_SIZE;
}

void emit(iopcode op , expr* arg1 , expr* arg2 , expr* result, unsigned label, unsigned line){
    if(currQuad == total) expand();

    quad* p = quads + currQuad++;
    p->op = op;
    p->arg1 = arg1;
    p->arg2 = arg2;
    p->result = result;
    p->label = label;
    p->line = line + 1;
    /*char number[10];
    sprintf(number,"%d",p->label);
        printf("%3d: %s\t%s\t%s\t%s\t%s\n"
                            ,p->line
                            ,typeStr[p->op]
                            ,p->arg1 != NULL?p->arg1->strConst:"\b"
                            ,p->arg2 != NULL?p->arg2->strConst:"\b"
                            ,p->result != NULL?p->result->strConst:"\b"
                            ,p->label != -1?number:"\b"
                            ); */
}

expr* lvalue_expr ( symbolTable* sym){
    assert(sym);
    expr* e = (expr*) malloc (sizeof(expr));
    memset(e , 0 , sizeof(expr));

    e->next = (expr*) 0;
    e->sym  = sym;
    e->strConst = strdup(sym->name);

    switch(sym->type){
        case GLOBAL      :   
        case ARGV        :    
        case LOCAL_SCOPE :   e->type = var_e; break;   
        case PROG_FUNCT  :   e->type = programfunc_e; break;
        case LIB_FUNCT   :   e->type = libraryfunc_e; break;
        default          :   assert(0);
    }

    return e;
}

void printQuads(){
    int counter = 0;
    char number[10];
    while(counter < currQuad){
        sprintf(number,"%d",quads[counter].label);
        printf("%3d: %s\t%s\t%s\t%s\t%s\n"
                            ,quads[counter].line
                            ,typeStr[quads[counter].op]
                            ,quads[counter].arg1 != NULL?quads[counter].arg1->strConst:"\b"
                            ,quads[counter].arg2 != NULL?quads[counter].arg2->strConst:"\b"
                            ,quads[counter].result != NULL?quads[counter].result->strConst:"\b"
                            ,quads[counter].label != -1?number:"\b"
                            );
        counter++;
    }
}

char* newtempfuncname(){
    char counter[20];
    char prefix[20] = "_f";
    sprintf(counter , "%d" , tempfunccounter);
    strcat(prefix , counter);
    tempfunccounter++;

    char* tempfunctionName = strdup(prefix);
    return tempfunctionName;
}

symbolTable* newtemp(){
    char counter[20];
    char prefix[20] = "_t";
    sprintf(counter , "%d" , tempcounter);
    strcat(prefix , counter);
    tempcounter++;

    insert(0 , strdup(prefix) , Cscope , yylineno);
    return findNode(strdup(prefix), Cscope);
}

void resetScopeSpace(void)      {scopespace = 0;}
void resetformalargsoffset(void) { formalArgOffset = 0; }
void resetfunctionlocaloffset(void) { functionLocalOffset = 0; }
void restorecurrscopeoffset(unsigned n){
    switch(currscopespace()){
        case programm_vars      : programVarOffset = n; break;
        case function_locals    : functionLocalOffset = n; break;\
        case function_arguments : formalArgOffset = n; break;
        default:   assert(0);
    }
}

unsigned int nextquadlabel(void){
     return currQuad;
}
void patchlabel( unsigned int quadNo , unsigned int label){
     assert( quadNo <= currQuad);
     quads[quadNo-1].label = label;
}
void patchlabelI( unsigned int instNo , unsigned int label){
     assert( instNo <= currInst);
     if(instructions[instNo].result->type == forword_a){
         instructions[instNo].result->val = label+1;
     }else{
        instructions[instNo].result->val = label;
     }
}
expr* newexpr(expr_t t){
     expr* e = (expr*) malloc (sizeof(expr));
     memset(e , 0 , sizeof(expr));
     e->type = t;
     return e;
}
expr* emit_iftableitem(expr* e){
    if (e->type != tableitem_e) return e;
    expr* result = newexpr(var_e);
    result->sym = newtemp();
    result->strConst = result->sym->name;
    result->index = e->index;
    emit(tablegetelem, e, e->index,result,-1,currQuad);
    result->table = malloc(sizeof(expr));
    result->table->type = e->type;
    result->table->strConst = e->strConst;
    result->table->index = e->index;
    result->table->sym = e->sym;
    return result;
}
expr* newexpr_conststring(char* s){
     expr* e = newexpr(conststring_e);
     e->strConst = strdup(s);
     return e;
}
expr*  member_item(expr* lvalue , char* id){
    char* name = (char*)malloc(100*sizeof(char));
    sprintf(name , "\"%s\"" , id);
     lvalue->index = newexpr_conststring(name);
     lvalue      = emit_iftableitem(lvalue);
     //if(lvalue->type != tableitem_e){
         lvalue->table = malloc(sizeof(expr));
         lvalue->table->type = lvalue->type;
         lvalue->table->strConst = lvalue->strConst;
         lvalue->table->index = lvalue->index;
         lvalue->table->sym = lvalue->sym;
     //}
     expr* item  = newexpr(tableitem_e);
     item->sym   = lvalue->sym;
     item->strConst = item->sym->name;
     item->index = lvalue->index;
     item->table = lvalue->table;
     return item;
}
expr* newexpr_constbool (unsigned char i){
    expr* e = newexpr(constbool_e);
    e->boolConst = i;
    if (i == 0) e->strConst = "false";
    else        e->strConst = "true";
    return e;
}
expr* newexpr_constnum ( double i){
     char number[30];
     expr* e = newexpr(constnum_e);
     e->numConst = i;
     sprintf(number,"%3f",i);
     e->strConst = strdup(number);
     return e;
}
void checkuminus(expr* e){
    if( e->type == var_e       ||
        e->type == tableitem_e ||
        e->type == arithexpr_e ||
        e->type == assignexpr_e||
        e->type == constnum_e){
        return;
    }else{
        printf("Illegal expr to unary -");
    }
}

expr* calls(expr* elist, unsigned char b, char* name){
    expr* result = (expr*)malloc(sizeof(expr));
    result->boolConst = b;
    result->strConst = name;
    result->next = elist;
    return result;
}

expr* make_call(expr* lvalue, expr* elist){
    //expr* func = emit_iftableitem(lvalue);
    expr* temp = elist;
    while(temp != NULL){
        emit(param,temp,NULL,NULL,-1,currQuad);
        temp = temp->next;
    }
    printf("%s with type %d\n" , lvalue->strConst , lvalue->type);
    emit(call,lvalue,NULL,NULL,-1,currQuad);
    temp = newexpr(var_e);
    temp->sym = newtemp();
    temp->strConst = temp->sym->name;
    if(lvalue->sym->table == 1){                //---------------
        printf("FUNCTION RETURNING ARRAY\n");   //---------------
        temp->type = newtable_e;                //----------------
    }                                           //---------------
    emit(getretval,temp,NULL,NULL,-1,currQuad);
    return temp;
}
/*
node_list* newlist(int quadno){
    node_list* temp = (node_list*) malloc(sizeof(node_list));
    temp->value = quadno;
    temp->next = NULL;
    return temp;
}

node_list* merge(node_list* toWhere , node_list* what){
        if(what == NULL){
            return toWhere;
        }

        what->next = toWhere;
        return what;
}*/

expr* check_arithop(expr* e1 , expr* e2){
    expr* result = (expr*)malloc(sizeof(expr));
    expr_t type1 = e1->type;
    expr_t type2 = e2->type;


    if(type1 == programfunc_e ||
       type2 == programfunc_e ||
       type1 == libraryfunc_e ||
       type2 == libraryfunc_e ||
       type1 == boolexpr_e    ||
       type2 == boolexpr_e    ||
       type1 == newtable_e    ||
       type2 == newtable_e    ||
       type1 == constbool_e ||
       type2 == constbool_e ||
       type1 == conststring_e ||
       type2 == conststring_e ||
       type1 == nil_e         ||
       type2 == nil_e         
       ){return NULL;}

    if(type1 == type2 && type1 == constnum_e){
       result->type = type1;
       result->sym  = newtemp();
       result->strConst = result->sym->name;
       return result;
    }else{
       result->type = arithexpr_e;
       result->sym = newtemp();
       result->strConst = result->sym->name;
       return result;
    }
}

expr* check_relop(expr* e1, expr* e2){
    expr* result = (expr*)malloc(sizeof(expr));
    result->type = nil_e;
    result->strConst = NULL;
    if(e1->type != constnum_e || e2->type != constnum_e)    return result;
    result->type = boolexpr_e;
    result->sym = newtemp();
    result->strConst = result->sym->name;
    return result;
}

expr* check_true(expr* e){
    expr_t type = e->type;
    expr* true_e = (expr*)malloc(sizeof(expr));
    expr* false_e = (expr*)malloc(sizeof(expr));
    true_e->boolConst = 1;
    true_e->strConst = "true";
    true_e->type = boolexpr_e;
    true_e->boolConst = 0;
    true_e->strConst = "false";
    true_e->type = boolexpr_e;
    switch (type){
        case 0: return true_e;
        case 1: return true_e;
        case 2: return true_e;
        case 3: return true_e;
        case 4: return e->numConst==0?false_e:true_e;
        case 5: return e;
        case 6: return true_e;
        case 7: return true_e;
        case 8: return e->numConst==0?false_e:true_e;
        case 9: e->type = boolexpr_e; return e;
        case 10: return strcmp(e->strConst,"")==0?false_e:true_e;
        case 11: return false_e;
        default: assert(0);
    }
}

ValuesStack* makelist(int val){
    ValuesStack* temp = (ValuesStack*)malloc(sizeof(ValuesStack));
    temp->value = val;
    temp->prev = NULL;
    return temp;
}

ValuesStack* merge(ValuesStack* e1 , ValuesStack* e2){
    ValuesStack* temp = e1;
    if(temp == NULL) return e2;
    while(temp->prev != NULL)   temp = temp->prev;
    temp->prev = e2;
    return e1;
}

void backpatch(ValuesStack* list , int quad){
    ValuesStack* temp = list;
    while(temp != NULL){
        patchlabel(temp->value, quad);
        temp = temp->prev;
    }
    return;
}

userfunc* pushToFunc(userfunc* stack, symbolTable* f){
    userfunc* temp = (userfunc*)malloc(sizeof(userfunc));
    temp->address = f->taddress;
    temp->localSize = f->totallocals;
    temp->id = f->name;
    temp->returnList = NULL;
    temp->prev = stack;
    return temp;
}
userfunc* popFromFunc(userfunc* stack){
    return stack->prev;
}
void addToUserFuncs(userfunc stack, symbolTable* f){
    stack.address = f->taddress;
    stack.localSize = f->totallocals;
    stack.id = f->name;
    stack.returnList = NULL;
    stack.prev = NULL;
}
void backpatchI(ValuesStack* list , int inst){
    ValuesStack* temp = list;
    while(temp != NULL){
        patchlabelI(temp->value, inst);
        temp = temp->prev;
    }
    return;
}
ValuesStack* append(ValuesStack* list, int val){
    ValuesStack* temp = makelist(val);
    temp->prev = list;
    return temp;
}
int ultimateLookUpForVariables(expr** lvalue, expr_t type){                                        
    int numberofblock = 0;
    int i;
    functionStack* p = stackF;
    while(p != NULL){
        if(strcmp(p->name , "_$block") == 0){
            numberofblock++;
            p = p->prev;
        }else{
            break;
        }
    }
    int haveAccess = 0;
    for(i = 0; i <= numberofblock; i++){
        if(found_local){
            if(lookup((*lvalue)->strConst , Cscope) == 1){
                (*lvalue)->sym = findNode((*lvalue)->strConst , Cscope);
                if((*lvalue)->sym->table == 1){
                    (*lvalue)->type = newtable_e;
                }else if((*lvalue)->sym->funct == 1){
                    (*lvalue)->type = programfunc_e;
                }
                haveAccess = 1;
            }
            found_local = 0;
            break;
        }else if(lookup((*lvalue)->strConst , Cscope - i) == 1){
            (*lvalue)->sym = findNode((*lvalue)->strConst , Cscope - i);
            if((*lvalue)->sym->table == 1){
                (*lvalue)->type = newtable_e;
            }else if((*lvalue)->sym->funct == 1){
                (*lvalue)->type = programfunc_e;
            }
            haveAccess = 1;
            break;
        }else if(i == numberofblock){
            if(lookup((*lvalue)->strConst , 0) == 1){
                (*lvalue)->sym = findNode((*lvalue)->strConst , 0);
                if((*lvalue)->sym->table == 1){
                    (*lvalue)->type = newtable_e;
                }else if((*lvalue)->sym->funct == 1){
                    (*lvalue)->type = programfunc_e;
                }
                haveAccess = 1;
            }
        }
    }
    if(haveAccess){
        if((*lvalue)->sym->funct == 1 && !isIndexed){
            printf(RED"ERROR" RESET ": programm function %s used as an l-value\n" , (*lvalue)->strConst);
            error++;
            return -1;
        }else if(&(*lvalue)->sym == NULL){
            (*lvalue)->type = type;
            return 1;
        }
    }else{
        int NotAccess = 0;
        for(i = 1; i <= Cscope-numberofblock; i++){
            if(lookup((*lvalue)->strConst , i) == 1){
                NotAccess = 1;
            }
        }
        if(NotAccess){
            printf(RED"ERROR" RESET ": %s not accessible\n" , (*lvalue)->strConst);
            error++;
            return -1;
        }
        return 0;
    }
}

expr* exprCopy(expr* e){
    if(e == NULL)   return NULL;
    expr* toRet = (expr*)malloc(sizeof(expr));
    toRet->type = e->type;
    toRet->sym = e->sym;
    toRet->index = e->index;
    toRet->numConst= e->numConst;
    toRet->strConst= e->strConst;
    toRet->boolConst= e->boolConst;
    toRet->table = e->table;
    toRet->truelist= e->truelist;
    toRet->falselist= e->falselist;
    toRet->next = exprCopy(e->next);
    return toRet;
}