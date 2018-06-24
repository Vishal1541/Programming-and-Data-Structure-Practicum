#include <stdio.h>
#include <stdlib.h>

int total_vertex;
static int tail=-1, tail2=-1;

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

void graphTranspose(int m[total_vertex][total_vertex], int mT[total_vertex][total_vertex]){
	for (int i = 0; i < total_vertex; i++)
		for(int j=0; j<total_vertex; j++)
			if(m[i][j]==1)
				mT[j][i]=1;
}

void dfsSearch(int v, int m[total_vertex][total_vertex], int visited[total_vertex], int stack[total_vertex]){
	visited[v] = 1;
	for (int i = 0; i < total_vertex; i++){
		if(m[v][i]==1 & !visited[i]){
			dfsSearch(i, m, visited, stack);
		}
	}
	stack[++tail] = v;
}
int isVisitedAll(int visited[total_vertex]){
	for(int i=0; i<total_vertex; i++)
		if(visited[i]==0)
			return 0;
	return 1;
}
int popFromStack(int stack[total_vertex]){
	if(tail==-1)
		return -1;
	return stack[tail--];
}
void stronglyConnectedGroups(int m[total_vertex][total_vertex], int visited[total_vertex], int stack[total_vertex]){
	int popped_vertex = popFromStack(stack);
	if(!visited[popped_vertex]){

	}
}
int main(){
	printf("Enter the no of vertices: \n");
	scanf("%d",&total_vertex);
	int matrix[total_vertex][total_vertex], matrixT[total_vertex][total_vertex], visited[total_vertex], stack[total_vertex];
	createGraph(matrix);
	graphTranspose(matrix, matrixT);
	for (int i = 0; i < total_vertex; i++)
		visited[i] = 0;
	dfsSearch(0, matrix, visited, stack);
	for (int i = 0; i < total_vertex; i++)
		if(visited[i]==0)
			dfsSearch(i, matrix, visited, stack);
	for (int i = 0; i <= tail; ++i)
	{
		printf("%d\n",stack[i]);
	}
	for (int i = 0; i < total_vertex; i++)
		visited[i] = 0;


	return 0;
}