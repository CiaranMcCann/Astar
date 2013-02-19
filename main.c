#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Edge;

typedef struct{

	Edge * edges; //ArcList
	int numEdges;
	int cost;

}Node;

struct Edge{

	Node * node; //Node which it pionts to
	int weight;

};



int numberOfNodes;
Node * listOfnodes;

#define READ_BYTE_SIZE 300

const char *trim(char *s) {
    char *ptr;
    if (!s)
        return NULL;   // handle NULL string
    if (!*s)
        return s;      // handle empty string
    for (ptr = s + strlen(s) - 1; (ptr >= s) && isspace(*ptr); --ptr);
    ptr[1] = '\0';
    return s;
}

// Node * findNodeInList(char * name, Node * pList, int listLenght)
// {
// 	int i = 0;
// 	while( i < listLenght)
// 	{
// 		printf("[%s] == [%s]", trim(name),trim(pList[i].name) );
// 		if(trim(name) == trim(pList[i].name))
// 		{
// 			printf("%s\n", "FOUNED!!!");
// 			return &pList[i];
// 		}
			

// 		i++;
// 	}
// 	printf("%s [%s] %s \n", "Error: Node with name", name, "not found");
// 	return NULL;
// }


void readInput(char * path)
{
	FILE * pFile;
	char buffer[500];

	pFile = fopen(path, "r");
	//if (pFile==NULL) {printf("Error opening file");}

	//Get the first line from file which is number of nodes
	fgets(buffer, READ_BYTE_SIZE, pFile);
	numberOfNodes = atoi(buffer);

	//Seek to next line basically
	fgets(buffer, READ_BYTE_SIZE, pFile);

	//Allocate nodes array on the heap
	listOfnodes =  (Node*)malloc(sizeof(Node)*numberOfNodes);

	int i = 0;
	while( i < numberOfNodes)
	{
		fgets(buffer, READ_BYTE_SIZE, pFile);

		//Copy buffer into the name
		//strcpy(listOfnodes[i].name,trim(buffer));

		//Alocating the edge list for each node
		//FIXME: This is hardcoded
		listOfnodes[i].edges = (Edge*)malloc(sizeof(Edge)*10);


		//printf("%s", listOfnodes[i].name);
		i++;
	}

	// int j = 0;
	// 	    while(j < numberOfNodes)
	// 	    {

	// 	    	printf(listOfnodes[j].name);
	// 	    	j++;
	// 	    }


	printf("%s\n", "Nodes objects constructed");

	//Seek to next line basically
	fgets(buffer, READ_BYTE_SIZE, pFile);
	fgets(buffer, READ_BYTE_SIZE, pFile);

	char* string;
	char* tofree;
	string = strdup(trim(buffer));

	if (string != NULL)
	{
		  tofree = string;

		  char * nodeA = strsep(&string, " ");
		  char * nodeB = strsep(&string, " ");
		  char * weight = strsep(&string, " ");

		 // printf("%s\n", nodeA);
		 //  printf("%s\n", nodeB);
		  //  printf("%s\n", weight);



		   Edge edge;
		   edge.node = findNodeInList(nodeB,listOfnodes,numberOfNodes);
		   //edge.weight = atoi(weight);

		  // Node * node = findNodeInList(nodeA,nodes,numberOfNodes);
		  // node->edges[node->numEdges] = edge;
		  // node->numEdges++;

		  // printf("%s\n", node->name);
		  // printf("%s\n", node->edges[node->numEdges-1].weight);

		  free(tofree);
	}

}


int main(int argc, char* argv[])
{
	readInput("data.txt");
	//getch();
}
