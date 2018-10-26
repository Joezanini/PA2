//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj {
   int data;
   struct NodeObj* next;
   struct NodeObj* previous;
} NodeObj;

// private Node type
typedef NodeObj* Node;

typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data) {
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->previous = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void) {
   List L = malloc(sizeof(ListObj));
   L->front = NULL;
   L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

// freeList()
// Frees all heap memory associated with List to NULL.
void freeList(List* L) {
   if(L != NULL && *L != NULL) { 
      while(!isEmpty(*L)) { 
         deleteFront(*L); 
      }
      free(*L);
      L = NULL;
   }
}


// Access functions -----------------------------------------------------------
// length()
// Returns the length of L.
int length(List L) {
   if(L == NULL) {
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return(L->length);
}

// index()
// Returns the index reference for the cursor.
int index(List L) {
   if(L->cursor == NULL) { //this could be a problem
      return(-1);
   }
   return(L->index);
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L) {
   if(L == NULL) {
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L) ){
      printf("List Error: calling front() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}

// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L) {
   if(L == NULL) {
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L) ){
      printf("List Error: calling back() on an empty List\n");
      exit(1);
   }
   return(L->back->data);
}

// get()
// Returns the value contained in cursor.
// Pre: !isEmpty(L)
int get(List L) {
   if(L == NULL) {
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)){
      printf("List Error: calling get() on an empty List\n");
      exit(1);
   }
   if(L->cursor == NULL) {
      printf("List Error: calling get() on undefined cursor\n");
      exit(1);
   }
   return(L->cursor->data);
}

// equals()
// Returns true (1) if Lists match, otherwise returns false (0)
int equals(List A, List B) {
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if(A == NULL || B == NULL) {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }

   eq = (A->length == B->length);
   N = A->front;
   M = B->front;
   while(eq && N != NULL){
      eq = (N->data == M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty(List L){
   if(L == NULL) {
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(1);
   }
   return(L->length == 0); 
}


// Manipulation procedures ----------------------------------------------------

//moveFront()
//moves cursor to the front of the List
void moveFront(List L) {
   if(!isEmpty(L)) {
      L->cursor = L->front;
      //printf("%p\n", (void*) &L->cursor->previous);
      //printf("%p\n", (void*) &L->front->previous);
      //printf("%d\n", L->cursor->next->data);
      //printf("%d\n", L->front->next->data);
      L->index = 0;
   }
}

// void moveBack()
// if List is non-empty moves cursor to the back of the list.
// otherwise does nothing
void moveBack(List L) {
   if(!isEmpty(L)) {
      L->cursor = L->back;
      L->index = length(L) - 1;
   }
}

// void movePrev()
// if List is non-empty, and cursor is not at front,
// moves cursor towards the front of the List
// if cursor is undefined, does nothing
void movePrev(List L) {
   if(!isEmpty(L)) {
      if(index(L) == 0) {
         L->cursor = NULL;
         L->index = -1;
      } else {
         L->cursor = L->cursor->previous;
         L->index--;
      }
   }
}

// void moveNext()
// if List is non-empty, and cursor is not at back,
// moves cursor towards the back of the List
// if cursor is undefined, does nothing
void moveNext(List L) {
   if(!isEmpty(L)) {
      if(index(L) == length(L) - 1) {
         L->cursor = NULL;
         L->index = -1;
      } else {
         L->cursor = L->cursor->next;
         //printf("%d\n", L->cursor->previous->next->data);
         L->index++;
      }
   }
}


// append()
// Places new data element at the end of L
void append(List L, int data) {
   Node N = newNode(data);
   if(L == NULL){
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }

   if(isEmpty(L)) {
      L->front = L->back = N;
   } else {
      L->back->next = N; 
      N->previous = L->back;
      L->back = N;
   }
   L->length++;
}

// prepend()
// Places new data element at the end of L
void prepend(List L, int data) {
   if(L == NULL){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)) { 
      Node N = newNode(data);
      L->front = L->back = N; 
   }else{ 
      Node N = newNode(data);
      L->front->previous = N; 
      N->next = L->front; 
      L->front = N;
   }
   L->length++;
   if(index(L) >= 0) {
      L->index++;
   }
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data) {
   if(isEmpty(L)) {
      printf("List Error: insertBefore() called on empty List\n");
   }
      
   if(L->cursor == NULL) {
      printf("List Error: inserBefore() called on undefined cursor\n");
   }
   if (index(L) == 0) {
      prepend(L, data);
   } else {
      Node N = newNode(data);
      N->next = L->cursor;
      N->previous = L->cursor->previous;
      L->cursor->previous->next = N;
      L->cursor->previous = N;
      L->index++;
      L->length++;
   }
}

// insertAffer()
// Insert new element After cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data) {
   if(isEmpty(L)) {
      printf("List Error: insertAfter() called on empty List\n");
   }
      
   if(L->cursor == NULL) {
      printf("List Error: insertAfter() called on undefined cursor\n");
   }
   if (index(L) == length(L) - 1) {
      append(L, data);
   } else {
      Node N = newNode(data);
      N->next = L->cursor->next;
      L->cursor->next->previous = N;
      N->previous = L->cursor;
      L->cursor->next = N;
      L->length++;
   }
}

// delete()
// Deletes element at cursor position
// Pre: !isEmpty(L) and cursor is defined
void delete(List L) {
   if(isEmpty(L)) {
      printf("List Error: delete() called on empty List\n");
   }
      
   if(L->cursor == NULL) {
      printf("List Error: delete() called on undefined cursor\n");
   }

   if(index(L) == 0) {
      deleteFront(L);
   } else if(index(L) == length(L) - 1) {
      deleteBack(L);
   } else {
      L->cursor->previous->next = L->cursor->next;
      L->cursor->next->previous = L->cursor->previous;
      freeNode(&L->cursor); //change this to L->cursor maybe.
      L->cursor = NULL;
      L->index= -1;
      L->length--;
   }
}

// deleteBack()
// Deletes element at back of L
// Pre: !isEmpty(L)
void deleteBack(List L) {
   Node N = NULL;

   if(L == NULL) {
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)){
      printf("List Error: calling deleteFront on an empty List\n");
      exit(1);
   }
   N = L->back;
   if(length(L) > 1) { 
      L->back = L->back->previous; 
   } else { 
      L->back = L->front = NULL; 
   }
   L->length--;
   freeNode(&N);
}

// deletefront()
// Deletes element at front of L
// Pre: !isEmpty(L)
void deleteFront(List L) {
   Node N = NULL;

   if(L == NULL) {
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)){
      printf("List Error: calling deleteFront on an empty List\n");
      exit(1);
   }
   N = L->front;
   if(length(L) > 1) { 
      L->front = L->front->next; 
   }else{ 
      L->front = L->back = L->cursor = NULL; 
      L->index = -1;
   }
   L->length--;
   if(index(L) >= 0) {
      L->index--;
   }
   freeNode(&N);
}

// clear() 
// resets list to it's original empty state.
void clear(List L) {
   moveFront(L);
   while(L->cursor != NULL) {
      moveNext(L);
      deleteFront(L);
   }
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L){
   Node N = NULL;

   if(L==NULL){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }

   for(N = L->front; N != NULL; N = N->next){
      fprintf(out, "%d ", N->data);
   }
   //printf("\n");
}

// copyList()
// Returns a new List representing the same integer sequence as this 
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L) {
   List Q = newList();
   int spot = index(L);

   for(moveFront(L); index(L) >= 0; moveNext(L)){
      append(Q, get(L));
   }
   if(spot >= 0) {
      moveFront(L);
      while(index(L) != spot) {
         moveNext(L);
      }
   }
   return Q;
}

