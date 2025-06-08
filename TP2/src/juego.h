#ifndef JUEGO_H
#define JUEGO_H

#include "lista.h"
#include "pila.h"
#include "cola.h"
#include "pokedex.h"

#define MAX_FILAS 12
#define MAX_COLUMNAS 12
#define MIN_POKEMONES 4

typedef struct juego juego_t;

/**
 * Inicializa y devuelve un puntero al juego cargando toda la información inicial.
 * Si no se quiere usar una semilla se pasa -1.
 * Se deben pasar los pokemones iniciales del juego.
 * 
 * En caso de error devuelve NULL.
 */
juego_t *inicializar_juego(int semilla,
			   struct pokemon pokes_iniciales[MIN_POKEMONES]);

/**
 * Realizará la acción recibida por parámetro.
 */
void realizar_jugada(juego_t *juego, char accion);

/**
 * Devuelve: 1 si perdio y 0 si se sigue jugando.
 * 
 * Un jugador pierde cuando se queda sin puntos.
 */
unsigned estado_juego(juego_t juego);

/**
 * Libera la memoria dinámica reservada para el juego.
 */
void destruir_juego(juego_t *juego);

#endif // JUEGO_H