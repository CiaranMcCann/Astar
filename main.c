// Author: Ciaran McCann
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include "Utilities.h"
#include "GraphStructs.h"
#include "List.h"

#define DEBUG_MODE 1
#define READ_BYTE_SIZE 300
#define READ_BUFFER 500

// Predicate functions //

//Compare function used to find a node with name
int lookUpCmp(void * node, void * nodeName)
{
	//string compares a nodes name to a string passed in
	return (strncmp(trim(nodeName), trim( ((Node*)node)->name), strlen(nodeName)) == 0);
}

//Compares the Nodes so as to allow them be sorted
int nodeCompare(void * pNodeA, void * pNodeB)
{
	//Casting to actual types
	Node * nodeA = pNodeA;
	Node * nodeB = pNodeB;

	return (nodeA->actualCost + nodeA->estimatedCost) > (nodeB->actualCost + nodeB->estimatedCost);
}
// End Predicate functions //

//Straight line distance - Heuristic for aStar
int calcHeuristic(int x0, int y0, int x1, int y1)
{
	int x2 = x0 - x1;
	int y2 = y0 - y1; 
	int distance = (x2*x2)+(y2*y2);

	return (int) sqrt((double)distance);
}


void loadDataInGraph(char * path, List * nodeList, List * pathList)
{
	FILE * pFile;
	char buffer[READ_BUFFER];

	pFile = fopen(path, "r");

	//Seek - Skip first line
	fgets(buffer, READ_BYTE_SIZE, pFile);

	//Get the second line from file which is number of nodes
	fgets(buffer, READ_BYTE_SIZE, pFile);
	int numberOfNodes = atoi(buffer);

	int i = 0;
	char * nodeName;
	char * x;
	char * y;

	//Reading in each Node line
	while( i < numberOfNodes)
	{
		fgets(buffer, READ_BYTE_SIZE, pFile);
		split(buffer,3,&nodeName,&x,&y);

		Node * newNode = malloc(sizeof(Node));

		//Alocate memory for the stirng name
		newNode->name = malloc(sizeof(char)*strlen(nodeName));
		strcpy (newNode->name,nodeName);

		newNode->x = atoi(x);
		newNode->y = atoi(y);

		//Alocating the edge list for each node
		newNode->edgeList = ListAllocate();
		newNode->edges = (Edge*)malloc(sizeof(Edge*)*20);

		ListPush(nodeList,newNode, 0);

		i++;
	}

	free(nodeName);
	free(x);
	free(y);

	if(DEBUG_MODE == 1)
	{
		Link * iter = nodeList->mHead;
		while(iter!= 0)
		{          
			printf("Node [%s] created \n", ((Node *)iter->mData)->name);
			iter = iter->mNext;
		}
	}

	// Seek to next line two lines basically
	fgets(buffer, READ_BYTE_SIZE, pFile); // "EDGES"
	fgets(buffer, READ_BYTE_SIZE, pFile); // numEdges 

	char * nodeAName;
	char * nodeBName;
	char * weight;

	// While there are lines in the file and the line is not equal to PATHS
	while(fgets(buffer, READ_BYTE_SIZE, pFile) != NULL && strncmp(trim(buffer), "PATHS", 5) != 0)
	{
		split(buffer,3,&nodeAName,&nodeBName,&weight);

		if(DEBUG_MODE == 1)
		{
			printf("Buffer[%s] Edge: From Node [%s] to Node [%s] weight [%s]\n", buffer, nodeAName,nodeBName,weight);
		}

		Edge * edge = malloc(sizeof(Edge));
		edge->node = (Node*)ListFind(nodeList,nodeBName, lookUpCmp)->mData;
		edge->weight = atoi(weight);

		Node * node = ListFind(nodeList,nodeAName, lookUpCmp)->mData;
		ListPush(node->edgeList, edge, 0);
		//node->edges[node->numEdges] = edge;
		//node->numEdges++;
	}

	free(nodeAName);
	free(nodeBName);
	free(weight);

	//This just print out some useful information
	if(DEBUG_MODE == 1)
	{
		Link * nodeListIter = nodeList->mHead;;
		Node * currentNode = 0;

		while(nodeListIter != 0)
		{          
			currentNode = nodeListIter->mData;
			printf("Node [%s] has edges \n", currentNode->name);

			Link * edgeIter = currentNode->edgeList->mHead;
			Edge * currentEdge = 0;
			while( edgeIter != 0)
			{
				currentEdge = edgeIter->mData;		
				printf("	Edge to Node [%s] and a weight of %i \n", currentEdge->node->name, currentEdge->weight);

				edgeIter = edgeIter->mNext;
			}
			printf("\n");
			nodeListIter = nodeListIter->mNext;
		}
	}

	char * start;
	char * dest;
	//Get the paths to find
	while(fgets(buffer, READ_BYTE_SIZE, pFile) != NULL)
	{
		split(buffer,2,&start, &dest);

		Path * path  = malloc(sizeof(Path));
		path->nodeStart = ListFind(nodeList,start, lookUpCmp)->mData; 
		path->nodeDest = ListFind(nodeList,dest, lookUpCmp)->mData; 
		ListPush(pathList, path, 0);
	}

	free(start);
	free(dest);
}


