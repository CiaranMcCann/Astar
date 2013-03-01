#ifndef GRAPH_STRUCTS
#define GRAPH_STRUCTS value


typedef struct EdgeType Edge;
//typedef struct Node NodeType;
//typedef struct Node Node;

typedef struct Node_t{

	Edge ** edges; //ArcList
	int numEdges;

	int x;
	int y;


	int actualCost;
	int estimatedCost;

	struct Node_t * previous;
	
	int index;

} Node;

struct EdgeType{

	Node * node; //Node which it pionts to
	int weight;

};

typedef struct 
{
	int nodeA;
	int nodeB;

}Path;

#endif

