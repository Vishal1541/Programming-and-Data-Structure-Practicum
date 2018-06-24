#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createBinaryTree(binaryTree *rootnode, int values[total_numbers]){
	binaryTree *temp = rootnode;
	temp->value = values[0];
	temp->left = NULL;
	temp->right = NULL;
	for(int i=1; i<total_numbers; i++){
		int val = values[i];
		temp = rootnode;
		if(val<= temp->value){
			if(temp->left == NULL){
				temp->left = malloc(sizeof(binaryTree));
				temp = temp->left;
				temp->value = val;
				temp->left = NULL;
				temp->right =NULL;
			}
			else
				temp = temp->left;
		}
		else{
			if(temp->right == NULL){
				temp->right = malloc(sizeof(binaryTree));
				temp = temp->right;
				temp->value = val;
				temp->left = NULL;
				temp->right =NULL;
			}
			else
				temp = temp->right;
		}
	}
}

void insertIntoTree(binaryTree *node, int value){
	if(value <= node->value){
		if(node->left == NULL){
			node->left = malloc(sizeof(binaryTree));
			node = node->left;
			node->value = value;
			node->left = NULL;
			node->right =NULL;
		}
		else
			insertIntoTree(node->left, value);
	}
	else{
		if(node->right == NULL){
			node->right = malloc(sizeof(binaryTree));
			node = node->right;
			node->value = value;
			node->left = NULL;
			node->right =NULL;
		}
		else
			insertIntoTree(node->right, value);
	}
}

char *infToPostfix(char *infix){
	char *postfix = malloc(100);
	int pointer = 0;
	for(int i=0; i<length; i++){
		if(isOperand(infix[i])){
			postfix[pointer++] = infix[i];
		}
		else if(isOperator(infix[i])){
			while(!isStackEmpty && hasHigherPrec(stackTop(), infix[i])){
				postfix[pointer++] = stackTop();
				stackPop();
			}
			stackPush(infix[i]);
		}
	}
	while(!isStackEmpty()){
		postfix[pointer++] = stackTop();
		stackPop();
	}
	return postfix;
}

binaryTree *postfixToTree(char *postfix){
	for(int i=0; i<length; i++){
		if(isOperand(postfix[i])){
			stackPush(postfix[i]);
		}
		else if(isOperator(postfix[i])){
			binaryTree *node = malloc(sizeof(binaryTree));
			node->value = postfix[i];
			node->left = stackTop();
			stackPop();
			node->right = stackTop();
			stackPop();
			stackListPush(node);
		}
	}
	return stackTop();
}

void preOrder(binaryTree *node){
	if(node!=NULL){
		printf("%c ",node->value);
		preOrder(node->left);
		preOrder(node->right);
	}
}

void inOrder(binaryTree *node){
	if(node!=NULL){
		inOrder(node->left);
		printf("%c ",node->value);
		inOrder(node->right);
	}
}

void postOrder(binaryTree *node){
	if(node!=NULL){
		postOrder(node->left);
		postOrder(node->right);
		printf("%c ",node->value);
	}
}

int postfixEvaluate(char *postfix){
	for(int i=0; i<length; i++){
		if(isOperand(postfix[i])){
			stackPush((int)postfix[i] - 48);
		}
		else if(isOperator(postfix[i])){
			int pop1 = stackTop();
			stackPop();
			int pop2 = stackTop();
			stackPop();
			int res = perform(postfix[i], pop1, pop2);
			stackPush(res);
		}
	}
	return stackTop();
}

//---------------------------------------------------------

void DFS(int vertex){								//stack
	visited[vertex] = 1;
	printf("%d ",vertex);
	for(int i=0; i<total_vertex; i++){
		if(!visited[i] && m[vertex][i])
			DFS(i);
	}
}

void BFS(int vertex){								//queue
	visited[vertex] = 1;
	int head=0, tail=0;
	queue[tail++] = vertex;
	while(tail>head){
		int dequeue = queue[head++];
		printf("%d ",dequeue);
		for(int i=0; i<total_vertex; i++){
			if(!visited[i] && m[dequeue][i]){
				visited[i] = 1;
				queue[tail++] = i;
			}
		}
	}
}

//---------------------------------------------------------

void merge_sort(int *d, int l, int u){
	int m = (l+u)/2;
	if(l<u){
		merge_sort(d, l, m);
		merge_sort(d, m+1, u);
		merge(d, l, u);
	}
}

void merge(int *d, int l, int u){
	int m = (l+u)/2;
	int L[m-l+1], U[u-m], S[u-l+1];
	for(int i=l; i<=m; i++)
		L[i-l] = d[i];
	for(int i=m+1; i<=u; i++)
		U[i-m-1] = d[i];
	int p1=0, p2=m+1;
	int j=0;
	while(!(p1==m+1 || p2==u+1)){
		if(L[p1]<U[p2])
			S[j++] = L[p1++];
		else
			S[j++] = U[p2++];
	}
	while(p1!=m+1)
		S[j++] = L[p1++];
	while(p2!=u+1)
		S[j++] = U[p2++];
	j=0;
	for(j=0; j<u-l+1; j++)
		d[j+l] = S[j];
}

//---------------------------------------------------------

