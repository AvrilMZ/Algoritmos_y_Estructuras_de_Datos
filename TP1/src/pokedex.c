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

// Realoca memoria para un arreglo de caracteres.
char *realocar_memoria_linea(char *linea, size_t capacidad)
{
	char *nueva_linea = realloc(linea, sizeof(char) * capacidad);
	if (!nueva_linea) {
		return NULL;
	}
	return nueva_linea;
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

// Ordena los pokemones por ID (insertion sort).
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

// Ordena los pokemones por nombre (insertion sort).
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

// Duplica un string, reservando memoria para el nuevo.
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

// Lee una línea del archivo.
// Devuelve un puntero a la línea leída, o NULL si no hay más líneas.
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

// Lee un campo hasta encontrar un ';' o fin de línea.
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

// Devuelve el 'tipo_pokemon' correspondiente a el carácter dado por parámetro, si no es válido devuelve -1.
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
	return -1;
}

// Libera todos los campos de un pokemon.
void liberar_campos(char *campo_id, char *nombre_poke, char *campo_tipo,
		    char *campo_fuerza, char *campo_destreza,
		    char *campo_inteligencia)
{
	free(campo_id);
	free(nombre_poke);
	free(campo_tipo);
	free(campo_fuerza);
	free(campo_destreza);
	free(campo_inteligencia);
}

// Parsea un Pokémon desde una línea de texto.
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

	liberar_campos(campo_id, NULL, campo_tipo, campo_fuerza, campo_destreza,
		       campo_inteligencia);
	return poke;
}

// Devuelve true si todos los campos de la linea se encuentran presentes, de lo contrario devuelve false.
bool es_linea_valida(struct pokemon poke)
{
	return (poke.id != 0 && poke.nombre && poke.tipo != -1 &&
		poke.fuerza != 0 && poke.destreza != 0 &&
		poke.inteligencia != 0);
}

// Carga ordenadamente, por ID y nombre, los pokemones en los vectores del struct.
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
	for (int i = 0; i < pokedex->cantidad_pokemones; i++) {
		char *linea = archivo_leer_linea(pokedex);
		struct pokemon poke = parsear_pokemon(linea);

		pokedex->pokes_ordenados_id[i] = poke;
		pokedex->pokes_ordenados_id[i].nombre =
			duplicar_string(poke.nombre);

		pokedex->pokes_ordenados_nombre[i] = poke;
		pokedex->pokes_ordenados_nombre[i].nombre =
			duplicar_string(poke.nombre);

		free((char *)poke.nombre);
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
	char *linea = archivo_leer_linea(pokedex);
	while (linea != NULL && !linea_invalida) {
		struct pokemon poke = parsear_pokemon(linea);
		if (es_linea_valida(poke)) {
			pokedex->cantidad_pokemones++;
			linea = archivo_leer_linea(pokedex);
		} else {
			linea_invalida = true;
		}
		free((char *)poke.nombre);
	}

	if (pokedex->cantidad_pokemones == 0) {
		fclose(pokedex->archivo);
		free((char *)pokedex->ultima_linea);
		free(pokedex);
		pokedex = NULL;
		return NULL;
	}

	cargar_pokemones_ordenados(pokedex);
	return pokedex;
}

unsigned pokedex_cantidad_pokemones(pokedex_t *pokedex)
{
	if (!pokedex || !pokedex->archivo) {
		return 0;
	}
	return (unsigned)pokedex->cantidad_pokemones;
}

// Busqueda binaria del pokemon con 'nombre' en 'pokes_ordenados', si lo encuentra lo devuelve, si no devuelve un pokemon vacio.
struct pokemon busqueda_binaria_nombre(struct pokemon *pokes_ordenados,
				       const char *nombre, int cant_pokes)
{
	int inicio = 0;
	int fin = cant_pokes - 1;
	int indice_encontrado = -1;
	bool encontrado = false;
	while (inicio <= fin && !encontrado) {
		int medio = (inicio + fin) / 2;
		int cmp = strcmp(nombre, pokes_ordenados[medio].nombre);
		if (cmp == 0) {
			indice_encontrado = medio;
			encontrado = true;
		} else if (cmp < 0) {
			fin = medio - 1;
		} else {
			inicio = medio + 1;
		}
	}

	if (encontrado) {
		return pokes_ordenados[indice_encontrado];
	} else {
		struct pokemon vacio = { 0, NULL, 0, 0, 0, 0 };
		return vacio;
	}
}

