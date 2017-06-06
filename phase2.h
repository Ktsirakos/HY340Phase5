#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "colors.h"

symbolTable** symT;
symbolTable* scopeList;
functionStack* stackF;
loop_stack* breakStack = NULL;
loop_stack* conStack = NULL;
ValuesStack* forfunctionsLocalStack = NULL;
ValuesStack* forfunctionsScopeSpace = NULL;
ValuesStack* forloops = NULL;
ValuesStack* forscopespace = NULL;
ValuesStack* breaklist = NULL;
ValuesStack* conlist = NULL;
ValuesStack* truelist = NULL;
ValuesStack* falselist = NULL;
ValuesStack* forTables = NULL;
funcF* funcf = NULL;

int programVarOffset = 0;
int formalArgOffset = 0;
int functionLocalOffset = 0;
Scopespace scopespace;


void enterscopespace() { scopespace++; }
void exitscopespace()  { scopespace--; }
int currscopespace() { return scopespace; }

void initHashTable(){   
    int i;
    scopeList = NULL;
    stackF = NULL;
    symT = (symbolTable**)malloc(HASHMAX*sizeof(symbolTable*));
    for(i=0; i<HASHMAX; i++){
        symT[i] = NULL;
    }
    insert(1,"print",0,0);
    insert(1,"input",0,0);
    insert(1,"objectmemberkeys",0,0);
    insert(1,"objecttotalmembers",0,0);
    insert(1,"objectcopy",0,0);
    insert(1,"totalarguments",0,0);
    insert(1,"argument",0,0);
    insert(1,"typeof",0,0);
    insert(1,"strtonum",0,0);
    insert(1,"sqrt",0,0);
    insert(1,"cos",0,0);
    insert(1,"sin",0,0);

}

int mull(int x, int y){
    return x*y;
}

int hashCode(char* name){
    int Nname  = 0;
    char* c = name;
    int i = 1;
    while (*c != '\0'){
        Nname += mull(*c,i++);
        c++;
    }
    return Nname%HASHMAX;
}

symbolTable* insertH(symbolTable* head, symbolTable* x){
    if(head == NULL) return x;
    head->next = insertH(head->next,x);
    return head;
}
symbolTable* insertS(symbolTable* head, symbolTable* x){
    if(head == NULL) return x;
    head->nextInScope = insertS(head->nextInScope,x);
    return head;
}
symbolTable* insertScope(symbolTable* head, symbolTable* x){
    if(head == NULL){
        return x;
    }else if(x->scope > head->scope){
        head->nextScope = insertScope(head->nextScope, x);
    }else if(x->scope < head->scope){
        x->nextScope = head;
        return x;
    }else{
        head = insertS(head,x);
    }
    return head;
}

void insert(int funct, char* name, int scope,int line){
    int i;
    symbolTable* h;
    symbolTable* p;
    symbolTable* temp = (symbolTable*)malloc(sizeof(symbolTable));

    temp->visible = 1;
    temp->funct = funct;
    temp->name = (char*)malloc(strlen(name)*sizeof(char)+1);
    strcpy(temp->name,name);
    if(scope == 0)  temp->type = 0;
    else    temp->type = 2;
    if(funct == 1)  temp->type = 4;
    if(line == 0)   temp->type = 3;

    if(currscopespace() == 2){
        temp->scopespace = function_locals;
    }else if(currscopespace() == 0){
        temp->scopespace = programm_vars;
    }

    temp->offset  = functionLocalOffset++;
    temp->scope = scope;
    temp->line = line;
    temp->argv = NULL;
    temp->nextScope = NULL;
    temp->nextInScope = NULL;
    temp->next = NULL;

    p = symT[hashCode(name)];
    p = insertH(p,temp);
    symT[hashCode(name)] = p;

    scopeList = insertScope(scopeList,temp);
}

int lookup(char* name, int scope){
    symbolTable* p = symT[hashCode(name)];
    while(p != NULL){
        if(strcmp(p->name ,name) == 0 && p->line == 0)         return -1;
        if(strcmp(p->name ,name) == 0 && p->scope == scope && p->visible == 1)    return 1;
        p = p->next;
    }
    return 0;
}

symbolTable* findNode(char* name, int scope){
    symbolTable* p = symT[hashCode(name)];
    while(p != NULL){
        if(strcmp(p->name ,name) == 0 && p->scope == scope)    return p;
        p = p->next;
    }
    return NULL;
}

void hide(int scope){
    int i;
    symbolTable* p = scopeList;
    for(i=0; i<scope && p!=NULL; i++)  p = p->nextScope;
    while(p != NULL){
        p->visible = 0;
        p = p->nextInScope;
    }
}

void insertArgv(symbolTable* s, int funct, char* name, int scope, int line){
    symbolTable* p;
    int i;
    symbolTable* temp = (symbolTable*)malloc(sizeof(symbolTable));
    temp->visible = 1;
    temp->funct = funct;
    temp->name = (char*)malloc(strlen(name)*sizeof(char)+1);
    strcpy(temp->name,name);
    temp->type = 1;
    temp->scope = scope;
    temp->line = line;
    temp->argv = NULL;
    temp->scopespace = function_arguments;
    temp->offset     = formalArgOffset;
    temp->nextScope = NULL;
    temp->nextInScope = NULL;
    temp->next = NULL;

    p = s->argv;
    p = insertH(p,temp);
    s->argv = p;

    temp = (symbolTable*)malloc(sizeof(symbolTable));
    temp->visible = 1;
    temp->funct = funct;
    temp->name = (char*)malloc(strlen(name)*sizeof(char)+1);
    strcpy(temp->name,name);
    temp->type = 1;
    temp->scope = scope;
    temp->line = line;
    temp->argv = NULL;
    temp->scopespace = function_arguments;
    temp->offset     = formalArgOffset++;
    temp->nextScope = NULL;
    temp->nextInScope = NULL;
    temp->next = NULL;
    
    p = symT[hashCode(name)];
    p = insertH(p,temp);
    symT[hashCode(name)] = p;

    scopeList = insertScope(scopeList,temp);
}

