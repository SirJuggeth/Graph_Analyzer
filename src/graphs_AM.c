/*
 * ---------------------------
 * CP264: Spring 2018
 * Graphs (Adjacency Matrix)
 * Header File
 * Author: Qutaiba Albluwi
 * ---------------------------
 */

/*
 -------------------------------------------------------
 Author:  Justin Harrott
 ID:      161449800
 Course:  CP264 Spring 2018
 Category: Assignment 10
 -------------------------------------------------------
 */

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <string.h>
# include "graphs_AM.h"

int _findpath_graph_AM_aux(GraphAM* g, int currV, int preV, int destV, int* cost, int tempCost, int* path, int* tempPath,
		int* steps, int tempSteps);
GraphAM* create_graph_AM() {
	GraphAM* g = (GraphAM*) malloc(sizeof(GraphAM));
	g->matrix = (int**) malloc(sizeof(int*) * 2); //create 2x2 matrix
	g->matrix[0] = (int*) malloc(sizeof(int) * 2);
	g->matrix[1] = (int*) malloc(sizeof(int) * 2);
	g->matrix[0][0] = -1;
	g->matrix[0][1] = -1;
	g->matrix[1][0] = -1;
	g->matrix[1][1] = -1;
	g->vertexList = (Vertex*) malloc(sizeof(Vertex));
	g->vertexCount = 0;
	g->edgeCount = 0;
	return g;\

}

void destroy_graph_AM(GraphAM** g) {
	int rows = (*g)->vertexCount;
	(*g)->vertexCount = 0;
	(*g)->edgeCount = 0;
	free((*g)->vertexList);
	(*g)->vertexList = NULL;
	int i;
	for (i = rows - 1; i >= 0; i--) {
		free((*g)->matrix[i]);
		(*g)->matrix[i] = NULL;
	}
	free((*g)->matrix);
	(*g)->matrix = NULL;
	free(*g);
	*g = NULL;
	return;
}

int isNull_graph_AM(GraphAM* g) {
	assert(g!=NULL);
	if (g->edgeCount == 0 && g->vertexCount == 0)
		return True;
	return False;
}

int isEmpty_graph_AM(GraphAM* g) {
	assert(g!=NULL);
	if (g->edgeCount == 0)
		return True;
	return False;
}

void print_graph_AM(GraphAM* g) {
	assert(g!=NULL);
	int i, j;
	printf("(Adjacency Matrix Representation): #Vertices = %d, #Edges = %d\n",
			g->vertexCount, g->edgeCount);
	if (isNull_graph_AM(g))
		printf("<null graph>\n");
	else if (g->vertexCount == 1) {
		printf("Single Vertex graph:\n");
		printf("%d\n", g->matrix[0][0]);
		printf("\n");
	}
	else {
		printf("Adjacency Matrix:\n");
		for (i = 0; i < g->vertexCount; i++) {
			for (j = 0; j < g->vertexCount; j++)
				printf("%5d", g->matrix[i][j]);
			printf("\n");
		}
	}
	return;
}

int addVertex_graph_AM(GraphAM* g, Vertex* v) {
	assert(g!=NULL);
	assert(v!=NULL);
	int success = 0;

	if (findVertex_graph_AM(g, v) == -1) { //vertex is not found
		//increase size of vertexList
		if (g->vertexCount > 0)
			g->vertexList = realloc(g->vertexList, sizeof(Vertex) * (g->vertexCount + 1));
		//force vertices to be numbered sequentially
		if (v->num != g->vertexCount)
			v->num = g->vertexCount;
		//add vertex to vertexList
		g->vertexList[g->vertexCount] = *v;
		g->vertexCount++;
		success = 1;
		//re-adjust size of adjacency matrix
		int i;
		if (g->vertexCount > 2) {
			//increment #rows
			g->matrix = realloc(g->matrix, sizeof(int*) * g->vertexCount);
			//increment #columns for each row
			for (i = 0; i < g->vertexCount - 1; i++) {
				g->matrix[i] = realloc(g->matrix[i], sizeof(int) * g->vertexCount);
				g->matrix[i][g->vertexCount - 1] = -1;
			}
			g->matrix[g->vertexCount - 1] = (int*) malloc(sizeof(int) * g->vertexCount);
			for (i = 0; i < g->vertexCount; i++)
				g->matrix[g->vertexCount - 1][i] = -1;
		}
	}
	else
		//vertex already exist
		printf("Error (addVertex_graph_AM): vertex already exist!\n");
	return success;
}

