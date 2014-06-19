#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "linked_list.h"
#include "bool.h"
#include "ese_malloc.h"

LINKED_LIST* malloc_block_list;

void* ese_malloc(size_t new_size){
	MALLOC_BLOCK* new_block;
	
	mb_list_check_initialize();
	
	new_block = mb_create();
	new_block->state = MB_INITIALIZED;
	new_block->size = new_size;
	new_block->address = malloc(new_size);
	ll_push_back(malloc_block_list, new_block);
	
	return new_block->address;
}

void* ese_calloc(size_t number, size_t size){
	return ese_malloc(number * size);
}

void ese_free(void* old_address){
	
	int i = 0;
	MALLOC_BLOCK* temp_block;
	
	mb_list_check_initialize();
	
	for(i = 0; i < malloc_block_list->size; i++){
		ll_get(malloc_block_list, i, (void**)(&temp_block));
		if(temp_block->address == old_address){
			temp_block->state = MB_FREED;
		}
	}
	
	free(old_address);
	
}

int ese_malloc_allocated_count(){
	int counter = 0;
	int i = 0;
	MALLOC_BLOCK* temp_block;
	
	for(i = 0; i < malloc_block_list->size; i++){
		ll_get(malloc_block_list, i, (void**)(&temp_block));
		if(temp_block->state == MB_INITIALIZED){
			counter++;
		}
	}
	
	return counter;
}

void ese_reset_list(){
	mb_list_check_initialize();
	
	int i = 0;
	for(i = malloc_block_list->size - 1; i >= 0; i--){
		ll_remove(malloc_block_list, i, NULL);
	}
}

void mb_list_check_initialize(){
	static int initialized = FALSE;
	
	if(!initialized){
		malloc_block_list = ll_create(&free);
		initialized = TRUE;
	}
}

MALLOC_BLOCK* mb_create(){
	MALLOC_BLOCK* new_mb = malloc(sizeof(MALLOC_BLOCK));
  mb_initialize(new_mb);
  if(new_mb == NULL){
    errno = ENOMEM;
    return NULL;
  }
  return new_mb;
}

int mb_initialize(MALLOC_BLOCK* new_mb){
  if(new_mb != NULL){
  	new_mb->state = MB_UNINITIALIZED;
  	new_mb->size = 0;
  	new_mb->address = NULL;
    return 0;
  }
  else{
    errno = ENOMEM;
    return -1;
  }
}
