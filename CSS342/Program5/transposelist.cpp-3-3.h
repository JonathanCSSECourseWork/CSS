template<class Object>
int TransposeList<Object>::find( const Object &obj ) {
  DListNode<Object> *found = DList<Object>::header->next;

  int i = 0;
  for ( ; found != NULL && found->item != obj;  found = found->next, ++i )
    ++DList<Object>::cost;

  if ( found == NULL )
    return -1; // not found

  if ( found == DList<Object>::header->next )
    return 0;  // no need to swap

  // remove found from the current position
  DListNode<Object> *before = found->prev;
  
  before->next = found->next;
  if (found->next != NULL) 
	found->next->prev = before;

  // insert found before previous
  found->next = before;
  found->prev = before->prev;
  before->prev = found;
  found->prev->next = found;

  return i;
}