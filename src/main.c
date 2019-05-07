/*
 * ---------------------------
 * CP264: Spring 2018
 * Graphs (Adjacency Matrix)
 * Test file
 * Author: Qutaiba Albluwi
 * ---------------------------
 */
# include <stdio.h>
# include <stdlib.h>
# include "graphs_AM.h"

void test_create_destroy();
void test_add_vertex();
void test_add_edge();
GraphAM* create_graph1(int directed, int weighted);
void test_create_graph1();
void test_removeEdge();
void test_removeVertex();
GraphAM* create_graph2();
void test_findpath();

int main() {
	setbuf(stdout, NULL);
//	test_create_destroy();
//	test_add_vertex();
//	test_add_edge();
//	test_create_graph1();
//	test_removeEdge();
//	test_removeVertex();
	test_findpath();
	return 0;
}

void test_create_graph1() {
	GraphAM* g;
	printf("undirected and non-weighted graph:\n");
	g = create_graph1(0, 0);
	print_graph_AM(g);
	printf("directed and non-weighted graph:\n");
	g = create_graph1(1, 0);
	print_graph_AM(g);
	printf("undirected and weighted graph:\n");
	g = create_graph1(0, 1);
	print_graph_AM(g);
	printf("directed and weighted graph:\n");
	g = create_graph1(1, 1);
	print_graph_AM(g);
	return;
}

void test_removeEdge() {
	GraphAM *g = create_graph1(1, 1);
	print_graph_AM(g);

	int i, w = 10;
	Vertex* v[5];
	Edge* e[7];

	for (i = 0; i < 5; i++)
		v[i] = create_vertex(i, "");


	for (i = 0; i < 3; i++)
		e[i] = create_edge(v[i], v[i + 1], (i + 1) * w, 1);
	e[3] = create_edge(v[3], v[0], w * 4, 1);
	e[4] = create_edge(v[0], v[2], w * 5, 1);
	e[5] = create_edge(v[1], v[3], w * 6, 1);
	e[6] = create_edge(v[4], v[1], w * 7, 1);

//	printf("[");
//	for (int i = 0; i < g->vertexCount; i++) {
//		for (int j = 0; j < g->vertexCount; j++)
//			print_edge(e[(i * g->vertexCount) + j]);
//			printf("[%d],", g->matrix[i][j]);
//		printf("\n");
//	}
//	printf("]");


	printf("\nRemoving Edge: ");
	print_edge(e[0]);
	printf("\n");
	removeEdge_graph_AM(g, e[0]);
	print_graph_AM(g);

	printf("\nRemoving Edge: ");
	print_edge(e[1]);
	printf("\n");
	removeEdge_graph_AM(g, e[1]);
	print_graph_AM(g);

	printf("\nRemoving Edge: ");
	print_edge(e[2]);
	printf("\n");
	removeEdge_graph_AM(g, e[2]);
	print_graph_AM(g);

	printf("\nRemoving Edge: ");
	print_edge(e[6]);
	printf("\n");
	removeEdge_graph_AM(g, e[6]);
	print_graph_AM(g);

	printf("\nRemoving Edge: ");
	print_edge(e[3]);
	printf("\n");
	removeEdge_graph_AM(g, e[3]);
	print_graph_AM(g);

	printf("\nRemoving Edge: ");
	print_edge(e[4]);
	printf("\n");
	removeEdge_graph_AM(g, e[4]);
	print_graph_AM(g);

	printf("\nRemoving Edge: ");
	print_edge(e[5]);
	printf("\n");
	removeEdge_graph_AM(g, e[5]);
	print_graph_AM(g);

	printf("\nRemoving Edge: ");
	print_edge(e[5]);
	printf("\n");
	removeEdge_graph_AM(g, e[5]);
	print_graph_AM(g);

	return;
}
void test_create_destroy() {
	GraphAM* g = create_graph_AM();
	print_graph_AM(g);
	printf("Making sure that all elements in adjacency matrix are set to -1:\n");
	printf("[[%d,%d],[%d,%d]]", g->matrix[0][0], g->matrix[0][1],
			g->matrix[1][0], g->matrix[1][1]);
	printf("\nDestroying the graph:\n");
	destroy_graph_AM(&g);
//	print_graph_AM(g);
	return;
}

void test_add_vertex() {
	GraphAM* g = create_graph_AM();
	printf("Creating an empty graph: \n");
	print_graph_AM(g);

	printf("\nCreating vertex: ");
	Vertex* v0 = create_vertex(0, "");
	print_vertex(v0);
	printf("\nAdding vertex to graph:\n");
	addVertex_graph_AM(g, v0);
	print_graph_AM(g);

	printf("\nCreating vertex: ");
	Vertex* v1 = create_vertex(1, "");
	print_vertex(v1);
	printf("\nAdding vertex to graph:\n");
	addVertex_graph_AM(g, v1);
	print_graph_AM(g);

	printf("\nCreating vertex: ");
	Vertex* v2 = create_vertex(2, "");
	print_vertex(v2);
	printf("\nAdding vertex to graph:\n");
	addVertex_graph_AM(g, v2);
	print_graph_AM(g);

	printf("\nCreating vertex: ");
	Vertex* v3 = create_vertex(3, "");
	print_vertex(v3);
	printf("\nAdding vertex to graph:\n");
	addVertex_graph_AM(g, v3);
	print_graph_AM(g);
	destroy_graph_AM(&g);
	return;
}

