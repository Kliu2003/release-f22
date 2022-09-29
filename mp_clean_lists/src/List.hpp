/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <typename T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  ListNode* curr = head_;
  while(curr != NULL){
     ListNode* temp = curr;
     curr = curr->next;
     delete temp;
  }
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  ListNode* currHead = head_;
  newNode -> next = currHead;
  newNode -> prev = NULL;
  if(head_ != NULL){
    head_->prev = newNode;
  }
  head_ = newNode;
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);
  if(tail_ == NULL && head_ == NULL){
     tail_ = newNode;
     head_ = newNode;
  }
  else{
    tail_->next = newNode;
    newNode->prev = tail_;
    tail_ = newNode;
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if(splitPoint <= 0){
    return start;
  }
  ListNode* prev = NULL;
  ListNode* curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    prev = curr;
    curr = curr->next;
  }

  if (curr != NULL) {
      tail_ = curr->prev;
      prev->next = NULL;
      curr->prev = NULL;
  }
  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode* startOfNextThree = head_;
  while(startOfNextThree != NULL){
    ListNode* first = startOfNextThree;
    if(first->next == NULL){
      tail_ = first;
      break;
    }
    ListNode* second = first->next;
    if(second->next == NULL){
      tail_ = second;
      break;
    }
    ListNode* third = second->next;
    startOfNextThree = third->next;
  
    if(first->prev != NULL){
      first->prev->next = second;
    }
    else{
      head_ = second;
    }
    second->prev = first->prev;

    third->next = first;
    first->prev = third;
    first->next = startOfNextThree;
    if(startOfNextThree != NULL){
      startOfNextThree->prev = first;
    }
    else{
      tail_ = first;
    }
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if(startPoint == endPoint || startPoint == NULL || endPoint == NULL){
    return;
  }
  ListNode* curr = startPoint; //Keeps track of current node that is being operated on
  ListNode* left = startPoint->prev; //Node before start
  ListNode* right = endPoint->next; //Node after end
  ListNode* start = startPoint;
  ListNode* end = endPoint;

  while(curr != endPoint){ //Swap every node from startPoint to endPoint
      ListNode* temp;
      temp = curr->next;
      curr->next = curr->prev;
      curr->prev = temp;
      curr = curr->prev;
  }

  //curr == endpoint now

  curr->next = curr->prev;
  curr->prev = left;
  startPoint->next = right;
  endPoint->prev = left;

  //swap start and end pointers

  startPoint = end;
  endPoint = start;

  if(left != NULL){ // If the startPoint is not the head node, the next of the node before startPoint will point to the new startPoint
    left->next = startPoint;
  }
  else{ //Otherwise, head_ is the new startPoint
    head_ = startPoint;
  }
  if(right != NULL){ //If the endPoint is not the tail node, the prev of the node after the endPoint will point to the new endPoint
    right->prev = endPoint;
  }
  else{ //Otherwise, tail_ is the new endPoint
    tail_ = endPoint;
  }

  return;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  int cycles = length_/n;
  std::cout<<cycles<<" "<<length_<<" "<<n<<std::endl;
  ListNode* start = head_;
  ListNode* end = head_;
  while(start != NULL){
    for(int j = 0; j < n-1; j++){
      if(end->next != NULL){
        end = end->next;
      }
    }
    reverse(start, end);
    start = end->next;
    end = start; 
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if(first == NULL && second == NULL){
    return NULL;
  }

  ListNode* currFirst = first;
  ListNode* currSecond = second;
  ListNode* curr;
  ListNode* head;

  if(currFirst->data < currSecond->data){ //Set curr to the smaller data value between first and seocnd
    curr = currFirst;
    currFirst = currFirst->next;
  }
  else{
    curr = currSecond;
    currSecond = currSecond->next;
  }
 
  head = curr; //head that will be returned

  while(currFirst != NULL && currSecond != NULL){
    if(currFirst->data < currSecond->data){
      curr->next = currFirst;
      currFirst = currFirst->next;
    }
    else{
      curr->next = currSecond;
      currSecond = currSecond->next;
    }
    curr = curr->next;
  }

  while(currFirst != NULL){
    curr->next = currFirst;
    currFirst = currFirst->next;
    curr = curr->next;
  }

  while(currSecond != NULL){
    curr->next = currSecond;
    currSecond = currSecond->next;
    curr = curr->next;
  }

  ListNode* prev = NULL;
  curr = head;
  while(curr != NULL){
    curr->prev = prev;
    prev = curr;
    curr = curr->next;
  }

  return head;

}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength == 1){
    return start;
  }
  ListNode* midPoint = split(start, chainLength/2);

  ListNode* L1 = mergesort(start, chainLength/2);
  ListNode* L2 = mergesort(midPoint , chainLength-chainLength/2);
  start = merge(L1, L2);
  return start;
}