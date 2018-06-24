#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000
int total_vertex, total_edges;

void getTotalVE(){																	//user-input
	printf("Enter the no of cities: \n");
	scanf("%d",&total_vertex);
	printf("Enter the no of edges: \n");
	scanf("%d",&total_edges);
	return;
}

void initMatrix(int m[total_vertex][total_vertex]){									//INF <= i!=j, 0 <= i=j
	for(int i=0; i<total_vertex; i++)
		for(int j=0; j<total_vertex; j++){
			if(i==j)
				m[i][j] = 0;
			else
				m[i][j] = INF;
		}
		return;
}

void fillMatrix(int m[total_vertex][total_vertex]){									//origin-dest-edge weight
	int starting_vertex, ending_vertex, weight;
	for(int i=0; i<total_edges; i++){
		printf("Enter the starting, ending and weight of edge [%d]: ",i+1);
		scanf("%d%d%d",&starting_vertex,&ending_vertex,&weight);
		m[starting_vertex][ending_vertex] = weight;
		m[ending_vertex][starting_vertex] = weight;
	}
	return;
}

void setFlagAllZero(int flag[total_vertex]){										//make all unmarked
	for(int i=0; i<total_vertex; i++)
		flag[i] = 0;
}

void findShortestDistance(int v, int arr[total_vertex], int flag[total_vertex], int m[total_vertex][total_vertex]){
	flag[v] = 1;																	//make v as marked
	int distance = arr[v];															//previous distance (to be added later)
	for(int i=0; i<total_vertex; i++){
		if(flag[i]==0 && (m[v][i]+distance)<arr[i])									//if umarked and new dist < prv dist
			arr[i] = m[v][i]+distance;												//update the shortest dist
	}
	int temp_min_dist=INF, temp_min_dist_vertex;									//min dist in the arr[] till now
	for(int i=0; i<total_vertex; i++){	
		if(arr[i]<temp_min_dist && flag[i]==0){										//which are also unmarked
			temp_min_dist = arr[i];
			temp_min_dist_vertex = i;
		}
	}
	if(temp_min_dist!=INF)
		findShortestDistance(temp_min_dist_vertex, arr, flag, m);
	else																			//all are marked
		return;
}

void mapCities(char cities[total_vertex]){											//vertices to city name
	char city_name = 'A';
	for(int i=0; i<total_vertex; i++){
		cities[i] = city_name++;
	}
}

int main(){
		//FILE *file_input = fopen("input","r");
		getTotalVE();
		int matrix[total_vertex][total_vertex], shortest_dist[total_vertex], flag[total_vertex];
		char cities[total_vertex];
		mapCities(cities);
		initMatrix(matrix);															//0(i=j) and INF(i!=j)
		fillMatrix(matrix);															//user-input
		setFlagAllZero(flag);														//all verties unmarked
		printf("Enter the starting vertex number: \n");
		for(int i=0; i<total_vertex; i++)
			printf("%d - %c\n",i,cities[i]);
		int start_vertex;
		scanf("%d",&start_vertex);
		for(int i=0; i<total_vertex; i++){											//shortest dist => start vertex = 0, else INF
			if(i == start_vertex)
				shortest_dist[i] = 0;
			else
				shortest_dist[i] = INF;
		}
		findShortestDistance(start_vertex, shortest_dist, flag, matrix);
		printf("Shortest distance from city %c to \n",cities[start_vertex]);
		for(int i=0; i<total_vertex; i++)
			if(i!=start_vertex)
				printf("%c = %d\n",cities[i], shortest_dist[i]);
		return 0;
}