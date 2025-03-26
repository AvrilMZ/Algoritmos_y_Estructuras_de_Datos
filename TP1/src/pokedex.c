#include "pokedex.h"
#include <stdio.h>
#include <string.h>

#define MODO_LECTURA "r"
const size_t CAPACIDAD_INICIAL = 16;

struct pokedex {
	FILE *archivo;
	struct pokemon poke_buscado;
};

/*
 * Crea una nueva pokedex a partir de un archivo.
 * 
 * Devuelve un puntero a la pokedex si se pudo abrir el archivo, o NULL en caso contrario.
 * 
 * Cada pokemon en el archivo debe tener el siguiente formato: id;nombre;tipo;fuerza;destreza;inteligencia
 * 
 * Al encontrar un pokemon inválido, se ignora y deja de leer del archivo. Se leen todos los pokemon válidos del archivo y se almacenan en la pokedex. Si no se pudo leer ningún pokemon válido, se devuelve NULL.
 */
pokedex_t *pokedex_abrir(const char *archivo)
{
	if (!archivo || !*archivo) {
		printf("No se pudo abrir el archivo\n");
		return NULL;
	}

	pokedex_t *pokedex = malloc(sizeof(pokedex_t));
	if (!pokedex) {
		printf("Error reservando memoria\n");
		return NULL;
	}

	pokedex->archivo = fopen(archivo, MODO_LECTURA);
	if (!pokedex->archivo) {
		free(pokedex);
		printf("No se pudo abrir el archivo \n");
		return NULL;
	}

	pokedex->poke_buscado = (struct pokemon){ 0, NULL, 0, 0, 0, 0 };
	return pokedex;
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

// Reserva memoria para la línea y la inicializa.
char *reservar_memoria_linea(size_t capacidad)
{
	char *linea = malloc(sizeof(char) * capacidad);
	if (!linea) {
		printf("Error reservando memoria\n");
		return NULL;
	}
	return linea;
}

// Realoca memoria para la línea y los bytes adicionales (si los hay) se inicializan en 0.
char *realocar_memoria_linea(char *linea, size_t capacidad)
{
	char *nueva_linea = realloc(linea, sizeof(char) * capacidad);
	if (!nueva_linea) {
		printf("Error realocando memoria\n");
		return NULL;
	}

	return nueva_linea;
}

/*
 * Busca un pokemon con el nombre especificado en la pokedex.
 * 
 * Devuelve un puntero al pokemon si se encontró, o NULL en caso contrario.
 */
const struct pokemon *pokedex_buscar_pokemon_nombre(pokedex_t *pokedex,
						    const char *nombre)
{
	if (!pokedex || !pokedex->archivo || !nombre) {
		return NULL;
	}

	rewind(pokedex->archivo);

	size_t capacidad = CAPACIDAD_INICIAL;
	char *linea = reservar_memoria_linea(capacidad);
	if (!linea) {
		return NULL;
	}

	bool poke_encontrado = false;
	while (fgets(linea, (int)capacidad, pokedex->archivo) &&
	       !poke_encontrado) {
		while (strlen(linea) == (capacidad - 1) &&
		       !feof(pokedex->archivo)) {
			capacidad *= 2;
			char *nueva_linea =
				realocar_memoria_linea(linea, capacidad);
			if (!nueva_linea) {
				free(linea);
				return NULL;
			}
			linea = nueva_linea;

			size_t longitud_actual = strlen(linea);
			if (!fgets(linea + longitud_actual,
				   (int)(capacidad - longitud_actual),
				   pokedex->archivo)) {
				free(linea);
				return NULL;
			}
		}

		int id = atoi(strtok(linea, ";"));
		char *nombre_poke = strtok(NULL, ";");
		char tipo = strtok(NULL, ";")[0];
		int fuerza = atoi(strtok(NULL, ";"));
		int destreza = atoi(strtok(NULL, ";"));
		int inteligencia = atoi(strtok(NULL, ";"));

		if (nombre_poke && strcmp(nombre_poke, nombre) == 0) {
			pokedex->poke_buscado.id = (unsigned)id;

			size_t nombre_len = strlen(nombre_poke) + 1;
			pokedex->poke_buscado.nombre =
				reservar_memoria_linea(nombre_len);
			if (!pokedex->poke_buscado.nombre) {
				free(linea);
				return NULL;
			}
			strcpy((char *)pokedex->poke_buscado.nombre,
			       nombre_poke);

			pokedex->poke_buscado.tipo = tipo;
			pokedex->poke_buscado.fuerza = (unsigned)fuerza;
			pokedex->poke_buscado.destreza = (unsigned)destreza;
			pokedex->poke_buscado.inteligencia =
				(unsigned)inteligencia;

			poke_encontrado = true;
		}
	}

	if (linea) {
		free(linea);
		linea = NULL;
	}

	if (poke_encontrado) {
		return &(pokedex->poke_buscado);
	} else {
		return NULL;
	}
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
		if (pokedex->poke_buscado.nombre) {
			free((char *)pokedex->poke_buscado.nombre);
			pokedex->poke_buscado.nombre = NULL;
		}
		free(pokedex);
		pokedex = NULL;
	}
}