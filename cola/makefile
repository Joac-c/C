CC= gcc
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
ARCHIVOS= arrecife.txt acuario.txt
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

cola: pruebas_cola.c testing.c cola.c
		$(CC) pruebas_cola.c testing.c cola.c $(CFLAGS) $(WFLAGS) -o cola
val: cola
		$(V) $(VFLAGS) ./cola $(ARCHIVOS)
std: cola
	./cola $(ARCHIVOS)
help: cola
	./cola --help
gdb: cola
		$(GDB) cola  $(GFLAGS)
rm:
	$(R) cola 