#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void check();
char stack[50], input[50], action[50];
int top=0, ip=0, i=0; 
int main()
{
	printf("Enter the input string: ");
	scanf("%s", input);
	printf("STACK\t\tINPUT\t\tACTION\n");
	while(input[i] != '$')
	{
		printf("$%s\t\t%s\t\t", stack, (input+i));
		if(input[i] == 'i' && input[i+1] == 'd')
		{
			stack[top]='i';
			stack[top+1] = 'd';
			stack[top+2] = '\0';
			strcpy(action, "id");
			i += 2;
			top++;	
		}	
		else
		{
			stack[top] = input[i];
			stack[top+1] = '\0';
			action[0] = input[i];
			action[1] = '\0';
			i++;
		}
		printf("Shift %s\n", action);
		check();
		top++;

	}
	check();
}
void check()
{
	int flag=0;
	while(1)
	{
		if(stack[top] == 'd' && stack[top-1] == 'i')
		{
			printf("$%s\t\t%s\t\tReduce F->id\n", stack, (input+i));
			stack[top-1] = 'F';
			top--;
			stack[top+1] = '\0';
			flag=1;
		}
		if(stack[top] == ')' && stack[top-1] == 'E' && stack[top-2] == '(')
		{
			printf("$%s\t\t%s\t\tReduce F->(E)\n", stack, (input+i));
			stack[top-2] = 'F';
			top-=2;
			stack[top+1] = '\0';
			flag=1;
		}
		if(stack[top] == 'F' && stack[top-1] == '*' && stack[top-2] == 'T')
		{
			printf("$%s\t\t%s\t\tReduce T->T*F\n", stack, (input+i));
			stack[top-2] = 'T';
			top-=2;
			stack[top+1] = '\0';
			flag=1;
		}
		if(stack[top] == 'F')
		{
			printf("$%s\t\t%s\t\tReduce T->F\n", stack, (input+i));
			stack[top] = 'T';
			flag=1;
		}
		if(stack[top] == 'T' && stack[top-1] == '+' && stack[top-2] == 'E' && input[i] != '*')
		{
			printf("$%s\t\t%s\t\tReduce E->E+T\n", stack, (input+i));
			stack[top-2] = 'E';
			top-=2;
			stack[top+1] = '\0';
			flag=1;
		}
		if(stack[top] == 'T' && top==0 && input[i] != '*')
		{
			printf("$%s\t\t%s\t\tReduce E->T\n", stack, (input+i));
			stack[top] = 'E';
			flag=1;
		}
		else
		{
			flag=2;
		}
		if(stack[top] == 'E' && input[i] == '$')
		{
			printf("$%s\t\t%s\t\tAccepted\n", stack, (input+i));
			exit(0);
		}
		if(flag == 2)
			return;
		if(flag == 0)
		{
			printf("Rejected\n");
			exit(0);
		}
		flag = 0;
	}
}