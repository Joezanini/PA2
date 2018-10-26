//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;



// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList(void);

// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------
// length()
// Returns the length of Q.
int length(List L);

// index()
// Returns the index position of the cursor
int index(List L);

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L);

// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L);

// get()
// Returns the value contained in cursor.
// Pre: !isEmpty(L)
int get(List L);

// equals()
// Returns true (1) if Lists match, otherwise returns false (0)
int equals(List A, List B);

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L);


// Manipulation procedures ----------------------------------------------------
// clear() 
// resets list to it's original empty state.
void clear(List L);

// void moveFront()
// if List is non-empty moves cursor to the front of the list.
// otherwise does nothing
void moveFront(List L);

// void moveBack()
// if List is non-empty moves cursor to the back of the list.
// otherwise does nothing
void moveBack(List L);

// void movePrev()
// if List is non-empty, and cursor is not at front,
// moves cursor towards the front of the List
// if cursor is undefined, does nothing
void movePrev(List L);

// void moveNext()
// if List is non-empty, and cursor is not at back,
// moves cursor towards the back of the List
// if cursor is undefined, does nothing
void moveNext(List L);

// prepend()
// Places new data element at the front end of L
void append(List L, int data);

// append()
// Places new data element at the back end of L
void prepend(List L, int data);

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data);

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data);

// deletefront()
// Deletes element at front of L
// Pre: !isEmpty(L)
void deleteFront(List L);

// deleteBack()
// Deletes element at back of L
// Pre: !isEmpty(L)
void deleteBack(List L);

// delete()
// Deletes element at cursor position
// Pre: !isEmpty(L)
void delete(List L);


// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L);

// copyList()
// Returns a new List representing the same integer sequence as this 
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L);

#endif