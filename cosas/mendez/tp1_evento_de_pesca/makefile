CC= gcc
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
ARCHIVOS= arrecife.txt acuario.txt
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

evento_pesca: simulador.c evento_pesca.c
		$(CC) simulador.c evento_pesca.c $(CFLAGS) $(WFLAGS) -o evento_pesca
val: evento_pesca
		$(V) $(VFLAGS) ./evento_pesca $(ARCHIVOS)
std: evento_pesca
	./evento_pesca $(ARCHIVOS)
help: evento_pesca
	./evento_pesca --help
gdb: evento_pesca
		$(GDB) evento_pesca  $(GFLAGS)
rm:
	$(R) evento_pesca 

	