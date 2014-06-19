#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "linked_list.h"

/**
 * Creates a new generalized linked list, and initlizes it to size zero
 * 
 * @param free_fcn, the function used to free the type of object the list is holding
 * @return NULL if unable to malloc the group, others the new LINKED_LIST
 */
LINKED_LIST* ll_create(void(*free_fcn)(void*)){
  LINKED_LIST *new_ll = malloc(sizeof(LINKED_LIST));
  ll_initialize(new_ll, free_fcn);
  if(new_ll == NULL){
    errno = ENOMEM;
    return NULL;
  }
  return new_ll;
}

/**
 * Initilizes a new generalized linked list of type void*, set the first node to NULL, assigns the free_fcn
 * 
 * @param new_list the list to be initilized to the default value
 * @param free_fcn the function used to free the type of object the list is holding
 * @return -1 if unable to inititlize, otherwise 0
 */
int ll_initialize(LINKED_LIST *new_list, void(*free_fcn)(void*)){
  if(new_list != NULL){
    new_list->size = 0;
    new_list->first_node = NULL;
    new_list->free_fcn = free_fcn;
    return 0;
  }
  else{
    errno = ENOMEM;
    return -1;
  }
}

/**
 * Initilizes a new node to be added to the linked list, hold a object of type void*
 * 
 * @param object a new object to be added to the node
 * @return NULL if unable to allocate for a new node, otherwise return the new Node
 */
LINKED_LIST_NODE* ll_create_node(void *object){
  LINKED_LIST_NODE *new_node = malloc(sizeof(LINKED_LIST_NODE));
  if(new_node == NULL){
    errno = ENOMEM;
    return NULL;
  }
  
  new_node->object = object;
  new_node->next = NULL;
  
  return new_node; 
}

/**
 * Get a object from a LINKED_LIST, will return the object as type void*
 * 
 * @param list the list to get the object off of
 * @param index, the index from where to get the object
 * @param object, the object to be returnd
 * @return -1 if unable to find, otherwise 0 if success
 */
int ll_get(LINKED_LIST *list, int index, void** object){
  LINKED_LIST_NODE *node;
  
  if(ll_get_node(list, index, &node) == -1){
    errno = EINVAL;
    *object = NULL;
    return -1;
  }
  
  else *object = node->object;
  return index;
}

/**
 * Push a object to the back of a LINKED_LIST
 * 
 * @param list the list to add the object too
 * @param object, the object that you are adding
 * @return -1 if unable to add due to memory errors, otherwise 0
 */
int ll_push_back(LINKED_LIST *list, void* object){
  LINKED_LIST_NODE *end_node;
  LINKED_LIST_NODE *new_node = ll_create_node(object);
  
  if(new_node == NULL){
    errno = ENOMEM;
    return -1;
  }
  
  if(list->size > 0){
    if(ll_get_node(list, list->size - 1, &end_node) == -1){
      errno = EINVAL;
      printf("Error: Unable to retrieve end node\n");
      return -1;
    }
    
    end_node->next = new_node;
    (list->size)++;
    return list->size - 1;
  }
  else{
    list->first_node = new_node;
    (list->size)++;
    return 0;
  }
}

/**
 * Remove an object from a linked list given the index
 * 
 * @param list the list to remove the object from
 * @param index, the index from where to remove the object
 * @param object, the object to be returnd
 * @return -1 if unable to find, otherwise 0 if success
 */
int ll_remove(LINKED_LIST *list, int index, void **object){
  LINKED_LIST_NODE *node, *prev_node;
  
  if(index < 0 || index >= list->size){
    errno = EINVAL;
    return -1;
  }

  if(index == 0){
    node = list->first_node;
    list->first_node = list->first_node->next;
    ll_free_node(list, node, object);
    (list->size)--;
    return index;
  }
  else{
    if(ll_get_node(list, index, &node) == -1){
      errno = EINVAL;
      if(object != NULL){
      	*object = NULL;
      }
      return -1;
    }
    if(ll_get_node(list, index - 1, &prev_node) == -1){
      errno = EINVAL;
      if(object != NULL){
      	*object = NULL;
      }
      return -1;
    }
    prev_node->next = node->next;
    ll_free_node(list, node, object);
    (list->size)--;
    return index;
  }  
  return 0;
}

/**
 * Clear the linked list of all nodes, and free the nodes.  DON'T FREE THE LIST
 * 
 * @param list the list to clear
 * @return -1 if remove returns an error, otherwise return 0
 */
int ll_clear(LINKED_LIST *list){
  while(list->size > 0){
    if(ll_remove(list, 0, NULL) != 0){
      errno = 0;
      return -1;
    }
  }
  return 0;
}

/**
 * Free a linked List, first freeing all of it's elements
 * 
 * @param list the list free
 */
void ll_free(LINKED_LIST *list){
  ll_clear(list);
  free(list);
}

/**
 * Free a linked list node.  Assign it's void* object to the object paramter if != NULL
 * 
 * @param node the node to free
 * @param object, the object to be returnd
 */
void ll_free_node(LINKED_LIST *list, LINKED_LIST_NODE *node, void** object){
  if(object != NULL) *object = node->object;
  else list->free_fcn(node->object);
  free(node);
}

/**
 * Get a node from a linked list, not called by anybody but linked list functions
 * 
 * @param list the list to get the off of
 * @param index, the index from where to get the object
 * @param object, the object to be returnd
 * @return -1 if unable to find, otherwise 0 if success
 */
int ll_get_node(LINKED_LIST *list, int index, LINKED_LIST_NODE **node){
  int i = 0;
  LINKED_LIST_NODE *loc;
  
  if(i < 0 || index >= list->size || list->size == 0){
    errno = EINVAL;
    return -1;
  }
 
  loc = list->first_node;
  for(i = 0; i < index; i++){
    loc = loc->next;
  }
  
  *node = loc;
  return index;
}