void astar(List * graph, Node * start, Node * dest)
{
	List * closedList = ListAllocate();
	List * openedList = ListAllocate();

	Node * endNode = dest;

	//Holds the node current beging expanded
	Node * currentNode;

	start->estimatedCost = calcHeuristic( start->x, start->y, endNode->x, endNode->y);
	ListPush(openedList, start,nodeCompare);	

	// While the open list is not empty and the top of the open list instead the desition
	while(openedList->mLength > 0 && ListHead(openedList)->mData != endNode )
	{
		currentNode = ListPop(openedList)->mData;

		//printf("Expanding currentNode [%i] that has [%i] edges\n",currentNode->name, currentNode->numEdges);
		//expand connecting Nodes

		Link * edgeIter = currentNode->edgeList->mHead;
		Edge * currentEdge = 0;
		while( edgeIter != 0)
		{
			currentEdge = edgeIter->mData;

			Node * toExpand = currentEdge->node;
			toExpand->estimatedCost = calcHeuristic( toExpand->x, toExpand->y, endNode->x, endNode->y);
			toExpand->actualCost = currentEdge->weight;

			//Aside previous node so path can be traverised
			toExpand->previous = currentNode;
			
			//printf("Push Node %i onto openedList with emimatedCost %i and actualCost %i \n", toExpand->name, toExpand->estimatedCost, toExpand->actualCost );
			ListPush( openedList, toExpand, nodeCompare);
			
			edgeIter = edgeIter->mNext;
		}

		//Node has been completely expanded so put in closed list
		ListPush(closedList, currentNode,nodeCompare);
	}

	while(endNode != 0)
	{		
		printf("	Path %s \n", endNode->name);
		endNode = endNode->previous;
	}

}

int main(int argc, char* argv[])
{
	//ListRunAllTests();
	List * nodeList = ListAllocate();
	List * pathList = ListAllocate();

	if(argc>1)
	{
		//Read name of file from commandline
		loadDataInGraph(argv[1],nodeList,pathList);
	}else{
		loadDataInGraph("data.txt",nodeList,pathList);
	}	

	Link * pathListIter = pathList->mHead;
	Path * currentPath = 0;
	while(pathListIter != 0)
	{
		//Get Path pionter from void * mData 
		currentPath = pathListIter->mData;

		printf("\nRunning A * with start Node [%s] and dest [%s] \n", currentPath->nodeStart->name, currentPath->nodeDest->name);
		astar(nodeList, currentPath->nodeStart,currentPath->nodeDest);		

		//Increment the iteratior
		pathListIter = pathListIter->mNext;
	}
}
