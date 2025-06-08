#include "extra/engine.h"
#include "juego.h"
#include <time.h>

const int PUNTOS_INICIALES = 10;
const int PERDIDA_DE_PUNTOS = 1;
const char TECLA_W = 'w';
const char TECLA_S = 's';
const char TECLA_D = 'd';
const char TECLA_A = 'a';
const unsigned PERDIO = 1;
const unsigned SIGUE_JUGANDO = 0;

typedef struct coordenada {
	int fil;
	int col;
} coordenada_t;

typedef struct pokemon_juego {
	coordenada_t posicion;
	struct pokemon poke;
} pokemon_juego_t;

typedef struct jugador {
	coordenada_t posicion;
	lista_t *pokes_capturados;
	pila_t *pokes_pendientes;
	unsigned puntos;
} jugador_t;

struct juego {
	jugador_t jugador;
	unsigned semilla;
	lista_t *pokes_en_juego;
	cola_t *pokes_a_aparecer;
};

/**
 * Devuelve una posición aleatoria con la semilla dada.
 */
coordenada_t generar_posicion_aleatoria(int semilla)
{
	srand(semilla + rand());
	coordenada_t pos;
	pos.fil = rand() % MAX_FILAS;
	pos.col = rand() % MAX_COLUMNAS;
	return pos;
}

juego_t *inicializar_juego(int semilla,
			   struct pokemon pokes_iniciales[MIN_POKEMONES])
{
	juego_t *juego = calloc(1, sizeof(juego_t));
	if (!juego) {
		return NULL;
	}
	juego->jugador.posicion.col = 0;
	juego->jugador.posicion.fil = 0;
	juego->jugador.puntos = PUNTOS_INICIALES;

	if (semilla != -1) {
		juego->semilla = semilla;
	} else {
		juego->semilla = (unsigned)time(NULL);
	}
	srand(juego->semilla);

	juego->jugador.pokes_capturados = lista_crear();
	juego->jugador.pokes_pendientes = pila_crear();
	juego->pokes_en_juego = lista_crear();
	juego->pokes_a_aparecer = cola_crear();

	if (!juego->jugador.pokes_capturados ||
	    !juego->jugador.pokes_pendientes || !juego->pokes_en_juego ||
	    !juego->pokes_a_aparecer) {
		destruir_juego(juego);
		return NULL;
	}

	for (int i = 0; i < MIN_POKEMONES; i++) {
		pokemon_juego_t *pokemon_en_juego =
			calloc(1, sizeof(pokemon_juego_t));
		if (!pokemon_en_juego) {
			destruir_juego(juego);
			return NULL;
		}

		pokemon_en_juego->poke = pokes_iniciales[i];
		pokemon_en_juego->posicion =
			generar_posicion_aleatoria(juego->semilla + i);

		if (!lista_insertar(juego->pokes_en_juego, pokemon_en_juego)) {
			free(pokemon_en_juego);
			destruir_juego(juego);
			return NULL;
		}
	}

	return juego;
}

/**
 * Devuelve true si la posición del jugador es la misma que la del pokemon, en caso contrario false.
 */
bool misma_posicion_que_poke(void *jugador, void *pokemon)
{
	if (!jugador || !pokemon) {
		return false;
	}

	jugador_t *player = (jugador_t *)jugador;
	pokemon_juego_t *poke = (pokemon_juego_t *)pokemon;

	bool misma_fil = (player->posicion.fil == poke->posicion.fil);
	bool misma_col = (player->posicion.col == poke->posicion.col);

	return (misma_fil && misma_col);
}

/**
 * En caso de que la posición del jugador coincida con la de algún pokemon en el juego, este se elimina y se devuelve.
 * 
 * De no coincidir de devuelve NULL.
 */
pokemon_juego_t *capturar_pokemon(jugador_t *jugador, lista_t *pokes_en_juego)
{
	if (!jugador || !pokes_en_juego || !lista_tamanio(pokes_en_juego)) {
		return NULL;
	}

	pokemon_juego_t *poke_capturado = (pokemon_juego_t *)lista_buscar(
		pokes_en_juego, misma_posicion_que_poke, jugador);

	if (poke_capturado) {
		pokemon_juego_t *poke_sacado =
			(pokemon_juego_t *)lista_sacar_elemento(pokes_en_juego,
								poke_capturado);
		return poke_sacado;
	}

	return NULL;
}

/**
 * Captura todos los pokemones en la misma posición que el jugador.
 */
void capturar_todos_los_pokemones(jugador_t *jugador, lista_t *pokes_en_juego)
{
	if (!jugador || !pokes_en_juego || !lista_tamanio(pokes_en_juego)) {
		return NULL;
	}

	pokemon_juego_t *pokemon_capturado;
	while ((pokemon_capturado =
			capturar_pokemon(jugador, pokes_en_juego))) {
		lista_insertar(jugador->pokes_capturados, pokemon_capturado);
	}
}

/**
 * Mueve la posición del jugador en el juego segun la accion pasada.
 */
void realizar_movimiento(juego_t *juego, char accion)
{
	if (accion == (TECLA_W || TECLA_ARRIBA)) {
		if (juego->jugador.posicion.fil - 1 > 0) {
			juego->jugador.posicion.fil--;
		}
	} else if (accion == (TECLA_S || TECLA_ABAJO)) {
		if (juego->jugador.posicion.fil + 1 < MAX_FILAS - 1) {
			juego->jugador.posicion.fil++;
		}
	} else if (accion == (TECLA_D || TECLA_DERECHA)) {
		if (juego->jugador.posicion.col + 1 < MAX_COLUMNAS - 1) {
			juego->jugador.posicion.col++;
		}
	} else if (accion == (TECLA_A || TECLA_IZQUIERDA)) {
		if (juego->jugador.posicion.col - 1 > 0) {
			juego->jugador.posicion.col--;
		}
	}
}

void realizar_jugada(juego_t *juego, char accion)
{
}

unsigned estado_juego(jugador_t jugador)
{
	if (jugador.puntos > 0) {
		return SIGUE_JUGANDO;
	}
	return PERDIO;
}

void destruir_juego(juego_t *juego)
{
	if (!juego) {
		return;
	}
	lista_destruir(juego->jugador.pokes_capturados);
	pila_destruir(juego->jugador.pokes_pendientes);
	lista_destruir(juego->pokes_en_juego);
	cola_destruir(juego->pokes_a_aparecer);
	free(juego);
}