char* printType(TYPE t){
    switch(t){
        case 0: return "Global Variable    ";
        case 1: return "Argument           ";
        case 2: return "Local Variable     ";
        case 3: return "Library Function   ";
        case 4: return "Programmer Function";
    }
}

void printHash(){
    int i;
    symbolTable* p;
    printf("HIDE\t\t|LINE\t\t|SCOPE\t\t|TYPE\t\t\t\t\t|NAME\n");
    printf(GREEN "---------------------------------------------------------------------------------------------------\n" RESET);
    for(i=0;i<HASHMAX;i++){
        p = symT[i];
        while(p != NULL){
            if(p->visible == 0)  printf("Hided   \t");
            else                 printf("Visibled\t");
            printf("|%d\t\t",p->line);  
            printf("|%d\t\t",p->scope); 
            printf("|%s\t\t\t",printType(p->type)); 
            printf("|%s \t  Scope space: %d , Offset: %d\n",p->name , p->scopespace , p->offset);
            p = p->next;
        }
    }
}

int findFunctionInScope(char * name , int scope){
    if(lookup(name , scope) == 0){
        return 0;
    }else{
        return 1;
    }
}


int check(char* name, int scope,int ret , int yylineno){
    if(ret == 1){
        if(lookup(name,scope) == -1){
            printf("ERROR: %s is Library Function.\n",name);
        }else if(lookup(name,scope) == 0){
            
            int i = scope; 
            int iffound = 0;
            while(i >= 0){
                   iffound = findFunctionInScope(name , i);  
                   if(iffound == 1) {
                       break;
                   }
                   i--;
            }
            if(iffound == 0) printf("ERROR: %s not decleared.\n",name);

        }else{
            /*Do nothing*/
            }
        }else{
            if(lookup(name,scope) == -1){
                printf("ERROR: %s is Library Function.\n",name);
            }else if(lookup(name,scope) == 1 && findNode(name , scope)->visible == 1){
                if(findNode(name , scope)->funct == 1) return 15;
            }else{
                if(scope == -1){
                    printf(RED"ERROR" RESET ": %s not defined in global scope!\n" , name);
                    return 0;
                }
                    insert(0,name,scope,yylineno);
            }
        }
        return 0;
}

int CheckIDinArgs(char* parameter , char* currentfunctionname , int scope){

    char colon[] = ":";
    char argvscope[50];
    strcpy(argvscope , currentfunctionname);
    strcat(argvscope , colon);
    strcat(argvscope , parameter);

    if(lookup(argvscope , scope) == 0){
        printf("Not Found %s\n" , argvscope);
        return 0;
    }else if(lookup(argvscope , scope) == 1){
        printf("Found %s\n" , argvscope);
        return 1;
    }
}


// char* createNameForVariable(char* var , char* currentfunctionname){
//     char colon[] = ":";
//     char argvscope[100];
//     strcpy(argvscope , currentfunctionname);
//     strcat(argvscope , colon);
//     strcat(argvscope , var);
//     return strdup(argvscope);

// }


char* pop(){
    functionStack* temp = stackF;
    if(stackF == NULL){
        return NULL;
    }
    char* name = temp->name;
    stackF = stackF->prev;
    free(temp);
    return name;
}

void push(char* name){
    functionStack* temp = (functionStack*)malloc(sizeof(functionStack));
    temp->name = (char*)malloc(strlen(name)*sizeof(char)+1);
    strcpy(temp->name,name);
    temp->prev = stackF;
    stackF = temp;
}

functionStack* top(){
    return stackF;
}

void printF(functionStack* h){
    if(h == NULL)   return;
    printf("%s\n" ,h->name);
    printF(h->prev);
}

int getStackSize(){
    int c = 0;
    functionStack* p = stackF;
    while(p != NULL){
        c++;
        p = p->prev;
    }
    return c;
}


int topin(ValuesStack* fromWhere){
    if(fromWhere == NULL) return -1;
    return fromWhere->value;
}

ValuesStack* popin(ValuesStack* fromWhere){
    if(fromWhere == NULL){
        return 0;
    }

    fromWhere = fromWhere->prev;
    /*free(temp);*/
    return fromWhere;
}

ValuesStack* pushin(ValuesStack* towhere , int value){
    ValuesStack* temp = (ValuesStack*)malloc(sizeof(ValuesStack));
    temp->value = value;
    temp->prev = towhere;
    return temp;
}

loop_stack* pushStack(loop_stack* stack, ValuesStack* list){
    loop_stack* temp = (loop_stack*)malloc(sizeof(loop_stack));
    temp->stack = list;
    temp->prev = stack;
    return temp;
}
loop_stack* popStack(loop_stack* stack){
    if (stack == NULL) return NULL;
    return stack->prev;
}
void pushF(int i){
    funcF* temp = (funcF*)malloc(sizeof(funcF));
    temp->value = i;
    temp->prev = funcf;
    funcf = temp;
}
int popF(){
    funcF* temp = (funcF*)malloc(sizeof(funcF));
    int i = funcf->value;
    temp = funcf;
    funcf = temp->prev;
    free(temp);
    return i;
}

void fordebug(){};