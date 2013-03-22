#ifndef GRAPH_STRUCTS
#define GRAPH_STRUCTS value
#include "List.h"


typedef struct EdgeType Edge;

/*! \brief Graph Node structure
 */
typedef struct Node_t{

	List * edgeList; /*!< List of the edges this node has */

	int x; 
	int y;

	int actualCost; 
	int estimatedCost;


	struct Node_t * previous;
	char * name;

} Node;

/*! \brief Edges which connect the Nodes
 */
struct EdgeType{

	Node * node; /*!< Node which this edge connects to*/ 
	int weight;

};

/*! \brief Path to test, start and dest nodes
 */
typedef struct 
{
	Node * nodeStart;
	Node * nodeDest;

}Path;

#endif

