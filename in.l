%{
   #include "definitions.h"
   #include "parser.h" 

%}

%option noyywrap
%option yylineno



/* KEYWORDS */
if              "if"
else            "else"
while           "while"
for             "for"
function        "function"
return          "return"
break           "break"
continue        "continue"
and             "and"
not             "not"
or              "or"
local           "local"
true            "true"
false           "false"
nil             "nil"


/* Operators */

assign          "="
plus            "+"
minus           "-"
mul             "*"
divide          "/"
modulo          "%"
eq              "=="
ne              "!="
plusx2           "++"
minusx2          "--"
gt              ">"
lt              "<"
ge              ">="
le              "<="

/* Simeia Stiksis */

leftb            "{"
rightb           "}"
leftsb           "["
rightsb          "]"
leftparenthesis  "("
rightparenthesis ")"
semicolon        ";"
comma            ","
doubledot        ":"
doubledotx2      "::"
dot              "."
dotx2            ".."


integer        [0-9]*
real           [0-9]+\.[0-9]*
string         \"(\\.|[^\\"])*\"
whitespace     [\r \t\v\n]
id             [a-zA-Z][a-zA-Z_0-9]*
commentLine    "//".*
commentMulty   "/*"
undefined      .

%x COMMENT
%%
{whitespace}   {}
{if}           {return IF;}   
{else}         {return ELSE;}   
{while}        {return WHILE;}   
{for}          {return FOR;}   
{function}     {return FUNCTION;}   
{return}       {return RETURN;}   
{break}        {return BREAK;}  
{continue}     {return CONTINUE;}   
{and}          {return AND;}   
{not}          {return NOT;}   
{or}           {return OR;}   
{local}        {return LOCAL;}  
{true}         {return TRUE;} 
{false}        {return FALSE;} 
{nil}          {return NIL;} 


{assign}      {return ASSIGN;}
{plus}        {return PLUS;}
{minus}       {return MINUS;}
{mul}         {return MUL;}
{divide}      {return DIVIDE;}
{modulo}      {return MODULO;}
{eq}          {return EQ;}
{ne}          {return NE;}
{plusx2}      {return PLUSx2;}
{minusx2}     {return MINUSx2;}
{gt}          {return GT;}
{lt}          {return LT;}
{ge}          {return GE;}
{le}          {return LE;}


{leftb}            {return LEFTB; } 
{rightb}           {return RIGHTB; } 
{leftsb}           {return LEFTSB; } 
{rightsb}          {return RIGHTSB; }
{leftparenthesis}  {return LEFTPARENTHESIS; }
{rightparenthesis} {return RIGHTPARENTHESIS; }
{semicolon}        {return SEMICOLON; }
{comma}            {return COMMA; }
{doubledot}        {return DOUBLEDOT; } 
{doubledotx2}      {return DOUBLEDOTx2; }
{dot}              {return DOT; }
{dotx2}            {return DOTx2; }

{id}           { yylval.stringvalue = strdup(yytext); return ID;}
{string}       { yylval.stringvalue = strdup(yytext); return STRING;}
{commentLine}  { }
{commentMulty} { BEGIN(COMMENT); }
{integer}      { yylval.intvalue = atoi(yytext);  return INTEGER;}
{real}         { yylval.realvalue = atoi(yytext); return REAL;}
{undefined}    { return UNDEFINED_CHAR;}

<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>\n   { }
<COMMENT>.    { }
<<EOF>>              {return EOF; }

%%
/*
int main(int argc , char** argv){

    FILE* output;

    if(argc == 2){
        if(!(yyin = fopen(argv[1] , "r"))){
            printf("Cannot read file!\n");
        }

        file = stdout;
    }else if(argc > 2){
        if(!(yyin = fopen(argv[1] , "r"))){
            printf("Cannot read file!\n");
        }

        if(!(output = fopen(argv[2] , "w"))){
            printf("Cannot read output file!\n");
        }else{
            file = output;
        }

    }else{
        yyin = stdin;
        file = stdout;
    }


    int i = 0;
    while(i != 1){
        alpha_token_t* yylval = malloc(sizeof(alpha_token_t));
        i = alpha_yylex(yylval);
        if(i == 0){
           symT = insert2(yylval,symT); 
        }
    }
    
    if(parenthesis > 0){
        printf("ERROR: Parenthesis unclosed in line: %d\n" , pline);
    }else if(parenthesis < 0){
        printf("ERROR: Parenthesis unoped\n");
    }

    if(brackets > 0){
        printf("ERROR: brackets unclosed in line: %d\n" , bline);
    }else if(brackets < 0){
        printf("ERROR: brackets unoped\n");
    }

    if(sbrackets > 0){
        printf("ERROR: sbrackets unclosed in line: %d\n" , sbline);
    }else if(sbrackets < 0){
        printf("ERROR: sbrackets unoped\n");
    }

    if(cline != -1){
        printf("ERROR: Unclosed comment in line: %d\n" , cline);
    }

    printSymT();
    return 0;
}

*/