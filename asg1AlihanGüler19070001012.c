#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef struct {
    int source,                                
        destination,                           
        weight;                                
}EDGE;                                         

typedef struct{
    int num_vertices,                          
        num_edges;                             
    EDGE *edges;                               
}GRAPH;                                        

GRAPH *init_graph(int vertices, int edges);    
void fill_graph(GRAPH *graph);                 

void heap_sort(EDGE *edgeList,int numVertices);
int is_cycle(int dest,int destArr[]);
GRAPH Kruskals_MST(GRAPH *graph);               

int main() {

    GRAPH *graph = init_graph(10, 14);         
    fill_graph(graph);                         
    Kruskals_MST(graph);                       
    return 0;
}

GRAPH *init_graph(int vertices, int edges) {

    GRAPH *graph = calloc(1, sizeof(*graph));  
    if(graph == NULL) {                        
        printf("Error:");                      
        exit(EXIT_FAILURE);                    
    }
    graph->num_vertices = vertices;            
    graph->num_edges = edges;                  
    graph->edges = calloc(edges, sizeof(EDGE));

    if(graph->edges == NULL){                  
        printf("Error:");                      
        exit(EXIT_FAILURE);                    
    }
    return graph;                              
}

void fill_graph(GRAPH *graph){

    graph->edges[0].source = 1;                
    graph->edges[0].destination = 3;           
    graph->edges[0].weight = 12;               

    graph->edges[1].source = 1;                
    graph->edges[1].destination = 2;           
    graph->edges[1].weight = 4;                

    graph->edges[2].source = 2;                
    graph->edges[2].destination = 5;           
    graph->edges[2].weight = 10;               

    graph->edges[3].source = 3;                
    graph->edges[3].destination = 5;           
    graph->edges[3].weight = 2;                

    graph->edges[4].source = 3;                
    graph->edges[4].destination = 4;           
    graph->edges[4].weight = 7;                

    graph->edges[5].source = 4;                
    graph->edges[5].destination = 5;           
    graph->edges[5].weight = 3;                

    graph->edges[6].source = 4;                
    graph->edges[6].destination = 6;           
    graph->edges[6].weight = 8;                

    graph->edges[7].source = 5;                
    graph->edges[7].destination = 6;           
    graph->edges[7].weight = 9;                

    graph->edges[8].source = 6;                
    graph->edges[8].destination = 7;           
    graph->edges[8].weight = 11;               

    graph->edges[9].source = 6;                
    graph->edges[9].destination = 8;           
    graph->edges[9].weight = 1;                

    graph->edges[10].source = 7;               
    graph->edges[10].destination = 8;          
    graph->edges[10].weight = 13;              

    graph->edges[11].source = 7;               
    graph->edges[11].destination = 10;         
    graph->edges[11].weight = 6;               

    graph->edges[12].source = 8;               
    graph->edges[12].destination = 9;          
    graph->edges[12].weight = 5;               

    graph->edges[13].source = 9;               
    graph->edges[13].destination = 10;         
    graph->edges[13].weight = 14;              
}

void sortList(EDGE *edgeList){									//Time Complexity is (n-1)*n = O(n^2)
	int i,j;
	for(i=0;i<13;i++){ // let's travel all our edgeList. In this loop i<13 because we are gonna sort our edgeList. So for the last element we don't need to any sort operation.
		for(j=0;j<14;j++){
			if(edgeList[j].weight>edgeList[j+1].weight){// if jth index of our list greater than j+1th then swap it.
				EDGE tmp = edgeList[j];//basic swap operation.
				edgeList[j] = edgeList[j+1];//basic swap operation.
				edgeList[j+1] = tmp;//basic swap operation.
			}
		}
	}
}

