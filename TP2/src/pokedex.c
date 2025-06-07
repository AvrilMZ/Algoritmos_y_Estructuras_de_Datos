#include "pokedex.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MODO_LECTURA "r"
const size_t CAPACIDAD_INICIAL = 16;
const int POKEMON_NO_ENCONTRADO = -1;
const int TIPO_INVALIDO = -1;
const char SEPARADOR_CAMPO = ';';

struct pokedex {
	FILE *archivo;
	unsigned cantidad_pokemones;
	struct pokemon *pokemones;
	struct pokemon **pokes_ordenados_nombre;
	struct pokemon **pokes_ordenados_id;
};

/**
 * Ordena punteros a pokemones por ID (insertion sort).
 */
void ordenar_punteros_por_id(struct pokemon **pokemones, unsigned cantidad)
{
	for (unsigned i = 1; i < cantidad; i++) {
		struct pokemon *temp = pokemones[i];
		int j = (int)i - 1;

		while (j >= 0 && pokemones[j]->id > temp->id) {
			pokemones[j + 1] = pokemones[j];
			j--;
		}

		pokemones[j + 1] = temp;
	}
}

/**
 * Ordena punteros a pokemones por nombre (insertion sort).
 */
void ordenar_punteros_por_nombre(struct pokemon **pokemones, unsigned cantidad)
{
	for (unsigned i = 1; i < cantidad; i++) {
		struct pokemon *temp = pokemones[i];
		int j = (int)i - 1;

		while (j >= 0 &&
		       strcmp(pokemones[j]->nombre, temp->nombre) > 0) {
			pokemones[j + 1] = pokemones[j];
			j--;
		}

		pokemones[j + 1] = temp;
	}
}

/**
 * Duplica un string, reservando memoria para el nuevo.
 */
char *duplicar_string(const char *original)
{
	if (!original) {
		return NULL;
	}

	size_t longitud = strlen(original) + 1;
	char *nuevo = calloc(longitud, sizeof(char));
	if (!nuevo) {
		return NULL;
	}

	memcpy(nuevo, original, longitud);
	return nuevo;
}

/**
 * Lee una línea del archivo.
 * 
 * Devuelve un puntero a la línea leída, o NULL si no hay más líneas.
 */
