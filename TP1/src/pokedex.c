#include "pokedex.h"
#include <stdio.h>

#define MODO_LECTURA "r"

struct pokedex {
	FILE *archivo;
};

/*
 * Crea una nueva pokedex a partir de un archivo.
 * 
 * Devuelve un puntero a la pokedex si se pudo abrir el archivo, o NULL en caso contrario.
 * 
 * Cada pokemon en el archivo debe tener el siguiente formato: id;nombre;tipo;fuerza;destreza;inteligencia
 * 
 * Al encontrar un pokemon inválido, se ignora y finaliza la lectura del archivo. Se leen todos los pokemon válidos del archivo y se almacenan en la pokedex. Si no se pudo leer ningún pokemon válido, se devuelve NULL.
 */
pokedex_t *pokedex_abrir(const char *archivo)
{
	if (!archivo || !*archivo) {
		printf("No se pudo abrir el archivo\n");
		return NULL;
	}

	pokedex_t *pokemones = malloc(sizeof(pokedex_t));
	if (!pokemones) {
		printf("Error reservando memoria\n");
		return NULL;
	}

	pokemones->archivo = fopen(archivo, MODO_LECTURA);
	if (!pokemones->archivo) {
		free(pokemones);
		printf("No se pudo abrir el archivo \n");
		return NULL;
	}

	return pokemones;
}

/*
 * Devuelve la cantidad de pokemones en la pokedex.
 */
unsigned pokedex_cantidad_pokemones(pokedex_t *pokedex)
{
	if (!pokedex || !pokedex->archivo) {
		return 0;
	}

	rewind(pokedex->archivo);
	unsigned contador_lineas = 0;
	bool linea_tiene_contenido = false;

	int caracter = fgetc(pokedex->archivo);
	while (caracter != EOF) {
		linea_tiene_contenido = true;
		if (caracter == '\n') {
			contador_lineas++;
			linea_tiene_contenido = false;
		}
		caracter = fgetc(pokedex->archivo);
	}

	if (linea_tiene_contenido && caracter != '\n') {
		contador_lineas++;
	}

	return contador_lineas;
}

/*
 * Busca un pokemon con el nombre especificado en la pokedex.
 * 
 * Devuelve un puntero al pokemon si se encontró, o NULL en caso contrario.
 */
const struct pokemon *pokedex_buscar_pokemon_nombre(pokedex_t *pokedex,
						    const char *nombre)
{
}

/*
 * Busca un pokemon con el id especificado en la pokedex.
 * 
 * Devuelve un puntero al pokemon si se encontró, o NULL en caso contrario.
 */
const struct pokemon *pokedex_buscar_pokemon_id(pokedex_t *pokedex, unsigned id)
{
}

/*
 * Invoca la función especificada para cada pokemon en la pokedex.
 * 
 * La función se debe invocar con los pokemon ordenados según el criterio de iteracion dado (creciente por nombre o por id).
 * 
 * La función de iteración recibe un puntero al pokemon y un puntero al contexto y devuelve 
 * true si se debe seguir iterando, o false en caso contrario.
 * 
 * Devuelve la cantidad de pokemones iterados.
 * 
 * Restriccion del TP: implementar con complejidad O(n) en tiempo y O(1) en espacio.
 */
unsigned pokedex_iterar_pokemones(pokedex_t *pokedex, enum modo_iteracion modo,
				  bool (*funcion)(struct pokemon *, void *),
				  void *ctx)
{
}

/*
 * Destruye la pokedex.
 */
void pokedex_destruir(pokedex_t *pokedex)
{
	if (pokedex) {
		if (pokedex->archivo) {
			fclose(pokedex->archivo);
			pokedex->archivo = NULL;
		}
		free(pokedex);
		pokedex = NULL;
	}
}