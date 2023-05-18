/*rahulbs_351 Memory allocation techniques*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
	float size;
	float avail;
	struct node *link;
};
struct mem
{
	float size;
	int bn;
	char stat[15];
	struct mem *link;
};
struct node *node(float mb[],int nmb)
{
	struct node *head,*temp,*new;
	head=0;
	int i=0;
	while(i<nmb)
	{
		new=(struct node *)malloc(sizeof(struct node));
		new->size=mb[i];
		new->avail=mb[i];
		new->link=0;
		if(head==0)
		{
			head=temp=new;
		}
		else
		{
			temp->link=new;
			temp=new;
		}
		i++;
	}
	return head;
}
float minimum(int nmb,struct node *head,float proc)
{
	float m[nmb];
	struct node *temp;
	temp=head;
	int i=0,j=0,min;
	while(temp!=0)
	{
		if(proc<=temp->avail)
		{
			m[i]=temp->avail;
			i++;
		}
		temp=temp->link;
	}
	min=m[j];
	while(j<i)
	{
		if(m[j]<min && m[j]!=0)
		{
			min=m[j];
		}
		j++;
	}
	return min;
}
void ff(float mb[],float p[],int nmb,int np)
{
	struct node *head,*temp;
	struct mem *mhead,*mnew,*mtemp;
	head=0,mhead=0;
	int i=0,count;
	head=node(mb,nmb);
	mtemp=mhead;
	while(i<np)
	{
		count=0;
		float proc=p[i];
		temp=head;
		mnew=(struct mem *)malloc(sizeof(struct mem));
		mnew->size=proc;
		mnew->link=0;
		while(proc>temp->avail && temp->link!=0)
		{
			temp=temp->link;
			count++;
		}
		if(proc<=temp->avail)
		{
			temp->avail=temp->avail-proc;
			mnew->bn=count+1;
			strcpy(mnew->stat,"Allocated");
		}
		else
		{
			strcpy(mnew->stat,"Not Allocated");
		}
		if(mhead==0)
		{
			mhead=mtemp=mnew;
		}
		else
		{
			mtemp->link=mnew;
			mtemp=mnew;
		}
		i++;
	}
	printf("\n\t\t\t\t\tFirst Fit\n");
	printf("_________________________________________________________________________________________________\n");
	printf("Process Size(in Kb)\t\t|\tMemory Block Allocated\t|\tStatus\t\t\t|\n");
	printf("________________________________|_______________________________|_______________________________|\n");
	mtemp=mhead;
	while(mtemp!=0)
	{
		printf("%f\t\t\t|\t%d\t\t\t|\t%s\t\t|\n",mtemp->size,mtemp->bn,mtemp->stat);
		mtemp=mtemp->link;
	}
	printf("________________________________|_______________________________|_______________________________|\n");
}
void wf(float mb[],float p[],int nmb,int np)
{
	struct node *head,*temp;
	struct mem *mhead,*mnew,*mtemp;
	float max;
	head=0,mhead=0;
	int i=0,count;
	head=node(mb,nmb);
	mtemp=mhead;
	while(i<np)
	{
		count=0;
		float proc=p[i];
		temp=head;
		mnew=(struct mem *)malloc(sizeof(struct mem));
		mnew->size=proc;
		mnew->link=0;
		max=temp->avail;
		while(temp!=0)
		{
			if(temp->avail>max)
			{
				max=temp->avail;
			}
			temp=temp->link;
		}
		temp=head;
		while(temp->avail!=max)
		{
			temp=temp->link;
			count++;
		}
		if(temp->avail==max && proc<=temp->avail)
		{
			temp->avail=temp->avail-proc;
			mnew->bn=count+1;
			strcpy(mnew->stat,"Allocated");
		}
		else
		{
			strcpy(mnew->stat,"Not Allocated");
		}
		if(mhead==0)
		{
			mhead=mtemp=mnew;
		}
		else
		{
			mtemp->link=mnew;
			mtemp=mnew;
		}
		i++;
	}
	printf("\n\t\t\t\t\tWorst Fit\n");
	printf("_________________________________________________________________________________________________\n");
	printf("Process Size(in Kb)\t\t|\tMemory Block Allocated\t|\tStatus\t\t\t|\n");
	printf("________________________________|_______________________________|_______________________________|\n");
	mtemp=mhead;
	while(mtemp!=0)
	{
		printf("%f\t\t\t|\t%d\t\t\t|\t%s\t\t|\n",mtemp->size,mtemp->bn,mtemp->stat);
		mtemp=mtemp->link;
	}
	printf("________________________________|_______________________________|_______________________________|\n");
}
void bf(float mb[],float p[],int nmb,int np)
{
	struct node *head,*temp;
	struct mem *mhead,*mnew,*mtemp;
	float min;
	head=0,mhead=0;
	int i=0,count;
	head=node(mb,nmb);
	mtemp=mhead;
	while(i<np)
	{
		count=0;
		float proc=p[i];
		mnew=(struct mem *)malloc(sizeof(struct mem));
		mnew->size=proc;
		mnew->link=0;
		min=minimum(nmb,head,proc);
		temp=head;
		while(temp->avail!=min)
		{
			temp=temp->link;
			count++;
		}
		if(temp->avail==min)
		{
			temp->avail=temp->avail-proc;
			mnew->bn=count+1;
			strcpy(mnew->stat,"Allocated");
		}
		else
		{
			strcpy(mnew->stat,"Not Allocated");
		}
		if(mhead==0)
		{
			mhead=mtemp=mnew;
		}
		else
		{
			mtemp->link=mnew;
			mtemp=mnew;
		}
		i++;
	}
	printf("\n\t\t\t\t\tBest Fit\n");
	printf("_________________________________________________________________________________________________\n");
	printf("Process Size(in Kb)\t\t|\tMemory Block Allocated\t|\tStatus\t\t\t|\n");
	printf("________________________________|_______________________________|_______________________________|\n");
	mtemp=mhead;
	while(mtemp!=0)
	{
		printf("%f\t\t\t|\t%d\t\t\t|\t%s\t\t|\n",mtemp->size,mtemp->bn,mtemp->stat);
		mtemp=mtemp->link;
	}
	printf("________________________________|_______________________________|_______________________________|\n");
}
void main()
{
	int nmb,np;
	printf("Enter the Number of memory blocks: ");
	scanf("%d",&nmb);
	printf("Enter the Number of Processes: ");
	scanf("%d",&np);
	float mb[nmb],p[np];
	printf("Enter the size of the memory blocks in Kb: \n");
	for(int i=0;i<nmb;i++)
	{
		scanf("%f",&mb[i]);
	}
	printf("Enter the size of the Processes in Kb: \n");
	for(int i=0;i<np;i++)
	{
		scanf("%f",&p[i]);
	}
	printf("\n__*__*__*__*__*__*__*__*__*__*__*__*__*__\n");
	printf("|\t   Memory Block   \t\t|\n");
	printf("|__*__*__*__*__*__*__*__*__*__*__*__*__*|\n");
	printf("Block Number\t|\tPartition Size\t|\n");
	printf("________________|_______________________|\n");
	for(int i=0;i<nmb;i++)
	{
		printf("%d\t\t|\t%f\t|\n",i+1,mb[i]);
	}
	printf("________________|_______________________|\n");
	printf("\nAllocatiing Memory.......\n");
	ff(mb,p,nmb,np);
	wf(mb,p,nmb,np);
	bf(mb,p,nmb,np);
}
