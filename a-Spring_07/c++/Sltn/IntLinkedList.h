#ifndef INTLINKEDLIST_H
#define INTLINKEDLIST_H

using namespace std;
#include<iostream>

/*
INTLINKEDLIST is an implementation of a one-directional linked list of nodes.
Each node contains an integer.
*/

class IntLinkedList 
{
 private:
  class ListNode { 
  public:
    int element;
    ListNode *next;
    ListNode(int e, ListNode *n = NULL);
  }; 
  ListNode *front;
  ListNode *back;
  int len;
  
  void makeEmpty();
  bool isEmpty() const;
  
 public:
  IntLinkedList();
  IntLinkedList(const IntLinkedList & rhs);
  ~IntLinkedList();
  const IntLinkedList & operator= (const IntLinkedList & rhs);
  
  void addLast(int x);    // add a node with data x to the end of the list
  void add(int i, int x); // add a node at index i with data x 
  void deleteNode(int x);     // deletes last occurance of node of with data x
  int get(int i) const;   // returns ith element
  int length() const;     // returns the length of the list
 
};

#endif
