#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int infix_len;
char stack[], stack_pointer = -1;

typedef struct s{												//Structure for binary tree
	char value;
	struct binaryTree *left, *right;
	int flag;
}binaryTree;

int stackbin_pointer = -1;

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

//Postfix to Binary Tree
void binPushChar(char a, binaryTree *stackbin[infix_len]);
void binPushNode(binaryTree *node, binaryTree *stackbin[infix_len]);
binaryTree* binPop(binaryTree *stackbin[infix_len]);
binaryTree* arthExpreTree(char *postfix, binaryTree *stackbin[infix_len]);
//----------------------------------

//------Preorder Traversal
void preOrder(binaryTree *node);
//----------------------------------

void makeAllFlagZero(binaryTree *root){
	root->flag = 0;
	if(root->left != NULL)
		makeAllFlagZero(root->left);
	if(root->right != NULL)
		makeAllFlagZero(root->right);
}

//------Inorder Traversal
void inOrder(binaryTree *root);
//----------------------------------

//------Postorder traversal
void PostOrder(binaryTree *root);
//----------------------------------


int main(){
	char *infix = malloc(100);
	char *postfix = malloc(100);
	printf("Enter the prefix form\n");
	scanf("%s",infix);
	infix_len = strlen(infix);

	postfix = infToPostf(infix);
	printf("\nPostfix form = %s\n",postfix );

	binaryTree *stackbin[infix_len];
	for(int i=0; i<infix_len; i++)
		stackbin[i] = malloc(sizeof(binaryTree));

	binaryTree *expressionTree = arthExpreTree(postfix, stackbin);

	printf("\nPreorder : ");
	preOrder(expressionTree);
	printf("\n");

	makeAllFlagZero(expressionTree);


	printf("\nInorder : ");
	inOrder(expressionTree);
	printf("\n");

	printf("\nPostorder : ");
	PostOrder(expressionTree);
	printf("\n");
	/*
	binaryTree *LEFT = expressionTree->left;
	binaryTree *RIGHT = expressionTree->right;
	printf("%c,%c,%c\n", expressionTree->value, LEFT->value, RIGHT->value);
	RIGHT = LEFT->right;
	LEFT = LEFT->left;

	printf("%c,%c \n",LEFT->value,RIGHT->value );
	*/
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

//-------Postfix to Binary Tree

void binPushChar(char a, binaryTree *stackbin[infix_len]){
	binaryTree *temp = stackbin[++stackbin_pointer];
	temp->value = a;
	temp->left = temp->right = NULL;
	temp->flag = 0;
}

void binPushNode(binaryTree *node, binaryTree *stackbin[infix_len]){
	stackbin[++stackbin_pointer] = node;
}

binaryTree* binPop(binaryTree *stackbin[infix_len]){
	binaryTree *temp = stackbin[stackbin_pointer];
	stackbin[stackbin_pointer] = malloc(sizeof(binaryTree));
	stackbin_pointer--;
	return temp;
}

binaryTree* arthExpreTree(char *postfix, binaryTree *stackbin[infix_len]){
	for(int i=0; i<infix_len; i++){
		if(isOperand(postfix[i])){
			binPushChar(postfix[i], stackbin);
		}
		else if(isOperator(postfix[i])){
			binaryTree *root = malloc(sizeof(binaryTree));
			binaryTree *popped1 = binPop(stackbin);
			binaryTree *popped2 = binPop(stackbin);
			root->value = postfix[i];
			root->left = popped1;
			root->right = popped2;
			binPushNode(root, stackbin);
		}
	}
	binaryTree* tree = stackbin[0];
	return tree;
}

//--------Preorder traversal

void preOrder(binaryTree *node){
	binaryTree *node_child = node;
	printf("%c", node->value);
	node->flag = 1;
	if(node->left != NULL){
		node_child = node->left;
		if(node_child->flag == 0)
			preOrder(node_child);
	}
	if(node->right != NULL){
		node_child = node->right;
		if(node_child->flag == 0)
			preOrder(node_child);
	}
}

//---------Inorder traversal

void inOrder(binaryTree *root){
	if(root != NULL){
		inOrder(root->left);
		printf("%c", root->value);
		inOrder(root->right);
	}
}

//---------Postoder travesal
void PostOrder(binaryTree *root){
	if(root != NULL){
		PostOrder(root->left);
		PostOrder(root->right);
		printf("%c", root->value);
	}
}