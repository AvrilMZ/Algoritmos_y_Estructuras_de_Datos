#include "pokedex.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MODO_LECTURA "r"
const size_t CAPACIDAD_INICIAL = 16;

struct pokedex {
	FILE *archivo;
	int cantidad_pokemones;
	const char *ultima_linea;
	struct pokemon *poke_buscado;
	struct pokemon *pokes_ordenados_nombre;
	struct pokemon *pokes_ordenados_id;
};

// Reserva memoria para un arreglo de caracteres.
char *reservar_memoria_linea(size_t capacidad)
{
	char *linea = calloc(capacidad, sizeof(char));
	if (!linea) {
		return NULL;
	}
	return linea;
}

// Reserva memoria para un struct pokemon.
struct pokemon *reservar_memoria_pokemon(size_t capacidad)
{
	struct pokemon *pokemon = calloc(capacidad, sizeof(struct pokemon));
	if (!pokemon) {
		return NULL;
	}
	return pokemon;
}

// Realoca memoria para un arreglo de caracteres.
char *realocar_memoria_linea(char *linea, size_t capacidad)
{
	char *nueva_linea = realloc(linea, sizeof(char) * capacidad);
	if (!nueva_linea) {
		return NULL;
	}

	return nueva_linea;
}

// Función para ordenar los pokemones por ID (insertion sort)
void ordenar_pokemones_por_id(struct pokemon *pokemones, int cantidad)
{
	for (int i = 1; i < cantidad; i++) {
		struct pokemon temp = pokemones[i];
		int j = i - 1;

		while (j >= 0 && pokemones[j].id > temp.id) {
			pokemones[j + 1] = pokemones[j];
			j--;
		}

		pokemones[j + 1] = temp;
	}
}

// Función para ordenar los pokemones por nombre (insertion sort)
void ordenar_pokemones_por_nombre(struct pokemon *pokemones, int cantidad)
{
	for (int i = 1; i < cantidad; i++) {
		struct pokemon temp = pokemones[i];
		int j = i - 1;

		while (j >= 0 && strcmp(pokemones[j].nombre, temp.nombre) > 0) {
			pokemones[j + 1] = pokemones[j];
			j--;
		}

		pokemones[j + 1] = temp;
	}
}

// Duplica un string, reservando memoria para el nuevo string
char *duplicar_string(const char *original)
{
	if (!original) {
		return NULL;
	}

	size_t longitud = strlen(original) + 1;
	char *nuevo = reservar_memoria_linea(longitud);
	if (!nuevo) {
		return NULL;
	}

	memcpy(nuevo, original, longitud);
	return nuevo;
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
		free((char *)pokedex->ultima_linea);
		pokedex->ultima_linea = NULL;
	}

	size_t capacidad = CAPACIDAD_INICIAL;
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

// 'tipo' debe ser un char válido para un tipo de pokemon.
// Devuelve el 'tipo_pokemon' correspondiente a el carácter dado por parámetro.
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
	} else {
		return TIPO_LUCHA;
	}
}

// Parsear un Pokémon desde una línea de texto
struct pokemon parsear_pokemon(char *linea)
{
	struct pokemon poke = { 0, NULL, 0, 0, 0, 0 };
	char *puntero_lectura = linea;

	char *campo_id = leer_campo(&puntero_lectura);
	if (campo_id) {
		poke.id = (unsigned)atoi(campo_id);
	}
	free(campo_id);
	campo_id = NULL;

	poke.nombre = leer_campo(&puntero_lectura);

	char *campo_tipo = leer_campo(&puntero_lectura);
	if (campo_tipo) {
		poke.tipo = pasar_a_tipo(campo_tipo[0]);
	}
	free(campo_tipo);
	campo_tipo = NULL;

	char *campo_fuerza = leer_campo(&puntero_lectura);
	if (campo_fuerza) {
		poke.fuerza = (unsigned)atoi(campo_fuerza);
	}
	free(campo_fuerza);
	campo_fuerza = NULL;

	char *campo_destreza = leer_campo(&puntero_lectura);
	if (campo_destreza) {
		poke.destreza = (unsigned)atoi(campo_destreza);
	}
	free(campo_destreza);
	campo_destreza = NULL;

	char *campo_inteligencia = leer_campo(&puntero_lectura);
	if (campo_inteligencia) {
		poke.inteligencia = (unsigned)atoi(campo_inteligencia);
	}
	free(campo_inteligencia);
	campo_inteligencia = NULL;

	return poke;
}

