// Author: Ciaran McCann
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Utilities.h"
#include "SortedArray.h"
#include "GraphStructs.h"
#include "List.h"


//Stores all the Nodes in the graph
Node ** listOfnodes;
int numberOfNodes;

//Stores all the paths that need to be found
//Path listOfPaths[100]; //TODO need to implement LinkList!!
//int numberOfPaths;

#define READ_BYTE_SIZE 300

//Used to find a node by name in the list
int lookUpCmp(void * dataA, void * dataB)
{
    Node * node = dataA;
    char * name = dataB;

    //printf("Node %s looking for %s \n", node->name, name );
    return (strncmp(trim(name), trim(node->name), 4) == 0);
}

void loadData(char * path, List * nodeList, List * pathList)
{
	FILE * pFile;
	char buffer[500];

	pFile = fopen(path, "r");

	//Seek - Skip first line
	fgets(buffer, READ_BYTE_SIZE, pFile);

	//Get the second line from file which is number of nodes
	fgets(buffer, READ_BYTE_SIZE, pFile);
	numberOfNodes = atoi(buffer);

	//Get the number of edges from the file
	//fgets(buffer, READ_BYTE_SIZE, pFile);
	//int numberOfEdges = atoi(buffer);

	//Allocate nodes array on the heap
	//listOfnodes =  (Node*)malloc(sizeof(Node*)*numberOfNodes);

	int i = 0;
	//Reading in each Node line
	while( i < numberOfNodes)
	{
		fgets(buffer, READ_BYTE_SIZE, pFile);

		char* string;
		char* tofree;
		string = strdup(trim(buffer));

		if (string != NULL)
		{
			tofree = string;

			char * nodeName = strsep(&string, " ");
			char * x = strsep(&string, " ");
			char * y = strsep(&string, " ");

			//listOfnodes[i] = malloc(sizeof(Node)*numberOfNodes);

			Node * newNode = malloc(sizeof(Node));

			//Alocate memory for the stirng name
			newNode->name = malloc(sizeof(char)*strlen(nodeName));
			strcpy (newNode->name,nodeName);

			newNode->x = atoi(x);
			newNode->y = atoi(y);

			//Alocating the edge list for each node
			//TODO Fix spec to have edges first
			newNode->edges = (Edge*)malloc(sizeof(Edge*)*20);

			ListPush(nodeList,newNode, 0);

		  free(tofree);
		}

		i++;
	}

		Link * iter = nodeList->mHead;

            while(iter!= 0)
            {          
                Node * p = iter->mData;
                printf("Node [%s] created \n", p->name);

                iter = iter->mNext;
            }

	// printf("%s\n\n", "Nodes objects constructed");


	// //Seek to next line basically
	fgets(buffer, READ_BYTE_SIZE, pFile);


	// While there are lines in the file and the line is not equal to PATHS
	while(fgets(buffer, READ_BYTE_SIZE, pFile) != NULL && strncmp(trim(buffer), "PATHS", 4) != 0)
	{
		char* string;
		char* tofree;
		string = strdup(trim(buffer));

		if (string != NULL)
		{
			tofree = string;

			char * nodeAName = strsep(&string, " ");
			char * nodeBName = strsep(&string, " ");
			char * weight = strsep(&string, " ");

			printf("Buffer[%s] Edge: From Node [%s] to Node [%s] weight [%s]\n", buffer, nodeAName,nodeBName,weight);

			Edge * edge = malloc(sizeof(Edge));
			edge->node = ListFind(nodeList,nodeBName, lookUpCmp)->mData; //listOfnodes[atoi(nodeB)];
			edge->weight = atoi(weight);


			Node * node = ListFind(nodeList,nodeAName, lookUpCmp)->mData; //listOfnodes[atoi(nodeA)];
			node->edges[node->numEdges] = edge;
			node->numEdges++;

			//printf("Edge from %s to %s\n", node->name, edge->node->name );
			free(tofree);
		}
	}

	//Print out some in formative info for the user
	// printf("%s\n\n", "Edges objects constructed");
	// i = 0;
	// while( i < numberOfNodes)
	// {
	// 	printf("Node [%i] has edges \n", i);
	// 	int j = 0;
	// 	while(j < listOfnodes[i]->numEdges)
	// 	{
	// 		Edge * e = listOfnodes[i]->edges[j];

	// 		printf("	Edge to Node [%i] and a weight of %i \n", e->node->index , e->weight);
	// 		j++;
	// 	}
	// 	printf("\n");

	// 	i++;
	// }


	// //Get the paths to find
	// while(fgets(buffer, READ_BYTE_SIZE, pFile) != NULL)
	// {
	// 	char* string;
	// 	char* tofree;
	// 	string = strdup(trim(buffer));

	// 	if (string != NULL)
	// 	{
	// 	  tofree = string;

	// 	  Path path;
	// 	  path.nodeA = ListFind(nodeList,strsep(&string, " "), lookUpCmp)->mData; 
	// 	  path.nodeB = ListFind(nodeList,strsep(&string, " "), lookUpCmp)->mData; 
	// 	  printf("Path: from Node [%i] to Node [%i] \n", path.nodeA, path.nodeB );
	// 	  listOfPaths[numberOfPaths] = path;
	// 	  free(tofree);
	// 	}
	// 	numberOfPaths++;
	// }

}

