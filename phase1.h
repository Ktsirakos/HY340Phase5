
void print(alpha_token_t* x){
    if(x==NULL) return;
    fprintf(file,"%d:\t\t#%d\t\t\"%s\"\t\t\t%s\n",x->line,x->id,x->name,x->type);
    print(x->next);
}


alpha_token_t* insert2(alpha_token_t* x, alpha_token_t* head){
    assert(x!=NULL);
    if(head == NULL) {
        return x;
    }
    x->id++;
    head->next = insert2(x,head->next);
    return head;
}


void makeToken(int line, char* name, char* type,  alpha_token_t* temp){
    assert(name != NULL);
    assert(type != NULL);

    temp->id = 1;
    temp->line = line;
    temp->name = (char*)malloc(strlen(name)*sizeof(char)+1);
    strcpy(temp->name,name);
    temp->type = (char*)malloc(strlen(type)*sizeof(char)+1);
    strcpy(temp->type,type);
    temp->next = NULL;
}


void printSymT(void){
    print(symT);
}

/*STRING*/
int parseString(alpha_token_t* yylval){
    int c = input();
    char s[6000];
    int startline = 0;
    int i=0;
    startline = yylineno;
    while(c != '\"' && c != EOF){
        if(c == '\\'){
            c = input();
            switch (c){
                case 'a':   s[i++]='\a'; break;
                case 'b':   i--; break;
                case 't':   s[i++]='\t'; break;
                case 'n':   s[i++]='\n'; break;
                case 'v':   s[i++]='\v'; break;
                case 'f':   s[i++]='\f'; break;
                case 'r':   s[i++]='\r'; break;
                case '\"':  s[i++]='\"'; break;
                case '\'':  s[i++]='\''; break;
                case '?':   s[i++]='\?'; break;
                case '\\':  s[i++]='\\'; break;
                default:    unput(c);  printf("WARNING: Invalid escape char: \\%c\n" , c); break;
            }
        }else   s[i++]=c;
        c = input();
    }

    if(c == EOF){
        printf("ERROR: Unclosed String in line %d!\n" , startline);
        return UNCLOSED_STRING;
    }

    s[i++]='\0';
    makeToken(yylineno , s , "STRING" , yylval);
    return 0;
}

/*COMMENTS*/

void commentLine(alpha_token_t* yylval){
    int startline = yylineno;
    char c = input();
    while(c != '\n' && c != EOF){
        c = input();
    }

   /* makeToken(startline , "-" , "SINGLE LINE COMMENT" , yylval);*/
}

int commentMulty(alpha_token_t* yylval){
    /*makeToken(yylineno , "-" , "MULTYLINE COMMENT STARTS" , yylval);*/
    char c = input();
    char s[10240];
    int i = 0;
    while(1){
        if(c == '*'){
            c = input();
            if(c == '/') break;
            s[i++] = '*';
            unput(c);
        }else  c = input();
    }
    s[i++] = '\0';
    /*makeToken(yylineno , "-" , "MULTYLINE COMMENT ENDS" , yylval);*/
}


void up(int code){
    if(code == 1){
        parenthesis++;
        if(parenthesis == 1) pline = yylineno;
    }else if(code == 2){
        brackets++;
        if(brackets == 1) bline = yylineno;
    }else if(code == 3){
        sbrackets++;
        if(sbrackets == 1) sbline = yylineno;
    }
}

void down(int code){
    if(code == 1){
        parenthesis--;
    }else if(code == 2){
        brackets--;
    }else if(code == 3){
        sbrackets--;
    }
}

int checkForToken(alpha_token_t* yylval){
    if(depth == 0) 
    { 
        cline = -1; 
        makeToken(yylineno , "*/" , "STOP MULTY COMMENT" , yylval); 
        return 0;
    } else  
    {
        makeToken(yylineno , "*/" , "STOP NESTED MULTY COMMENT" , yylval);
        depth--;
        return 1;
    }
}
