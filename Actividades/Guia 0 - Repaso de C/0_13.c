/*
 * Terminemos esta guía a lo grande!
 *
 * Último ejercicio de archivos. Ahora, lo almacenado en el archivo corresponde
 * a información de pokemones. No se sabe cuántos pokemones hay en el archivo,
 * pero te aviso que que no va a haber más de 10.
 *
 * También conocemos cómo están organizados:
 * 	Vulpix;
 * 	15;20;19;
 * Donde Vulpix es el nombre de ese pokemon, 15 es la cantidad de batallas
 * ganadas, 20 es la cantidad de batallas perdidas y 19 es la cantidad de
 * batallas empatadas.
 *
 * Se pide devolver el pokemon que compitió en más batallas, contando las que
 * ganó, empató y perdió. Se puede asumir que no se va a recibir un archivo
 * nulo.
 *
 * Y no te preocupes por el archivo, nosotros lo cerramos detrás de bambalinas
 * ;)
 */

#include "solucion.h"

typedef struct pokemon {
	char nombre[MAX_NOMBRE];
	int b_ganadas;
	int b_perdidas;
	int b_empatadas;
} pokemon_t;

pokemon_t pokemon_con_mas_batallas(FILE *archivo)
{
	pokemon_t pokemon, max_pokemon;
	int max_batallas = -1;

	while (fscanf(archivo, "%[^;];%d;%d;%d;\n", pokemon.nombre,
		      &pokemon.b_ganadas, &pokemon.b_perdidas,
		      &pokemon.b_empatadas) == 4) {
		int total_batallas = pokemon.b_ganadas + pokemon.b_perdidas +
				     pokemon.b_empatadas;
		if (total_batallas > max_batallas) {
			max_batallas = total_batallas;
			max_pokemon = pokemon;
		}
	}

	return max_pokemon;
}