int findVertex_graph_AM(GraphAM* g, Vertex* v) {
	assert(g!=NULL);
	assert(v!=NULL);
	//only compares vertex names, because vertex numbering is enforced sequentially
	int i;
	if (strcmp(v->name, "") == 0)
		return -1;		//if vertex has no name, return not found
	for (i = 0; i < g->vertexCount; i++)
		if (strcmp(v->name, g->vertexList[i].name) == 0)
			return i;
	return -1; //not found
}

//if an edge already exist, it is replaced
int addEdge_graph_AM(GraphAM* g, Edge* e) {
	int success = 0;
	int v1_index = findVertex_graph_AM(g, e->v1);
	if (v1_index == -1 && e->v1->num >= g->vertexCount) {
		addVertex_graph_AM(g, e->v1);
		v1_index = g->vertexCount - 1;
	}
	else
		v1_index = e->v1->num;

	int v2_index = findVertex_graph_AM(g, e->v2);
	if (v2_index == -1 && e->v2->num >= g->vertexCount) {
		addVertex_graph_AM(g, e->v2);
		v2_index = g->vertexCount - 1;
	}
	else
		v2_index = e->v2->num;

	if (e->direction == 1 || e->direction == 0)
		g->matrix[v1_index][v2_index] = e->weight;
	else if (e->direction == -1)
		g->matrix[v2_index][v1_index] = e->weight;
	else if (e->direction == 2) {
		g->matrix[v1_index][v2_index] = e->weight;
		g->matrix[v2_index][v1_index] = e->weight;
		g->edgeCount++;
	}
	success = 1;
	g->edgeCount++;

	return success;
}

int removeEdge_graph_AM(GraphAM* g, Edge* e) {
	int success = 0;

	if (e->v1->num >= g->vertexCount || e->v2->num >= g->vertexCount || g->edgeCount == 0
			|| ((e->direction == 1 || e->direction == 1) && e->weight != g->matrix[e->v1->num][e->v2->num])
			|| (e->direction == -1 && e->weight != g->matrix[e->v2->num][e->v1->num])) { // only using numbers for vertices, not names
		fprintf(stderr, "Error (removeEdge_graph_AM): Edge does not exist\n");
		return success;
	}

	if (e->direction == 2) {

		g->matrix[e->v1->num][e->v2->num] = -1;
		g->matrix[e->v2->num][e->v1->num] = -1;
		g->edgeCount--;
	}
	else if (e->direction == 1 || e->direction == 0)
		g->matrix[e->v1->num][e->v2->num] = -1;
	else if (e->direction == -1)
		g->matrix[e->v2->num][e->v1->num] = -1;

	success = 1;
	g->edgeCount--;

	return success;
}

