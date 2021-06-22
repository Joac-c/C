
CC= gcc
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
ARCHIVOS= arrecife.txt acuario.txt
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes


lista: lista.c lista_pruebas.c
		$(CC) lista.c lista_pruebas.c $(CFLAGS) $(WFLAGS) -o lista
val: lista
		$(V) $(VFLAGS) ./lista 
std: lista
	./lista $(ARCHIVOS)
help: lista
	./lista --help
gdb: lista
		$(GDB) lista  $(GFLAGS)
rm:
	$(R) lista 


listap: lista.c lista_minipruebas.c
		$(CC) lista.c lista_minipruebas.c $(CFLAGS) $(WFLAGS) -o listap
valp: listap
		$(V) $(VFLAGS) ./listap