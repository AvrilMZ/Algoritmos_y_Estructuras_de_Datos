/*
 * Démosle una vuelta de tuerca al ejercicio anterior. Ahora, en vez de recibir
 * el puntero a la fuerza en sí, recibimos un pokemon que posee dicha variable.
 *
 * Se requiere modificar la fuerza del pokemon con las mismas reglas del
 * ejercicio anterior. Por si no te las acordás…
 * 	- El porcentaje viene dado como 90, no como 0,90
 * 	- Si la fuerza actual es 100 y nos pasan el porcentaje 90, la nueva
 * 	fuerza debe valer 90.
 * 	- No podemos calcular la nueva fuerza con un porcentaje negativo; en ese
 * 	caso, no se modifica la fuerza actual del pokemon.
 */

#include "solucion.h"

typedef struct pokemon {
	float fuerza;
	char *nombre;
} pokemon_t;

void ajustar_fuerza(pokemon_t *pokemon, float porcentaje)
{
	if (porcentaje >= 0)
		pokemon->fuerza = (pokemon->fuerza * porcentaje) / 100;
}