void test_add_edge() {
	GraphAM* g = create_graph_AM();
	printf("Creating an empty graph: \n");
	print_graph_AM(g);

	printf("\nAdding five vertices:\n");
	Vertex* v[5];
	int i;
	for (i = 0; i < 5; i++) {
		v[i] = create_vertex(i, "");
		addVertex_graph_AM(g, v[i]);
	}
	print_graph_AM(g);

	Edge* e1 = create_edge(v[0], v[1], 0, 0);
	printf("\nAdding edge: ");
	print_edge(e1);
	printf("\n");
	addEdge_graph_AM(g, e1);
	print_graph_AM(g);

	Edge* e2 = create_edge(v[2], v[1], 5, 2);
	printf("\nAdding edge: ");
	print_edge(e2);
	printf("\n");
	addEdge_graph_AM(g, e2);
	print_graph_AM(g);

	Vertex* v5 = create_vertex(7, "");
	Edge* e3 = create_edge(v5, v[3], 8, 2);
	printf("\nAdding edge: ");
	print_edge(e3);
	printf("\n");
	addEdge_graph_AM(g, e3);
	print_graph_AM(g);

	Vertex* v6 = create_vertex(9, "");
	Edge* e4 = create_edge(v[3], v6, 4, 1);
	printf("\nAdding edge: ");
	print_edge(e4);
	printf("\n");
	addEdge_graph_AM(g, e4);
	print_graph_AM(g);

	destroy_graph_AM(&g);
	return;
}

GraphAM* create_graph1(int directed, int weighted) {
	GraphAM* g = create_graph_AM();
	int i, d = 0, w = 0;
	Vertex* v[4];
	Edge* e[6];

	for (i = 0; i < 4; i++) {
		v[i] = create_vertex(i, "");
		addVertex_graph_AM(g, v[i]);
	}

	if (directed == 1)
		d = 1;
	if (weighted == 1)
		w = 10;

	for (i = 0; i < 3; i++)
		e[i] = create_edge(v[i], v[i + 1], (i + 1) * w, d);
	e[3] = create_edge(v[3], v[0], w * 4, d);
	e[4] = create_edge(v[0], v[2], w * 5, d);
	e[5] = create_edge(v[1], v[3], w * 6, d);

	for (i = 0; i < 6; i++)
		addEdge_graph_AM(g, e[i]);

	return g;
}

void test_removeVertex() {
	GraphAM *g = create_graph1(1, 1);
	print_graph_AM(g);
	int i;
	Vertex* v[5];
	for (i = 0; i < 5; i++)
		v[i] = create_vertex(i, "");

	printf("\nRemoving Vertex 1:\n");
	removeVertex_graph_AM(g, v[1]);
	print_graph_AM(g);

	printf("\nRemoving Vertex 4:\n");
	removeVertex_graph_AM(g, v[4]);
	print_graph_AM(g);

	printf("\nRemoving Vertex 2:\n");
	removeVertex_graph_AM(g, v[2]);
	print_graph_AM(g);

	printf("\nRemoving Vertex 0:\n");
	removeVertex_graph_AM(g, v[0]);
	print_graph_AM(g);

	printf("Removing Vertex 0:\n");
	removeVertex_graph_AM(g, v[0]);
	print_graph_AM(g);

	printf("\nRemoving Vertex 1:\n");
	removeVertex_graph_AM(g, v[1]);
	print_graph_AM(g);

	return;
}

GraphAM* create_graph2() {
	GraphAM* g = create_graph_AM();

	int i;
	Vertex* v[6];
	Edge* e[5];

	for (i = 0; i < 6; i++) {
		v[i] = create_vertex(i, "");
		addVertex_graph_AM(g, v[i]);
	}

	e[0] = create_edge(v[0], v[1], 10, 1);
	e[1] = create_edge(v[1], v[2], 20, 1);
	e[2] = create_edge(v[3], v[0], 50, 1);
	e[3] = create_edge(v[2], v[4], 30, 1);
	e[4] = create_edge(v[4], v[5], 40, 1);


	for (i = 0; i < 5; i++)
		addEdge_graph_AM(g, e[i]);
	return g;
}

void test_findpath() {
	GraphAM* g = create_graph2();
	print_graph_AM(g);
	Vertex* v[6];
	int i;

	for (i = 0; i < 6; i++)
		v[i] = create_vertex(i, "");

	int cost;
	printf("\n");
	cost = findpath_graph_AM(g, v[0], v[1]);
	printf("Cost = %d\n\n", cost);
	cost = findpath_graph_AM(g, v[1], v[0]);
	printf("Cost = %d\n\n", cost);
	cost = findpath_graph_AM(g, v[0], v[2]);
	printf("Cost = %d\n\n", cost);
	cost = findpath_graph_AM(g, v[3], v[2]);
	printf("Cost = %d\n\n", cost);
	cost = findpath_graph_AM(g, v[3], v[5]);
	printf("Cost = %d\n\n", cost);
	cost = findpath_graph_AM(g, v[5], v[3]);
	printf("Cost = %d\n\n", cost);
	cost = findpath_graph_AM(g, v[1], v[4]);
	printf("Cost = %d\n\n", cost);
	return;
}
