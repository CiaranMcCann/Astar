#ifndef GRAPH_STRUCTS
#define GRAPH_STRUCTS value
#include "List.h"


typedef struct EdgeType Edge;
//typedef struct Node NodeType;
//typedef struct Node Node;

typedef struct Node_t{

	List * edgeList;

	int x;
	int y;

	int actualCost;
	int estimatedCost;

	struct Node_t * previous;

	char * name;

} Node;

struct EdgeType{

	Node * node; //Node which it pionts to
	int weight;

};

typedef struct 
{
	Node * nodeStart;
	Node * nodeDest;

}Path;

#endif

