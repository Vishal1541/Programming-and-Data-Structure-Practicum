#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000
int total_vertex, total_edges;

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

void getVertexWeights(int vertex_weight[total_vertex]){
	int v_weight;
	for(int i=0; i<total_vertex; i++){
		printf("Enter the weight of vertex [%d]: ",i);
		scanf("%d",&v_weight);
		vertex_weight[i] = v_weight;
	}
}

void setFlagAllZero(int flag[total_vertex]){
	for(int i=0; i<total_vertex; i++)
		flag[i] = 0;
}

void findShortestDistance(int v, int shortest_dist[total_vertex], int flag[total_vertex], int m[total_vertex][total_vertex], int vertex_weight[total_vertex]){
	flag[v] = 1;
	int distance = shortest_dist[v];
	for(int i=0; i<total_vertex; i++){
		if(flag[i]==0 && (m[v][i]+vertex_weight[i]+distance)<shortest_dist[i])
			shortest_dist[i] = m[v][i]+vertex_weight[i]+distance;
	}
	int temp_min_dist=INF, temp_min_dist_vertex;
	for(int i=0; i<total_vertex; i++){
		if(shortest_dist[i]<temp_min_dist && flag[i]==0){
			temp_min_dist = shortest_dist[i];
			temp_min_dist_vertex = i;
		}
	}
	if(temp_min_dist!=INF)
		findShortestDistance(temp_min_dist_vertex, shortest_dist, flag, m, vertex_weight);
	else
		return;
}

void updateDistance(int shortest_dist[total_vertex], int update){
	for(int i=0; i<total_vertex; i++)
		shortest_dist[i] = shortest_dist[i] + update;
}

void mapCities(char cities[total_vertex]){
	char city_name = 'A';
	for(int i=0; i<total_vertex; i++){
		cities[i] = city_name++;
	}
}

int main(){
		//FILE *file_input = fopen("input2","r");
		getTotalVE();
		int matrix[total_vertex][total_vertex], shortest_dist[total_vertex], vertex_weight[total_vertex], flag[total_vertex];
		char cities[total_vertex];
		mapCities(cities);
		initMatrix(matrix);
		fillMatrix(matrix);
		getVertexWeights(vertex_weight);
		setFlagAllZero(flag);
		printf("Enter the starting vertex number: \n");
		for(int i=0; i<total_vertex; i++)
			printf("%d - %c\n",i,cities[i]);
		int start_vertex;
		scanf("%d",&start_vertex);
		for(int i=0; i<total_vertex; i++){
			if(i == start_vertex)
				shortest_dist[i] = 0;
			else
				shortest_dist[i] = INF;
		}
		findShortestDistance(start_vertex, shortest_dist, flag, matrix, vertex_weight);
		updateDistance(shortest_dist, vertex_weight[start_vertex]);
		printf("Shortest distance from city %c to \n",cities[start_vertex]);
		for(int i=0; i<total_vertex; i++)
			if(i!=start_vertex)
				printf("%c = %d\n",cities[i], shortest_dist[i]);
		return 0;
}