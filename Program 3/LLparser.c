#include<stdio.h>
#include<string.h>
int i, j, top=-1;
char production[][10]={"A->aBa", "B->bB", "B->@"}, table[3][4][10], first[] = {'a', 'b', '@'}, follow[] = {'$', 'a', 'a'};
char stack[100], input[100];
void push(char c)
{ stack[++top] = c; }
void pop()
{ top--; }
void bigLine()
{ printf("-------------------------------------------------------\n"); }
void displayStack()
{
	for(int k=top; k>=0; k--)
		printf("%c", stack[k]);
}
int numr(char c)
{
	switch(c){
		case 'a': return 1;
		case 'A': return 1;
		case 'b': return 2;
		case 'B': return 2;
		case '@': return 3;
	}
	return -1;
}
int main()
{
	for(i=0; i<3; i++)
		for(j=0; j<4; j++)
			strcpy(table[i][j], " ");
	strcpy(table[0][1], "a");
	strcpy(table[0][2], "b");
	strcpy(table[0][3], "$");
	strcpy(table[1][0], "A");
	strcpy(table[2][0], "B");	
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			if(first[i] != '@')
				strcpy(table[numr(production[i][0])][numr(first[i])], production[i]);
			else
				strcpy(table[numr(production[i][0])][numr(follow[i])], production[i]);
		}
	}	
	printf("Predictive Parsing Table\n");
	bigLine();
	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
			printf("%s\t", table[i][j]);
		printf("\n");
	}
	bigLine();
	printf("\nEnter input string (terminated by $): ");
	scanf("%s", input);
	i=0;
	printf("\nSTACK\t\tINPUT\t\tACTION\n");
	bigLine();
	push('$');
	push('A');
	while(input[i]!='$')
	{	
		displayStack();
		printf("\t\t%s\t\t", (input+i));
		if(input[i] == stack[top])
		{
			printf("Matched %c\n", stack[top]);
			pop();
			i++;
		}
		else
		{
			char apply[50];
			strcpy(apply, table[numr(stack[top])][numr(input[i])]);
			printf("Apply production %s\n", apply);
			if(apply[3] == '@')
				pop();
			else
			{
				pop();
				for(int x=strlen(apply)-1; x>=3; x--)
					push(apply[x]);
			}
		}
	}
	if(stack[top] == '$' && input[i] == '$')
		printf("Accepted\n");
	else
		printf("Rejected\n");
}