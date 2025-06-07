#include "hash.h"
#include <string.h>

const float MAX_FACTOR_DE_CARGA = 0.75;
const int CAPACIDAD_MINIMA = 3;

typedef struct par {
	char *clave;
	void *valor;
	bool fue_eliminado;
} par_t;

struct hash {
	size_t capacidad;
	size_t cantidad;
	par_t *tabla;
	size_t (*funcion_hash)(const char *);
};

/**
 * Algoritmo djb2 usado como función de hash por default.
 */
size_t hash_djb2(const char *clave)
{
	size_t hash = 5381;
	while (*clave != '\0') {
		unsigned char caracter = (unsigned char)(*clave);
		hash = (hash * 33) + caracter;
		clave++;
	}
	return hash;
}

hash_t *hash_crear(size_t capacidad_inicial)
{
	return hash_crear_con_funcion(capacidad_inicial, hash_djb2);
}

hash_t *hash_crear_con_funcion(size_t capacidad_inicial,
			       size_t (*f)(const char *))
{
	if (!f) {
		return NULL;
	} else if (capacidad_inicial < CAPACIDAD_MINIMA) {
		capacidad_inicial = CAPACIDAD_MINIMA;
	}

	hash_t *hash = calloc(1, sizeof(hash_t));
	if (!hash) {
		return NULL;
	}
	hash->capacidad = capacidad_inicial;
	hash->funcion_hash = f;

	hash->tabla = calloc(capacidad_inicial, sizeof(par_t));
	if (!hash->tabla) {
		free(hash);
		return NULL;
	}

	return hash;
}

/**
 * Devuelve el factor de carga de la tabla hash.
 */
float factor_carga(size_t cantidad, size_t capacidad)
{
	return (float)cantidad / (float)capacidad;
}

/**
 * Devuelve la posición correspondiente en la tabla hash.
 */
size_t obtener_posicion_hash(size_t clave, size_t capacidad)
{
	return clave % capacidad;
}

/**
 * Duplica la capacidad del hash dado y rehashea los elementos previamente guardados.
 * 
 * Devuelve true si se pudo hacer el rehash, en caso contrario false.
 */
bool rehash(hash_t *hash)
{
	if (!hash) {
		return false;
	}

	size_t nueva_capacidad = hash->capacidad * 2;
	par_t *nueva_tabla = calloc(nueva_capacidad, sizeof(par_t));
	if (!nueva_tabla) {
		return false;
	}

	for (size_t i = 0; i < hash->capacidad; i++) {
		if (hash->tabla[i].clave && !hash->tabla[i].fue_eliminado) {
			size_t clave_hash =
				hash->funcion_hash(hash->tabla[i].clave);
			size_t posicion_nueva = obtener_posicion_hash(
				clave_hash, nueva_capacidad);

			while (nueva_tabla[posicion_nueva].clave) {
				posicion_nueva = obtener_posicion_hash(
					posicion_nueva + 1, nueva_capacidad);
			}

			nueva_tabla[posicion_nueva] = hash->tabla[i];
			nueva_tabla[posicion_nueva].fue_eliminado = false;
		}
	}
	free(hash->tabla);

	hash->tabla = nueva_tabla;
	hash->capacidad = nueva_capacidad;
	return true;
}

/**
 * Se crea y devuelve una copia de la clave dada, en caso de error se retorna NULL.
 */
char *copiar_clave(const char *clave)
{
	char *copia = calloc(strlen(clave) + 1, sizeof(char));
	if (!copia) {
		return NULL;
	}
	return strcpy(copia, clave);
}

/**
 * Busca una posición en la tabla hash existente o libre, según se pase.
 * 
 * Devuelve la capacidad del hash + 1 si no encuentra.
 */
size_t buscar_posicion(hash_t *h, const char *clave, bool buscar_existente)
{
	size_t hash_clave = h->funcion_hash(clave);
	size_t posicion = obtener_posicion_hash(hash_clave, h->capacidad);

	size_t posicion_encontrada = h->capacidad + 1;
	bool encontrado = false;
	bool no_existe = false;

	for (size_t i = 0; i < h->capacidad && !encontrado && !no_existe; i++) {
		size_t posicion_actual =
			obtener_posicion_hash(posicion + i, h->capacidad);
		par_t *elemento = &h->tabla[posicion_actual];

		if (buscar_existente) {
			if (elemento->clave && !elemento->fue_eliminado &&
			    strcmp(elemento->clave, clave) == 0) {
				posicion_encontrada = posicion_actual;
				encontrado = true;
			}
		} else {
			if (!elemento->clave) {
				posicion_encontrada = posicion_actual;
				encontrado = true;
			}
		}

		if (!elemento->clave && !elemento->fue_eliminado) {
			no_existe = true;
		}
	}

	return posicion_encontrada;
}

