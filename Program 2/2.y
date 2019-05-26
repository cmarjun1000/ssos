%{
	#include<stdio.h>
	#include<stdlib.h>
	extern int yylex();
	extern int yylval;	
%}
%token A B
%%
start: S '\n' { printf("Valid Expression\n"); return 0; }
S: E B
E: A E
|
;
%%
int main()
{
	printf("Enter the expression: ");
	yyparse();
}
yyerror()
{
	printf("Invalid Expression\n");
	exit(0);
}