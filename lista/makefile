CC= gcc
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
ARCHIVOS= arrecife.txt acuario.txt
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

lista: pruebas_lista.c testing.c lista.c
		$(CC) pruebas_lista.c testing.c lista.c $(CFLAGS) $(WFLAGS) -o lista
val: lista
		$(V) $(VFLAGS) ./lista $(ARCHIVOS)
std: lista
	./lista $(ARCHIVOS)
help: lista
	./lista --help
gdb: lista
		$(GDB) lista  $(GFLAGS)
rm:
	$(R) lista 