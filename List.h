#ifndef LIST
#define LIST value

#include <assert.h>

//Forward decaleration
typedef struct LinkType Link;

typedef struct 
{
  Link * mHead;
  Link * mTail;

}List;

struct LinkType
{
    Link * mPrevious;
    Link * mNext;

    int length;

    void * mData;
};

//LinkedList Member methods
Link * ListNext(Link * currentLink)
{
    assert(currentLink->mNext != 0);
    return currentLink->mNext;
}

//LinkedList Member methods
Link * ListPrevious(Link * currentLink)
{
    assert(currentLink->mPrevious != 0);
    return currentLink->mPrevious;
}

void ListPush(List * list,void * data)
{
    Link * link = (Link*)malloc(sizeof(Link*));
    link->mData = data;
    link->mNext = 0;
    link->mPrevious = 0;

    // if the list is empty
    if(list->mTail == 0 && list->mHead == 0)
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

}


Link * ListTail(List * list)
{
    assert(list->mTail != 0);
    return list->mTail;
}

Link * ListHead(List * list)
{
    assert(list->mHead != 0);
    return list->mHead;
}


// Constructor method
List * new_List()
{
    List * list = (List*)malloc(sizeof(List*));
    list->mHead = 0;
    list->mTail = 0;
    list->length = 0;
    return list;
}

// Destructor method
void ListDestory(List * ll)
{

}


#endif