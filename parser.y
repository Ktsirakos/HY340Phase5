%{
    #include <stdio.h>
    #include "colors.h"
    #include <ctype.h>

    #define CP(x) printf("Checkpoint %s\n" , #x);
    #define PI(a,x) printf("Variable: %f\n" , x);

    int yyerror (char* yaccProvidedMessage);
    int yylex(void);
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;

    #include "SymbolTable.h"
    #include "instructions.h"

    expr* funcexpr;
%}

%start program

%token <stmtvalue>  BREAK
%token <stmtvalue>  CONTINUE
%token <stringvalue> AND
%token <stringvalue> OR
%token <stringvalue> NOT
%token <stringvalue>  ID
%token <stringvalue> LOCAL
%token <intvalue>   NUMBER
%token <stringvalue> STRING
%token <stringvalue> NIL
%token <stringvalue> TRUE
%token <stringvalue> FALSE
%token <stringvalue> IF
%token <stringvalue> ELSE
%token <stringvalue> WHILE
%token <stringvalue> FOR 
%token <stringvalue> RETURN
%token <stmtvalue> SEMICOLON
%token <stringvalue> FUNCTION
%token <stringvalue> DIVIDE
%token <stringvalue> DOT
%token <stringvalue> DOTx2
%token <stringvalue> ASSIGN          
%token <stringvalue> PLUS          
%token <stringvalue> MINUS           
%token <stringvalue> MUL           
%token <stringvalue> DE IDE          
%token <stringvalue> MODULO          
%token <stringvalue> EQ          
%token <stringvalue> NE             
%token <stringvalue> PLUSx2          
%token <stringvalue> MINUSx2         
%token <stringvalue> GT              
%token <stringvalue> LT              
%token <stringvalue> GE              
%token <stringvalue> LE 
%token <stringvalue> LEFTB
%token <stringvalue> RIGHTB
%token <stringvalue> LEFTSB
%token <stringvalue> RIGHTSB      
%token <stringvalue> LEFTPARENTHESIS
%token <stringvalue> RIGHTPARENTHESIS
%token <stringvalue> COMMA
%token <stringvalue> DOUBLEDOT
%token <stringvalue> DOUBLEDOTx2
%token <stringvalue> COMMENTLINE
%token <stringvalue> COMMENTMYLTY
%token <intvalue> INTEGER
%token <realvalue> REAL


%union {
    char*               stringvalue;
    int                 intvalue;
    double              realvalue;
    struct expr_type*        exprvalue;
    struct symbolTable*     symbol;
    struct for_pre*	    forvalue;
    struct stmt_list*   stmtvalue;
    struct quad_t*          quadvalue;
}

%right ASSIGN 
%left OR AND 
%nonassoc EQ NE
%nonassoc GT GE LT LE
%left PLUS MINUS MUL DIVIDE MODULO
%right NOT PLUSx2 MINUSx2 UMINUS
%left DOT DOUBLEDOT
%left  LEFTSB   RIGHTSB
%left LEFTPARENTHESIS RIGHTPARENTHESIS

%type <exprvalue> expr

%type <exprvalue>   lvalue
%type <exprvalue>   tableitem
%type <exprvalue>   primary
%type <exprvalue>   assignexpr
%type <exprvalue>   call
%type <exprvalue>   term
%type <exprvalue>   tablemake
%type <exprvalue>   const
%type <stringvalue> funcname
%type <intvalue>    funcbody
%type <symbol>      funcprefix
%type <symbol>      funcdef
%type <intvalue>    block
%type <exprvalue>   callsuffix
%type <exprvalue>   elist
%type <exprvalue>   normcall
%type <exprvalue>   methodcall
%type <exprvalue>   indexed
%type <exprvalue>   indexedelem
%type <intvalue>   ifprefix
%type <intvalue>   elsestmt
%type <intvalue>   else
%type <intvalue>    whilestmt
%type <intvalue>    whilecond
%type <intvalue>    whilestart
%type <intvalue>    N
%type <intvalue>    M
%type <forvalue>    forprefix
%type <stmtvalue>   stmt
%type <stmtvalue>   loopstmt
%type <stmtvalue>   error
%type <stmtvalue>   returnstmt
%type <stmtvalue>   forstmt
%type <stmtvalue>   ifstmt

%%

program:    stmt program
            | 
            ;

stmt:         expr SEMICOLON
            | ifstmt
            | whilestmt
            | forstmt
            | returnstmt { $$ = $1; }
            | BREAK SEMICOLON
                {
                    if(loopcounter == 0) {printf(RED"ERROR" RESET ": Cant break outside a loop\n"); error++;}
                    breaklist = pushin(breaklist,nextquadlabel()+1);
                    emit(jump,NULL,NULL,NULL,0,currQuad);
                }
            | CONTINUE SEMICOLON
                {
                    if(loopcounter == 0) {printf(RED"ERROR" RESET ": Cant continue outside a loop\n");   error++;}
                    int temp = conlist->toJump;
                    conlist = pushin(conlist,nextquadlabel()+1);
                    conlist->toJump = temp;
                    emit(jump,NULL,NULL,NULL,0,currQuad);
                }
            | block
            | funcdef
            | SEMICOLON
            | error SEMICOLON
            ;

        

