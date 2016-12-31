#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "bool.h"

#define MB_UNINITIALIZED 0
#define MB_INITIALIZED 1
#define MB_FREED 2

typedef struct{
	int state;
	size_t size;
	void* address;
} MALLOC_BLOCK;

void* ese_malloc(size_t new_size);

void* ese_calloc(size_t number, size_t size);

void ese_free(void* old_address);

int ese_malloc_allocated_count();

void ese_reset_list();

void mb_list_check_initialize();

MALLOC_BLOCK* mb_create();

int mb_initialize(MALLOC_BLOCK* new_mb);