const struct pokemon *pokedex_buscar_pokemon_nombre(pokedex_t *pokedex,
						    const char *nombre)
{
	if (!pokedex || !pokedex->archivo || !nombre) {
		return NULL;
	}

	if (pokedex->poke_buscado) {
		free((char *)pokedex->poke_buscado->nombre);
		free(pokedex->poke_buscado);
		pokedex->poke_buscado = NULL;
	}

	struct pokemon *poke = reservar_memoria_pokemon(1);
	if (!poke) {
		return NULL;
	}

	*poke = busqueda_binaria_nombre(pokedex->pokes_ordenados_nombre, nombre,
					pokedex->cantidad_pokemones);
	if (!poke->nombre) {
		free(poke);
		poke = NULL;
		return NULL;
	} else {
		char *nombre_duplicado = duplicar_string(poke->nombre);
		if (!nombre_duplicado) {
			free(poke);
			return NULL;
		}
		poke->nombre = nombre_duplicado;
		pokedex->poke_buscado = poke;
		return poke;
	}
}

// Busqueda binaria del pokemon con 'id' en 'pokes_ordenados', si lo encuentra lo devuelve, si no devuelve un pokemon vacio.
struct pokemon busqueda_binaria_id(struct pokemon *pokes_ordenados, int id,
				   int cant_pokes)
{
	int inicio = 0;
	int fin = cant_pokes - 1;
	int indice_encontrado = -1;
	bool encontrado = false;
	while (inicio <= fin && !encontrado) {
		int medio = (inicio + fin) / 2;
		if (id == pokes_ordenados[medio].id) {
			indice_encontrado = medio;
			encontrado = true;
		} else if (id < pokes_ordenados[medio].id) {
			fin = medio - 1;
		} else {
			inicio = medio + 1;
		}
	}

	if (encontrado) {
		return pokes_ordenados[indice_encontrado];
	} else {
		struct pokemon vacio = { 0, NULL, 0, 0, 0, 0 };
		return vacio;
	}
}

const struct pokemon *pokedex_buscar_pokemon_id(pokedex_t *pokedex, unsigned id)
{
	if (!pokedex || !pokedex->archivo || !id) {
		return NULL;
	}

	if (pokedex->poke_buscado) {
		free((char *)pokedex->poke_buscado->nombre);
		free(pokedex->poke_buscado);
		pokedex->poke_buscado = NULL;
	}

	struct pokemon *poke = reservar_memoria_pokemon(1);
	if (!poke) {
		return NULL;
	}

	*poke = busqueda_binaria_id(pokedex->pokes_ordenados_id, (int)id,
				    pokedex->cantidad_pokemones);
	if (!poke->nombre) {
		free(poke);
		poke = NULL;
		return NULL;
	} else {
		char *nombre_duplicado = duplicar_string(poke->nombre);
		if (!nombre_duplicado) {
			free(poke);
			return NULL;
		}
		poke->nombre = nombre_duplicado;
		pokedex->poke_buscado = poke;
		return poke;
	}
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
	for (int i = 0; i < pokedex->cantidad_pokemones && continuar_iterando;
	     i++) {
		struct pokemon poke_temp = arreglo[i];
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
		}
		if (pokedex->ultima_linea) {
			free((char *)pokedex->ultima_linea);
		}
		if (pokedex->poke_buscado) {
			free((char *)pokedex->poke_buscado->nombre);
			free(pokedex->poke_buscado);
		}
		if (pokedex->pokes_ordenados_nombre) {
			for (int i = 0; i < pokedex->cantidad_pokemones; i++) {
				free((char *)pokedex->pokes_ordenados_nombre[i]
					     .nombre);
			}
			free(pokedex->pokes_ordenados_nombre);
		}
		if (pokedex->pokes_ordenados_id) {
			for (int i = 0; i < pokedex->cantidad_pokemones; i++) {
				free((char *)pokedex->pokes_ordenados_id[i]
					     .nombre);
			}
			free(pokedex->pokes_ordenados_id);
		}
		free(pokedex);
		pokedex = NULL;
	}
}