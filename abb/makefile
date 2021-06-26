CC= cc -g -O2
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
ARCHIVOS= arrecife.txt acuario.txt
WFLAGS= -Wall -Wconversion 
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 

abb: abb_pruebas_ext.c testing.c abb.c pila.c
		$(CC) abb_pruebas_ext.c testing.c abb.c pila.c  -Wall -pedantic -Wformat=2 -Wshadow -Wpointer-arith -Wunreachable-code -Wconversion -Wno-sign-conversion -Wbad-function-cast --coverage -Werror -DTDA=abb -o abb
val: abb
		$(V) $(VFLAGS) ./abb $(ARCHIVOS)
std: abb
	./abb $(ARCHIVOS)
help: abb
	./abb --help
gdb: abb
		$(GDB) abb  $(GFLAGS)
rm:
	$(R) abb 