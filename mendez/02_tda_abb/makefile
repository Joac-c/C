C= gcc
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes


abb: abb.c abb_pruebas.c
		$(CC) abb.c abb_pruebas.c $(CFLAGS) $(WFLAGS) -o abb
val: abb
		$(V) $(VFLAGS) ./abb 
std: abb
	./abb $(ARCHIVOS)
help: abb
	./abb --help
gdb: abb
		$(GDB) abb  $(GFLAGS)
rm:
	$(R) abb

mini: abb.c abb_minipruebas.c
		$(CC) abb.c abb_minipruebas.c $(CFLAGS) $(WFLAGS) -o abbm
valmi: abbm
		$(V) $(VFLAGS) ./abbm 