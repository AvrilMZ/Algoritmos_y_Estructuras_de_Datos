/*
 * Trabajemos un poco más con structs. Aquí se presenta nuevamente el struct de
 * un pokémon (en solucion.h). Un pokémon, según esta definición, posee un
 * nombre en formato string (termina con un '\0'), y la cantidad de victorias de
 * ese pokemon.
 *
 * Se pide devolver el pokémon de ese vector con más victorias. Exactamente,
 * ahora no se devuelve un int, o un char, que son tipos de datos nativos de C.
 * Ahora, queremos devolver un tipo de dato creado por nosotros. Que es igual de
 * válido que devolver un int, un char, un float, etc.
 *
 * En caso de que dos pokemones tengan la misma cantidad de victorias, se
 * debería devolver el que tenga el "menor nombre". Es decir, el que primero
 * aparecería en el diccionario.
 */

#include "solucion.h"

typedef struct pokemon {
	char nombre[MAX_NOMBRE_POKEMON];
	int victorias;
} pokemon_t;

pokemon_t pokemon_con_mas_victorias(pokemon_t pokemones[MAX_VECTOR],
				    int tope_vector)
{
	pokemon_t pokemon_ganador = pokemones[0];
	for (int i = 1; i < tope_vector; i++) {
		if (pokemones[i].victorias > pokemon_ganador.victorias) {
			pokemon_ganador = pokemones[i];
		} else if (pokemones[i].victorias ==
			   pokemon_ganador.victorias) {
			if (strcmp(pokemones[i].nombre,
				   pokemon_ganador.nombre) < 0)
				pokemon_ganador = pokemones[i];
		}
	}
	return pokemon_ganador;
}