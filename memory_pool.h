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

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Memory pool object strucutre.
 * Each object contains pointers to the front and back of the data,
 * whether or not it is in use,
 * the size and a pointer to the next memory pool object (similar to a list).
 */
typedef struct MEMORY_POOL_OBJECT_STRUCT {
    struct MEMORY_POOL_OBJECT_STRUCT *prev; // points to previous item in memory pool
    unsigned char *front; // beginning of data
    unsigned char *back; // end of data
    bool in_use; // whether or not chunk is in use
    int size; // size in bytes
    struct MEMORY_POOL_OBJECT_STRUCT *next; // points to next item in memory pool
} memory_object;

/**
 * @brief Memory Pool structure.
 *
 */
typedef struct MEMORY_POOL_STRUCT {
    unsigned char *front;
    unsigned char *back;
    memory_object *objects;
    size_t size_remaining;
} memory_pool;

/**
 * @brief Initializes a new memory pool of size, size.
 * @param size - Pool size in bytes
 * @return memory_pool* - Pointer to a memory_pool structure.
 */
memory_pool *memory_pool_init(size_t size);

/**
 *
 * @param mempool
 * @param size
 * @return
 */
void *memory_pool_alloc(memory_pool *mempool, size_t size);

/**
 * @brief Allocates a word aligned amount of memory
 * @param mempool
 * @param size
 * @return
 */
void *memory_pool_alloc_aligned(memory_pool *mempool, size_t size);

/**
 * @brief Removes in-use memory from the pool
 * @param mempool - Memory pool from which data is removed
 * @param data - Data to be removed from pool
 */
void memory_pool_remove(memory_pool *mempool, void **data);

/**
 * @brief Clears all references to active objects and nullifies all bytes
 * in the pool.
 * @param mempool
 */
void memory_pool_clear(memory_pool *mempool);

/**
 * @brief Deletes memory from the heap. Modifies the memory_pool pointer to be null.
 * @param mempool
 */
void memory_pool_free(memory_pool **mempool);

#ifdef __cplusplus
}
#endif

#endif //MEMORY_POOL_MEMORY_POOL_H
