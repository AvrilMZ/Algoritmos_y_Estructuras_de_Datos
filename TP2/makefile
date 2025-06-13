VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
ENGINECFLAGS =-Wall -O2 -g
CC = gcc

all: clean valgrind-tp2

valgrind-alumno: pruebas_menu pruebas_juego
	valgrind $(VALGRIND_FLAGS) ./pruebas_menu
	valgrind $(VALGRIND_FLAGS) ./pruebas_juego

pruebas_menu: src/*.c testing/pruebas_menu.c engine
	$(CC) $(CFLAGS) src/*.c testing/pruebas_menu.c engine.o -o pruebas_menu

pruebas_juego: src/*.c testing/pruebas_juego.c engine
	$(CC) $(CFLAGS) src/*.c testing/pruebas_juego.c engine.o -o pruebas_juego

valgrind-tp2: tp2
	valgrind $(VALGRIND_FLAGS) ./tp2 datos/pokedex.csv

engine:
	$(CC) $(ENGINECFLAGS) -c extra/engine.c -o engine.o

tp2: engine
	$(CC) $(CFLAGS) src/*.c tp2.c engine.o -o tp2

clean:
	rm -f pruebas_menu pruebas_juego tp2 engine.o
