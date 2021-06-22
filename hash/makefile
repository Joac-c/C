CC= cc -g -O2
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
ARCHIVOS= arrecife.txt acuario.txt
WFLAGS= -Wall -Wconversion 
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 

hash: hash_pruebas.c testing.c hash.c lista.c
		$(CC) hash_pruebas.c testing.c hash.c lista.c  -Wall -pedantic -Wformat=2 -Wshadow -Wpointer-arith -Wunreachable-code -Wconversion -Wno-sign-conversion -Wbad-function-cast --coverage -Werror -DTDA=hash -o hash
val: hash
		$(V) $(VFLAGS) ./hash $(ARCHIVOS)
std: hash
	./hash $(ARCHIVOS)
help: hash
	./hash --help
gdb: hash
		$(GDB) hash  $(GFLAGS)
rm:
	$(R) hash 