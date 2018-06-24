#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000
int total_vertex, total_edges;
int min_cost = 0;

void getTotalVE(){
	printf("Enter the no of cities: \n");
	scanf("%d",&total_vertex);
	printf("Enter the no of edges: \n");
	scanf("%d",&total_edges);
	return;
}

void initMatrix(int m[total_vertex][total_vertex]){
	for(int i=0; i<total_vertex; i++)
		for(int j=0; j<total_vertex; j++){
			if(i==j)
				m[i][j] = 0;
			else
				m[i][j] = INF;
		}
		return;
}

void fillMatrix(int m[total_vertex][total_vertex]){
	int starting_vertex, ending_vertex, weight;
	for(int i=0; i<total_edges; i++){
		printf("Enter the starting, ending and weight of edge [%d]: ",i+1);
		scanf("%d%d%d",&starting_vertex,&ending_vertex,&weight);
		m[starting_vertex][ending_vertex] = weight;
		m[ending_vertex][starting_vertex] = weight;
	}
	return;
}

void printMatrix(int m[total_vertex][total_vertex]){
	printf("\n\t");
	for(int i=0; i<total_vertex; i++){
		printf("%d\t",i);
	}
	printf("\n");
	for(int i=0; i<total_vertex; i++){
		printf("%d\t",i);
		for(int j=0; j<total_vertex; j++)
			if(m[i][j]==INF)
				printf("INF\t");
			else
				printf("%d\t",m[i][j]);
		printf("\n");
	}
}

void spanningTreeMatrix (int row, int m[total_vertex][total_vertex], int spanM[total_vertex][total_vertex], int visited[total_vertex]){
	visited[row] = 1;
	int min_weight = INF, min_col_index, min_row_index;
	int col, rows;
	for(rows=0; rows<total_vertex; rows++){
		if(visited[rows])																//already spanned vertices
			for(col=0; col<total_vertex; col++){
				if((m[rows][col] < min_weight) && !visited[col]){						//outside vertex
					min_weight = m[rows][col];											//update min weight till now
					min_col_index = col;
					min_row_index = rows;
				}
			}
	}
	if(min_weight != INF){
		spanM[min_row_index][min_col_index] = min_weight;
		spanM[min_col_index][min_row_index] = min_weight;
		min_cost += min_weight;															//add to the min cost
		spanningTreeMatrix(min_col_index,m,spanM,visited);
		/*if(ret==0)
			ret = spanningTreeMatrix(row,m,spanM,visited);
		else
			return 1;*/
	}
	/*else
		return 0;
	*/
}

int main(){
		//FILE *file_input = fopen("input","r");
		getTotalVE();
		int matrix[total_vertex][total_vertex], spanning_tree_matrix[total_vertex][total_vertex];
		initMatrix(matrix);
		initMatrix(spanning_tree_matrix);
		fillMatrix(matrix);
		//printMatrix(matrix);
		int visited[total_vertex];
		for(int i=0; i<total_vertex; i++)
			visited[i] = 0;
		spanningTreeMatrix(0, matrix, spanning_tree_matrix, visited);
		printMatrix(spanning_tree_matrix);
		printf("\nThe minimum construction cost is %d\n",min_cost);
	return 0;
}