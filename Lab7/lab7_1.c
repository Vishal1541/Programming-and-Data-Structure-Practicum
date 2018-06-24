#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct s{															//Structure for list
	int v;
	struct list *ptr;
}list;

int TotalVertex=0;

void fileToMatrix(int m[TotalVertex][TotalVertex], FILE *f){
	int num,i,j;
	for(i=0;i<TotalVertex;i++)
		for(j=0;j<TotalVertex;j++){
			fscanf(f,"%d",&m[i][j]);
		}
}
void fileToList(list *l[TotalVertex], FILE *f){
	char *line = malloc(50);
	char *item = malloc(5);
	int i=0,len,j;
	list *nxt;
	while(fgets(line,50,f)){
		len = strlen(line);
		l[i] = malloc(sizeof(list));
		nxt = l[i];
		item = strtok(line," ");
		int space=1;
		for(j=0;j<len/2-1;j++){
			nxt->v = atoi(item);
			nxt->ptr = malloc(sizeof(list));
			if(space==len/2-1){
				item = strtok(NULL,"\n");
				nxt=nxt->ptr;
				nxt->v = atoi(item);
				nxt->ptr = NULL;
			}
			else{
				nxt=nxt->ptr;
				item = strtok(NULL," ");
				space++;
			}
		}
		i++;
	}
}
void lTOm(list *l[TotalVertex],int m[TotalVertex][TotalVertex] ){
	int i=0,j,k,V;
	list *nxt;
	for(i=0;i<TotalVertex;i++){
		nxt = l[i]->ptr;
		V = nxt->v;
		for(j=0;j<TotalVertex;j++){
			if(V==j+1){
				m[i][j] = 1;
				nxt = nxt->ptr;
				if(nxt!=NULL)	V = nxt->v;
			}
			else	m[i][j] = 0;
		}
	}
}
int back=0, front=0, lev_retrieve, isBipartite=1;
void BFS(int v,int m[TotalVertex][TotalVertex], int q[TotalVertex], int visited[TotalVertex], int colorcode[TotalVertex], int level[TotalVertex]) {
 
    																			// make vertex v visited
    visited[v] = 1;
    																			// enqueue vertex v
    q[front] = v; 																// insert at front
    level[front] = 1;
    colorcode[v] = 1;															//1->Red 0->Blue
    front++; 																	// increment front
 
    while (front != back) 														// condition for empty queue
    {
        																		// dequeue
        int u = q[back];
        lev_retrieve = level[back];
        printf("%d ", u);
        back++;
 
        																		// check adjacent nodes from u
        int i=0;
        for (i=0;i<TotalVertex;i++) {
            																	// if there is adjacent vertex enqueue it
            if (!visited[i] && m[u][i]) {
                q[front] = i;
                level[front] = lev_retrieve+1;									//prv level+1
                colorcode[i] = (lev_retrieve+1)%2;								//this level % 2
                front++;
                visited[i] = 1;
            }
            else if(visited[i] && m[u][i]){
            	if(colorcode[i] != ((lev_retrieve+1)%2)){						//color code not matched
            		isBipartite=0;
            		return;
            	}
            }
        }
    }
    printf("\n");
}
int main(){
	printf("1. Input file list\n");
	printf("2. Input file matrix\n");
	int serial;
	scanf("%d",&serial);
	printf("Enter the input file name: ");
	char *cinput = malloc(100);
	scanf("%s",cinput);
	FILE *fin = fopen(cinput,"r");
	char *linecount = malloc(50);
	while(fgets(linecount,50,fin))	TotalVertex++;
	rewind(fin);
	int adm[TotalVertex][TotalVertex];
	list *adl[TotalVertex];
	int q[TotalVertex],visited[TotalVertex];
	for(int i=0;i<TotalVertex;i++){												//Visited all 0
		visited[i] = 0;
		q[i] = -1;
	}
	if(serial==1){
		fileToList(adl, fin);
		lTOm(adl, adm);
	}
	else
		fileToMatrix(adm, fin);
	int colorcode[TotalVertex];													//1,0,1,...
	int level[TotalVertex];														//1,2,3,...
	for(int i=0;i<TotalVertex;i++)
		colorcode[i] = -1;
	BFS(0,adm,q,visited,colorcode,level);
	if(isBipartite==0)
		printf("Not bipartite.\n");
	else{
		printf("\tVertex\tColor\n\n");
		for(int i=0;i<TotalVertex;i++){
			if(colorcode[i]==1)
				printf("\t%d\tRed\n",i+1);
			else
				printf("\t%d\tGreen\n",i+1);
		}
	}
	return 0;
}

