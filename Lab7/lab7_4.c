#include <stdio.h>
#include <stdlib.h>

int total_vertex;

void createGraph(int m[total_vertex][total_vertex]){										//create m[n][n] with entries 1
	int vertex_start, vertex_end;
	printf("Enter the start and the end vertex.\n");
	for (int i = 0; i < total_vertex*(total_vertex-1); i++){
		scanf("%d%d",&vertex_start,&vertex_end);
		if(vertex_start==-1 && vertex_end==-1)
			break;
		else
			m[vertex_start][vertex_end] = 1;
	}
}
static int count=0;
void DFS(int v, int m[total_vertex][total_vertex], int visited[total_vertex]){
	visited[v] = 1;
	for (int i = 0; i < total_vertex; i++)
		if (m[v][i]==1 && !visited[i]){
			printf("%5d",i);																//vertex reachable from v
			count++;
			DFS(i,m,visited);
		}
}
int main()
{	
	printf("Enter the number of vertices.\n");
	scanf("%d",&total_vertex);
	int matrix[total_vertex][total_vertex], sorted_graph[total_vertex+1];
	createGraph(matrix);
	int visited[total_vertex];
	for (int i = 0; i < total_vertex; i++)
		visited[i] = 0;
	printf("Enter the vertex no: \n");
	int vertex;
	scanf("%d",&vertex);
	DFS(vertex,matrix,visited);
	if(count==0)
		printf("No vertex is reachable from the given vertex '%d'.\n",vertex);
	printf("\n");
	return 0;
}