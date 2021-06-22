CC= gcc
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
ARCHIVOS= arrecife.txt acuario.txt
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

tp0: vector.c testing.c pruebas_vector.c
		$(CC) vector.c testing.c pruebas_vector.c $(CFLAGS) $(WFLAGS) -o vector
val: vector
		$(V) $(VFLAGS) ./vector $(ARCHIVOS)
std: vector
	./vector $(ARCHIVOS)
help: vector
	./vector --help
gdb: vector
		$(GDB) vector  $(GFLAGS)
rm:
	$(R) vector 