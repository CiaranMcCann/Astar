#include "GraphStructs.h"

void removeNodeFromArray(Node ** array, int lenght, int indexToRemove)
{
	//If othered in other of greater then
	array[indexToRemove]->cost = -10;
	sortNodeArray(array,lenght);

	//FIXME free memory correctly or not fuck it lol
	 //free(array[lenght-1]);
	 //array[lenght-1] = NULL;

	 lenght--;
	 //printf("%s\n", "dfd");
	 sortNodeArray(array,lenght);
}

void sortNodeArray(Node ** array, int lenght)
{
    int i = 0;
    int notOrder = 1;

    while(notOrder)
    {
    	notOrder = 0;
    	i = 0;
  
	    while( i < lenght-1)
	    {
	    	//printf("%i\n", array[i].cost);
	    	if(array[i]->cost < array[i+1]->cost)
	    	{
	    		//printf("Swap %i\n with %i\n", array[i].cost, array[i+1].cost);
	    		//Swap nodes
	    		Node * tmp = array[i+1];
	    		array[i+1] = array[i];
	    		array[i] = tmp;
	 			notOrder = 1;
	    	}

	    	i++;
	    }
	}

	printf("%s\n", "############");
	i = 0;
	while( i < lenght )
	{
		 printf("Node %i cost %i\n", array[i]->index, array[i]->cost );
		 i++;
	}
	printf("%s\n", "############");

}