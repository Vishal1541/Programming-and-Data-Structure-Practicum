#include<stdio.h>
#include<stdlib.h>
#include"stack.c"
int main(){
	stack *s1=  (stack*)malloc(sizeof(stack));
	stack *s2=  (stack*)malloc(sizeof(stack));
	create(s1);
	create(s2);
	printf("\nQueue created (using two stacks!!).\n");
	char input;
	char *temp=malloc(1000);
	printf("Choose option: Enqueue, Dequeue, Head-tail, iseMpty, getSize, eXit: ");
	scanf("%c",&input);
	while(input!='X'){
	
		if(input=='E'){
			char enq;
			fgets(temp,100,stdin);
			printf("Enter element to be enqueued: ");
			scanf("%c",&enq);
			push(s1,enq);
		}
		else if(input=='D'){
			char deq = pop(s2);
			revStack(s1, s2);
			if(deq==0)
       				printf("Error : Trying to dequeue from empty queue.\n");
       			else
       				printf("Dequeued: %c\n",deq);
		}
		else if(input=='H'){
			char head = peek(s2);
			char tail = peek(s1);
			if(head==0)
				printf("Error : Trying to peek from empty queue.\n");
			else
				printf("Head of queue: %c, tail of queue: %c\n",head,tail);
		}
		else if(input=='M'){
			int empty = isEmpty(s1);
			if(empty)
				printf("The queue is empty.\n");
			else
				printf("The queue is not empty.\n");
			
		}
		else{
			int size = getSize(s1);
			printf("The size of the queue is %d.\n",size);
		}
		revStack(s2, s1);
		printf("Stack1: ");
		printStack(s1);
		printf("Stack2: ");
		printStack(s2);
		fgets(temp,1000,stdin);
		printf("Choose option: Enqueue, Dequeue, Head-tail, iseMpty, getSize, eXit: ");
		scanf("%c",&input);
	}
	return 0;
}
