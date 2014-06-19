#include <iostream>
#include "IntLinkedList.h"

using namespace std;

IntLinkedList::ListNode::ListNode(int e, ListNode *n)
  : element (e), next (n) { }


// private functions

void IntLinkedList::makeEmpty()
{
  ListNode *old;
  while (!isEmpty())
    {
      old = front;
      front = front ->next;
      delete old; 
    }
}

bool IntLinkedList::isEmpty() const
{ return front == NULL; }

// public functions

IntLinkedList::IntLinkedList() 
  : front (NULL), back (NULL), len (0) { }

IntLinkedList::IntLinkedList(const IntLinkedList & rhs)
  : front (NULL), back (NULL), len(0)
{ *this = rhs;}

IntLinkedList::~IntLinkedList() 
{ makeEmpty(); }
  
const IntLinkedList & IntLinkedList::operator= (const IntLinkedList & rhs)
{
  if (this != &rhs)
    {
      makeEmpty();
      ListNode *rptr = rhs.front;
      for (; rptr != NULL; rptr = rptr->next)
	addLast (rptr->element); 
    }
  return *this;
}

void IntLinkedList::addLast (int x)
{
  if (isEmpty())
    back = front = new ListNode (x);
  else
      back = back->next = new ListNode (x); 
  len++;
}

void IntLinkedList::add (int i, int x)
{
  ListNode *ptr;
  if (i < 0 || i > len)
    {
      cout << "Index out of bounds" << endl;
      return;
    }
  if (i == len)
    addLast(x);      // add at end of list of beginning of empty list 
  else if (i == 0)
    {                // add at beginning of non-empty list
      ptr = front;   
      front = new ListNode (x, ptr);
      len++;
    }
  else
    {               // add in middle of list
      for (ptr = front ; ptr != NULL && i > 1 ; i--)
	ptr = ptr->next;
      ptr->next = new ListNode (x, ptr->next);
      len++;
    }
}

void IntLinkedList::deleteNode(int x)
{
  if (isEmpty())
    return;
  ListNode *prev = NULL;
  ListNode *ptr = front;
  while (ptr != NULL && ptr->element != x)  // find x 
    {
      prev = ptr;
      ptr = ptr->next;
    }
  if (ptr == NULL)
    return;
  if (prev == NULL)
    front = front->next;          // Deleting first element
  else if (ptr->next != NULL)  
    prev->next = ptr->next;     // Deleting middle element
   else if (ptr == back)
    {
      prev->next = NULL;        // Deleting last element 
      back = prev;
    }
  len--;
  delete ptr;
  return;
}

int IntLinkedList::get(int i) const 
{
  ListNode *ptr;
  if (i < 0 || i >= len)
    {
      cout << "Index out of bounds" << endl;
      return 0;
    }
  if ( i == len - 1)
    return back->element;
  else
    {
      for (ptr = front; i > 0 ; i--)
	ptr = ptr->next;
      return ptr->element;
    }
}

int IntLinkedList::length() const
{ return len;}
