template<class Object>
SList<Object>::SList( ) {
    init( );
}

template<class Object>
SList<Object>::SList( const SList &rhs ) {
    init( );
    *this = rhs;                                   // then assign rhs to this.
}

template<class Object>
void SList<Object>::init( ) {
    for ( int i = 0; i < LEVEL; i++ ) {  // for each level
        // create the left most dummy nodes;
        header[i] = new SListNode<Object>;
        header[i]->prev = NULL;
        header[i]->down = ( i > 0 ) ? header[i - 1] : NULL;
        header[i]->up = NULL;
        if ( i > 0 ) header[i - 1]->up = header[i];
        
        // create the right most dummy nodes;
        header[i]->next = new SListNode<Object>;
        header[i]->next->next = NULL;
        header[i]->next->prev = header[i];
        header[i]->next->down = ( i > 0 ) ? header[i - 1]->next : NULL;
        header[i]->next->up = NULL;
        if ( i > 0 ) header[i - 1]->next->up = header[i]->next;
    }
    
    // reset cost.
    cost = 0;
}

template<class Object>
SList<Object>::~SList( ) {
    clear( );                                      // delete items starting 1st
    for ( int i = 0; i < LEVEL; i++ ) {
        delete header[i]->next;                      // delete the right most dummy
        delete header[i];                            // delete the left most dummy
    }
}

template<class Object>
bool SList<Object>::isEmpty( ) const {
    return ( header[0]->next->next == NULL );
}

template<class Object>
int SList<Object>::size( ) const {
    SListNode<Object> *p = header[0]->next; // at least the right most dummy
    int size = 0;
    
    for ( ; p->next != NULL; p = p->next, ++size );
    return size;
}

template<class Object>
void SList<Object>::clear( ) {
    for ( int i = 0; i < LEVEL; i++ ) {        // for each level
        SListNode<Object> *p = header[i]->next;  // get the 1st item
        while ( p->next != NULL ) {              // if this is not the left most
            SListNode<Object> *del = p;
            p = p->next;                           // get the next item
            delete del;                            // delete the current item
        }
        
        header[i]->next = p;                     // p now points to the left most
    }                                          // let the right most point to it
}

template<class Object>

void SList<Object>::insert( const Object &obj ) {
    // right points to the level-0 item before which a new object is inserted.
    SListNode<Object> *right = searchPointer( obj );
    SListNode<Object> *up = NULL;
    
    if ( right->next != NULL && right->item == obj )
        // there is an identical object
        return;
    
    
    
    // Implement the rest by yourself /////////////////////////////////////////
    
    
    
    //New object pointer that will be pointing to the Object
    SListNode<Object> *newObjPTR = new SListNode<Object>;
    
    newObjPTR->item = obj; //making the item in the the newPter to the object we will be inserting
    
    newObjPTR->prev = right->prev; //making a link to  -inf since searchPointers gives us righ->prev gives us left
    
    newObjPTR->next = right; //making a link to +inf
    
    
    //new object does not have up/down yet
    // up = new SListNode<Object>;
    newObjPTR->up = NULL;
    newObjPTR->down = NULL;
    
    newObjPTR->prev->next = newObjPTR;
    right->prev = newObjPTR;
    
    int levels = 0; //counter for the levels that will be used
    
    //randomly choosing how many levels will be added
    SListNode<Object> *baseObjPTR = newObjPTR;
    
    while(rand()%2==1) // if 1 then it is heads and levels will increase
    {
        levels++;
        if(levels == LEVEL) // checkingto to see if levels is equal to levels
        {
            break;
        }
        
        
        
        
        up = new SListNode<Object>;
        up->item = obj;
        
        
        SListNode<Object> *currLvlNewObj = baseObjPTR;
        
        while(currLvlNewObj->prev != NULL )
        {
            currLvlNewObj = currLvlNewObj->prev;
            
            
            if(currLvlNewObj->up != NULL) //when it doesnt equal null this is when we know we need to move up
            {
                //go to next level
                currLvlNewObj = currLvlNewObj->up;
                
                //the node will be inserted infront of the current node
              
                up->prev = currLvlNewObj;
                up->next = currLvlNewObj->next;
                currLvlNewObj->next->prev = up;
                currLvlNewObj->next = up;
                break;
            }
            
        }
        
        //connecthing point up and donw with the base pointer to make the link
        up->down = baseObjPTR;
        baseObjPTR->up = up;
        up->up = NULL; // should be null since there is nothing ther yet
        
       //moving up to the next
        baseObjPTR = up;
    }
}











template<class Object>
bool SList<Object>::find( const Object &obj ) {
    // p oints to the level-0 item close to a given object
    SListNode<Object> *p = searchPointer( obj );
    
    return ( p->next != NULL && p->item == obj );     // true if obj was found
}

template<class Object>
SListNode<Object> *SList<Object>::searchPointer( const Object &obj ) {
    SListNode<Object> *p = header[LEVEL - 1];     // start from the top left
    while ( p->down != NULL ) {                   // toward level 0
        p = p->down;                                // shift down once
        cost++;
        
        if ( p->prev == NULL ) {                    // at the left most item
            if ( p->next->next == NULL )              // no intermediate items
                continue;
            else {                                    // some intermadiate items
                if ( p->next->item <= obj )             // if 1st item <= obj
                    p = p->next;                          // shift right to item 1
                cost++;
            }
        }
        
        while ( p->next->next != NULL && p->next->item <= obj ) {
            // shift right through intermediate items as far as the item value <= obj
            p = p->next;
            cost++;
        }
    }
    
    // now reached the bottom. shift right once if the current item < obj
    if ( p->prev == NULL || p->item < obj ) {
        p = p->next;
        cost++;
    }
    return p; // return the pointer to an item >= a given object.
}

template<class Object>
void SList<Object>::remove( const Object &obj ) {
    // p points to the level-0 item to delete
    SListNode<Object> *p = searchPointer( obj );
    
    // validate if p is not the left most or right most and exactly contains the
    // item to delete
    if ( p->prev == NULL || p->next == NULL || p->item != obj )
        return;
    // Implement the rest by yourself /////////////////////////////////////////
    
    
    while (p != NULL)
    {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        p = p->up;
        if (p != NULL && p->down != NULL)
        {
            delete p->down;
        }
        
    }
}







template<class Object>
const SList<Object> &SList<Object>::operator=( const SList &rhs ) {
    if ( this != &rhs ) { // avoid self-assignment
        clear( );           // deallocate old items
        
        int index;
        SListNode<Object> *rnode;
        for ( index = 0, rnode = rhs.header[0]->next; rnode->next != NULL;
             rnode = rnode->next, ++index )
            insert( rnode->item );
        
        cost = rhs.cost;
    }
    return *this;
}

template<class Object>
int SList<Object>::getCost( ) const {
    return cost;
}

template<class Object>
void SList<Object>::show( ) const {
    cout << "contents:" << endl;
    for ( SListNode<Object> *col = header[0]; col != NULL; col = col->next ) {
        SListNode<Object> *row = col;
        for ( int level = 0; row != NULL && level < LEVEL; level++ ) {
            if ( row->prev == NULL )
                cout << "-inf\t";
            else if ( row->next == NULL )
                cout << "+inf\t";
            else
                cout << row->item << "\t";
            row = row->up;
        }
        cout << endl;
    }
}

