#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Edge;

typedef struct{

	Edge * edges; //ArcList
	int numEdges;
	int cost;
	int index;

}Node;

struct Edge{

	Node * node; //Node which it pionts to
	int weight;

};

typedef struct 
{
	int nodeA;
	int nodeB;

}Path;



//Stores all the Nodes in the graph
Node * listOfnodes;
int numberOfNodes;

//Stores all the paths that need to be found
Path listOfPaths[100]; 
int numberOfPaths;


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

		listOfnodes[i].index = i;

		//Alocating the edge list for each node
		//FIXME: This is hardcoded
		listOfnodes[i].edges = (Edge*)malloc(sizeof(Edge)*10);


		printf("Node [%i] created \n", listOfnodes[i].index);
		i++;
	}

	printf("%s\n\n", "Nodes objects constructed");

	//Seek to next line basically
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

		  char * nodeA = strsep(&string, " ");
		  char * nodeB = strsep(&string, " ");
		  char * weight = strsep(&string, " ");

		  printf("Buffer[%s] Edge: From Node [%s] to Node [%s] weight [%s]\n", buffer, nodeA,nodeB,weight);

		  Edge edge;
		  edge.node = &listOfnodes[atoi(nodeB)];
		  edge.weight = atoi(weight);

		  Node * node = &listOfnodes[atoi(nodeA)];
		  node->edges[node->numEdges] = edge;
		  node->numEdges++;

		 // printf("Node index: [%i] numEdges: [%i] \n", node->index, node->numEdges);
		  //printf("%i\n", node->edges[node->numEdges-1].weight);

		  free(tofree);
		}
	}

	//Print out some in formative info for the user
	printf("%s\n\n", "Edges objects constructed");
	i = 0;
	while( i < numberOfNodes)
	{
		printf("Node [%i] has edges \n", i);
		int j = 0;
		while(j < listOfnodes[i].numEdges)
		{
			Edge e = listOfnodes[i].edges[j];

			printf("	Edge to Node [%i] and a weight of %i \n", e.node->index , e.weight);
			j++;
		}
		printf("\n");

		i++;
	}

	//Get the paths to find
	while(fgets(buffer, READ_BYTE_SIZE, pFile) != NULL)
	{
		char* string;
		char* tofree;
		string = strdup(trim(buffer));

		if (string != NULL)
		{
		  tofree = string;

		  Path path;
		  path.nodeA = atoi( strsep(&string, " ") );
		  path.nodeB = atoi( strsep(&string, " ") );
		  printf("Path: from Node [%i] to Node [%i] \n", path.nodeA, path.nodeB );
		  listOfPaths[numberOfPaths] = path;
		  free(tofree);
		}
		numberOfPaths++;
	}

}

void astar(Node * graph, int start, int dest)
{

}

int main(int argc, char* argv[])
{
	readInput("data.txt");

	int i = 0;
	while( i < numberOfPaths)
	{
		astar(listOfnodes, listOfPaths[i].nodeA,listOfPaths[i].nodeB);		
		i++;
	}
}
