#include "pokedex.h"
#include <stdio.h>
#include <string.h>

#define MODO_LECTURA "r"
const size_t CAPACIDAD_INICIAL = 16;

struct pokedex {
	FILE *archivo;
	int cantidad_pokemones;
	char *ultima_linea;
	struct pokemon *poke_buscado;
};

// Reserva memoria para un arreglo de caracteres.
char *reservar_memoria_linea(size_t capacidad)
{
	char *linea = malloc(sizeof(char) * capacidad);
	if (!linea) {
		printf("Error reservando memoria\n");
		return NULL;
	}
	return linea;
}

// Realoca memoria para un arreglo de caracteres.
char *realocar_memoria_linea(char *linea, size_t capacidad)
{
	char *nueva_linea = realloc(linea, sizeof(char) * capacidad);
	if (!nueva_linea) {
		printf("Error realocando memoria\n");
		return NULL;
	}

	return nueva_linea;
}

// Lee un campo dinámicamente hasta encontrar un ';' o fin de línea.
char *leer_campo(char **linea)
{
	if (!linea || !*linea || **linea == '\0') {
		return NULL;
	}

	size_t capacidad = CAPACIDAD_INICIAL;
	char *campo = reservar_memoria_linea(capacidad);
	if (!campo) {
		return NULL;
	}

	size_t indice_campo = 0;
	while (**linea != '\0' && **linea != ';') {
		if (indice_campo >= capacidad - 1) {
			capacidad *= 2;
			char *nuevo_campo =
				realocar_memoria_linea(campo, capacidad);
			if (!nuevo_campo) {
				free(campo);
				campo = NULL;
				return NULL;
			}
			campo = nuevo_campo;
		}
		campo[indice_campo++] = **linea;
		(*linea)++;
	}
	campo[indice_campo] = '\0';

	if (campo[0] == '\0') {
		free(campo);
		campo = NULL;
		return NULL;
	}

	if (**linea == ';') {
		(*linea)++;
	}

	return campo;
}

// Liberar todos los campos de un pokemon.
void liberar_campos(char *campo_id, char *nombre_poke, char *campo_tipo,
		    char *campo_fuerza, char *campo_destreza,
		    char *campo_inteligencia)
{
	free(campo_id);
	campo_id = NULL;
	free(nombre_poke);
	nombre_poke = NULL;
	free(campo_tipo);
	campo_tipo = NULL;
	free(campo_fuerza);
	campo_fuerza = NULL;
	free(campo_destreza);
	campo_destreza = NULL;
	free(campo_inteligencia);
	campo_inteligencia = NULL;
}

// Devuelve true si todos los campos de la linea se encuentran presentes, de lo contrario devuelve false.
bool es_linea_valida(char *linea)
{
	if (!linea || *linea == '\0') {
		return false;
	}

	char *puntero_lectura = linea;

	char *campo_id = leer_campo(&puntero_lectura);
	char *nombre_poke = leer_campo(&puntero_lectura);
	char *campo_tipo = leer_campo(&puntero_lectura);
	char *campo_fuerza = leer_campo(&puntero_lectura);
	char *campo_destreza = leer_campo(&puntero_lectura);
	char *campo_inteligencia = leer_campo(&puntero_lectura);

	if (!campo_id || !nombre_poke || !campo_tipo || !campo_fuerza ||
	    !campo_destreza || !campo_inteligencia) {
		liberar_campos(campo_id, nombre_poke, campo_tipo, campo_fuerza,
			       campo_destreza, campo_inteligencia);
		return false;
	}

	liberar_campos(campo_id, nombre_poke, campo_tipo, campo_fuerza,
		       campo_destreza, campo_inteligencia);
	return true;
}

/*
 * Lee una línea del archivo.
 *
 * Devuelve un puntero a la línea leída, o NULL si no hay más líneas.
 */
char *archivo_leer_linea(pokedex_t *pokedex)
{
	if (!pokedex || !pokedex->archivo) {
		return NULL;
	}

	if (pokedex->ultima_linea) {
		free(pokedex->ultima_linea);
		pokedex->ultima_linea = NULL;
	}

	int capacidad = CAPACIDAD_INICIAL;
	char *linea = reservar_memoria_linea(capacidad);
	if (!linea) {
		return NULL;
	}

	int caracter = fgetc(pokedex->archivo);
	int chars_leidos = 0;
	while (caracter != '\n' && feof(pokedex->archivo) == 0) {
		if (chars_leidos + 1 >= capacidad) {
			capacidad *= 2;
			char *nueva_linea =
				realocar_memoria_linea(linea, capacidad);
			if (!nueva_linea) {
				free(linea);
				linea = NULL;
				return NULL;
			}
			linea = nueva_linea;
		}
		linea[chars_leidos++] = (char)caracter;
		caracter = fgetc(pokedex->archivo);
	}

	if (chars_leidos == 0 && caracter == EOF) {
		free(linea);
		linea = NULL;
		return NULL;
	}

	linea[chars_leidos] = '\0';
	pokedex->ultima_linea = linea;
	return linea;
}

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
		pokedex = NULL;
		printf("No se pudo abrir el archivo \n");
		return NULL;
	}
	pokedex->cantidad_pokemones = 0;
	pokedex->ultima_linea = NULL;
	pokedex->poke_buscado = NULL;

	bool linea_invalida = false;
	char *linea = NULL;
	while ((linea = archivo_leer_linea(pokedex)) != NULL &&
	       !linea_invalida) {
		if (es_linea_valida(linea)) {
			pokedex->ultima_linea = linea;
			pokedex->cantidad_pokemones++;
		} else {
			linea_invalida = true;
		}
	}

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
	return (unsigned)pokedex->cantidad_pokemones;
}

