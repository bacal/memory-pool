//
// Created by Bacal Mesfin on 7/20/21.
//

#ifndef MEMORY_POOL_MEMORY_POOL_H
#define MEMORY_POOL_MEMORY_POOL_H
#include <stdbool.h>
#include <stddef.h>

#define KIB (unsigned long long int)1024
#define MIB (unsigned long long int)1024*KIB
#define GIB (unsigned long long int)1024*MIB


typedef struct MEMORY_POOL_OBJECT_STRUCT
{
    struct MEMORY_POOL_OBJECT_STRUCT* prev; // points to previous item in memory pool
    unsigned char* front; // beginning of data
    unsigned char* back; // end of data
    bool in_use; // whether or not chunk is in use
	int size; // size in bytes
	struct MEMORY_POOL_OBJECT_STRUCT* next; // points to next item in memory pool
}memory_object;

typedef struct MEMORY_POOL_STRUCT
{
    unsigned char* front;
    unsigned char* back;
    memory_object* objects;
    size_t size_remaining;
} memory_pool;


memory_pool* memory_pool_init(size_t size);

void* memory_pool_alloc(memory_pool* mempool, size_t size);

void memory_pool_remove(memory_pool* mempool, void* data);

void memory_pool_clear(memory_pool* mempool);

void memory_pool_free(memory_pool* mempool);

#endif //MEMORY_POOL_MEMORY_POOL_H
