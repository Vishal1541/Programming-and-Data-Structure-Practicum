#include <stdio.h>
#include <stdlib.h>

int total_vertex;
static int head = -1, tail = -1;

void createGraph(int m[total_vertex][total_vertex]){								//create m[n][n] with entries 1
	int vertex_start, vertex_end;
	printf("Enter the child and the child whom he hates. (-1 -1 to exit).\n");
	for (int i = 0; i < total_vertex*(total_vertex-1); i++){
		scanf("%d%d",&vertex_start,&vertex_end);
		if(vertex_start==-1 && vertex_end==-1)
			break;
		else
			m[vertex_start][vertex_end] = 1;
	}
}
int getInDegree(int v, int m[total_vertex][total_vertex]){							//edges coming into v
	int indegree = 0;
	for(int i=0;i<total_vertex;i++)
		if(m[i][v]==1)
			indegree++;
	return indegree;
}
void addToQueue(int v, int q[total_vertex]){
	if(tail == -1)
		tail = 0;
	q[++head] = v;
}
int isQueueEmpty(int q[total_vertex]){
	if(tail == -1 || tail > head)
		return 1;
	else
		return 0;
}
int popFromQueue(int q[total_vertex]){
	return (q[tail++]);
}
int main()
{	
	int count = 0, popped_vertex;
	printf("Enter the number of children.\n");
	scanf("%d",&total_vertex);
	int matrix[total_vertex][total_vertex], sorted_graph[total_vertex+1];
	createGraph(matrix);															//matrix with entries 1 created
	int in_degree[total_vertex], queue[total_vertex];
	for(int i=0;i<total_vertex;i++){
		in_degree[i] = getInDegree(i,matrix);
		if(in_degree[i]==0)
			addToQueue(i,queue);													//++head
	}
	while(!isQueueEmpty(queue) && count<total_vertex){								//while tail<=head
		popped_vertex = popFromQueue(queue);										//tail++
		sorted_graph[++count] = popped_vertex;										//finally sorted one
		for (int i = 0; i < total_vertex; i++)
			if (matrix[popped_vertex][i]==1)										//2-->4-->5
			{
				matrix[popped_vertex][i] = 0;										//2   4-->5
				in_degree[i]--;
				if (in_degree[i]==0)
					addToQueue(i,queue);
			}
	}																				//after while count should be = total_vertex
	if(count<total_vertex){															//while loop breaked early
		printf("Cyclic graph. Arrangment not possible.\n");
		exit(1);
	}
	printf("Order of childern: \n");
	for (int i = count; i >= 1; i--)
		printf("%5d",sorted_graph[i]);
	printf("\n");
	return 0;
}