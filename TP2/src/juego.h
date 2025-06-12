#ifndef JUEGO_H
#define JUEGO_H

#include "lista.h"
#include "pila.h"
#include "pokedex.h"

#define MAX_FILAS 12
#define MAX_COLUMNAS 12
#define MAX_JUGADORES 2

typedef struct juego juego_t;
typedef struct conexion_juegos conexion_juegos_t;

/**
 * Inicializa y devuelve un puntero al juego cargando toda la información inicial.
 * Si no se quiere usar una semilla se pasa -1.
 * Se deben pasar los pokemones iniciales del juego.
 * 
 * En caso de error devuelve NULL.
 */
conexion_juegos_t *inicializar_juego(pokedex_t *pokedex, unsigned int semilla);

/**
 * 
 */
juego_t *obtener_juego(conexion_juegos_t *conexion, int numero);

/**
 * Realizará la acción recibida por parámetro.
 */
void realizar_jugada(conexion_juegos_t *conexion, int accion);

/**
 * Devuelve: 1 si gano el jugador uno, -1 si gano el jugador dos y 0 si se siguen jugando.
 * 
 * Un jugador pierde cuando se queda sin puntos.
 */
int estado_juego(conexion_juegos_t *conexion);

/**
 * Obtiene el contenido de una posición específica del tablero.
 */
char obtener_contenido_posicion(juego_t *juego, int fila, int columna);

/**
 * Obtiene el struct pokemon en una posición específica del tablero
 */
struct pokemon *obtener_pokemon_en_posicion(juego_t *juego, int fila,
					    int columna);

/**
 * Obtiene los puntos del jugador.
 */
unsigned obtener_puntos_jugador(juego_t *juego);

/**
 * Obtiene la cantidad de pokemones capturados.
 */
size_t obtener_cantidad_pokes_capturados(juego_t *juego);

/**
 * 
 */
unsigned recorrer_pokemones_capturados(juego_t *juego,
				       bool (*criterio)(void *, void *),
				       void *ctx);

/**
 * Obtiene el pokémon en la posición específica de la lista de pokémones capturados
 */
struct pokemon *obtener_pokemon_capturado(juego_t *juego, int posicion);

/**
 * Obtiene el pokémon en el tope de la pila de pokémones pendientes
 */
struct pokemon *obtener_pokemon_pendiente_tope(juego_t *juego);

/**
 * Obtiene el tamaño de la pila de pokémones pendientes
 */
size_t obtener_cantidad_pokes_pendientes(juego_t *juego);

/**
 * Obtiene el tiempo restante en segundos para el juego.
 * 
 * Devuelve 0 cuando se ha agotado el tiempo.
 */
int obtener_tiempo_restante(conexion_juegos_t *conexion);

/**
 * Libera la memoria dinámica reservada para el juego.
 */
void destruir_juego(conexion_juegos_t *juego);

#endif // JUEGO_H