char *archivo_leer_linea(pokedex_t *pokedex)
{
	if (!pokedex || !pokedex->archivo) {
		return NULL;
	}

	size_t capacidad = CAPACIDAD_INICIAL;
	char *linea = calloc(capacidad, sizeof(char));
	if (!linea) {
		return NULL;
	}

	int caracter = fgetc(pokedex->archivo);
	int chars_leidos = 0;
	while (caracter != '\n' && feof(pokedex->archivo) == 0) {
		if (chars_leidos + 1 >= capacidad) {
			capacidad *= 2;
			char *nueva_linea =
				realloc(linea, sizeof(char) * capacidad);
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
	return linea;
}

/**
 * Lee un campo hasta encontrar un SEPARADOR_CAMPO o fin de línea.
 */
char *leer_campo(char **linea)
{
	if (!linea || !*linea || **linea == '\0') {
		return NULL;
	}

	char *inicio_campo = *linea;

	while (**linea != '\0' && **linea != SEPARADOR_CAMPO) {
		(*linea)++;
	}

	if (*linea == inicio_campo) {
		if (**linea == SEPARADOR_CAMPO) {
			(*linea)++;
		}
		return NULL;
	}

	if (**linea == SEPARADOR_CAMPO) {
		**linea = '\0';
		(*linea)++;
	}

	return inicio_campo;
}

/**
 * Devuelve el 'tipo_pokemon' correspondiente a el carácter dado por parámetro, si no es válido devuelve TIPO_INVALIDO.
 */
tipo_pokemon pasar_a_tipo(const char tipo)
{
	if (tolower(tipo) == 'a') {
		return TIPO_AGUA;
	} else if (tolower(tipo) == 'f') {
		return TIPO_FUEGO;
	} else if (tolower(tipo) == 'p') {
		return TIPO_PLANTA;
	} else if (tolower(tipo) == 'r') {
		return TIPO_ROCA;
	} else if (tolower(tipo) == 'e') {
		return TIPO_ELECTRICO;
	} else if (tolower(tipo) == 'n') {
		return TIPO_NORMAL;
	} else if (tolower(tipo) == 'l') {
		return TIPO_LUCHA;
	}
	return TIPO_INVALIDO;
}

/**
 * Parsea un Pokémon desde una línea de texto.
 */
struct pokemon parsear_pokemon(char *linea)
{
	struct pokemon poke = { 0, NULL, 0, 0, 0, 0 };
	char *puntero_lectura = linea;

	char *campo_id = leer_campo(&puntero_lectura);
	if (campo_id) {
		poke.id = (unsigned)atoi(campo_id);
	}

	poke.nombre = leer_campo(&puntero_lectura);

	char *campo_tipo = leer_campo(&puntero_lectura);
	if (campo_tipo) {
		poke.tipo = pasar_a_tipo(campo_tipo[0]);
	}

	char *campo_fuerza = leer_campo(&puntero_lectura);
	if (campo_fuerza) {
		poke.fuerza = (unsigned)atoi(campo_fuerza);
	}

	char *campo_destreza = leer_campo(&puntero_lectura);
	if (campo_destreza) {
		poke.destreza = (unsigned)atoi(campo_destreza);
	}

	char *campo_inteligencia = leer_campo(&puntero_lectura);
	if (campo_inteligencia) {
		poke.inteligencia = (unsigned)atoi(campo_inteligencia);
	}

	return poke;
}

/**
 * Devuelve true si todos los campos de la linea se encuentran presentes, de lo contrario devuelve false.
 */
bool es_linea_valida(struct pokemon poke)
{
	return (poke.id != 0 && poke.nombre && poke.tipo != TIPO_INVALIDO &&
		poke.fuerza != 0 && poke.destreza != 0 &&
		poke.inteligencia != 0);
}

/**
 * Carga ordenadamente, por ID y nombre, los pokemones en los vectores del struct.
 */
void cargar_pokemones_ordenados(pokedex_t *pokedex)
{
	if (!pokedex || !pokedex->archivo || pokedex->cantidad_pokemones <= 0)
		return;

	pokedex->pokemones = calloc((size_t)pokedex->cantidad_pokemones,
				    sizeof(struct pokemon));
	if (!pokedex->pokemones) {
		return;
	}

	pokedex->pokes_ordenados_id = calloc(
		(size_t)pokedex->cantidad_pokemones, sizeof(struct pokemon *));
	if (!pokedex->pokes_ordenados_id) {
		free(pokedex->pokemones);
		pokedex->pokemones = NULL;
		return;
	}

	pokedex->pokes_ordenados_nombre = calloc(
		(size_t)pokedex->cantidad_pokemones, sizeof(struct pokemon *));
	if (!pokedex->pokes_ordenados_nombre) {
		free(pokedex->pokemones);
		free(pokedex->pokes_ordenados_id);
		pokedex->pokemones = NULL;
		pokedex->pokes_ordenados_id = NULL;
		return;
	}

	bool linea_vacia = false;
	for (int i = 0; i < pokedex->cantidad_pokemones && !linea_vacia; i++) {
		char *linea = archivo_leer_linea(pokedex);

		struct pokemon poke = parsear_pokemon(linea);
		pokedex->pokemones[i] = poke;
		pokedex->pokemones[i].nombre = duplicar_string(poke.nombre);

		pokedex->pokes_ordenados_id[i] = &pokedex->pokemones[i];
		pokedex->pokes_ordenados_nombre[i] = &pokedex->pokemones[i];

		free(linea);
	}

	ordenar_punteros_por_id(pokedex->pokes_ordenados_id,
				pokedex->cantidad_pokemones);
	ordenar_punteros_por_nombre(pokedex->pokes_ordenados_nombre,
				    pokedex->cantidad_pokemones);
}

pokedex_t *pokedex_abrir(const char *archivo)
{
	if (!archivo || !*archivo) {
		return NULL;
	}

	pokedex_t *pokedex = calloc(1, sizeof(pokedex_t));
	if (!pokedex) {
		return NULL;
	}

	pokedex->archivo = fopen(archivo, MODO_LECTURA);
	if (!pokedex->archivo) {
		free(pokedex);
		pokedex = NULL;
		return NULL;
	}

	char *linea = NULL;
	bool linea_invalida = false;
	while (!linea_invalida &&
	       (linea = archivo_leer_linea(pokedex)) != NULL) {
		struct pokemon poke = parsear_pokemon(linea);
		if (es_linea_valida(poke)) {
			pokedex->cantidad_pokemones++;
			free(linea);
		} else {
			free(linea);
			linea_invalida = true;
		}
	}

	if (pokedex->cantidad_pokemones == 0) {
		fclose(pokedex->archivo);
		free(pokedex);
		return NULL;
	}

	rewind(pokedex->archivo);
	cargar_pokemones_ordenados(pokedex);
	return pokedex;
}

unsigned pokedex_cantidad_pokemones(pokedex_t *pokedex)
{
	if (!pokedex || !pokedex->archivo) {
		return 0;
	}
	return pokedex->cantidad_pokemones;
}

/**
 * Busqueda binaria del pokemon con 'nombre' en 'pokes_ordenados', si lo encuentra devuelve el índice, si no devuelve POKEMON_NO_ENCONTRADO.
 */
int busqueda_binaria_nombre(struct pokemon **pokes_ordenados,
			    const char *nombre, unsigned cant_pokes)
{
	unsigned inicio = 0;
	unsigned fin = cant_pokes - 1;
	int indice_encontrado = POKEMON_NO_ENCONTRADO;
	bool encontrado = false;
	while (inicio <= fin && !encontrado) {
		unsigned medio = (inicio + fin) / 2;
		int cmp = strcmp(nombre, pokes_ordenados[medio]->nombre);
		if (cmp == 0) {
			indice_encontrado = (int)medio;
			encontrado = true;
		} else if (cmp < 0) {
			fin = medio - 1;
		} else {
			inicio = medio + 1;
		}
	}

	return indice_encontrado;
}

const struct pokemon *pokedex_buscar_pokemon_nombre(pokedex_t *pokedex,
						    const char *nombre)
{
	if (!pokedex || !pokedex->archivo || !nombre) {
		return NULL;
	}

	int indice = busqueda_binaria_nombre(pokedex->pokes_ordenados_nombre,
					     nombre,
					     pokedex->cantidad_pokemones);
	if (indice == POKEMON_NO_ENCONTRADO) {
		return NULL;
	}
	return pokedex->pokes_ordenados_nombre[indice];
}

/**
 * Busqueda binaria del pokemon con 'id' en 'pokes_ordenados', si lo encuentra devuelve el índice, si no devuelve POKEMON_NO_ENCONTRADO.
 */
int busqueda_binaria_id(struct pokemon **pokes_ordenados, int id,
			unsigned cant_pokes)
{
	unsigned inicio = 0;
	unsigned fin = cant_pokes - 1;
	int indice_encontrado = POKEMON_NO_ENCONTRADO;
	bool encontrado = false;
	while (inicio <= fin && !encontrado) {
		unsigned medio = (inicio + fin) / 2;
		if (id == pokes_ordenados[medio]->id) {
			indice_encontrado = (int)medio;
			encontrado = true;
		} else if (id < pokes_ordenados[medio]->id) {
			fin = medio - 1;
		} else {
			inicio = medio + 1;
		}
	}

	return indice_encontrado;
}

const struct pokemon *pokedex_buscar_pokemon_id(pokedex_t *pokedex, unsigned id)
{
	if (!pokedex || !pokedex->archivo || !id) {
		return NULL;
	}

	int indice = busqueda_binaria_id(pokedex->pokes_ordenados_id, (int)id,
					 pokedex->cantidad_pokemones);
	if (indice == POKEMON_NO_ENCONTRADO) {
		return NULL;
	}
	return pokedex->pokes_ordenados_id[indice];
}

unsigned pokedex_iterar_pokemones(pokedex_t *pokedex, enum modo_iteracion modo,
				  bool (*funcion)(struct pokemon *, void *),
				  void *ctx)
{
	if (!pokedex || !pokedex->archivo || !funcion) {
		return 0;
	}

	struct pokemon **arreglo = NULL;
	if (modo == ITERAR_ID && pokedex->pokes_ordenados_id) {
		arreglo = pokedex->pokes_ordenados_id;
	} else if (modo == ITERAR_NOMBRE && pokedex->pokes_ordenados_nombre) {
		arreglo = pokedex->pokes_ordenados_nombre;
	}

	if (!arreglo) {
		return 0;
	}

	unsigned pokemones_iterados = 0;
	bool continuar_iterando = true;
	for (int i = 0; i < pokedex->cantidad_pokemones && continuar_iterando;
	     i++) {
		pokemones_iterados++;
		if (!funcion(arreglo[i], ctx)) {
			continuar_iterando = false;
		}
	}

	return pokemones_iterados;
}

void pokedex_destruir(pokedex_t *pokedex)
{
	if (!pokedex) {
		return;
	}

	if (pokedex->archivo) {
		fclose(pokedex->archivo);
	}

	if (pokedex->pokemones) {
		for (int i = 0; i < pokedex->cantidad_pokemones; i++) {
			free((char *)pokedex->pokemones[i].nombre);
		}
		free(pokedex->pokemones);
	}

	free(pokedex->pokes_ordenados_nombre);
	free(pokedex->pokes_ordenados_id);
	free(pokedex);
}