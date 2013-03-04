#ifndef LIST
#define LIST value

// This is more of a proity_queue rather then a list but fuck it

#include <assert.h>

//Forward decaleration
typedef struct LinkType Link;

typedef struct 
{
  Link * mHead;
  Link * mTail;

  int mLength;

}List;

struct LinkType
{
    Link * mNext;
    void * mData;
};

//LinkedList Member methods
Link * ListNext(Link * currentLink)
{
    assert(currentLink->mNext != 0);
    return currentLink->mNext;
}


Link * ListHead(List * list)
{
    assert(list->mHead != 0);
    return list->mHead;
}



void ListPush(List * list,void * data,int (* cmp)(void *, void *))
{
    Link * link = (Link*)malloc(sizeof(Link*));
    link->mData = data;
    link->mNext = 0;

    // if the list is empty
    if(list->mLength == 0)
    {
        list->mTail = link;
        list->mHead = link;
        //printf("%s\n", "First element");

    }else{
         //printf("%s\n", "More element");
        //Push onto the end of the list
        list->mTail->mNext = link;
        list->mTail = link;
    }
    //Adding new link so increment
    list->mLength++;
    
    if(cmp != 0)
    {
        ListSort(list,cmp);
    }

}

// Only for test
typedef struct 
{
    int x;

}SomeDataType;

void ListSort(List * list, int (* cmp)(void *, void *))
{
    int i = 0;
    int notOrder = 1;
    Link * tmp = ListHead(list);

    while(notOrder)
    {
        notOrder = 0;
        i = 0;
        tmp = ListHead(list);
        
        while( i < list->mLength-1 && tmp->mNext != 0)
        {

            Link * dataToBeSwapped = tmp;
            Link * otherDataToBeSwapped = ListNext(tmp);

            SomeDataType * dataA = dataToBeSwapped->mData;
            SomeDataType * dataB = otherDataToBeSwapped->mData;
            
            if( cmp( dataA, dataB ) )
            {
                //printf("Index %i - Swap %i with %i \n", i, dataA->x,dataB->x );

                void * tempData = dataToBeSwapped->mData;
                dataToBeSwapped->mData = otherDataToBeSwapped->mData;
                otherDataToBeSwapped->mData = tempData;
 

                notOrder = 1;
            }

            tmp = ListNext(tmp);

            i++;
        }
    }

    // printf("%s\n", "Ordered");
    // {
    //     Link * iter = list->mHead;

    //         while(iter!= 0)
    //         {          
    //             Node * p = iter->mData;
    //             printf("    Item %i Node %i \n", p->actualCost + p->estimatedCost, p->index);

    //             iter = iter->mNext;
    //         }
    // }
}

Link * ListPop(List * list)
{

    Link * tmp = list->mHead;
    list->mHead = list->mHead->mNext;
    list->mLength--;

    //Important notice!!
    // User is responaible for freeing the memory 
    // of this Links mData and the link itself
    return tmp;
}


// Constructor method
List * ListAllocate()
{
    List * list = (List*)malloc(sizeof(List*));
    list->mHead = 0;
    list->mTail = 0;
    list->mLength = 0;
    return list;
}

Link * ListFind(List * list, void * data, int (* cmp)(void *, void *))
{
    Link * iter = list->mHead;

    while(iter != 0)
    {
        if(cmp(data,iter->mData))
        {
            return iter;
        }

        iter = iter->mNext;
    }

    return iter;
}

// Destructor method
void ListDeallocate(List * list)
{
    // assert(true && " Deallocate bitch!! ")
    //TODO :)
}


// UNIT TESTING CODE BELOW


int cmp(void * a, void * b)
{
    SomeDataType * x = a;
    SomeDataType * y = b;
    //printf("%i > %i\n", x->x , y->x);
    return x->x > y->x;
}

void ListTestPushPop()
{
    List * list = ListAllocate();

    int i = 0;
    while(i < 10)
    {
        SomeDataType * tmp = malloc(sizeof(SomeDataType*));
        tmp->x = i;

        //Add links to the end of the list
        ListPush(list,tmp,cmp);
        i++;
    }

    //Remove links from the top of the list
    ListPop(list);
    ListPop(list);
    ListPop(list);
    
    SomeDataType * tmp = ListHead(list)->mData;
    assert( tmp->x == 3 && " UNIT TEST FAILED ");

    Link * link = ListNext( ListHead(list) );
    tmp = link->mData;


    assert( tmp->x == 4 && " UNIT TEST FAILED ");

}

void ListTestSort()
{
    List * list = ListAllocate();
    SomeDataType * tmp;

    int i = 0;
    while(i < 10)
    {
        SomeDataType * tmp = malloc(sizeof(SomeDataType*));
        tmp->x = randr(0,10);

        //Add links to the end of the list
        ListPush(list,tmp,cmp);
        i++;
    }

    
    //tmp = ListHead(list)->mData;
    //assert( tmp->x == 9 && " UNIT TEST FAILED ");
    printf("%s\n", "Unordered");
    {
        Link * iter = list->mHead;

            while(iter!= 0)
            {          
                SomeDataType * p = iter->mData;
                printf("Item %i\n", p->x);

                iter = iter->mNext;
            }
    }

        ListSort(list,cmp);

    printf("%s\n", "Ordered");
    {
        Link * iter = list->mHead;

            while(iter!= 0)
            {          
                SomeDataType * p = iter->mData;
                printf("Item %i\n", p->x);

                iter = iter->mNext;
            }
    }
}


void ListRunAllTests()
{
    //ListTestPushPop();
    ListTestSort();
}



#endif