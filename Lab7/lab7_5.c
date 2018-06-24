#include <stdio.h>

int total_vertex;

void createGraph(int m[total_vertex][total_vertex]){											//create m[n][n] with entries 1
	int vertex_start, vertex_end;
	printf("Enter the origin and the destination vertex. (-1 -1 to exit).\n");
	for (int i = 0; i < total_vertex*(total_vertex-1); i++){
		scanf("%d%d",&vertex_start,&vertex_end);
		if(vertex_start==-1 && vertex_end==-1)
			break;
		else
			m[vertex_start][vertex_end] = 1;
	}
}

void graphSquare(int G[total_vertex][total_vertex], int G2[total_vertex][total_vertex]){
	for (int i = 0; i < total_vertex; i++){
		for(int j=0; j<total_vertex; j++){
			if(G[i][j]==1){
				for(int k=0; k<total_vertex; k++){
					if(G[j][k]==1){																	//G = 1-->2-->3
						G2[i][k] = 1;																//G2= 1------>3
					}
				}
			}
		}
	}
}

void printGraph(int m[total_vertex][total_vertex]){
	printf("\t");
	for (int i = 0; i < total_vertex; i++){
		printf("%d  ",i);
	}
	printf("	\n");
	for (int i = 0; i < total_vertex; i++){
		printf("%d\t",i);
		for(int j=0; j<total_vertex; j++){
			if(m[i][j]==1)
				printf("1  ");
			else
				printf("0  ");
		}
		printf("\n");
	}
}
int main(){
	printf("Enter the no of vertices: \n");
	scanf("%d",&total_vertex);
	int matrixG[total_vertex][total_vertex], matrixG2[total_vertex][total_vertex];
	createGraph(matrixG);
	graphSquare(matrixG, matrixG2);
	printf("Graph G:\n\n");
	printGraph(matrixG);
	printf("Graph G2:\n\n");
	printGraph(matrixG2);
	return 0;
}