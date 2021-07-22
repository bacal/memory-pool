#include <stdio.h>
#include "memory_pool.h"

int main() {
    memory_pool* mempool = memory_pool_init(16*MIB);
    int* a = memory_pool_alloc(mempool, sizeof(int));
    *a = 0x20;
    memory_pool_remove(mempool,a);
    char* string = memory_pool_alloc(mempool,6);
    *string = 'a';
    *(string+1) = 'b';
    memory_pool_remove(mempool,string);
    memory_pool_free(mempool);
    return 0;
}
