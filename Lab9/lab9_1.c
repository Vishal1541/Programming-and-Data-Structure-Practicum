#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int totalNoToBeSearched;

typedef struct s{												//Structure for binary tree
	int value;
	struct binaryTree *left, *right;
}binaryTree;

typedef struct t{												//Structure for searching into the tree
	int value;
	int comparisions;
	int found;
}searchTree;

void initTree(binaryTree *tree, int rootvalue){					//creating tree
	tree->value = rootvalue;
	//tree->up = NULL;
	tree->left = NULL;
	tree->right = NULL;
}

/*void finaliseInsertion(binaryTree *parent, binaryTree *child, int value){
	child->value = value;
	child->left = NULL;
	child->right = NULL;
	child->up = parent;
}
*/
int getValueNext(FILE *f){										//next value from file
	char *data = malloc(10);
	fgets(data,10,f);
	int val = atoi(data);
	return val;
}

void insertIntoTree(binaryTree *rootnode, int value){			//BINARY SEARCH TREE (BST)
	binaryTree *temp = NULL;
	temp = rootnode;
	int c=1;
	while(c){
		if(value > temp->value){
			if(temp->right == NULL){
				temp->right = (binaryTree*) malloc(sizeof(binaryTree));
				temp = temp->right;
				temp->value = value;
				temp->left = NULL;
				temp->right = NULL;
				c=0;
			}
			else{
				temp = temp->right;
			}
		}
		else{
			if(temp->left == NULL){
				temp->left = (binaryTree*) malloc(sizeof(binaryTree));
				temp = temp->left;
				temp->value = value;
				temp->left = NULL;
				temp->right = NULL;
				c=0;
			}
			else{
				temp = temp->left;
			}	
		}
	}
}

int cmpfunc (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

void search(binaryTree *rootnode, searchTree arr[],int totalNoToBeSearched){
	for(int i=0; i<totalNoToBeSearched; i++){	
		binaryTree *temp = rootnode;
		int val = arr[i].value;										//value to be searched
		while(1){
			if(val == temp->value){
				arr[i].comparisions++;
				arr[i].found = 1;
				break;
			}
			else if(val > temp->value){
				arr[i].comparisions++;
				temp = temp->right;
			}
			else{
				arr[i].comparisions++;
				temp = temp->left;
			}
			if(temp==NULL){
				break;
			}
		}
	}
}

void printSearch(searchTree arr[], int totalNoToBeSearched){

	printf("\tX\t\t\tY\n\n");
	for(int i=0; i<totalNoToBeSearched ;i++){
		printf("%d\t%d\t\t\t%d",i+1,arr[i].value, arr[i].comparisions);
		if(arr[i].found == 0)
			printf("\t(Not Found)");
		printf("\n");
	}
	printf("\n\n\n");
}

int max(int a, int b){
	if(a>b)
		return a;
	else
		return b;
}

int findHeight(binaryTree *rootnode){
	if(rootnode == NULL)
		return -1;												//to compensate max(-1,-1)+1 = 0 --> leaf node
	else
		return max(findHeight(rootnode->left),findHeight(rootnode->right))+1;
}

int main(){

	FILE *frand = fopen("random.txt","r");
	FILE *fsorted = fopen("sorted.txt","r");
	FILE *fsearch = fopen("search.txt","r");
	
	binaryTree *trand=malloc(sizeof(binaryTree)), *tsort=malloc(sizeof(binaryTree));

	int rootnodevalue_rand = getValueNext(frand);				//top most node value
	int rootnodevalue_sorted = getValueNext(fsorted);

	initTree(trand, rootnodevalue_rand);						//creating tree
	initTree(tsort, rootnodevalue_sorted);

	int get_value_next_rand, get_value_next_sorted;				//values from both the files
	char *data = malloc(10);									//each value (line)

	while(fgets(data,10,frand)){
		get_value_next_rand = atoi(data);
		insertIntoTree(trand, get_value_next_rand);				//inserting/expanding the tree
		//printf("%d\n", get_value_next_rand);
	}

	while(fgets(data,10,fsorted)){
		get_value_next_sorted = atoi(data);
		insertIntoTree(tsort, get_value_next_sorted);			//inserting/expanding the tree
		//printf("%d\n", get_value_next_sorted);
	}

	/*Inserting operation done
	 *To go now
	 *Searching part
	 */

	int totalNoToBeSearched = 0;
	while(fgets(data,10,fsearch))
		totalNoToBeSearched++;
	rewind(fsearch);

	searchTree mySearchRand[totalNoToBeSearched], mySearchSort[totalNoToBeSearched];
	for(int i=0; i<totalNoToBeSearched; i++){
		fscanf(fsearch, "%d", &mySearchRand[i].value);
		mySearchRand[i].comparisions = 0;
		mySearchRand[i].found = 0;
	}

	//qsort(mySearchRand,totalNoToBeSearched,4,cmpfunc);				//ascending order
	for(int i=0; i<totalNoToBeSearched; i++)
		mySearchSort[i] = mySearchRand[i];


		search(trand,mySearchRand,totalNoToBeSearched);
		search(tsort,mySearchSort,totalNoToBeSearched);

	printf("Random\n"); 
	printSearch(mySearchRand, totalNoToBeSearched);
	printf("Sorted\n");
	printSearch(mySearchSort, totalNoToBeSearched);

	int height_rand=0, height_sort=0;

	height_rand = findHeight(trand);
	height_sort = findHeight(tsort);

	printf("\nThe height of:\n");
	printf("Random : %d\n",height_rand );
	printf("Sorted : %d\n",height_sort );

	return 0;
}