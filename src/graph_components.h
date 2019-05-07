/*
 * ---------------------------
 * CP264: Spring 2018
 * Graph Components (Vertex and Edge)
 * Header file
 * Author: Qutaiba Albluwi
 * ---------------------------
 */

#ifndef GRAPH_COMPONENTS_H_
#define GRAPH_COMPONENTS_H_

# define True 1
# define False 0

typedef struct{
	int num;
	char name[20];
}Vertex;

typedef struct{
	Vertex* v1;
	Vertex* v2;
	int weight;
	int direction; //0: undirected, 1: v1->v2, -1: v1<-v2, 2:v1<->v2
}Edge;

Vertex* create_vertex(int num, char* name);
Edge* create_edge(Vertex* v1, Vertex* v2, int w, int d);

void print_vertex(Vertex* v);
void print_edge(Edge* e);

void destroy_vertex(Vertex** v);
void destroy_edge(Edge** e);

int isEqualVertices(Vertex* v1, Vertex* v2);
int isEqualEdges(Edge* e1, Edge* e2);

#endif /* GRAPH_COMPONENTS_H_ */
