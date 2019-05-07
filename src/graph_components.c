/*
 * ---------------------------
 * CP264: Spring 2018
 * Graph Components (Vertex and Edge)
 * Source file
 * Author: Qutaiba Albluwi
 * ---------------------------
 */

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <string.h>
# include "graph_components.h"


//------------------- Vertex -----------------------
Vertex* create_vertex(int num, char* name){
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->num = num;
	strcpy(v->name,name);
	return v;
}

void print_vertex(Vertex* v){
	assert(v!=NULL);
	if (!strcmp(v->name,""))
		printf("(%d)",v->num);
	else
		printf("(%d,%s)",v->num,v->name);
	return;
}

void destroy_vertex(Vertex** v){
	(*v)->num = 0;
	strcpy((*v)->name,"");
	free(*v);
	(*v) = NULL;
	return;
}

int isEqualVertices(Vertex* v1, Vertex* v2){
	assert(v1!=NULL);
	assert(v2!=NULL);
	if(v1->num == v2->num && strcmp(v1->name,v2->name) == 0)
		return True;
	return False;
}
//--------------------- Edge -----------------------------

Edge* create_edge(Vertex* v1, Vertex* v2, int w, int d){
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->v1 = v1;
	e->v2 = v2;
	e->weight = w;
	e->direction = d;
	return e;
}

void destroy_edge(Edge** e){
	(*e)->v1 = NULL;
	(*e)->v2 = NULL;
	(*e)->weight = 0;
	(*e)->direction = 0;
	free(*e);
	*e = NULL;
}
void print_edge(Edge* e){
	assert(e!=NULL);
	printf("[");
	print_vertex(e->v1);
	if(e->direction == -1 || e->direction == 2)
		printf("<");
	printf("-");
	if(e->weight == 0)
		printf("-");
	else
		printf("%d",e->weight);
	printf("-");
	if(e->direction == 1 || e->direction == 2)
		printf(">");
	print_vertex(e->v2);
	printf("]");
	return;
}

int isEqualEdges(Edge* e1, Edge* e2){
	assert(e1!=NULL);
	assert(e2!=NULL);
	if(e1->weight != e2->weight)
		return False;
	if(isEqualVertices(e1->v1, e1->v1)){
		if(isEqualVertices(e1->v2, e2->v2)){
			if (e1->direction == e2->direction)
				return True;
			if (e1->direction == 2 || e2->direction == 2)
				return True;
		}
	}

	if(isEqualVertices(e1->v1, e2->v2)){
		if(isEqualVertices(e1->v2, e2->v1)){
			if(e1->direction == 2 && e2->direction == 2)
				return True;
			else if (e1->direction == e2->direction*-1)
				return True;
		}
	}
	return False;
}
