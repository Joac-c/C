CC= gcc
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
ARCHIVOS= arrecife.txt acuario.txt
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

tp0: tp0_pruebas.c testing.c tp0.c
		$(CC) tp0_pruebas.c testing.c tp0.c $(CFLAGS) $(WFLAGS) -o tp0
val: tp0
		$(V) $(VFLAGS) ./tp0 $(ARCHIVOS)
std: tp0
	./tp0 $(ARCHIVOS)
help: tp0
	./tp0 --help
gdb: tp0
		$(GDB) tp0  $(GFLAGS)
rm:
	$(R) tp0 