expr:        assignexpr        {$$ = $1;}
            | expr PLUS   expr { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                                 emit(add , $1 , $3 , tempexpr , -1 , currQuad);
                                 $$ = tempexpr; 
                                 }
            | expr MINUS  expr { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                                 emit(sub , $1 , $3 , tempexpr , -1 , currQuad); 
                                 $$ = tempexpr;
                                 }
            | expr MUL    expr { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                                 emit(mul , $1 , $3 , tempexpr , -1 , currQuad); 
                                 $$ = tempexpr;
                                 }
            | expr DIVIDE expr { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                                 emit(div_code , $1 , $3 , tempexpr , -1 , currQuad); 
                                 $$ = tempexpr;
                                 }
            | expr MODULO expr { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                                 emit(mod , $1 , $3 , tempexpr , -1 , currQuad); 
                                 $$ = tempexpr;
                                 }
            | expr GT     expr { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                            
                                 tempexpr->truelist = pushin($$->truelist , nextquadlabel()+1);
                                 tempexpr->falselist = pushin($$->falselist , nextquadlabel() + 2);
                                
                                 emit(if_greater , $1 , $3 , tempexpr , -1 , currQuad); 
                                 emit(jump , NULL , NULL , NULL , 0 , currQuad);
                                 isRelatioNal = 1;
                                 $$ = tempexpr;

                                 }
            | expr GE     expr { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                            
                                 tempexpr->truelist = pushin($$->truelist , nextquadlabel()+1);
                                 tempexpr->falselist = pushin($$->falselist , nextquadlabel() + 2);
                                                                
                            
                                 emit(if_greatereq , $1 , $3 , tempexpr , -1 , currQuad); 
                                 emit(jump , NULL , NULL , NULL , 0 , currQuad); 
                                 isRelatioNal = 1;

                                 $$ = tempexpr;
                                 }
            | expr LT     expr { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                            
                                 tempexpr->truelist = pushin($$->truelist , nextquadlabel()+1);
                                 tempexpr->falselist = pushin($$->falselist , nextquadlabel() + 2);

                                 
                                 emit(if_less , $1 , $3 , tempexpr , -1 , currQuad);  
                                 emit(jump , NULL , NULL , NULL , 0 , currQuad);
                                 isRelatioNal = 1;

                                 $$ = tempexpr;
                                 }
            | expr LE     expr { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                            
                                 tempexpr->truelist = pushin($$->truelist , nextquadlabel()+1);
                                 tempexpr->falselist = pushin($$->falselist , nextquadlabel() + 2);

                                  
                            
                                 emit(if_lesseq , $1 , $3 , tempexpr , -1, currQuad);  
                                 emit(jump , NULL , NULL , NULL , 0 , currQuad);
                                 isRelatioNal = 1;

                                 $$ = tempexpr;
                                 }
            | expr EQ     expr { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                            
                                 tempexpr->truelist = pushin($$->truelist , nextquadlabel()+1);
                                 tempexpr->falselist = pushin($$->falselist , nextquadlabel() + 2);

                                  
                                 emit(if_eq , $1 , $3 , tempexpr , nextquadlabel()+3 , currQuad);  
                                 emit(jump , NULL , NULL , NULL , nextquadlabel()+4 , currQuad);
                                 isRelatioNal = 1;

                                 $$ = tempexpr;
                                 }
            | expr NE     expr { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol);  
                            
                                 tempexpr->truelist = pushin($$->truelist , nextquadlabel()+1);
                                 tempexpr->falselist = pushin($$->falselist , nextquadlabel() + 2);

                                 
                            
                                 emit(if_noteq , $1 , $3 , tempexpr , -1 , currQuad);  
                                 emit(jump , NULL , NULL , NULL , 0 , currQuad);
                                 isRelatioNal = 1;

                                 $$ = tempexpr;
                                 }
            | expr AND  M  expr {
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol);  
                            
                                 if(!($1->truelist || $1->falselist)){
                                      $1->truelist = pushin($1->truelist , nextquadlabel() + 1);
                                      $1->falselist = pushin($1->falselist , nextquadlabel() + 2);

                                     emit(if_eq,$1,newexpr_constbool(1),NULL ,0,currQuad);
                                     emit(jump , NULL , NULL , NULL , 0 , currQuad);
                                     $3 = $3 + 2;

                                 }

                                 if(!($4->truelist || $4->falselist)){
                                      $4->truelist = pushin($4->truelist , nextquadlabel() + 1);
                                      $4->falselist = pushin($4->falselist , nextquadlabel() + 2);

                                     emit(if_eq,$4,newexpr_constbool(1) ,NULL ,0,currQuad);
                                     emit(jump , NULL , NULL , NULL , 0, currQuad);

                                 }

                                 backpatch($1->truelist , $3);
                                 tempexpr->truelist = $4->truelist;
                                 tempexpr->falselist = merge($1->falselist , $4->falselist);
                                 backpatch($4->truelist, nextquadlabel()+1);
                                 backpatch(tempexpr->falselist,nextquadlabel()+3);
                                 isRelatioNal = 1;

                                 //emit(and , $1 , $4 , tempexpr , -1 , curruad); 
                                 $$ = tempexpr;
                                 }
            | expr OR   M  expr { 

                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 

                                 if(!($1->truelist || $1->falselist)){
                                      $1->truelist = pushin($1->truelist , nextquadlabel() + 1);
                                      $1->falselist = pushin($1->falselist , nextquadlabel() + 2);

                                     emit(if_eq,$1,newexpr_constbool(1),NULL ,0,currQuad);
                                     emit(jump , NULL , NULL , NULL , 0 , currQuad);
                                     $3 = $3 + 2;

                                 }

                                 if(!($4->truelist || $4->falselist)){
                                      $4->truelist = pushin($4->truelist , nextquadlabel() + 1);
                                      $4->falselist = pushin($4->falselist , nextquadlabel() + 2);

                                     emit(if_eq,$4,newexpr_constbool(1) ,NULL ,0,currQuad);
                                     emit(jump , NULL , NULL , NULL , 0, currQuad);

                                 }


                                 backpatch($1->falselist , $3);
                                 tempexpr->falselist = $4->falselist;
                                 tempexpr->truelist = merge($1->truelist , $4->truelist);
                                 backpatch($4->falselist, nextquadlabel() + 3);
                                 backpatch(tempexpr->truelist,nextquadlabel()+1);


                                 isRelatioNal = 1;

                                 //emit(or , $1 , $4 , tempexpr , -1 , currQuad); 
                                 $$ = tempexpr;
                                 }
            | term {  
                    $$ = $1;
                   }
            ;