// Función para cargar y ordenar los pokemones
void cargar_pokemones_ordenados(pokedex_t *pokedex)
{
	if (!pokedex || !pokedex->archivo || pokedex->cantidad_pokemones <= 0)
		return;

	pokedex->pokes_ordenados_id =
		reservar_memoria_pokemon((size_t)pokedex->cantidad_pokemones);
	if (!pokedex->pokes_ordenados_id) {
		return;
	}

	pokedex->pokes_ordenados_nombre =
		reservar_memoria_pokemon((size_t)pokedex->cantidad_pokemones);
	if (!pokedex->pokes_ordenados_nombre) {
		free(pokedex->pokes_ordenados_id);
		pokedex->pokes_ordenados_id = NULL;
		return;
	}

	rewind(pokedex->archivo);
	int indice = 0;
	char *linea = NULL;

	while ((linea = archivo_leer_linea(pokedex)) != NULL &&
	       indice < pokedex->cantidad_pokemones) {
		if (es_linea_valida(linea)) {
			struct pokemon poke = parsear_pokemon(linea);

			pokedex->pokes_ordenados_id[indice] = poke;

			pokedex->pokes_ordenados_nombre[indice] = poke;
			pokedex->pokes_ordenados_nombre[indice].nombre =
				duplicar_string(poke.nombre);

			indice++;
		}
	}

	ordenar_pokemones_por_id(pokedex->pokes_ordenados_id,
				 pokedex->cantidad_pokemones);
	ordenar_pokemones_por_nombre(pokedex->pokes_ordenados_nombre,
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

	if (pokedex->cantidad_pokemones > 0) {
		cargar_pokemones_ordenados(pokedex);
	}

	return pokedex;
}

unsigned pokedex_cantidad_pokemones(pokedex_t *pokedex)
{
	if (!pokedex || !pokedex->archivo) {
		return 0;
	}
	return (unsigned)pokedex->cantidad_pokemones;
}

const struct pokemon *pokedex_buscar_pokemon_nombre(pokedex_t *pokedex,
						    const char *nombre)
{
	if (!pokedex || !pokedex->archivo || !nombre) {
		return NULL;
	}

	rewind(pokedex->archivo);

	if (pokedex->poke_buscado) {
		free((char *)pokedex->poke_buscado->nombre);
		pokedex->poke_buscado->nombre = NULL;
		free(pokedex->poke_buscado);
		pokedex->poke_buscado = NULL;
	}

	struct pokemon *poke = reservar_memoria_pokemon(1);
	if (!poke) {
		return NULL;
	}

	bool poke_encontrado = false;
	bool archivo_con_errores = false;
	char *linea = NULL;
	while ((linea = archivo_leer_linea(pokedex)) != NULL &&
	       !poke_encontrado && !archivo_con_errores) {
		if (!es_linea_valida(linea)) {
			archivo_con_errores = true;
		} else {
			*poke = parsear_pokemon(linea);
			if (poke->nombre && strcmp(poke->nombre, nombre) == 0) {
				pokedex->poke_buscado = poke;
				poke_encontrado = true;
			} else {
				free((char *)poke->nombre);
				poke->nombre = NULL;
			}
		}
	}

	if (poke_encontrado) {
		return poke;
	}

	free((char *)poke->nombre);
	poke->nombre = NULL;

	free(poke);
	poke = NULL;
	return NULL;
}

const struct pokemon *pokedex_buscar_pokemon_id(pokedex_t *pokedex, unsigned id)
{
	if (!pokedex || !pokedex->archivo || !id) {
		return NULL;
	}

	rewind(pokedex->archivo);

	if (pokedex->poke_buscado) {
		free((char *)pokedex->poke_buscado->nombre);
		pokedex->poke_buscado->nombre = NULL;
		free(pokedex->poke_buscado);
		pokedex->poke_buscado = NULL;
	}

	struct pokemon *poke = reservar_memoria_pokemon(1);
	if (!poke) {
		return NULL;
	}

	bool poke_encontrado = false;
	bool archivo_con_errores = false;
	char *linea = NULL;
	while ((linea = archivo_leer_linea(pokedex)) != NULL &&
	       !poke_encontrado && !archivo_con_errores) {
		if (!es_linea_valida(linea)) {
			archivo_con_errores = true;
		} else {
			*poke = parsear_pokemon(linea);
			if (poke->id == id) {
				pokedex->poke_buscado = poke;
				poke_encontrado = true;
			} else {
				free((char *)poke->nombre);
				poke->nombre = NULL;
			}
		}
	}

	if (poke_encontrado) {
		return poke;
	}

	free((char *)poke->nombre);
	poke->nombre = NULL;

	free(poke);
	poke = NULL;
	return NULL;
}

unsigned pokedex_iterar_pokemones(pokedex_t *pokedex, enum modo_iteracion modo,
				  bool (*funcion)(struct pokemon *, void *),
				  void *ctx)
{
	if (!pokedex || !pokedex->archivo || !funcion) {
		return 0;
	}

	struct pokemon *arreglo = NULL;
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
	for (unsigned i = 0;
	     i < pokedex->cantidad_pokemones && continuar_iterando; i++) {
		struct pokemon poke_temp;
		poke_temp = arreglo[i];
		poke_temp.nombre = duplicar_string(arreglo[i].nombre);

		if (poke_temp.nombre) {
			continuar_iterando = funcion(&poke_temp, ctx);
			pokemones_iterados++;

			free((char *)poke_temp.nombre);
			poke_temp.nombre = NULL;
		}
	}

	return pokemones_iterados;
}

void pokedex_destruir(pokedex_t *pokedex)
{
	if (pokedex) {
		if (pokedex->archivo) {
			fclose(pokedex->archivo);
			pokedex->archivo = NULL;
		}
		if (pokedex->ultima_linea) {
			free((char *)pokedex->ultima_linea);
			pokedex->ultima_linea = NULL;
		}
		if (pokedex->poke_buscado) {
			free((char *)pokedex->poke_buscado->nombre);
			pokedex->poke_buscado->nombre = NULL;
			free(pokedex->poke_buscado);
			pokedex->poke_buscado = NULL;
		}
		if (pokedex->pokes_ordenados_id) {
			for (int i = 0; i < pokedex->cantidad_pokemones; i++) {
				free((char *)pokedex->pokes_ordenados_id[i]
					     .nombre);
				pokedex->pokes_ordenados_id[i].nombre = NULL;
			}
			free(pokedex->pokes_ordenados_id);
			pokedex->pokes_ordenados_id = NULL;
		}
		if (pokedex->pokes_ordenados_nombre) {
			for (int i = 0; i < pokedex->cantidad_pokemones; i++) {
				free((char *)pokedex->pokes_ordenados_nombre[i]
					     .nombre);
				pokedex->pokes_ordenados_nombre[i].nombre =
					NULL;
			}
			free(pokedex->pokes_ordenados_nombre);
			pokedex->pokes_ordenados_nombre = NULL;
		}
		free(pokedex);
		pokedex = NULL;
	}
}