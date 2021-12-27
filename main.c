#include <stdio.h>
#include "memory_pool.h"

int main() {
    memory_pool* mempool = memory_pool_init(40);
    int* a = memory_pool_alloc(mempool, sizeof(int));
    *a = 0x20;
    memory_pool_remove(mempool,a);
    char* string = memory_pool_alloc(mempool,6);
    *string = 'a';
    *(string+1) = 'b';
    *(string+2) = '\0';

    printf("%s\n", string);

    memory_pool_remove(mempool,string);

    string = memory_pool_alloc(mempool, 5);
	memory_pool_clear(mempool);
	printf("Size remaining: %d\n", mempool->size_remaining);
	a = memory_pool_alloc(mempool,10*sizeof(int));
	for(unsigned char i=0; i<10; i++){
		printf("0x%x ",*(a+i));
	}

    memory_pool_free(mempool);
    return 0;
}