term:         LEFTPARENTHESIS expr RIGHTPARENTHESIS { $$ = $2;}
            | MINUS expr %prec UMINUS
                {   /*
                    checkuminus($2);
                    $$ = newexpr(arithexpr_e);
                    $$->sym = newtemp();
                    $$->strConst = $$->sym->name;
                    emit(uminus,$2,$$,NULL,-1,currQuad);
                    */
                    symbolTable* symbol = newtemp();
                    expr* tempexpr = lvalue_expr(symbol); 
                    symbol = newtemp();
                    expr* minus1 = lvalue_expr(symbol);
                    minus1->numConst = -1;
                    minus1->strConst = "-1";
                    minus1->type = constnum_e;
                    emit(mul , $2 , minus1 , tempexpr , -1 , currQuad); 
                    $$ = tempexpr;
                }
            | NOT expr
                {
                    $$ = newexpr(arithexpr_e);
                    $$->sym = newtemp();
                    $$->strConst = $$->sym->name;

                    ValuesStack* temp = $$->falselist;
                    $$->falselist = $$->truelist;
                    $$->truelist = temp;

                    emit(not,$2,NULL,$$,-1,currQuad);
                }
            | PLUSx2 lvalue { 
                                int code = ultimateLookUpForVariables(&$2,var_e);
                                if(code == 0){
                                    printf(RED"ERROR" RESET ": %s undeclared\n" , $2->strConst);
                                    error++;
                                }
                            /*==========================================================*/

                                if($2->type == tableitem_e ){
                                    $$ = emit_iftableitem($2);
                                    emit(add,$$,newexpr_constnum(1),$$,-1,currQuad);
                                    emit(tablesetelem,$2,$2->index,$$,-1,currQuad);
                                }else{
                                    emit(add,$2,newexpr_constnum(1),$2,-1,currQuad);
                                    $$ = newexpr(arithexpr_e);
                                    $$->sym = newtemp(); 
                                    $$->strConst = $$->sym->name;
                                    emit(assign,$2,NULL,$$,-1,currQuad);
                                }
                            }
            | lvalue PLUSx2 {
                                int code = ultimateLookUpForVariables(&$1,var_e);
                                if(code == 0){
                                    printf(RED"ERROR" RESET ": %s undeclared\n" , $1->strConst);
                                    error++;
                                }
                            /*==========================================================*/
                                $$ = newexpr(var_e);
                                $$->sym = newtemp();
                                $$->strConst = $$->sym->name;

                                if($1->type == tableitem_e ){
                                    expr* value = emit_iftableitem($1);
                                    emit(assign,value,NULL,$$,-1,currQuad);
                                    emit(add,value,newexpr_constnum(1),value,-1,currQuad);
                                    emit(tablesetelem,$1,$1->index, value,-1,currQuad);
                                }else{
                                    emit(assign,$1,NULL,$$,-1,currQuad);
                                    emit(add,$1,newexpr_constnum(1),$1,-1,currQuad);
                                }
                            }
            | MINUSx2 lvalue {
                                int code = ultimateLookUpForVariables(&$2,var_e);
                                if(code == 0){
                                    printf(RED"ERROR" RESET ": %s undeclared\n" , $2->strConst);
                                    error++;
                                }
                             /*==========================================================*/
                                if($2->type == tableitem_e ){
                                    $$ = emit_iftableitem($2);
                                    emit(sub,$$,newexpr_constnum(1),$$,-1,currQuad);
                                    emit(tablesetelem,$2,$2->index,$$,-1,currQuad);
                                }else{
                                    emit(sub,$2,newexpr_constnum(1),$2,-1,currQuad);
                                    $$ = newexpr(arithexpr_e);
                                    $$->sym = newtemp(); 
                                    $$->strConst = $$->sym->name;
                                    emit(assign,$2,NULL,$$,-1,currQuad);
                                }
                            }
            | lvalue MINUSx2 {
                                int code = ultimateLookUpForVariables(&$1,var_e);
                                if(code == 0){
                                    printf(RED"ERROR" RESET ": %s undeclared\n" , $1->strConst);
                                    error++;
                                }
                             /*==========================================================*/
                                $$ = newexpr(var_e);
                                $$->sym = newtemp();
                                $$->strConst = $$->sym->name;

                                if($1->type == tableitem_e ){
                                    expr* value = emit_iftableitem($1);
                                    emit(assign,value,NULL,$$,-1,currQuad);
                                    emit(sub,value,newexpr_constnum(1),value,-1,currQuad);
                                    emit(tablesetelem,$1,$1->index, value,-1,currQuad);
                                }else{
                                    emit(assign,$1,NULL,$$,-1,currQuad);
                                    emit(sub,$1,newexpr_constnum(1),$1,-1,currQuad);
                                }
                            }
            | primary { 
                   /* symbolTable* symbol = newtemp();
                    expr* tempexpr = lvalue_expr(symbol);  
                            
                    tempexpr->truelist = pushin($$->truelist , nextquadlabel()+1);
                    tempexpr->falselist = pushin($$->falselist , nextquadlabel() + 2);

                    emit(if_eq , $1 , newexpr_constbool(1) , tempexpr , -1 , currQuad);  
                    emit(jump , NULL , NULL , NULL , 0 , currQuad);

                    $$ = tempexpr; */

                    $$ = $1;
                    }
            ;

