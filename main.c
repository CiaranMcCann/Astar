// Author: Ciaran McCann
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include "Utilities.h"
#include "SortedArray.h"
#include "GraphStructs.h"
#include "List.h"

#define READ_BYTE_SIZE 300
#define READ_BUFFER 500

//Compare function used to find a node with name
int lookUpCmp(void * node, void * nodeName)
{
	//string compares a nodes name to a string passed in
	return (strncmp(trim(nodeName), trim( ((Node*)node)->name), strlen(nodeName)) == 0);
}

void loadData(char * path, List * nodeList, List * pathList)
{
	FILE * pFile;
	char buffer[READ_BUFFER];

	pFile = fopen(path, "r");

	//Seek - Skip first line
	fgets(buffer, READ_BYTE_SIZE, pFile);

	//Get the second line from file which is number of nodes
	fgets(buffer, READ_BYTE_SIZE, pFile);
	int numberOfNodes = atoi(buffer);

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

		char * nodeName;
		char * x;
		char * y;
		split(buffer,3,&nodeName,&x,&y);

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
		char * nodeAName;
		char * nodeBName;
		char * weight;
		split(buffer,3,&nodeAName,&nodeBName,&weight);

		printf("Buffer[%s] Edge: From Node [%s] to Node [%s] weight [%s]\n", buffer, nodeAName,nodeBName,weight);

		Edge * edge = malloc(sizeof(Edge));
		edge->node = (Node*)ListFind(nodeList,nodeBName, lookUpCmp)->mData;
		edge->weight = atoi(weight);

		Node * node = ListFind(nodeList,nodeAName, lookUpCmp)->mData;
		node->edges[node->numEdges] = edge;
		node->numEdges++;

		//printf("Edge from %s to %s\n", node->name, edge->node->name );
	}

	printf("%s\n\n", "Edges objects constructed");
	Link * nodeListIter = nodeList->mHead;;
	Node * currentNode = 0;

	//This just print out some useful information
	while(nodeListIter != 0)
	{          
		//printf("Node [%i] has edges \n", i);
		currentNode = nodeListIter->mData;
		printf("Node [%s] has edges \n", currentNode->name);
		int j = 0;
		while(j < currentNode->numEdges)
		{
			Edge * e = currentNode->edges[j];

			printf("	Edge to Node [%s] and a weight of %i \n", e->node->name, e->weight);
			j++;
		}
		printf("\n");
		nodeListIter = nodeListIter->mNext;
	}

	//Get the paths to find
	while(fgets(buffer, READ_BYTE_SIZE, pFile) != NULL)
	{
		char * start;
		char * dest;
		split(buffer,2,&start, &dest);

		Path * path  = malloc(sizeof(Path));
		path->nodeStart = ListFind(nodeList,start, lookUpCmp)->mData; 
		path->nodeDest = ListFind(nodeList,dest, lookUpCmp)->mData; 
		//printf("Created Path: from Node [%s] to Node [%s] \n", path->nodeA->name, path->nodeB->name );
		ListPush(pathList, path, 0);
	}

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

void astar(List * graph, Node * start, Node * dest)
{
	List * closedList = ListAllocate();
	List * openedList = ListAllocate();

	Node * endNode = dest;

	start->estimatedCost = calcHeuristic( start->x, start->y, endNode->x, endNode->y);
	ListPush(openedList, start,nodeCompare);
	
	Node * node;

	// While the open list is not empty and the top of the open list instead the desition
	while(openedList->mLength > 0 && ListHead(openedList)->mData != endNode )
	{
		node = ListPop(openedList)->mData;

		//printf("Expanding node [%i] that has [%i] edges\n",node->name, node->numEdges);
		//expand connecting Nodes
		int i = 0;

		while( i < node->numEdges)
		{
			Node * toExpand = node->edges[i]->node;
			toExpand->estimatedCost = calcHeuristic( toExpand->x, toExpand->y, endNode->x, endNode->y);
			toExpand->actualCost = node->edges[i]->weight;

			//Aside previous node so path can be traverised
			toExpand->previous = node;
			
			//printf("Push Node %i onto openedList with emimatedCost %i and actualCost %i \n", toExpand->name, toExpand->estimatedCost, toExpand->actualCost );
			ListPush( openedList, toExpand, nodeCompare);
			
			i++;
		}

		//Node has been completely expanded so put in closed list
		ListPush(closedList, node,nodeCompare);
	}

	while(endNode != 0)
	{		
		printf("	Path %s \n", endNode->name);
		endNode = endNode->previous;
	}

}

int main(int argc, char* argv[])
{

	printf("%s\n", "Program started");
	//ListRunAllTests();
	printf("%s\n", "Unit tests complete");

	List * nodeList = ListAllocate();
	List * pathList = ListAllocate();
	loadData("data.txt",nodeList,pathList);

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
