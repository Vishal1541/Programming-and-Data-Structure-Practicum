#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct s{
	int index;
	char fname[20], lname[20], dob[20], location[20], dept[20];
	struct Data *ptr; 
}Data;


Data* getFromFile(Data *d, FILE *f){
	char *line = malloc(300), *rec = malloc(20);
	Data *next = d, *tail;
	while(fgets(line,300,f)){
		rec = strtok(line,"\t");
		next->index = atoi(rec);
		rec = strtok(NULL," ");
		strcpy(next->fname,rec);
		rec = strtok(NULL," ");
		strcpy(next->lname,rec);
		rec = strtok(NULL," ");
		strcpy(next->dob,rec);
		rec = strtok(NULL," ");
		strcpy(next->location,rec);
		rec = strtok(NULL,"\n");
		strcpy(next->dept,rec);
		next->ptr = (Data*)malloc(sizeof(Data));
		tail = next;
		next = next->ptr;
	}
	next = NULL;
	return tail;
}
Data* getMid(Data *h, Data *t){
	Data *temp=h;
	int l=0;
	while(temp!=t){
		temp=temp->ptr;
		l++;
	}
	Data *m=h;
	for(int i=0;i<l/2;i++){
		m=m->ptr;	
	}
	return m;
}
Data *merge(Data *l1 , Data *l2)
{
	Data *h, *last, *new_node=malloc(sizeof(Data));
	h=new_node;
	while(l1!=NULL || l2!=NULL){
		last = new_node;
		if(l2==NULL){
			*new_node= *l1;
			l1=l1->ptr;
		}
		else if(l1==NULL){
			*new_node= *l2;
			l2=l2->ptr;
		}
		else if(l1->index <= l2->index){
			*new_node= *l1;	
			l1=l1->ptr;
		}
		else{
			*new_node= *l2;
			l2=l2->ptr;
		}
		Data *new_temp=malloc(sizeof(Data));
		new_node->ptr=new_temp;
		new_node=new_node->ptr;
	}
	last->ptr=NULL;
	return h;
}

Data *mergesort(Data *h ,Data *t)
{
	if(h==t){
		h->ptr=NULL;
		return h;
	}
	Data *m = getMid(h, t);
	
	Data *mergelist;
	Data *h2=m->ptr;
	Data *l1, *l2;
	l1=mergesort(h,m);
	l2=mergesort(h2,t);
	mergelist=merge(l1,l2);
	return mergelist;	
}
int main(){	
	
	FILE *fin = fopen("data_records.txt","r");
	FILE *fout = fopen("sorted_data2.txt","w");
	Data *head = (Data*)malloc(sizeof(Data));
	Data *tail = getFromFile(head, fin);
	clock_t begin = clock();
	Data *final = mergesort(head, tail);
	clock_t end = clock();
	while(final!=NULL){
		fprintf(fout,"%d\t%s\t%s\t%s\t%s\t%s\n",final->index,final->fname,final->lname,final->dob,final->location,final->dept);
		final = final->ptr;
	}
	
	float time_spent = (float)(end - begin) / CLOCKS_PER_SEC;
	printf("EXECUTION TIME : %f\n",time_spent);
	return 0;
}
