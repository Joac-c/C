CC= gcc
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
ARCHIVOS= arrecife.txt acuario.txt
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

strutil: pruebas_strutil.c testing.c strutil.c
		$(CC) pruebas_strutil.c testing.c strutil.c $(CFLAGS) $(WFLAGS) -o strutil
val: strutil
		$(V) $(VFLAGS) ./strutil $(ARCHIVOS)
std: strutil
	./strutil $(ARCHIVOS)
help: strutil
	./strutil --help
gdb: strutil
		$(GDB) strutil  $(GFLAGS)
rm:
	$(R) strutil 