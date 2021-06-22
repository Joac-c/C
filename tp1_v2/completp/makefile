CC= gcc
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
ARCHIVOS= archivo.txt
WFLAGS= -Wall -Wconversion -Werror -lm -Wbad-function-cast
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

dc: pila.c calc_helper.c dc.c strutil.c 
		$(CC) pila.c calc_helper.c dc.c strutil.c  $(CFLAGS) $(WFLAGS) -lm -o dc

infix: pila.c calc_helper.c  strutil.c cola.c infix.c
		$(CC) pila.c calc_helper.c  strutil.c cola.c infix.c  $(CFLAGS) $(WFLAGS) -lm -o infix
val: dc
		$(V) $(VFLAGS) ./dc < arch.txt

valfix: infix dc
		$(V) $(VFLAGS) ./infix $(ARCHIVOS) 
std: dc
	./dc $(ARCHIVOS)
help: dc
	./dc --help
gdb: dc
		$(GDB) dc  $(GFLAGS)
rm:
	$(R) dc 