%{
	#include<stdio.h>	
	#include<stdlib.h>
	extern int yylex();
	extern int yylval;
%}
%token NUM
%left '+' '-'
%left '*' '/'
%%
expr: E { printf("Value = %d\n", $1); return 0; }
E: E '+' E { $$ = $1 + $3; }
|E '-' E { $$ = $1 - $3; }
|E '*' E { $$ = $1 * $3; }
|E '/' E { if($3 == 0) printf("/ by Zero\n"); else $$ = $1 / $3; }
|'('E')' { $$ = $2; }
|NUM { $$ = $1; }
%%
int main()
{
	printf("Enter the expression: ");
	yyparse();
}
int yyerror()
{
	printf("Invalid Expression\n");
	exit(0);
}