assignexpr:   lvalue ASSIGN  {
                                if(lookup($1->strConst, 0) == -1){
                                    printf(RED"ERROR" RESET ": libfunction %s used as an l-value\n" , $1->strConst);
                                    found_error = 1;
                                    error++;
                                }
                                if(!found_error){
                                    if(globalscope == 1){
                                       if(lookup($1->strConst , 0) == 0){
                                           printf(RED"ERROR" RESET ": %s undeclared at global scope\n" , $1->strConst);
                                               error++;
                                       }else if(lookup($1->strConst , 0) == 1){
                                            if(findNode($1->strConst , 0)->funct == 1){
                                                printf(RED"ERROR" RESET ": programm function %s used as an l-value\n" , $1->strConst);
                                                error++;
                                            }else{
                                                $1->sym = findNode($1->strConst,0);
                                            }
                                        }
                                        globalscope = 0;
                                    }else{
                                        int code = ultimateLookUpForVariables(&$1,var_e);
                                        if(code == 0){
                                            insert(0 , $1->strConst , Cscope , yylineno);
                                            $1->sym = findNode($1->strConst , Cscope);
                                            $1->type = var_e;
                                        }
                                    }
                                }
                                rightSideValue = 1;
                            }
                            expr {

                                if(isRelatioNal == 1){
                                    backpatch($4->falselist , nextquadlabel() + 3);
                                    backpatch($4->truelist , nextquadlabel() + 1);
                                    emit(assign , newexpr_constbool(1) , NULL , $4 , -1 , currQuad);
                                    emit(jump   , NULL , NULL , NULL , nextquadlabel() + 3 , currQuad);
                                    emit(assign , newexpr_constbool(0) , NULL , $4 , -1 , currQuad);
                                    isRelatioNal = 0;
                                }
                                
                                rightSideValue = 0;
                               if($1->type == tableitem_e){
                                    emit(tablesetelem,$1->table,$1->index,$4,-1,currQuad);
                                    $$ = emit_iftableitem($1);
                                    $$->type = assignexpr_e;
                                }else{

                                    //printf("%s %d\n ", $1->strConst , $1->type);
                                    //printf("Checking %s %d\n" , $4->strConst , $4->type);
                                    $1->type = $4->type;
                                    emit(assign,$4,NULL,$1,-1,currQuad);
                                    $$ = newexpr(assignexpr_e);
                                    $$->sym = newtemp();
                                    $$->strConst = $$->sym->name;
                                    
                                    //printf("%s %d\n ", $1->strConst , $1->type);
                                    //printf("Checking %s %d\n" , $4->strConst , $4->type);
                                    expr* temp = $4;
                                    if($4->type == newtable_e)   {
                                        $$->type = newtable_e;
                                        $1->type = newtable_e;
                                        $$->sym->table = 1; //------------------
                                        $1->sym->table = 1;
                                        printf("%s got type %d\n" , $$->sym->name , $$->sym->table);
                                    }
                                    
                                    else if($4->type == tableitem_e) $$->type = tableitem_e; //----------------
                                    else if($4->type == newtable_e) $$->type = newtable_e;
                                    else $1->type = var_e;  //---------------
                                    
                                    emit(assign,$1,NULL,$$,-1,currQuad);
                                }

                            }

            ;

lvalue:       ID                    {
                                        expr* temp = (expr*)malloc(sizeof(expr));
                                        temp->strConst = strdup($1);
                                        temp->sym = findNode($1,Cscope);
                                        temp->type = var_e;
                                        $$ = temp;
                                    }
            | LOCAL ID              {
                                            if(lookup($2 , 0) == -1){
                                                 printf(RED"ERROR" RESET ": libfunction %s used as an l-value\n" , $2);
                                                 found_error = 1;
                                                 error++;
                                            }else if(lookup($2 , Cscope) == 0){
                                                insert(0 , $2 , Cscope , yylineno);
                                                found_local = 1;
                                                $$ = lvalue_expr(findNode($2,Cscope));
                                            }else if(findNode($2 , Cscope)->funct == 1){
                                                 printf(RED"ERROR" RESET ": %s declared as function in this scope\n" , $2);
                                                 found_error = 1;
                                                 error++;
                                            }else{
                                                $$ = lvalue_expr(findNode($2,Cscope));
                                            }
                                    }
            | DOUBLEDOTx2 ID        {
                                        globalscope = 1;
                                        expr* temp = (expr*)malloc(sizeof(expr));
                                        temp->strConst = strdup($2);
                                        $$ = temp;
                                    }
            | tableitem             {
                                        $$ = $1;
                                    }
            ;

