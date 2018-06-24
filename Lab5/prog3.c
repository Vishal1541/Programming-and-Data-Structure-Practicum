#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct 
{
	int index; // record-key
	char fname[20], lname[20], dob[20], location[20], dept[20];
	struct record*next;
}record;

record *merge(record *list1 , record *list2)
{
	record *head;
	record *new=malloc(sizeof(record));
	record *fin;
	
	head=new;
	
	while(list1!=NULL || list2!=NULL)
	{
		fin=new;
		if(list2==NULL)
		{
			*new= *list1;
			list1=list1->next;
		}
		
		else if(list1==NULL)
		{
			*new= *list2;
			list2=list2->next;
		}
		
		else if(list1->index <= list2->index)
		{
			*new= *list1;	
			list1=list1->next;
		}
		
		else if(list1->index > list2->index)
		{
			*new= *list2;
			list2=list2->next;
		}
	
		record *temp=malloc(sizeof(record));
		new->next=temp;
		new=new->next;
	}
	
	fin->next=NULL;
	
	return(head);
}

record *mergesort(record *head,record *tail)
{
	if(head==tail)
	{
		head->next=NULL;
		return head;
	}
	
	record *mid , *temp;
	temp=head;
	int len=0;
	
	while(temp!=tail)
	{
		temp=temp->next;
		len++;
	}
	
	mid=head;
	
	for(int i=0;i<len/2;i++)
	{
		mid=mid->next;	
	}
	
	record *list1, *list2;
	record *finlist;
	record *temp2=mid->next;
	
	list1=mergesort(head,mid);
	list2=mergesort(temp2,tail);
	
	finlist=merge(list1,list2);
	
	return(finlist);	
}

int main()
{
	FILE *p=fopen("data_records.txt","r");
	FILE *q=fopen("output.txt","w");
	
	int count=0;
	char a[1000];
	
	while(fgets(a,1000,p))
	{
		count++;
	}

        record *data=malloc(sizeof(record)*count);
	rewind(p);
	
	record *init;
	record *fin;
	
	char *b=malloc(sizeof(char)*10);
	init=data;
	
	while(fgets(a,1000,p))
	{
		fin=data;
		b=strtok(a,"\t");
		data->index=atoi(b);
		
		b=strtok(NULL," ");
		strcpy(data->fname,b);
		
		b=strtok(NULL," ");
		strcpy(data->lname,b);
		
		b=strtok(NULL," ");
		strcpy(data->dob,b);
		
		b=strtok(NULL," ");
		strcpy(data->location,b);
		
		b=strtok(NULL,"\n");
		strcpy(data->dept,b);
	
		record*temp=malloc(sizeof(record));	
		data->next=temp;
		data=temp;		
	}
	
	fin->next=NULL;	
		
	record *sorted;
	sorted=mergesort(init,fin);

	while(sorted!=NULL)
	{
		fprintf(q,"%d %s %s %s %s %s\n",sorted->index,sorted->fname,sorted->lname,sorted->dob,sorted->location,sorted->dept);
		sorted=sorted->next;
	}
	
	fclose(p);
	return 0;
}
