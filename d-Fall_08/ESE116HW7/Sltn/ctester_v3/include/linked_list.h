#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <unistd.h>

/**
 * A node for the generalized linked list node
 */
typedef struct linked_list_node{
  struct linked_list_node *next;
  void *object;
} LINKED_LIST_NODE;



/**
 * A generalized linked list structure that holds nodes that hold void*
 * This is used for the jobs list, the commands, and for the arguments in the commands
 */
typedef struct linked_list{
  int size;
  void (*free_fcn)(void*);
  LINKED_LIST_NODE *first_node;
} LINKED_LIST;



/**
 * Creates a new generalized linked list, and initlizes it to size zero
 * 
 * @param free_fcn, the function used to free the type of object the list is holding
 * @return NULL if unable to malloc the group, others the new LINKED_LIST
 */
LINKED_LIST* ll_create(void(*)(void*));



/**
 * Initilizes a new generalized linked list of type void*, set the first node to NULL, assigns the free_fcn
 * 
 * @param new_list the list to be initilized to the default value
 * @param free_fcn the function used to free the type of object the list is holding
 * @return -1 if unable to inititlize, otherwise 0
 */
int ll_initialize(LINKED_LIST*, void(*)(void*));



/**
 * Initilizes a new node to be added to the linked list, hold a object of type void*
 * 
 * @param object a new object to be added to the node
 * @return NULL if unable to allocate for a new node, otherwise return the new Node
 */
LINKED_LIST_NODE* ll_create_node(void*);



/**
 * Get a object from a LINKED_LIST, will return the object as type void*
 * 
 * @param list the list to get the object off of
 * @param index, the index from where to get the object
 * @param object, the object to be returnd
 * @return -1 if unable to find, otherwise 0 if success
 */
int ll_get(LINKED_LIST*, int, void**);



/**
 * Push a object to the back of a LINKED_LIST
 * 
 * @param list the list to add the object too
 * @param object, the object that you are adding
 * @return -1 if unable to add due to memory errors, otherwise 0
 */
int ll_push_back(LINKED_LIST*, void*);



/**
 * Remove an object from a linked list given the index
 * 
 * @param list the list to remove the object from
 * @param index, the index from where to remove the object
 * @param object, the object to be returnd
 * @return -1 if unable to find, otherwise 0 if success
 */
int ll_remove(LINKED_LIST*, int, void**);



/**
 * Free a linked list node.  Assign it's void* object to the object paramter if != NULL
 * 
 * @param node the node to free
 * @param object, the object to be returnd
 */
void ll_free_node(LINKED_LIST*, LINKED_LIST_NODE*, void**);



/**
 * Get a node from a linked list, not called by anybody but linked list functions
 * 
 * @param list the list to get the node off of
 * @param index, the index from where to get the object
 * @param object, the object to be returnd
 * @return -1 if unable to find, otherwise 0 if success
 */
int ll_get_node(LINKED_LIST*, int, LINKED_LIST_NODE**);



/**
 * Clear the linked list of all nodes, and free the nodes.  DON'T FREE THE LIST
 * 
 * @param list the list to clear
 * @return -1 if remove returns an error, otherwise return 0
 */
int ll_clear(LINKED_LIST*);



/**
 * Free a linked List, first freeing all of it's elements
 * 
 * @param list the list free
 */
void ll_free(LINKED_LIST*);

#endif