/**
 * Devulve true si se pudo insertar la clave dada en la posición especificada, en caso contrario devuelve false.
 */
bool insertar_nueva_clave(hash_t *h, size_t posicion, const char *clave,
			  void *valor, void **anterior)
{
	char *clave_copia = copiar_clave(clave);
	if (!clave_copia) {
		return false;
	}

	h->tabla[posicion].clave = clave_copia;
	h->tabla[posicion].valor = valor;
	h->tabla[posicion].fue_eliminado = false;
	h->cantidad++;

	if (anterior) {
		*anterior = NULL;
	}

	return true;
}

bool hash_insertar(hash_t *h, const char *clave, void *valor, void **anterior)
{
	if (!h || !clave) {
		return false;
	}

	if (factor_carga(hash_tamanio(h), h->capacidad) >=
	    MAX_FACTOR_DE_CARGA) {
		if (!rehash(h)) {
			return false;
		}
	}

	size_t posicion_clave_existente = buscar_posicion(h, clave, true);
	if (posicion_clave_existente != h->capacidad + 1) {
		if (anterior) {
			*anterior = h->tabla[posicion_clave_existente].valor;
		}
		h->tabla[posicion_clave_existente].valor = valor;
		return true;
	}

	size_t posicion_libre = buscar_posicion(h, clave, false);
	if (posicion_libre == h->capacidad + 1) {
		return false;
	}

	return insertar_nueva_clave(h, posicion_libre, clave, valor, anterior);
}

void *hash_sacar(hash_t *h, const char *clave)
{
	if (!h || !clave || hash_tamanio(h) == 0) {
		return NULL;
	}

	size_t posicion = buscar_posicion(h, clave, true);
	if (posicion == h->capacidad + 1) {
		return NULL;
	}

	void *valor = h->tabla[posicion].valor;
	free(h->tabla[posicion].clave);
	h->tabla[posicion].clave = NULL;
	h->tabla[posicion].valor = NULL;
	h->tabla[posicion].fue_eliminado = true;
	h->cantidad--;

	return valor;
}

void *hash_buscar(hash_t *h, const char *clave)
{
	if (!h || !clave || hash_tamanio(h) == 0) {
		return NULL;
	}

	size_t posicion = buscar_posicion(h, clave, true);
	if (posicion == h->capacidad + 1) {
		return NULL;
	}

	return h->tabla[posicion].valor;
}

bool hash_existe(hash_t *h, const char *clave)
{
	if (!h || !clave || hash_tamanio(h) == 0) {
		return false;
	}
	return buscar_posicion(h, clave, true) != h->capacidad + 1;
}

size_t hash_tamanio(hash_t *h)
{
	if (!h) {
		return 0;
	}
	return h->cantidad;
}

size_t hash_iterar_claves(hash_t *h, bool (*f)(const char *, void *), void *ctx)
{
	if (!h || !f) {
		return 0;
	}

	size_t contador = 0;
	bool seguir = true;
	for (size_t i = 0; i < h->capacidad && seguir; i++) {
		if (h->tabla[i].clave && !h->tabla[i].fue_eliminado) {
			contador++;
			seguir = f(h->tabla[i].clave, ctx);
		}
	}

	return contador;
}

void hash_destruir(hash_t *h)
{
	if (!h) {
		return;
	}
	hash_destruir_todo(h, NULL);
}

void hash_destruir_todo(hash_t *h, void (*destructor)(void *))
{
	if (!h) {
		return;
	}
	for (size_t i = 0; i < h->capacidad; i++) {
		if (h->tabla[i].clave) {
			if (!h->tabla[i].fue_eliminado && destructor) {
				destructor(h->tabla[i].valor);
			}
			free(h->tabla[i].clave);
		}
	}
	free(h->tabla);
	free(h);
}