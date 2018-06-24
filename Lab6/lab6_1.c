#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s{
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
void mTOl(int m[TotalVertex][TotalVertex], list *l[TotalVertex]){
	int i,j;
	list *nxt;
	for(i=0;i<TotalVertex;i++){
		l[i]=malloc(sizeof(list));
		l[i]->v = i+1;
		l[i]->ptr = malloc(sizeof(list));
		nxt = l[i];
		for(j=0;j<TotalVertex;j++){
			if(m[i][j]){
				nxt = nxt->ptr;
				nxt->v = j+1;
				nxt->ptr = malloc(sizeof(list));
			}
		}
		nxt->ptr = NULL;
	}
}
void lToFile(list *l[TotalVertex], FILE *f){
	int i;
	list *nxt;
	for(i=0;i<TotalVertex;i++){
		fprintf(f,"%d",l[i]->v);
		nxt = l[i]->ptr;
		while(nxt!=NULL){
			fprintf(f," %d",nxt->v);
			nxt = nxt->ptr;
		}
		fprintf(f,"\n");
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
void mToFile(int m[TotalVertex][TotalVertex], FILE *f){
	int i,j;
	for(i=0;i<TotalVertex;i++){
		fprintf(f,"%d",m[i][0]);
		for(j=1;j<TotalVertex;j++)
			fprintf(f," %d",m[i][j]);
		fprintf(f,"\n");
	}	
}
int front=0, rear=0;
void BFS(int v,int m[TotalVertex][TotalVertex], int q[TotalVertex], int visited[TotalVertex]) {
 
    // make vertex v visited
    visited[v] = 1;
    // enqueue vertex v
    q[rear] = v; // insert at rear
    rear++; // increment rear
 
    while (rear != front) // condition for empty queue
    {
        // dequeue
        int u = q[front];
        printf("%d ", u+1);
        front++;
 
        // check adjacent nodes from u
        int i=0;
        for (i=0;i<TotalVertex;i++) {
            // if there is adjacent vertex enqueue it
            if (!visited[i] && m[u][i]) {
                q[rear] = i;
                rear++;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}
void DFS(int i, int m[TotalVertex][TotalVertex],int visited[TotalVertex])
{
    int j;
    printf("%d\n",i+1);
    visited[i]=1;
    
    for(j=0;j<TotalVertex;j++)
       if(!visited[j]&&m[i][j]==1)
            DFS(j,m,visited);
}
int main(){
	printf("1. Adjacency Matrix to Adjacency List\n");
	printf("2. Adjacency List to Adjacency Matrix\n");
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
	int q[TotalVertex],visited[TotalVertex],visited2[TotalVertex];
	for(int i=0;i<TotalVertex;i++){
		visited[i] = 0;
		q[i] = -1;
	}
	for(int i=0;i<TotalVertex;i++)
		visited2[i] = 0;
	if(serial==1){
		fileToMatrix(adm, fin);
		mTOl(adm, adl);
		FILE *fout = fopen("mTol","w");
		lToFile(adl, fout);
	}
	else{
		fileToList(adl, fin);
		lTOm(adl, adm);
		FILE *fout = fopen("lTom","w");
		mToFile(adm, fout);
	}
	printf("For BFS enter the starting vertex: ");
		int ver1;
		scanf("%d",&ver1);
		BFS(ver1-1,adm,q,visited);
		printf("For DFS enter the starting vertex: ");
		int ver2;
		scanf("%d",&ver2);
		DFS(ver2-1,adm,visited2);
	return 0;
}

