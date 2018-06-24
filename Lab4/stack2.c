#include <stdio.h>
#include <stdlib.h>
#include "stack2.h"

// create stack
void create(stack *s){
	int i;
	for(i=0;i<SIZE_MAX;i++)
		s->arr[i]=0;
	s->top=-1;
	s->size=0;
}
// push a char into stack
void push(stack *s, char x){
	if(s->size==SIZE_MAX){
		printf("Stack overflow!\n");
		return;
	}
	s->arr[++(s->top)] = x;
	(s->size)++;
}
// pop the top of the stack
char pop(stack *s){
	if(s->size==0)
		return 0;
	char popc = s->arr[s->top];
	(s->top)--;
	(s->size)--;
	return popc;
}
// return the top of stack, without popping
char peek(stack *s){
	if(s->size==0)
		return 0;
	return (s->arr[s->top]);
}
// is the stack empty?
int isEmpty(stack *s){
	if(s->size==0)
		return 1;
	return 0;
}
// return the size of the stack
int getSize(stack *s){
	return (s->size);
}
