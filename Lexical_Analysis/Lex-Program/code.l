/* Lex program to count the number of tokens and find out all the tokens from input C program. */
/* Definition Section */
digit [0-9]
letter [a-zA-Z]
%{
	#include <stdio.h>
	#include <stdlib.h>
    int counter=0;
%}

/* Rule Section */
/* Token specification */
%%
\"(\\.|[^"\\])*\"   {printf("\nToken: string -> "); ECHO; counter++;}
"int"	{printf("\nToken: INT -> "); ECHO; counter++;}
"("		{printf("\nToken: Seperator -> "); ECHO; counter++;}
")"		{printf("\nToken: Seperator -> "); ECHO; counter++;}
"{"		{printf("\nToken: Seperator -> "); ECHO; counter++;}
"}"		{printf("\nToken: Seperator -> "); ECHO; counter++;}
["#import","stdio.h"]	{printf("\nToken: KEYWORD -> "); ECHO; counter++;}
";"		{printf("\nToken: End of Statement -> "); ECHO; counter++;}
"//".* 	;
"return" {printf("\nToken: RETURN -> "); ECHO; counter++;}
","		{printf("\nToken: , operator -> "); ECHO; counter++;}
"="		{printf("\nToken: assignment operator -> "); ECHO; counter++;}
"+"     {printf("\nToken: addition operator -> "); ECHO; counter++;}
{letter}({letter}|{digit})*	{printf("\nToken: identifier -> "); ECHO; counter++;}
{digit}+ {printf("\nToken: Integer value -> "); ECHO; counter++;}
.|\n 	;
%%

int main()
{
    extern FILE *yyin;
	char filename[100]; 
	printf("This Program program finds all tokens!!Enter the name of the file to read:\t");
	scanf("%s", filename);
	/* Opening file to read */
	yyin = fopen(filename, "r");
	if (yyin == NULL){
		printf("Cannot open file %s", filename);
	    exit(0);
	}
	/* call the yylex function. */
	yylex();
    printf("\nToken count: %d\n", counter);					
	return 0;
}

/* call the yywrap function */
int yywrap()					
{
	return 1;
}
