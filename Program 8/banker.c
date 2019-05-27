#include<stdio.h>
#include<stdlib.h>
int done(int a[], int n)
{
	for(int i=0; i<n; i++)
		if(a[i] == 0)
			return 0;
	return 1;
}
int main()
{
	int i, j, n, r, ch;
	printf("Enter no. of processes: ");
	scanf("%d", &n);
	printf("Enter no. of resource types: ");
	scanf("%d", &r);
	int allocation[n][r], max[n][r], need[n][r], avail[r], safe[n], k=0;
	int *finished = calloc(n, sizeof(int));
	printf("Enter allocation matrix:\n");
	for(i=0; i<n; i++)
		for(j=0; j<r; j++)
			scanf("%d", &allocation[i][j]);
	printf("Enter max matrix:\n");
	for(i=0; i<n; i++)
		for(j=0; j<r; j++)
		{
			scanf("%d", &max[i][j]);
			need[i][j] = max[i][j] - allocation[i][j];
		}
	printf("Enter available resources: ");
	for(i=0; i<r; i++)
		scanf("%d", &avail[i]);
	printf("Any immediate request?(1/0): ");
	scanf("%d", &ch);
	if(ch == 1)
	{
		int p, req[r];
		printf("Enter process no.: ");
		scanf("%d", &p);
		printf("Enter request: ");
		for(i=0; i<r; i++)
			scanf("%d", &req[i]);
		for(i=0; i<r; i++)
			if(req[i] > need[p][i])
			{
				printf("Error\n");
				return 0;
			}
		if(i == r)
		{
			for(i=0; i<r; i++)
				if(req[i] > avail[i])
					break;
			if(i == r)
			{
				safe[k++] = p;
				for(i=0; i<r; i++)
					avail[i] += allocation[p][i];
				finished[p] = 1;
			}
			else
				printf("Can't process immediately, wait for resources to be released\n");
		}
	}
	int flag=0, process=0;
	while(flag < 100)
	{
		if(done(finished, n))
		{
			flag = 0;
			break;	
		}
		if(finished[process] == 0)
		{
			for(i=0; i<r; i++)
				if(avail[i] < need[process][i])
					break;
			if(i == r)
			{
				safe[k++] = process;
				for(i=0; i<r; i++)
					avail[i] += allocation[process][i];
				finished[process] = 1;
			}
		}
		process = (process+1)%n;
		flag++;
	}
	if(flag == 0)
	{
		printf("Safe sequence: ");
		for(i=0; i<k; i++)
			printf("%d ", safe[i]);	
		printf("\n");
	}
	else
		printf("System is in unsafe state\n");
}