%{
#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.c"
int yywrap(); 
int yylex();
void yyerror(char *msg);
extern int yylval;
int flag=0;
int temp_count = 0; 
int genCode(int left, int right, const char op);
%}

%token NUM; 
%left '+' '-' 
%left '*' '/'

%%
input: expr { printf("Result: t%d\n", $1); }

expr: 
expr '+' expr { $$ = genCode($1, $3, '+');}
| expr '-' expr { $$ = genCode($1, $3, '-');}
| expr '*' expr { $$ = genCode($1, $3, '*');}
| expr '/' expr { $$ = genCode($1, $3, '/');}
| NUM   { $$ = genCode($1, -1, '#');}
;
%%

int genCode(int left, int right, const char op)
{
if(right==-1 && op=='#')
{
printf("t%d = %d\n",++temp_count, left);
return temp_count;
}
else
{
printf("t%d = t%d %c t%d\n", ++temp_count, left, op, right);
return temp_count;
}
}

void yyerror(char * msg)
{
flag = 1;
}

int main()
{
printf("Enter the single line program: ");
yyparse();
if(flag == 0)
{
printf("Error! \n");
}
return 0;
}
