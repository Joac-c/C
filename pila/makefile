CC= gcc
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
ARCHIVOS= arrecife.txt acuario.txt
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

pila: pruebas_pila.c testing.c pila.c
		$(CC) pruebas_pila.c testing.c pila.c $(CFLAGS) $(WFLAGS) -o pila
val: pila
		$(V) $(VFLAGS) ./pila $(ARCHIVOS)
std: pila
	./pila $(ARCHIVOS)
help: pila
	./pila --help
gdb: pila
		$(GDB) pila  $(GFLAGS)
rm:
	$(R) pila 