#ifndef LIST
#define LIST value

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
    void * mData;
};

//LinkedList Member methods
Link * next(Link * self)
{
    return self->mNext;
}

Link * ListTop(List * self)
{
    return self->mHead;
}


// Constructor method
List * new_List()
{
    List * ll = (List*)malloc(sizeof(List*));
    ll->mHead = 0;
    ll->mTail = 0;
    return ll;
}

// Destructor method
void ListDestory(List * ll)
{

}


#endif