//Straight line distance
int calcHeuristic(int x0, int y0, int x1, int y1)
{
	int x2 = x0 - x1;
	int y2 = y0 - y1; 
	int d = (x2*x2)+(y2*y2);

	return (int) sqrt((double)d);
}

int nodeCompare(void * a, void * b)
{
    Node * x = a;
    Node * y = b;

    return (x->actualCost + x->estimatedCost) > (y->actualCost + y->estimatedCost);
}

// void astar(Node ** graph, int numNodes, int start, int dest)
// {
// 	List * closedList = ListAllocate();
// 	List * openedList = ListAllocate();

// 	Node * endNode = graph[dest];

// 	graph[start]->estimatedCost = calcHeuristic( graph[start]->x, graph[start]->y, endNode->x, endNode->y);
// 	ListPush(openedList, graph[start],nodeCompare);
	
// 	Node * node;

// 	// While the open list is not empty and the top of the open list instead the desition
// 	while(openedList->mLength > 0 && ListHead(openedList)->mData != endNode )
// 	{
// 		node = ListPop(openedList)->mData;

// 		printf("Expanding node [%i] that has [%i] edges\n",node->index, node->numEdges);
// 		//expand connecting Nodes
// 		int i = 0;

// 		while( i < node->numEdges)
// 		{
// 			Node * toExpand = node->edges[i]->node;
// 			toExpand->estimatedCost = calcHeuristic( toExpand->x, toExpand->y, endNode->x, endNode->y);
// 			toExpand->actualCost = node->edges[i]->weight;

// 			//Aside previous node so path can be traverised
// 			toExpand->previous = node;
			
// 			printf("Push Node %i onto openedList with emimatedCost %i and actualCost %i \n", toExpand->index, toExpand->estimatedCost, toExpand->actualCost );
// 			ListPush( openedList, toExpand, nodeCompare);
			
// 			i++;
// 		}

// 		//Node has been completely expanded so put in closed list
// 		ListPush(closedList, node,nodeCompare);
// 	}

// 	printf("\n PATH \n");
// 	while(endNode != 0)
// 	{		
// 		printf("Pionter %i Index %i \n", endNode->previous, endNode->index);
// 		endNode = endNode->previous;
// 	}

// }

int main(int argc, char* argv[])
{

	printf("%s\n", "Program started");
	//ListRunAllTests();
	printf("%s\n", "Unit tests complete");

	List * nodeList = ListAllocate();
	List * pathList = ListAllocate();
	loadData("data.txt",nodeList,pathList);

	// int i = 0; 
	// while( i < numberOfPaths)
	// {
	// 	printf("\n\nRunning A * with start Node [%i] and dest [%i] \n", listOfPaths[i].nodeA,listOfPaths[i].nodeB);
	// 	astar(listOfnodes, numberOfNodes, listOfPaths[i].nodeA,listOfPaths[i].nodeB);		
	// 	i++;
	// }
}
