CC=gcc
FLAGS=-Wall -Werror --pedantic --std=c99

memory_pool.o:memory_pool.c memory_pool.h
	${CC} ${FLAGS} -c memory_pool.c -o memory_pool.o

clean:
	rm *.o