int is_cycle(int dest,int destArr[]) {							//Time Complexity is n = O(n)
	int i,size = 9;
	for(i=0;i<size;i++){// we are travelling our previous destinations that we go.
		if(destArr[i] == dest){//IF we have already go that destination then return 1 because it means that there will be a cycle!
			return 1;
		}
	}
    return 0;// If we don't have visited this destination then return 0. There won't be any cycle.
}

GRAPH Kruskals_MST(GRAPH *graph){

    GRAPH *subGraph = init_graph(graph->num_vertices,graph->num_vertices-1);//i created a subgraph for my MST.
    EDGE *edgeList = (EDGE *)malloc(sizeof(EDGE)*graph->num_edges);//I have created a list to keep the edges of graph.
	int i,count = 0;
	for(i=0;i<graph->num_edges;i++){//Now fill the list with edges using our graph.
		edgeList[i] = graph->edges[i];
	}
	sortList(edgeList);//i sorted my list according to ascending weight order.
	int cost = 0;
	int destArr[9] = {0};// i created an array to keep my visited destination. This array will be usfeul while writing is_cycle() function.
	for(i=0;i<graph->num_edges;i++){//now this loop will fill my subgraph that gives us a minimum spanning tree.
		if(is_cycle(edgeList[i].destination,destArr)==0){//lets check the subgraph is it cycle or not.
			subGraph->edges[count] = edgeList[i];//add the possible minimum weight of edges to our subgraph.
			destArr[count] = edgeList[i].destination;//add this edges destination info to this array. This is for check the cycle case. If we reach a destination that in the desatArr it means that this is gonna be a cycle!
			cost += edgeList[i].weight;
			count++;// this variable is gonna be our subgraph's edges num. That's why we are not iterate this count every time in this loop.
		}
	}
	printf("The minimum cost of our spanning tree is : %d \n",cost);//print the cost of spannign tree(Our solution).
	free(edgeList);//we can free our sorted edge list.
    return ;
}
/*******************		THE REPORT OF THE CODE IS BELOW		***************************/
/*
	1 - The Complexity of Kruskal's Algorithm:
	GRAPH Kruskals_MST(GRAPH *graph){											T(1)
    GRAPH *subGraph = init_graph(graph->num_vertices,graph->num_vertices-1);	T(1)
    EDGE *edgeList = (EDGE *)malloc(sizeof(EDGE)*graph->num_edges);				T(1)
	int i,count = 0;															T(1)
	for(i=0;i<graph->num_edges;i++){											n times
		edgeList[i] = graph->edges[i];											T(n)
	}
	sortList(edgeList);															T(n^2)
	
	int destArr[9] = {0};														T(1)
	for(i=0;i<graph->num_edges;i++){											n times
		if(is_cycle(edgeList[i].destination,destArr)==0){						T(n)
			subGraph->edges[count] = edgeList[i];								
			destArr[count] = edgeList[i].destination;
			count++;
		}
	}
	free(edgeList);//we can free our sorted edge list.							T(1)
    return ;
}											TOTAL COST = 6*T(1)+2*T(n)+T(n^2) = O(n^2)
	2 - I could not implement heap sort for Kruskal MST.
	3 - In Prim's algorithm while we are looking for the shortest path, if we found it
	then we don't directly get that path. Instead of this, we are comparing that path
	with the other path that is our starting point's other path(other path has largest 
	weight that our path at the same time it is shortest path after our first path).
	This algorithm can connect The graphs that haven't got any connections. But in the 
	Kruskal's algorithm, first we are sorting our edges according to their weights. Then
	we are taking these edges without create any cycle. The time complexity of Prim's
	is O(Elog(V)). Kruskal's cost is if we use the heap sort while sorting the weighted
	edges, O(nlog(n)). But if we use normal sorting like bubble sort the cost will be
	O(n^2).
	4 - In this assignment we have used 2 different structure called GRAPH and EDGE.
	We have used GRAPH structure to create a graph and we have used EDGE structure to connect
	our vertices each other according to their sources,destinations and weights.
*/