int removeVertex_graph_AM(GraphAM* g, Vertex* v) {
	int success = 0;

	if (v->num >= g->vertexCount || v->num >= g->vertexCount) {
		fprintf(stderr, "Error (removeVertex_graph_AM): Vertex does not exist\n");
		return success;
	}

	// decrement g->edgeCount
	int vEdges[g->vertexCount - 1];

	for (int i = 0; i < g->vertexCount; i++) {
		vEdges[i] = g->matrix[v->num][i];
		if (g->matrix[v->num][i] != -1)
			g->edgeCount--;
	}

	for (int i = 0; i < g->vertexCount; i++)
		if (g->matrix[i][v->num] != -1 && g->matrix[i][v->num] != vEdges[i])
			g->edgeCount--;

	// overwrite v
	if (v->num != g->vertexCount - 1) {
		for (int i = 0; i < g->vertexCount; i++)
			if (i != v->num) {
				// moving last row
				g->matrix[v->num][i] = g->matrix[g->vertexCount - 1][i];

				// moving last column
				g->matrix[i][v->num] = g->matrix[i][g->vertexCount - 1];
			}
	}

	// reallocate memory
	(int**) realloc(*g->matrix, sizeof(int*) * (g->vertexCount - 1) * (g->vertexCount - 1));

	g->vertexCount--;
	success = 1;

	return success;
}

//assumes directed weighted graph
int findpath_graph_AM(GraphAM* g, Vertex* v1, Vertex* v2) {
	// also assuming only positive weights

	int preV = -1, cost = 99999, tempCost = 0, steps = 1, tempSteps = 0, *path, tempPath[g->vertexCount];

	for (int i = 0; i < g->vertexCount; i++)
		tempPath[i] = 0;
	tempPath[0] = v1->num;
	path = &tempPath[0];

	cost = _findpath_graph_AM_aux(g, v1->num, preV, v2->num, &cost, tempCost, path, &tempPath[1], &steps, tempSteps);

	printf("Path from Vertex (%d) to Vertex (%d):\n", v1->num, v2->num);
	if (cost == 99999) {
		printf("No path was found\n");
		cost = -1;
	}
	else {
		int i = 0;
		for (i; i < steps; i++) {
			printf("(%d)-->", path[i]);
		}
		printf("(%d)\n", path[i]);
	}

	return cost;

	/*int costTot, cost[g->vertexCount], path[g->vertexCount], visited[g->vertexCount], currV, nextV, step, i;

	for (i = 0; i < g->vertexCount; i++)
		cost[i] = path[i] = visited[i] = 0;

	path[0] = costTot = g->matrix[v1->num][v2->num];
	step = 1;
	currV = visited[step] = v1->num;
	nextV = v2->num;

	while (currV != v2->num) {
		for (i = 0; i < g->vertexCount; i++) {
			if (g->matrix[currV][i] != -1 && (path[step] == -1 || g->matrix[currV][i] < path[step])) {
				int x = 0, j = 0;

				while (j <= step && x == 0) {
					if (visited[j] == i)
						x = 1;
					j++;
				}
				if (x == 0) {
					cost[step] = g->matrix[currV][i];
					path[step] = currV;
					nextV = i;
				}
			}
		}
		currV = nextV;
		step++;
	}

	printf("Path from Vertex (%d) to Vertex (%d):\n", v1->num, v2->num);
	if (step == 0 || path[step - 1] != v2->num)
		printf("No path was found\n");
	else {
		for (i = 0; i < step; i++) {
			printf("(%d)-->", path[i]);

			if (i == 0)
				costTot = 0;

			costTot += cost[i];
		}
		printf("(%d)\n", path[i]);
	}

	return costTot;
	 */
}

int _findpath_graph_AM_aux(GraphAM* g, int currV, int preV, int destV, int* cost, int tempCost, int* path, int* tempPath,
		int* steps, int tempSteps) {
	int TemP = -1;

	if (currV == destV) {
		if (tempCost < *cost) {
			TemP = *cost;
			*cost = tempCost;
			path = tempPath;
		}
		return TemP;
	}

	for (int i = 0; i < g->vertexCount; i++) {
		if (g->matrix[currV][i] != -1) {
			tempCost += g->matrix[currV][i];
			*tempPath = i;
			preV = currV;
			currV = i;
			TemP = _findpath_graph_AM_aux(g, currV, preV, destV, cost, tempCost, path, ++tempPath, steps, ++tempSteps);
		}
	}
	if (TemP != -1 && TemP > *cost) {
		path = tempPath;
	}
	return TemP;
}
