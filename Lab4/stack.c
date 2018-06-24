#include <stdio.h>
#include <stdlib.h>
#include <stack.h>

void create(stack *s){
	s->top=NULL;
	s->size=0;
}
void push(stack *s, char x){
	if(s->top==NULL){
		s->top = (list*)malloc(sizeof(list));
		s->top->ptr = NULL;
		s->top->info = x;
		s->size += 1;
	}
	else{
		list* temp =(list*)malloc(sizeof(list));
  	      	temp->ptr = s->top;
        	temp->info = x;
        	s->top = temp;
		s->size += 1;
	}
}
char pop(stack *s){
	list* top1 = s->top;
 	char popc;
    if (top1 == NULL){
        return 0;
    }
    else{
        top1 = top1->ptr;
    	popc = s->top->info;
    	free(s->top);
    	s->top = top1;
	s->size -= 1;
    }
    return popc;
   	 
}
char peek(stack *s){
	if(s->size==0)
		return 0;
	return (s->top->info);
}
int isEmpty(stack *s){
	if(s->size==0)
		return 1;
	else
		return 0;
}
int getSize(stack *s){
	return (s->size);
}
void revStack(stack *rs, stack *s){
	create(rs);
	list* top1 = s->top;
	if(top1==NULL)
		return;
	else if(top1->ptr==NULL)
		push(rs, top1->info);
	else{
		do{
			push(rs, top1->info);
			top1 = top1->ptr;
		}
		while(top1->ptr!=NULL);
		push(rs, top1->info);
	}
}
void printStack(stack *s){
	list* top1 = s->top;
	printf("[ ");
	if(top1==NULL){
		printf("--- ]\n");
		return;
		}
	else if(top1->ptr==NULL)
		printf("%c ", top1->info);
	else{
		do{
			printf("%c ", top1->info);
			top1 = top1->ptr;
		}
		while(top1->ptr!=NULL);
		printf("%c ", top1->info);
	}
	printf("]\n");
}
