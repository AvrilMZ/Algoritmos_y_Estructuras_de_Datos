#include "extra/engine.h"
#include "extra/ansi.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define X_MAXIMO 20
#define Y_MAXIMO 20

struct jugador {
	unsigned x;
	unsigned y;
};

struct juego{
	struct jugador jugadores[2];
	unsigned iteraciones_restantes;
	int ultimo_numero;
	unsigned int semilla;
};

int logica_del_juego(int tecla, void* ctx)
{
	struct juego *juego = ctx;

	borrar_pantalla();
	esconder_cursor();


	tecla = tolower(tecla);

	if(tecla == 'w'){
		juego->jugadores[0].y--;
	} else if(tecla == 's'){
		juego->jugadores[0].y++;
	} else if(tecla == TECLA_ARRIBA) {
		juego->jugadores[1].y--;
	} else if(tecla == TECLA_ABAJO) {
		juego->jugadores[1].y++;
	} else if(tecla == 'q') {
		printf("Saliendo....\n");
		mostrar_cursor();
		return 1;
	} else if(tecla == 'r') {
		juego->ultimo_numero = rand();
	}


	printf("Jugador 1: " ANSI_COLOR_RED  "%u/%u\n" ANSI_COLOR_WHITE, juego->jugadores[0].x,juego->jugadores[0].y);
	printf("Jugador 2: %u/%u\n", juego->jugadores[1].x,juego->jugadores[1].y);
	printf("Semilla: " ANSI_COLOR_GREEN ANSI_COLOR_BOLD "%u\n" ANSI_COLOR_RESET, juego->semilla);
	printf("Ultimo numero generado: " ANSI_COLOR_BLUE ANSI_COLOR_BOLD "%i\n" ANSI_COLOR_RESET, juego->ultimo_numero % 100);
	printf("Tiempo restante: %us\n", juego->iteraciones_restantes/5);
	printf("\n\nPresione Q para salir\n");
	juego->iteraciones_restantes--;

	return juego->iteraciones_restantes == 0;
}


int main(int argc, char *argv[])
{

	struct jugador j1 = {.x=0, .y=10};
	struct jugador j2 = {.x=6, .y=1};

	struct juego juego;
	juego.jugadores[0] = j1;
	juego.jugadores[1] = j2;
	juego.iteraciones_restantes = 1*60*5;

	srand((unsigned)time(NULL));
	juego.semilla = (unsigned)rand();

	juego.ultimo_numero = rand();

	game_loop(logica_del_juego, &juego);

	return 0;
}