tableitem:       lvalue DOT ID      {
                    if(!found_error){
                        if(lookup($1->strConst , 0) == -1){
                            printf(RED"ERROR" RESET ": libfunction %s used as an l-value\n" , $1->strConst);
                            error++;
                        }else if(globalscope == 1){
                            if(lookup($1->strConst , 0) == 0){
                                printf(RED"ERROR" RESET ": %s undeclared at global scope\n" , $1->strConst);
                                    error++;
                            }else if(lookup($1->strConst , 0) == 1){
                                 if(findNode($1->strConst , 0)->funct == 1){
                                     printf(RED"ERROR" RESET ": programm function %s used as an l-value\n" , $1->strConst);
                                     error++;
                                 }else{
                                    $1->sym = findNode($1->strConst,0);
                                 }
                            }   
                            globalscope = 0;
                        }else{
                            int code = ultimateLookUpForVariables(&$1,newtable_e);
                            if(code == 0){
                                printf(RED"ERROR" RESET ": %s undeclared\n" , $1->strConst);
                                error++;
                            }
                        }
                    }
                    if($1->sym != NULL){
                        /*if($1->type == var_e){
                            $1->type = newtable_e;
                            $1->strConst = $1->sym->name;
                            emit(tablecreate,$1,NULL,NULL,-1,currQuad);
                        }*/
                        $$ = member_item($1,$3);
                    }else{error++;}
                                    }

            | lvalue LEFTSB expr RIGHTSB{
                    if(!found_error){
                        if(lookup($1->strConst , 0) == -1){
                            printf(RED"ERROR" RESET ": libfunction %s used as an l-value\n" , $1->strConst);
                            error++;
                        }else if(globalscope == 1){
                            if(lookup($1->strConst , 0) == 0){
                                printf(RED"ERROR" RESET ": %s undeclared at global scope\n" , $1->strConst);
                                    error++;
                            }else if(lookup($1->strConst , 0) == 1){
                                 if(findNode($1->strConst , 0)->funct == 1){
                                     printf(RED"ERROR" RESET ": programm function %s used as an l-value\n" , $1->strConst);
                                     error++;
                                 }else{
                                    $1->sym = findNode($1->strConst,0);
                                 }
                            }
                            globalscope = 0;
                        }else{
                            int code = ultimateLookUpForVariables(&$1,newtable_e);
                            if(code == 0){
                                printf(RED"ERROR" RESET ": %s undeclared\n" , $1->strConst);
                                error++;
                            }
                        }
                    }                         
                    if($1->sym != NULL){
                        $1->index = $3;
                        $1 = emit_iftableitem($1);
                        if($1->type != tableitem_e){
                            $1->table = malloc(sizeof(expr));
                            $1->table->type = $1->type;
                            $1->table->strConst = $1->strConst;
                            $1->table->index = $1->index;
                            $1->table->sym = $1->sym;
                        }
                        $$ = $1;
                        $$->type = tableitem_e;
                    }else{error++;}
                }
            | call DOT ID   {
                                expr* temp = (expr*)malloc(sizeof(expr));
                                temp->strConst = strdup($3);
                                temp->sym = findNode($3,Cscope);
                                $$ = temp;
                            }
            | call LEFTSB expr RIGHTSB
            ;

call:         call LEFTPARENTHESIS elist RIGHTPARENTHESIS
                {
                    $$ = make_call($1 , $3);
                }
            | lvalue  callsuffix {
                                        if(lookup($1->strConst , 0) == -1){
                                            $1->type = libraryfunc_e;
                                            $1->sym = findNode($1->strConst , 0);
                                        }else{
                                                if(!found_error){
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
                                                        symbolTable* symTemp;
                                                        int haveAccess = 0;
                                                        for(i = 0; i <= numberofblock; i++){
                                                            if(found_local){
                                                                if(lookup($1->strConst , Cscope) == 1){
                                                                    symTemp = findNode($1->strConst , Cscope);
                                                                    haveAccess = 1;
                                                                }
                                                                found_local = 0;
                                                                break;
                                                            }else if(lookup($1->strConst , Cscope - i) == 1){
                                                                symTemp = findNode($1->strConst , Cscope - i);
                                                                haveAccess = 1;
                                                                break;
                                                            }else if(i == numberofblock){
                                                                if(lookup($1->strConst , 0) == 1){
                                                                    symTemp = findNode($1->strConst , 0);
                                                                    haveAccess = 1;
                                                                }
                                                            }
                                                        }
                                                        if(haveAccess){
                                                            if($1->sym == NULL){
                                                                $1->sym = symTemp;
                                                                printf("callsufix %s %d\n" , $1->sym->name , $1->type);
                                                                if($1->sym->funct == 1){
                                                                    $1->type = programfunc_e;
                                                                }
                                                            }
                                                        }else{
                                                            printf("callsufix %s %d\n" , $1->sym->name , $1->type);
                                                            int NotAccess = 0;
                                                            for(i = 1; i <= Cscope-numberofblock; i++){
                                                                if(lookup($1->strConst , i) == 1){
                                                                    NotAccess = 1;
                                                                }
                                                            }
                                                            if(NotAccess){
                                                                printf(RED"ERROR" RESET ": %s not accessible\n" , $1->strConst);
                                                                error++;
                                                            }else{
                                                                printf(RED"ERROR" RESET ": %s undeclared\n" , $1->strConst);
                                                                error++;
                                                            }
                                                        }
                                        }else{
                                            found_error = 0;
                                        }
                                    }
                            /*========================================================*/
                            /*
                                if($1->sym->table == 1){    //--------
                                    $1->type = newtable_e;  //---------
                                  }                           //----------
                            
                                */
                                if($2->boolConst){
                                    expr* self;
                                    self = $1;
                                    $1 = emit_iftableitem(member_item(self,$2->strConst));
                                    self->next = $2->next;
                                    $2->next = self;
                                }
                                if($1->type != libraryfunc_e){
                                    expr* temp = $1;
                                    if($1->sym->table == 1 && $1->sym->type != 4){
                                        $1->type = tableitem_e;
                                        fordebug();
                                        expr* temp = $1;
                                        $1->next = $2->next;
                                        $2->next = temp;
                                    
                                    }else{
                                        $1->type = programfunc_e;
                                    }
                                }
                                $1 = emit_iftableitem($1);
                                $$ = make_call($1, $2->next);
                            }
            | LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS
                {
                    expr* func = newexpr(programfunc_e);
                    func->sym = $2;
                    func->strConst = func->sym->name;
                    $$ = make_call(func , $5);
                }
            ;

primary:     lvalue {
                    if(!found_error){
                        if(globalscope == 1){
                            if(lookup($1->strConst , 0) == 0){
                                printf(RED"ERROR" RESET ": %s undeclared at global scope\n" , $1->strConst);
                                error++;
                            }else{
                                $1->sym = findNode($1->strConst,0);
                            }
                            globalscope = 0;
                        }else{
                            int code = ultimateLookUpForVariables(&$1,var_e);
                            if(code == 0){
                                insert(0 , $1->strConst , Cscope , yylineno);
                                $1->sym = findNode($1->strConst , Cscope);
                                $1->type = var_e;
                            }
                        }
                        $$ = $1;
                    }
                    $$ = emit_iftableitem($1);
                } 
            | call 
            | tablemake{$$ = $1;}
            | LEFTPARENTHESIS funcdef RIGHTPARENTHESIS
                {
                    $$ = newexpr(programfunc_e);
                    $$->sym = $2;
                    $$->strConst = $$->sym->name;
                }
            | const {$$ = $1;}
            ;




