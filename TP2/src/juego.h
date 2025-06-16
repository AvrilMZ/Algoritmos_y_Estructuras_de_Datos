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
 * Se deben pasar los pokémones iniciales del juego.
 * 
 * En caso de error devuelve NULL.
 */
conexion_juegos_t *inicializar_juego(pokedex_t *pokedex, unsigned int semilla);

/**
 * Devuelve un puntero al número de juego dado de la conexion.
 * 
 * En caso de error devuelve NULL.
 */
juego_t *obtener_juego(conexion_juegos_t *conexion, int numero);

/**
 * Realizará la acción recibida por parámetro.
 */
void realizar_jugada(conexion_juegos_t *conexion, int accion);

/**
 * Obtiene el contenido de una posición específica del tablero.
 */
char obtener_contenido_posicion(juego_t *juego, int fila, int columna);

/**
 * Obtiene el struct pokémon de una posición específica del tablero.
 * 
 * En caso de no existir o de error devuelve NULL.
 */
struct pokemon *obtener_pokemon_en_posicion(juego_t *juego, int fila,
					    int columna);

/**
 * Devuelve: 1 si gano el jugador uno, -1 si gano el jugador dos, 0 si se siguen jugando 
 * o 2 si se termino el tiempo y hubo un empate.
 * 
 * Un jugador pierde cuando se queda sin puntos.
 */
int estado_juego(conexion_juegos_t *conexion);

/**
 * Obtiene los puntos del jugador.
 */
unsigned obtener_puntos_jugador(juego_t *juego);

/**
 * Obtiene la cantidad de pokémones capturados.
 */
size_t obtener_cantidad_pokes_capturados(juego_t *juego);

/**
 * Obtiene el pokémon en el indice dado de la lista de pokémones capturados.
 * 
 * En caso de error devuelve NULL.
 */
struct pokemon *obtener_pokemon_capturado(juego_t *juego, int posicion);

/**
 * Recorre la lista de pokémones capturados del juego dado. La función recibe como 
 * primer parámetro el elemento de la lista y como segundo parámetro el contexto.
 * Si la función devuelve true, el elemento cumple el criterio.
 * 
 * Devuelve la cantidad de iteraciones realizadas.
 */
unsigned recorrer_pokemones_capturados(juego_t *juego,
				       bool (*criterio)(void *, void *),
				       void *ctx);

/**
 * Obtiene el tamaño de la pila de pokémones pendientes.
 */
size_t obtener_cantidad_pokes_pendientes(juego_t *juego);

/**
 * Obtiene el pokémon en el tope de la pila de pokémones pendientes.
 * 
 * Devuelve NULL si no hay elementos en la pila.
 */
struct pokemon *obtener_pokemon_pendiente_tope(juego_t *juego);

/**
 * Obtiene el tiempo restante en segundos para el juego.
 * 
 * Devuelve 0 cuando se ha agotado el tiempo.
 */
int obtener_tiempo_restante(conexion_juegos_t *conexion);

/**
 * Libera la memoria reservada para el juego.
 */
void destruir_juego(conexion_juegos_t *juego);

#endif // JUEGO_H