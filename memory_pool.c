//
// Created by Bacal Mesfin on 7/21/21.
//

#include "memory_pool.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void* use_preallocated_spot(memory_pool* mempool, size_t size);

memory_pool *memory_pool_init(size_t size)
{
    if(!size)
    {
        return NULL;
    }
    memory_pool* mempool = (memory_pool*) malloc(sizeof(struct MEMORY_POOL_STRUCT));
    mempool->front = (unsigned char*)malloc(size* sizeof(unsigned char));
    memset(mempool->front, 0, size);
    mempool->back = mempool->front + size;
    mempool->objects = NULL;
    mempool->size_remaining = size;
    return mempool;
}

void* memory_pool_alloc(memory_pool *mempool, size_t size)
{
    void* check = use_preallocated_spot(mempool,size);
    if(check)
        return check;

    if(mempool->size_remaining<size)
    {
        fprintf(stderr, "Error: Memory pool is full!\n");
        return NULL;
    }
    else if(mempool->objects == NULL)
    {
        mempool->objects = malloc(sizeof(struct MEMORY_POOL_OBJECT_STRUCT));
        mempool->objects->front = mempool->front;
        mempool->objects->back = mempool->front + size;
        mempool->objects->in_use = true;
        mempool->objects->next = NULL;
        mempool->objects->size = size;
        mempool->size_remaining -= size;
        return (void*) mempool->objects->front;
    }
    else
    {
        mempool->size_remaining -= size;
        memory_object* mem_object = mempool->objects;
        while(mem_object->next != NULL)
        {
            mem_object = mem_object->next;
        }
        mem_object->next = malloc(sizeof(struct MEMORY_POOL_OBJECT_STRUCT));
        mem_object->next->prev = mem_object;
        mem_object->next->in_use = true;
        mem_object->next->front = mempool->back - mempool->size_remaining;
        mem_object->next->back = mem_object->next->front + size;
        mem_object->next->size = size;
        mem_object->next->next = NULL;
        return (void*)mem_object->next->front;
    }
}

void memory_pool_remove(memory_pool* mempool, void* data)
{
    for(memory_object* temp = mempool->objects; temp != NULL; temp = temp->next)
    {
        if(temp->front == data)
        {
            temp->in_use = false;
            mempool->size_remaining += temp->size;
            break;
        }
    }
}


void memory_pool_clear(memory_pool *mempool)
{
	memory_object* t_obj,*mem_obj;
	mem_obj = mempool->objects;
	while(mem_obj != NULL){
		t_obj = mem_obj;
		mem_obj =  mem_obj->next;
		free(t_obj);
	}
	mempool->objects = NULL;
	mempool->size_remaining = mempool->back - mempool->front;

	memset(mempool->front, 0, mempool->size_remaining);

	mempool->objects = NULL;
}

void memory_pool_free(memory_pool *mempool)
{
	memory_object* mem_object;
	if (mempool->objects)
	{
		mem_object = mempool->objects;
		while (mem_object != NULL)
		{
			memory_object* p_obj = mem_object;
			mem_object = mem_object->next;
			free(p_obj);
		}

		free(mempool->front);
		free(mempool);

	}
}

void* use_preallocated_spot(memory_pool* mempool, size_t size)
{
    int i=0;
    if(mempool->objects == NULL)
        return NULL;
    for(memory_object* memory_object = mempool->objects;memory_object->next!= NULL; memory_object = memory_object->next)
    {
        if(memory_object->in_use == false && memory_object->size >= size)
        {
            memory_object->in_use = true;
            return memory_object->front;
        }
        i++;
    }
    return NULL;
}