callsuffix:   normcall 
                {
                    $$ = $1;
                }
            | methodcall
                {
                    $$ = $1;
                }
            ;

normcall:     LEFTPARENTHESIS elist RIGHTPARENTHESIS 
                {
                    $$ = calls($2,0,NULL);
                }
            ;

methodcall:    DOTx2 ID LEFTPARENTHESIS elist RIGHTPARENTHESIS //equivalent to lvalue ID(lvalue , elist)
                {
                    $$ = calls($4,1,$2);
                }
            ;
        

elist:        expr
                {
                    $1->next = NULL;
                    $$ = $1;
                }
            | elist COMMA expr
                {
                    $3->next = $1;
                    /*
                    $3->next = NULL;
                    expr* temp = $1;
                    while(temp->next != NULL)   temp = temp->next;
                    temp->next = $3;*/
                    $$ = $3;
                }
            | {$$ = NULL;}
            ;


tablemake:    LEFTSB elist RIGHTSB
                {
                    
                    expr* x = $2;
                    expr* t = newexpr(newtable_e);
                    t->sym = newtemp();
                    t->strConst = t->sym->name;
                    emit(tablecreate,t,NULL,NULL,-1,currQuad);
                    int i=0;
                    while(x != NULL){
                        t->table = t;
                        emit(tablesetelem,t,newexpr_constnum(i++),x,-1,currQuad);
                        x = x->next;
                    }
                    $$ = t;
                }
            | LEFTSB indexed RIGHTSB
                {
                    expr* x = $2;
                    expr* t = newexpr(newtable_e);
                    t->sym = newtemp();
                    t->strConst = t->sym->name;
                    emit(tablecreate,t,NULL,NULL,-1,currQuad);
                    while(x != NULL){
                        t->table = t;
                        emit(tablesetelem,t,x->index,x,-1,currQuad);
                        x = x->next;
                    }
                    $$ = t;
                }
            ;

indexed:    indexedelem
                {
                    $$ = $1;
                }
            | indexed COMMA indexedelem
                {
                    expr* temp = $1;
                    while(temp->next != NULL){
                        temp = temp->next;
                    }
                    temp->next = $3;
                    $$ = $1;
                }
            ;

              
indexedelem:  LEFTB expr DOUBLEDOT {rightSideValue = 1;} expr RIGHTB
                {
                    rightSideValue = 0;
                    $5->index = $2;
                    $5->next = NULL;
                    $$ = $5;
                }
            ;
/*
block_stmt: stmt
            | block_stmt stmt
            | 
            ;
*/         
block_stmt:    block_stmt stmt
            | 
            ;

block:        LEFTB { if(isFuncBlock != 0) {
                            Cscope++; 
                            if(getStackSize() < Cscope){
                                push("_$block");
                            }
                        } 
                    } block_stmt RIGHTB {
                                            if(isFuncBlock != 0){
                                                hide(Cscope);
                                                Cscope--;
                                                funcexpr = (expr*)malloc(sizeof(expr));
                                                funcexpr = lvalue_expr(findNode(pop(),Cscope));
                                                }
                                        };

funcname:       ID { $$ = $1;}
                |  { $$ = newtempfuncname(); }
                ;

funcprefix:     FUNCTION funcname {
                                        $$ = findNode($2 , Cscope);  
                                         if($$ == NULL){
                                             insert(1 , $2 , Cscope , yylineno);
                                             $$ = findNode($2 , Cscope);
                                             functionNode = $$;
                                         }else{
                                                if($$->type == 3) printf(RED"ERROR" RESET ": %s already defined as an libfunct\n" ,$1);
                                                else printf(RED"ERROR" RESET ": %s already defined\n" , $2);
                                                found_error = 1;
                                                error++;
                                              }
                                        

                                        funcname_string = strdup($2);

                                        //emit(jump , NULL , NULL , NULL , -1 , currQuad);
                                        //funcJumpToPatch = currQuad;
                                        emit(functstart , lvalue_expr($$) , NULL , NULL , -1 , currQuad);
                                        forfunctionsLocalStack = pushin(forfunctionsLocalStack , functionLocalOffset);
                                        forfunctionsScopeSpace = pushin(forfunctionsScopeSpace , currscopespace());
                                        resetScopeSpace();
                                        enterscopespace();
                                        resetformalargsoffset();
                                        
                                    };

funcargs:     LEFTPARENTHESIS {Cscope++; } idlist RIGHTPARENTHESIS {
                                    Cscope--;
                                    push(functionNode->name); 
                                    enterscopespace();
                                    resetfunctionlocaloffset();
                               };


funcblockstart: {forloops = pushin(forloops,loopcounter);   loopcounter = 0;    isFuncBlock++;}
funcblockend:   { loopcounter = topin(forloops); forloops = popin(forloops); isFuncBlock--;}

funcbody:    funcblockstart block funcblockend {
                        emit(functend , funcexpr , NULL , NULL , -1 , currQuad);
                        //printf("CUrrequad : %d\n" , currQuad);
                        //quads[funcJumpToPatch - 1].label = currQuad + 1;

                        functionLocalsToSym = functionLocalOffset;
                        functionLocalOffset = topin(forfunctionsLocalStack);
                        forfunctionsLocalStack = popin(forfunctionsLocalStack);
                        
                         
                        scopespace = topin(forfunctionsScopeSpace);
                        forfunctionsScopeSpace = popin(forfunctionsScopeSpace);
                    };


