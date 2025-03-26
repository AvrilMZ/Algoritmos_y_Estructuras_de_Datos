#include "src/pokedex.h"
#include <stdio.h>
#include <string.h>

bool mostrar_pokemon_y_sumar_fuerza(struct pokemon *pokemon, void *ctx)
{
	unsigned *fuerza_total = ctx;
	printf("Id: %d, Nombre: %s, Tipo: %d, Fuerza: %d, Destreza: %d, Inteligencia: %d\n",
	       pokemon->id, pokemon->nombre, pokemon->tipo, pokemon->fuerza,
	       pokemon->destreza, pokemon->inteligencia);

	*fuerza_total += pokemon->fuerza;
	return true;
}

int main(int argc, char const *argv[])
{
	// Todo este archivo es a modo de ejemplo.
	// Modificar, eliminar o agregar código según sea necesario para lograr lo pedido en el enunciado.

	if (argc < 2) {
		printf("Uso: %s <archivo_pokedex.csv>\n", argv[0]);
		return 1;
	}

	pokedex_t *pokedex = pokedex_abrir(argv[1]);
	if (!pokedex) {
		printf("Error al abrir el archivo %s\n", argv[1]);
		return 1;
	}

	if (argc >= 2) {
		const struct pokemon *pokemon =
			pokedex_buscar_pokemon_nombre(pokedex, argv[2]);
		if (pokemon) {
			printf("El nombre es %s\n", pokemon->nombre);
		} else {
			printf("Pokemon no encontrado\n");
		}
	}

	printf("La pokedex tiene %d pokemones\n",
	       pokedex_cantidad_pokemones(pokedex));

	unsigned fuerza_total = 0;

	//Muestro los pokemon ordenados por nombre
	printf("\nPokemones ordenados por nombre:\n");
	pokedex_iterar_pokemones(pokedex, ITERAR_NOMBRE,
				 mostrar_pokemon_y_sumar_fuerza, &fuerza_total);

	printf("\nSi sumamos todas las fuerzas, el resultado es: %d\n",
	       fuerza_total);

	pokedex_destruir(pokedex);

	return 0;
}
