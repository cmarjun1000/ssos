%{
#include<stdio.h>
int operators=0, identifiers=0, brkt=0;
%}
%%
[+|*] { operators++; }
[0-9]+ { identifiers++; }
[(] { brkt++; }
[)] { brkt--; }
%%
int main()
{
  printf("Enter the expression: ");
  yylex();
  if(brkt!=0 || operators>=identifiers || identifiers==1)
  	printf("Invalid Expression\n");
  else
  	printf("Valid Expression\nNo. of operators %d\nNo. of identifiers %d\n", operators, identifiers);
}
