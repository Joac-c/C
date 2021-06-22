C= gcc
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes


pruebas: heap.c pruebas_heap.c
		$(CC) heap.c pruebas_heap.c $(CFLAGS) $(WFLAGS) -o pruebas

val: pruebas
		$(V) $(VFLAGS) ./pruebas

 