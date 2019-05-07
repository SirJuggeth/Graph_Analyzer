/*
 * ---------------------------
 * CP264: Spring 2018
 * Graphs (Adjacency Matrix)
 * Header File
 * Author: Qutaiba Albluwi
 * ---------------------------
 */

#ifndef GRAPHS_AM_H_
#define GRAPHS_AM_H_

# include "graph_components.h"

typedef struct{
	int** matrix;		//adjacency matrix
	Vertex* vertexList;	//Needed if vertices has names
	int vertexCount;
	int edgeCount;
}GraphAM;

GraphAM* create_graph_AM();
void destroy_graph_AM(GraphAM** g);
int isNull_graph_AM(GraphAM* g);
int isEmpty_graph_AM(GraphAM* g);
int getVertexCount_graph_AM(GraphAM* g);
int getEdgeCount_graph_AM(GraphAM* g);
void print_graph_AM();
int addVertex_graph_AM(GraphAM* g, Vertex* v);
int findVertex_graph_AM(GraphAM* g, Vertex* v);
int addEdge_graph_AM(GraphAM* g, Edge* e);

//for A10
int removeEdge_graph_AM(GraphAM* g, Edge* e);
int removeVertex_graph_AM(GraphAM* g, Vertex* v);
int findpath_graph_AM(GraphAM* g, Vertex* v1, Vertex* v2);

#endif /* GRAPHS_AM_H_ */
