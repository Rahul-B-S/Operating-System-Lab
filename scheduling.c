/*rahulbs_351 Scheduling algorithms*/
#include<stdio.h>
#include<stdlib.h>
struct process
{
	int pid;
	float arr;
	float burst;
	float avail;
	float turn;
	float wait;
	float ctime;
	int prio;
	struct process *link;
};
void reset(struct process *head)
{
	struct process *temp;
	temp=head;
	while(temp!=0)
	{
		temp->avail=temp->burst;
		temp=temp->link;
	}
}
void output(struct process *head,int p)
{
	struct process *temp;
	printf("\n\n");
	printf("+---------------+------------------+----------------+\n");
	printf("|  Process ID   | Turnaround Time  |  Waiting Time  |\n");
	printf("+---------------+------------------+----------------+\n");
	int j=1;
	float tsum=0,wsum=0;
	while(j<=p)
	{
		temp=head;
		while(temp!=0)
		{
			if(temp->pid==j)
			{
				printf("| %2d\t\t|  %2.1f\t\t   |  %2.1f\t    |\n",temp->pid,temp->turn,temp->wait);
				tsum=tsum+temp->turn;
				wsum=wsum+temp->wait;
				temp=temp->link;
			}
			else
			{
				temp=temp->link;
			}
		}
		j++;
		
	}
	printf("+---------------+------------------+----------------+\n");
	printf("\nAverage Turnaround Time = %.1f\nAverage Waiting Time = %.1f\n",tsum/p,wsum/p);
}
void main()
{
	int end=0;
	while(end!=6)
	{
		struct process *head,*new,*temp,*prev,*min;
		head=0;
		int p,j,ch=0;
		printf("\nEnter the number of processes: ");
		scanf("%d",&p);
		int pid[p],prio[p];
		float arr[p],burst[p],time;
		printf("Enter the Burst time of the processes(in ms): \n");
		for(int i=0;i<p;i++)
		{
			pid[i]=i+1;
			printf("P[%d]: ",i+1);
			scanf("%f",&burst[i]);
		}
		printf("Enter the Arrival time of the processes(in ms): \n");
		for(int i=0;i<p;i++)
		{
			printf("P[%d]: ",i+1);
			scanf("%f",&arr[i]);
		}
		printf("Enter the Priority of the processes(default priority 1 if not given): \n");
		for(int i=0;i<p;i++)
		{
			printf("P[%d]: ",i+1);
			scanf("%d",&prio[i]);
		}
		printf("+---------------+---------------+---------------+----------+\n");
		printf("|  Process ID   | Arrival Time  |  Burst Time   | Priority |\n");
		printf("+---------------+---------------+---------------+----------+\n");
		for(int i=0;i<p;i++)
		{
			printf("| %2d\t\t|  %2.1f\t\t|  %2.1f\t\t|  %2d\t   |\n",pid[i],arr[i],burst[i],prio[i]);
		}
		printf("+---------------+---------------+---------------+----------+\n");
		for(int i=0;i<p;i++)
		{
			new=(struct process *)malloc(sizeof(struct process));
			new->pid=i+1;
			new->arr=arr[i];
			new->burst=burst[i];
			new->avail=burst[i];
			new->ctime=0;
			new->prio=prio[i];
			new->link=0;
			if(head==0)
			{
				head=temp=new;
			}
			else
			{
				temp=head;
				while(new->arr>=temp->arr && temp->link!=0)
				{
					prev=temp;
					temp=temp->link;
				}
				if(new->arr<temp->arr)
				{
					if(temp==head)
					{
						new->link=temp;
						head=new;
					}
					else
					{
						prev->link=new;
						new->link=temp;
					}
				}
				else
				{
					temp->link=new;
				}
			}
		}	
		while(ch!=5)
		{
			printf("\n1.Round Robin\n");
			printf("2.SJF\n");
			printf("3.FCFS\n");
			printf("4.Priority\n");
			printf("5.Reset\n");
			printf("6.Exit\n");
			printf("Select a option to perform: ");
			scanf("%d",&ch);
			if(ch==1)
			{
				float tq;
				float error=0;
				printf("Enter the time quantum for Round Robin: ");
				scanf("%f",&tq);
				printf("\n\t\t\tRound Robin\n");
				printf("\t\t\tGantt Chart\n");
				temp=head;
				printf("+");
				j=p;
				while(j>0)
				{
					float loop;
					if(temp->avail==0)
					{
						temp=temp->link;
						j--;
					}
					else
					{
						if(temp->arr>error)
						{
							for(int i=error;i!=temp->arr;i++)
							{
								printf("--");
							}
							printf("+");
						}
						if(temp->avail>tq)
						{
							loop=tq;
							temp->avail=temp->avail-tq;
						}
						else
						{
							loop=temp->avail;
							temp->avail=0;
						}
						for(int i=0;i<loop;i++)
						{
							printf("--");
						}
						printf("+");
						error+=tq;
						temp=temp->link;
						j++;
					}
					if(temp==0)
					{
						temp=head;
					}
				}
				reset(head);
				error=0;
				printf("\n|");
				temp=head;
				j=p;
				while(j>0)
				{
					float loop;
					if(temp->avail==0)
					{
						temp=temp->link;
						j--;
					}
					else
					{
						if(temp->arr>error)
						{
							for(int i=error;i!=temp->arr-1;i++)
							{
								printf(" ");
							}
							printf("--");
							for(int i=error;i!=temp->arr-1;i++)
							{
								printf(" ");
							}
							printf("|");
						}
						if(temp->avail>tq)
						{
							loop=tq;
							temp->avail=temp->avail-tq;
						}
						else
						{
							loop=temp->avail;
							temp->avail=0;
						}
						for(int i=0;i<loop-1;i++)
						{
							printf(" ");
						}
						printf("P%d",temp->pid);
						for(int i=0;i<loop-1;i++)
						{
							printf(" ");
						}
						printf("|");
						error+=tq;
						temp=temp->link;
						j++;
					}
					if(temp==0)
					{
						temp=head;
					}
				}
				reset(head);
				error=0;
				temp=head;
				printf("\n+");
				j=p;
				while(j>0)
				{
					float loop;
					if(temp->avail==0)
					{
						temp=temp->link;
						j--;
					}
					else
					{
						if(temp->arr>error)
						{
							for(int i=error;i!=temp->arr;i++)
							{
								printf("--");
							}
							printf("+");
						}
						if(temp->avail>tq)
						{
							loop=tq;
							temp->avail=temp->avail-tq;
						}
						else
						{
							loop=temp->avail;
							temp->avail=0;
						}
						for(int i=0;i<loop;i++)
						{
							printf("--");
						}
						printf("+");
						error+=tq;
						temp=temp->link;
						j++;
					}
					if(temp==0)
					{
						temp=head;
					}
				}
				reset(head);
				printf("\n0");
				temp=head;
				j=p;
				time=0;
				while(j>0)
				{
					float loop;
					float e;
					if(temp->avail==0)
					{
						temp=temp->link;
						j--;
					}
					else
					{
						if(temp->arr>time)
						{
							for(e=time;e!=temp->arr;e++)
							{
								printf("  ");
							}
							printf("%.1f",e);
							time=time+e;
						}
						if(temp->avail>tq)
						{
							loop=tq;
							time=time+tq;
							temp->avail=temp->avail-tq;
							temp->ctime=time;
						}
						else
						{
							loop=temp->avail;
							time=time+temp->avail;
							temp->avail=0;
							temp->ctime=time;
						}
						for(int i=0;i<loop-1;i++)
						{
							printf("  ");
						}
						if(time>9)
						{
							printf("\b");
						}
						printf("%.1f",time);
						temp->turn=temp->ctime-temp->arr;
						temp->wait=temp->turn-temp->burst;
						temp=temp->link;
						j++;
					}
					if(temp==0)
					{
						temp=head;
					}
				}
				reset(head);
				output(head,p);
			}
			else if(ch==2)
			{
				printf("\n\t\t\tSJF\n");
				printf("\t\t\t\b\bGantt Chart\n");
				time=0;
				printf("+");
				j=p;
				temp=head;
				while(j>0)
				{
					temp=head;
					while(temp!=0)
					{
						if(temp->avail!=0)
						{
							min=temp;
							break;
						}
						temp=temp->link;
					}
					temp=head;
					while(temp!=0)
					{
						if(min->burst>temp->burst && temp->avail!=0)
						{
							min=temp;
						}
						temp=temp->link;
					}
					temp=min;
					temp->avail=0;
					if(min->arr>time)
					{
						for(int i=time;i!=min->arr;i++)
						{
							printf("--");
						}
						printf("+");
						time+=min->arr;
					}
					if(min->arr<=time)
					{
						for(int i=0;i<min->burst;i++)
						{
							printf("--");
						}
						printf("+");
					}
					time=time+min->burst;
					j--;
				}
				reset(head);
				time=0;
				printf("\n|");
				j=p;
				temp=head;
				while(j>0)
				{
					temp=head;
					while(temp!=0)
					{
						if(temp->avail!=0)
						{
							min=temp;
							break;
						}
						temp=temp->link;
					}
					temp=head;
					while(temp!=0)
					{
						if(min->burst>temp->burst && temp->avail!=0)
						{
							min=temp;
						}
						temp=temp->link;
					}
					temp=min;
					temp->avail=0;
					if(min->arr>time)
					{
						for(int i=time;i!=min->arr-1;i++)
						{
							printf(" ");
						}
						printf("--");
						for(int i=time;i!=min->arr-1;i++)
						{
							printf(" ");
						}
						printf("|");
						time=time+min->arr;
					}
					if(min->arr<=time)
					{
						for(int i=0;i<min->burst-1;i++)
						{
							printf(" ");
						}
						printf("P%d",min->pid);
						for(int i=0;i<min->burst-1;i++)
						{
							printf(" ");
						}
						printf("|");
					}
					time=time+min->burst;
					j--;
				}
				reset(head);
				time=0;
				printf("\n+");
				j=p;
				temp=head;
				while(j>0)
				{
					temp=head;
					while(temp!=0)
					{
						if(temp->avail!=0)
						{
							min=temp;
							break;
						}
						temp=temp->link;
					}
					temp=head;
					while(temp!=0)
					{
						if(min->burst>temp->burst && temp->avail!=0)
						{
							min=temp;
						}
						temp=temp->link;
					}
					temp=min;
					temp->avail=0;
					if(min->arr>time)
					{
						for(int i=time;i!=min->arr;i++)
						{
							printf("--");
						}
						printf("+");
						time+=min->arr;
					}
					if(min->arr<=time)
					{
						for(int i=0;i<min->burst;i++)
						{
							printf("--");
						}
						printf("+");
					}
					time=time+min->burst;
					j--;
				}
				reset(head);
				time=0;
				printf("\n0");
				j=p;
				temp=head;
				float e;
				while(j>0)
				{
					temp=head;
					while(temp!=0)
					{
						if(temp->avail!=0)
						{
							min=temp;
							break;
						}
						temp=temp->link;
					}
					temp=head;
					while(temp!=0)
					{
						if(min->burst>temp->burst && temp->avail!=0)
						{
							min=temp;
						}
						temp=temp->link;
					}
					temp=min;
					temp->avail=0;
					if(min->arr>time)
					{
						for(e=time;e!=min->arr;e++)
						{
							printf("  ");
						}
						printf("%.1f",e);
						time=time+e;
					}
					if(min->arr<=time)
					{
						time=time+min->burst;
						temp->turn=time-temp->arr;
						temp->wait=temp->turn-temp->burst;
						for(int i=0;i<min->burst-1;i++)
						{
							printf("  ");
						}
						printf("%.1f",time);
						if(time>9)
						{
							printf("\b");
						}
					}
					j--;
				}
				reset(head);
				output(head,p);
			}
			else if(ch==3)
			{
				float error=0;
				printf("\n\t\t\tFCFS\n");
				printf("\t\t\t\b\bGantt Chart\n");
				temp=head;
				printf("+");
				while(temp!=0)
				{
					if(temp->arr>error)
					{
						for(int i=error;i!=temp->arr;i++)
						{
							printf("--");
						}
						printf("+");
					}
					for(int i=0;i<temp->burst;i++)
					{
						printf("--");
					}
					printf("+");
					error+=temp->burst;
					temp=temp->link;
				}
				error=0;
				printf("\n|");
				temp=head;
				while(temp!=0)
				{
					if(temp->arr>error)
					{
						for(int i=error;i!=temp->arr-1;i++)
						{
							printf(" ");
						}
						printf("--");
						for(int i=error;i!=temp->arr-1;i++)
						{
							printf(" ");
						}
						printf("|");
					}
					for(int i=0;i<temp->burst-1;i++)
					{
						printf(" ");
					}
					printf("P%d",temp->pid);
					for(int i=0;i<temp->burst-1;i++)
					{
						printf(" ");
					}
					printf("|");
					error+=temp->burst;
					temp=temp->link;
				}
				error=0;
				printf("\n+");
				temp=head;
				while(temp!=0)
				{
					if(temp->arr>error)
					{
						for(int i=error;i!=temp->arr;i++)
						{
							printf("--");
						}
						printf("+");
					}
					for(int i=0;i<temp->burst;i++)
					{
						printf("--");
					}
					printf("+");
					error+=temp->burst;
					temp=temp->link;
				}
				printf("\n0");
				temp=head;
				j=0;
				float e;
				time=0;
				while(temp!=0)
				{
					float loop;
					if(temp->arr>time)
					{
						for(e=time;e!=temp->arr;e++)
						{
							printf("  ");
						}
						printf("%.1f",e);
						time=time+e;
					}
					time=time+temp->burst;
					temp->turn=time-temp->arr;
					temp->wait=temp->turn-temp->burst;
					if(temp->burst<=1)
					{
						loop=1;
					}
					else
					{
						loop=temp->burst-1;
					}
					for(int i=0;i<loop;i++)
					{
						printf("  ");
					}
					if(time>9)
					{
						printf("\b");
					}
					printf("%.1f",time);
					temp=temp->link;
					j++;
				}
				output(head,p);
			}
			else if(ch==4)
			{
				printf("\n\t\t\tPriority\n");
				printf("\t\t\t\b\bGantt Chart\n");
				time=0;
				printf("+");
				j=p;
				temp=head;
				while(j>0)
				{
					temp=head;
					while(temp!=0)
					{
						if(temp->avail!=0)
						{
							min=temp;
							break;
						}
						temp=temp->link;
					}
					temp=head;
					while(temp!=0)
					{
						if(min->prio>temp->prio && temp->avail!=0)
						{
							min=temp;
						}
						temp=temp->link;
					}
					temp=min;
					temp->avail=0;
					if(min->arr>time)
					{
						for(int i=time;i!=min->arr;i++)
						{
							printf("--");
						}
						printf("+");
						time+=min->arr;
					}
					if(min->arr<=time)
					{
						for(int i=0;i<min->burst;i++)
						{
							printf("--");
						}
						printf("+");
					}
					time=time+min->burst;
					j--;
				}
				reset(head);
				time=0;
				printf("\n|");
				j=p;
				temp=head;
				while(j>0)
				{
					temp=head;
					while(temp!=0)
					{
						if(temp->avail!=0)
						{
							min=temp;
							break;
						}
						temp=temp->link;
					}
					temp=head;
					while(temp!=0)
					{
						if(min->prio>temp->prio && temp->avail!=0)
						{
							min=temp;
						}
						temp=temp->link;
					}
					temp=min;
					temp->avail=0;
					if(min->arr>time)
					{
						for(int i=time;i!=min->arr-1;i++)
						{
							printf(" ");
						}
						printf("--");
						for(int i=time;i!=min->arr-1;i++)
						{
							printf(" ");
						}
						printf("|");
						time=time+min->arr;
					}
					if(min->arr<=time)
					{
						for(int i=0;i<min->burst-1;i++)
						{
							printf(" ");
						}
						printf("P%d",min->pid);
						for(int i=0;i<min->burst-1;i++)
						{
							printf(" ");
						}
						printf("|");
					}
					time=time+min->burst;
					j--;
				}
				reset(head);
				time=0;
				printf("\n+");
				j=p;
				temp=head;
				while(j>0)
				{
					temp=head;
					while(temp!=0)
					{
						if(temp->avail!=0)
						{
							min=temp;
							break;
						}
						temp=temp->link;
					}
					temp=head;
					while(temp!=0)
					{
						if(min->prio>temp->prio && temp->avail!=0)
						{
							min=temp;
						}
						temp=temp->link;
					}
					temp=min;
					temp->avail=0;
					if(min->arr>time)
					{
						for(int i=time;i!=min->arr;i++)
						{
							printf("--");
						}
						printf("+");
						time+=min->arr;
					}
					if(min->arr<=time)
					{
						for(int i=0;i<min->burst;i++)
						{
							printf("--");
						}
						printf("+");
					}
					time=time+min->burst;
					j--;
				}
				reset(head);
				time=0;
				printf("\n0");
				j=p;
				temp=head;
				float e;
				while(j>0)
				{
					temp=head;
					while(temp!=0)
					{
						if(temp->avail!=0)
						{
							min=temp;
							break;
						}
						temp=temp->link;
					}
					temp=head;
					while(temp!=0)
					{
						if(min->prio>temp->prio && temp->avail!=0)
						{
							min=temp;
						}
						temp=temp->link;
					}
					temp=min;
					temp->avail=0;
					if(min->arr>time)
					{
						for(e=time;e!=min->arr;e++)
						{
							printf("  ");
						}
						printf("%.1f",e);
						time=time+e;
					}
					if(min->arr<=time)
					{
						time=time+min->burst;
						temp->turn=time-temp->arr;
						temp->wait=temp->turn-temp->burst;
						for(int i=0;i<min->burst-1;i++)
						{
							printf("  ");
						}
						printf("%.1f",time);
						if(time>9)
						{
							printf("\b");
						}
					}
					j--;
				}
				reset(head);
				output(head,p);
			}
			else if(ch==5)
			{
				printf("\n");
				break;
			}
			else if(ch==6)
			{
				end=6;
				printf("\nTHANK YOU\n");
				break;
			}
			else
			{
				printf("Invalid Input\n");
			}
		}
	}
}