// Parsear un Pokémon desde una línea de texto
struct pokemon parsear_pokemon(char *linea)
{
	struct pokemon poke = { 0, NULL, 0, 0, 0, 0 };
	char *puntero_lectura = linea;

	char *campo_id = leer_campo(&puntero_lectura);
	poke.id = atoi(campo_id);
	free(campo_id);
	campo_id = NULL;

	poke.nombre = leer_campo(&puntero_lectura);

	char *campo_tipo = leer_campo(&puntero_lectura);
	poke.tipo = campo_tipo[0];
	free(campo_tipo);
	campo_tipo = NULL;

	char *campo_fuerza = leer_campo(&puntero_lectura);
	poke.fuerza = atoi(campo_fuerza);
	free(campo_fuerza);
	campo_fuerza = NULL;

	char *campo_destreza = leer_campo(&puntero_lectura);
	poke.destreza = atoi(campo_destreza);
	free(campo_destreza);
	campo_destreza = NULL;

	char *campo_inteligencia = leer_campo(&puntero_lectura);
	poke.inteligencia = atoi(campo_inteligencia);
	free(campo_inteligencia);
	campo_inteligencia = NULL;

	return poke;
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

	struct pokemon *poke = malloc(sizeof(struct pokemon));
	if (!poke) {
		return NULL;
	}

	bool poke_encontrado = false;
	char *linea = NULL;
	while ((linea = archivo_leer_linea(pokedex)) != NULL &&
	       !poke_encontrado) {
		if (es_linea_valida(linea)) {
			*poke = parsear_pokemon(linea);
			if (poke->nombre && strcmp(poke->nombre, nombre) == 0) {
				pokedex->poke_buscado = poke;
				poke_encontrado = true;
			} else {
				if (poke->nombre) {
					free((char *)poke->nombre);
					poke->nombre = NULL;
				}
			}
		}
	}

	if (poke_encontrado) {
		return poke;
	}

	if (poke->nombre) {
		free((char *)poke->nombre);
		poke->nombre = NULL;
	}
	free(poke);
	poke = NULL;
	return NULL;
}

/*
 * Busca un pokemon con el id especificado en la pokedex.
 * 
 * Devuelve un puntero al pokemon si se encontró, o NULL en caso contrario.
 */
const struct pokemon *pokedex_buscar_pokemon_id(pokedex_t *pokedex, unsigned id)
{
	if (!pokedex || !pokedex->archivo || !id) {
		return NULL;
	}

	rewind(pokedex->archivo);

	struct pokemon *poke = malloc(sizeof(struct pokemon));
	if (!poke) {
		return NULL;
	}

	bool poke_encontrado = false;
	char *linea = NULL;
	while ((linea = archivo_leer_linea(pokedex)) != NULL &&
	       !poke_encontrado) {
		if (es_linea_valida(linea)) {
			*poke = parsear_pokemon(linea);
			if (poke->id == id) {
				pokedex->poke_buscado = poke;
				poke_encontrado = true;
			} else {
				if (poke->nombre) {
					free((char *)poke->nombre);
					poke->nombre = NULL;
				}
			}
		}
	}

	if (poke_encontrado) {
		return poke;
	}

	if (poke->nombre) {
		free((char *)poke->nombre);
		poke->nombre = NULL;
	}
	free(poke);
	poke = NULL;
	return NULL;
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
		if (pokedex->ultima_linea) {
			free(pokedex->ultima_linea);
			pokedex->ultima_linea = NULL;
		}
		if (pokedex->poke_buscado) {
			if (pokedex->poke_buscado->nombre) {
				free((char *)pokedex->poke_buscado->nombre);
				pokedex->poke_buscado->nombre = NULL;
			}
			free(pokedex->poke_buscado);
			pokedex->poke_buscado = NULL;
		}
		free(pokedex);
		pokedex = NULL;
	}
}