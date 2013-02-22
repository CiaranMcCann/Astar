#ifndef GRAPH_STRUCTS
#define GRAPH_STRUCTS value


typedef struct EdgeType Edge;

typedef struct{

	Edge ** edges; //ArcList
	int numEdges;

	int x;
	int y;


	int actualCost;
	int estimatedCost;
	
	int index;

}Node;

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

