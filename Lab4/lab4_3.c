#include<stdio.h>
#include<stdlib.h>
#include"stack2.c"

int main(){
	stack *s=  (stack*)malloc(sizeof(stack));
	create(s);
	printf("\nStack created.\n");
	char input;
	char *temp=malloc(100);
	printf("Choose option: pUsh, pOp, pEek, iseMpty, getSize, eXit: ");
	scanf("%c",&input);
	while(input!='X'){
	
		if(input=='U'){
			char pushc;
			fgets(temp,100,stdin);
			printf("Enter element to be pushed: ");
			scanf("%c",&pushc);
			push(s,pushc);
		}
		else if(input=='O'){
			char popc = pop(s);
			if(popc==0)
       				printf("Error : Trying to pop from empty stack.\n");
       			else
       				printf("Popped: %c\n",popc);
		}
		else if(input=='E'){
			char peekc = peek(s);
			if(peekc==0)
				printf("Error : Trying to peek from empty stack.\n");
			else
				printf("Top of stack: %c\n",peekc);
		}
		else if(input=='M'){
			int empty = isEmpty(s);
			if(empty)
				printf("The stack is empty.\n");
			else
				printf("The stack is not empty.\n");
			
		}
		else{
			int size = getSize(s);
			printf("The size of the stack is %d.\n",size);
		}
		fgets(temp,100,stdin);
		printf("Choose option: pUsh, pOp, pEek, iseMpty, getSize, eXit: ");
		scanf("%c",&input);
	}
	return 0;
}