funcdef:      funcprefix funcargs funcbody 
               {
                    
                        $$->totallocals = functionLocalsToSym;
                        if(found_error == 1) found_error = 0;
                        $$ = $1;
               }   
             ;


const:        INTEGER { 
                        expr* dummy = (expr*) malloc(sizeof(expr));
                        char number[30];
                        dummy->numConst = $1;
                        dummy->type = constnum_e;
                        sprintf(number,"%d",$1);
                        dummy->strConst = strdup(number);
                        $$ = dummy;
                      }
            | REAL    { 
                        expr* dummy = (expr*) malloc(sizeof(expr));
                        char number[30];
                        dummy->numConst = $1;
                        dummy->type = constnum_e;
                        sprintf(number,"%3f",$1);
                        dummy->strConst = strdup(number);
                        $$ = dummy;
                      }
            | STRING  {
                        struct expr_type* dummy = (expr*) malloc(sizeof(expr));
                        dummy->type = conststring_e;
                        dummy->strConst = strdup($1);
                        $$ = dummy;
                      }
            | NIL     { 
                        struct expr_type* dummy = (expr*) malloc(sizeof(expr));
                        dummy->type == nil_e;
                        dummy->boolConst = (unsigned char)0;
                        dummy->strConst = "null";
                        $$ = dummy;
                      }
            | TRUE    { 
                        struct expr_type* dummy = (expr*) malloc(sizeof(expr));
                        dummy->type = constbool_e;
                        dummy->boolConst = 1;
                        dummy->strConst = "true";
                        $$ = dummy;
                      }
            | FALSE   { 
                        struct expr_type* dummy = (expr*) malloc(sizeof(expr));
                        dummy->type = constbool_e;
                        dummy->boolConst = 0;
                        dummy->strConst = "false";
                        $$ = dummy;
                      };

 idlist:      ID                {
                                    if(!found_error){
                                        if(lookup($1 , Cscope) == -1){
                                            printf(RED"ERROR " RESET ": Argument %s is a libfunc\n" , $1);
                                        }else{

                                            int code = lookup($1 , Cscope);
                                            if(code == 0){
                                                insertArgv(functionNode ,
                                                        0 , 
                                                        $1,
                                                        Cscope,
                                                        yylineno
                                                        );
                                            }else if(code == 1){
                                                printf(RED"ERROR " RESET ": function argument %s redefined!\n" , $1);
                                            }
                                        }
                                    }
                                }

            | idlist COMMA ID   {
                                    if(!found_error){
                                        if(lookup($3 , Cscope) == -1){
                                            printf(RED"ERROR: " RESET "Argument %s is a libfunc\n" , $3);
                                        }else{


                                            int code = lookup($3 , Cscope);
                                            if(code == 0){
                                                insertArgv(functionNode ,
                                                        0 , 
                                                        $3,
                                                        Cscope,
                                                        yylineno
                                                        );
                                            }else if(code == 1){
                                                printf(RED"ERROR: " RESET "function argument %s redefined!\n" , $3);
                                            }
                                        }                                                                              
                                    }
                                }
            | /* empty */



ifprefix:   IF LEFTPARENTHESIS expr  RIGHTPARENTHESIS    
            {
                if(isRelatioNal == 1){
                    backpatch($3->falselist , nextquadlabel() + 3);
                    backpatch($3->truelist , nextquadlabel() + 1);
                    emit(assign , newexpr_constbool(1) , NULL , $3 , -1 , currQuad);
                    emit(jump   , NULL , NULL , NULL , nextquadlabel() + 3 , currQuad);
                    emit(assign , newexpr_constbool(0) , NULL , $3 , -1 , currQuad);
                    isRelatioNal = 0;
                }

                emit(if_eq , $3 , newexpr_constbool(1),NULL,nextquadlabel() + 3,currQuad);
                $$ = nextquadlabel()+1;
                emit(jump , NULL , NULL , NULL , 0 , currQuad);
            }
else:       ELSE{   emit(jump,NULL,NULL,NULL,0,currQuad);
                    $$ = nextquadlabel();
                }            

elsestmt:   else {pushF(isFuncBlock);isFuncBlock=0;} stmt {isFuncBlock = popF();  $$ = $1;}
            |           {$$ = 0;}
            ;

ifstmt:     ifprefix { pushF(isFuncBlock); isFuncBlock=0;} stmt {
                            isFuncBlock = popF();
                            patchlabel($1,nextquadlabel()+1);
                          } elsestmt{
                              if($5 != 0){
                                  patchlabel($1,$5+1);
                                  patchlabel($5,nextquadlabel()+1);
                              }
                          } ;

whilestart: WHILE {
                    if(breaklist != NULL){
                        breakStack = pushStack(breakStack,breaklist);
                    }
                    ValuesStack* dummy = (ValuesStack*)malloc(sizeof(ValuesStack));
                    dummy->value = -1;
                    dummy->prev = NULL;
                    breaklist = dummy;
                    if(conlist != NULL){
                        conStack = pushStack(conStack,conlist);
                    }
                    dummy = (ValuesStack*)malloc(sizeof(ValuesStack));
                    dummy->value = -1;
                    dummy->prev = NULL;
                    conlist = dummy;

                    toJumpexpr = nextquadlabel() +1;
                  }


whilecond: LEFTPARENTHESIS expr RIGHTPARENTHESIS {
                    if(isRelatioNal == 1){
                        backpatch($2->falselist , nextquadlabel() + 3);
                        backpatch($2->truelist , nextquadlabel() + 1);
                        emit(assign , newexpr_constbool(1) , NULL , $2 , -1 , currQuad);
                        emit(jump   , NULL , NULL , NULL , nextquadlabel() + 3 , currQuad);
                        emit(assign , newexpr_constbool(0) , NULL , $2 , -1 , currQuad);
                        isRelatioNal = 0;
                    }

                    emit(if_eq , $2 , newexpr_constbool(1) , NULL ,  nextquadlabel() + 3 , currQuad);
                    //$$ = $2;
                    conlist->toJump = toJumpexpr;
                    emit(jump , NULL , NULL , NULL , 0 , currQuad);
                    breaklist = pushin(breaklist,nextquadlabel());
            }

