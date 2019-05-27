#include<stdio.h>
#include<stdlib.h>
int n, arrivalTime[100], burstTime[100], tempBurstTime[100], readyQueue[100], l=0, r=0, time=-1, tq, finished[100]={0}, inserted[100]={0}, completionTime[100]={0}, tat[100], awt[100], avgw=0, avgt=0;
int done()
{
	for(int i=0; i<n; i++)
		if(finished[i] == 0)
			return 0;
	return 1;
}
void updateReadyQueue()
{
	for(int i=0; i<n; i++)
	{
		if(arrivalTime[i] <= time && !inserted[i])
		{
			readyQueue[r++] = i;
			inserted[i] = 1;
		}
	}
}
void sjf()
{
	int executeProcess = 0;
	while(!done())
	{
		time++;
		updateReadyQueue();
		int min = 9999, p=-1;
		for(int i=0; i<r; i++)
		{
			if(tempBurstTime[readyQueue[i]] > 0 && tempBurstTime[readyQueue[i]] < min)
			{
				min = tempBurstTime[readyQueue[i]];
				p = readyQueue[i];
			}
		}
		if(tempBurstTime[executeProcess] == 0)
			executeProcess = p;
		else if(tempBurstTime[executeProcess] > 0 && tempBurstTime[executeProcess] > min)
			executeProcess = p;
		if(tempBurstTime[executeProcess] > 0)
			tempBurstTime[executeProcess]--;
		if(tempBurstTime[executeProcess] == 0)
		{
			finished[executeProcess] = 1;
			completionTime[executeProcess] = time+1;
			tat[executeProcess] = completionTime[executeProcess] - arrivalTime[executeProcess];
			awt[executeProcess] = tat[executeProcess] - burstTime[executeProcess];
			avgw += awt[executeProcess];
			avgt += tat[executeProcess];
		}
		printf("P%d runs until time %d\n", executeProcess, time+1);
	}
	printf("Average turnaround time : %.2f\n", avgt/(1.0*n));
	printf("Average Waiting time : %.2f\n", avgw/(1.0*n));
}
void rr()
{
	time=0;
	while(!done())
	{
		updateReadyQueue();
		int temp = tq;
		while(temp--)
		{
			if(tempBurstTime[readyQueue[l]] > 0)
			{
				tempBurstTime[readyQueue[l]]--;
				time++;
			}
		}
		updateReadyQueue();
		if(tempBurstTime[readyQueue[l]] == 0)
		{
			finished[readyQueue[l]] = 1;
			completionTime[readyQueue[l]] = time;
			tat[readyQueue[l]] = time - arrivalTime[readyQueue[l]];
			awt[readyQueue[l]] = tat[readyQueue[l]] - burstTime[readyQueue[l]];
			avgw += awt[readyQueue[l]];
			avgt += tat[readyQueue[l]];
		}
		if(tempBurstTime[readyQueue[l]] > 0)
			readyQueue[r++] = readyQueue[l];
		printf("P%d runs until time %d\n", readyQueue[l], time);
		l++;
	}
	printf("Average turnaround time : %.2f\n", avgt/(1.0*n));
	printf("Average Waiting time : %.2f\n", avgw/(1.0*n));
}
int main()
{
	printf("Enter the no. of processes: ");
	scanf("%d", &n);
	printf("Process\tAT\tBT\n");
	for(int i=0; i<n; i++)
	{
		printf("%d\t", i);
		scanf("%d%d", &arrivalTime[i], &burstTime[i]);
		tempBurstTime[i] = burstTime[i];
	}
	printf("1. RR\n2.SJF\n");
	int ch;
	scanf("%d", &ch);
	if(ch == 1)
	{
		printf("time quantum : \n");
		scanf("%d", &tq);
		rr();
	}
	else
		sjf();
}