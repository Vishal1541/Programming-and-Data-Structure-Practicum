#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int infix_len;
char stack[], stack_pointer = -1;
int stackEVA[], stackEVA_pointer = -1;

//Convert Infix to Postfix
void createStack();
int priority(char a);
int isStackEmpty();
char stackTop();
int isOperand(char a);
int isOperator(char a);
int hasHigherPrec(char a, char b);
void stackPop();
void stackPush(char a);
char* infToPostf(char* infix);
//----------------------------------

int perform(char a, int op1, int op2){
	if(a=='*')
		return op1*op2;
	else if(a=='+')
		return op1+op2;
	else if(a=='/')
		return op1/op2;
	else
		return op1-op2;
}

int stackEVATop(){
	return stackEVA[stackEVA_pointer];
}

void stackEVAPop(){
	stackEVA[stackEVA_pointer--] = 0;
}

void stackEVAPush(int a){
	stackEVA[++stackEVA_pointer] = a;//printf("%d\n",stackEVA[stackEVA_pointer-1]);
}

int evaPostFix(char* postfix){
	for(int i=0; i<infix_len; i++)
		stackEVA[i] = 0;
	for(int i=0; i<infix_len; i++){
		if(isOperand(postfix[i])){
			int val = (int)postfix[i]-48;
			stackEVAPush(val);
		}
		else if(isOperator(postfix[i])){
			int op2 = stackEVATop();
			stackEVAPop();
			int op1 = stackEVATop();
			stackEVAPop();
			int res = perform(postfix[i], op1, op2);
			stackEVAPush(res);
		}
	}
	return stackEVA[0];
}

int main(){
	char *infix = malloc(100);
	char *postfix = malloc(100);
	printf("Enter the infix form: ");
	scanf("%s",infix);
	infix_len = strlen(infix);
	postfix = infToPostf(infix);

	printf("%s\n", postfix);
	int result = evaPostFix(postfix);

	printf("Result = %d\n", result);

	return 0;
}


//----------Infix to Postfix-------------
void createStack(){
	for(int i=0; i<infix_len; i++)
		stack[i] = 0;
}

int priority(char a){
	if(a=='/')
		return 4;
	else if(a=='*')
		return 3;
	else if(a=='+')
		return 2;
	else
		return 1;
}

int isStackEmpty(){
	if (stack_pointer==-1)
		return 1;
	else
		return 0;
}

char stackTop(){
	return stack[stack_pointer];
}

int isOperand(char a){
	if(a=='*' || a=='/' || a=='+' || a=='-')
		return 0;
	return 1;
}

int isOperator(char a){
	if(a=='*' || a=='/' || a=='+' || a=='-')
		return 1;
	return 0;
}

int hasHigherPrec(char a, char b){
	if(priority(a) > priority(b))
		return 1;
	else
		return 0;
}

void stackPop(){
	stack[stack_pointer--] = 0;
}

void stackPush(char a){
	stack[++stack_pointer] = a;
}

char* infToPostf(char* infix){
	createStack();
	char *postfix_form = malloc(100);
	int postfix_form_pointer=0;
	for(int i=0; i<infix_len; i++){
		if(isOperand(infix[i])){
			postfix_form[postfix_form_pointer++]=infix[i];
		}
		else if(isOperator(infix[i])){
			while(!isStackEmpty() && hasHigherPrec(stackTop(),infix[i])){
				postfix_form[postfix_form_pointer++] = stackTop();
				stackPop();
			}
			stackPush(infix[i]);
		}
	}
	while(!isStackEmpty()){
		postfix_form[postfix_form_pointer++] = stackTop();
		stackPop();
	}
	return postfix_form;
}