loopstart:  {++loopcounter;}
loopend:    {--loopcounter;}
loopstmt:   loopstart {pushF(isFuncBlock); isFuncBlock=0;} stmt {isFuncBlock = popF();} loopend{$$ = $3;};

whilestmt: whilestart whilecond loopstmt 
            {
                emit(jump , NULL , NULL , NULL , conlist->toJump , currQuad);
                
                ValuesStack* temp = breaklist;
                while(temp->value != -1){
                    patchlabel(temp->value, nextquadlabel()+1);
                    temp = temp->prev;
                }

                temp = conlist;
                while(temp->value != -1){
                    patchlabel(temp->value, temp->toJump);
                    temp = temp->prev;
                }
                if(breakStack != NULL){
                    breaklist = breakStack->stack;
                    breakStack = popStack(breakStack);
                }
                if(conStack != NULL){
                    conlist = conStack->stack;
                    conStack = popStack(conStack);
                }
                toJumpexpr = -1;
            }

N:          {$$ = nextquadlabel()+1; emit(jump,NULL,NULL,NULL,0,currQuad);}
M:          {$$ = nextquadlabel()+1;}

forprefix:  FOR LEFTPARENTHESIS elist SEMICOLON M expr SEMICOLON
            {
                if(isRelatioNal == 1){
                        backpatch($6->falselist , nextquadlabel() + 3);
                        backpatch($6->truelist , nextquadlabel() + 1);
                        emit(assign , newexpr_constbool(1) , NULL , $6 , -1 , currQuad);
                        emit(jump   , NULL , NULL , NULL , nextquadlabel() + 3 , currQuad);
                        emit(assign , newexpr_constbool(0) , NULL , $6 , -1 , currQuad);
                        isRelatioNal = 0;
                }
                for_pre* temp = (for_pre*)malloc(sizeof(for_pre));

                if(breaklist != NULL){
                    breakStack = pushStack(breakStack,breaklist);
                }
                ValuesStack* dummy = (ValuesStack*)malloc(sizeof(ValuesStack));
                dummy->value = -1;
                dummy->prev = NULL;
                breaklist = dummy;
                if(conlist != NULL){
                    conStack = pushStack(conStack,conlist);
                }
                dummy = (ValuesStack*)malloc(sizeof(ValuesStack));
                dummy->value = -1;
                dummy->prev = NULL;
                conlist = dummy;
                
                temp->toExpr = $5;
                temp->enter = nextquadlabel()+1;
                emit(if_eq,$6,newexpr_constbool(1),NULL,0,currQuad);
                $$ = temp;
            }

forstmt:    forprefix N elist RIGHTPARENTHESIS N loopstmt N
            {
                conlist->toJump = $2+1;
                patchlabel($1->enter, $5+1);
                patchlabel($2, nextquadlabel()+1);
                patchlabel($5,$1->toExpr);
                patchlabel($7,$2+1);

                ValuesStack* temp = breaklist;
                while(temp->value != -1){
                    patchlabel(temp->value, nextquadlabel()+1);
                    temp = temp->prev;
                }
                temp = conlist;
                while(temp->value != -1){
                    patchlabel(temp->value, temp->toJump);
                    temp = temp->prev;
                }
                if(breakStack != NULL){
                    breaklist = breakStack->stack;
                    breakStack = popStack(breakStack);
                }
                if(conStack != NULL){
                    conlist = conStack->stack;
                    conStack = popStack(conStack);
                }

                /*
                patchlabel($6->breaklist->value,nextquadlabel()+1);
                patchlabel($6->conlist->value,$2+1);    */
            }
returnstmt:   RETURN{ 
                        ret = 1; 
                        if(top() == NULL){
                                printf(RED"ERROR" RESET ": Can't return outside a function!\n");   
                                found_error = 1;
                                error++;
                        }
                    }expr SEMICOLON{
                        if($3->type == newtable_e){
                            symbolTable* temp; //--------------------
                            temp = findNode(top()->name , Cscope - 1);      //-------------------
                            temp->table = 1;        //-----------------
                        }
                        emit(ret_code,$3,NULL,NULL,-1,currQuad);
                        $$ = $3;
                        ret = 0;
                    }
            | RETURN SEMICOLON      {
                                        if(top() == NULL){
                                            printf(RED"ERROR" RESET ": Can't return outside a function!\n");   
                                            found_error = 1;
                                            error++;
                                        }
                                        emit(ret_code,NULL,NULL,NULL,-1,currQuad);
                                    }
            ;


%%

int yyerror (char* yaccProvidedMessage){ fprintf(stderr , RED"Fatal" RESET " %s in line %d\n" , yaccProvidedMessage , yylineno); error++;}

int main(int argc , char** argv){
    
    initHashTable();

    if(argc > 1){
        if(!(yyin = fopen(argv[1] , "r"))) {
            fprintf(stderr , "Cannot read file: %s\n" , argv[1]);
            return 1;
       }
    }else{
        yyin = stdin;
    }
    
    initialize_Arrays();
    yyparse(); 
    emit(program_end,NULL,NULL,NULL,-1,currQuad);
    if(error>0){
        printf(RED"Compile failed" RESET " with %d error "GREEN"NOOB"RESET" (Νατάσα όχι για σένα.)\n",error);
    }else{
        printQuads();
            ;
        generate();
        printf("----------------------------------------------------------------------------------\n");
        printInst();
        printHash();
        printArrays();
        writeBinaryFile();
    }
    return 0;
}
