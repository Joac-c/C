C= gcc
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes


juego: juego.c juego_pruebas.c
		$(CC) juego.c juego_pruebas.c herramientas/abb.c herramientas/lista.c herramientas/heap.c $(CFLAGS) $(WFLAGS) -o juego
val: juego
		$(V) $(VFLAGS) ./juego 
std: juego
	./juego $(ARCHIVOS)
help: juego
	./juego --help
gdb: juego
		$(GDB) juego  $(GFLAGS)
rm:
	$(R) juego

mini: juego.c juego_minipruebas.c
		$(CC) juego.c juego_minipruebas.c $(CFLAGS) $(WFLAGS) -o juegom
valmi: juegom
		$(V) $(VFLAGS) ./juegom 