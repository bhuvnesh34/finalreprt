#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
 
void WaitingTimecal(int Pburst_time[], int Qburst_time[], int Pnoq, int Qnoq)
{
	const int quantum=4;
	int q=Qnoq,p=Pnoq;
	int time=0, total_time=0;
	int Prem_bt[200], Qrem_bt[200], Prdq[200], Qrdq[200], Pwait[200], Qwait[200], Qtat[200], Ptat[200];
	for(int k=0;k<Qnoq;k++)
	{
		total_time+= Qburst_time[k];
		Qrdq[k]=Qburst_time[k];
	}
	for(int k=0;k<Pnoq;k++)
	{
		total_time+= Pburst_time[k];
		Prdq[k]=Pburst_time[k];
	}
	while (1)
    		{
		        bool done = true;
			for (int i = 0 ; i < q; i++)
			{
			        if (Qrdq[i] > 0)
            			{
			                done = false; 
			                if (Qrdq[i] > quantum)
			                {
				                time += quantum;
						Qrdq[i] -= quantum;
			                }
					else
			                {
				                time = time + Qrdq[i];
				                Qwait[i] = time - Qburst_time[i];
				                Qrdq[i] = 0;
                			}
            			}
        		}
			time++;
			if (done == true)
		        break;
		}
			while (1)
    		{
		        bool done = true;
			for (int i = 0 ; i < p; i++)
			{
			        if (Prdq[i] > 0)
            			{
			                done = false; 
			                if (Prdq[i] > quantum)
			                {
				                time += quantum;
						Prdq[i] -= quantum;
			                }
					else
			                {
				                time = time + Prdq[i];
				                Pwait[i] = time - Pburst_time[i];
				                Prdq[i] = 0;
                			}
            			}
        		}
			if (done == true)
		        break;
		}
	for (int k=0;k<Qnoq;k++)
        	Qtat[k] = Qburst_time[k] + Qwait[k];
	for (int k=0;k<Pnoq;k++)
	        Ptat[k] = Pburst_time[k] + Pwait[k];
	printf("Processes	Burst time	Waiting time	Turnaround time\n");
	for (int k=0;k<Qnoq;k++)
		printf("T%d\t\t%d\t\t%d\t\t%d\n",k,Qburst_time[k],Qwait[k],Qtat[k]);
	for (int k=0;k<Pnoq;k++)
		printf("S%d\t\t%d\t\t%d\t\t%d\n",k,Pburst_time[k],Pwait[k],Ptat[k]);
	printf("Total time spent- %d\n",total_time);
}

int main()
{
	int Pburst_time[200], Qburst_time[200];
	char Pques[200][MAX_LIM], Qques[200][MAX_LIM];
	int choice,Pnoq=0, Qnoq=0;
	const int MAX_LIM=700;
	system("clear");
	while(choice!=3)
	{
		printf("1.\tEnter questions as Teacher\n2.\tEnter questions as Student\n3.\tEnd query session\n\tYour choice-");
		scanf("%d",&choice);
		while(getchar()!='\n');
		if(choice==1)
		{
			system("clear");
			printf("Enter Question Number.%d-",Qnoq);
			fgets(Qques[Qnoq],MAX_LIM,stdin);
			Qburst_time[Qnoq]=(strlen(Qques[Qnoq])/10);
			Qnoq++;
		}
		if(choice==2)
		{
			system("clear");
			printf("Enter Question Number.%d-",Pnoq);
			fgets(Pques[Pnoq],MAX_LIM,stdin);
			Pburst_time[Pnoq]=(strlen(Pques[Pnoq])/10);
			Pnoq++;
		}
	}	
	printf("\n\n\t\tEvaluating all questions\n");
	WaitingTimecal( Pburst_time, Qburst_time, Pnoq, Qnoq);
	return 0;
}
