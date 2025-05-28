#include "hash.h"
#include <string.h>

const float MAX_FACTOR_DE_CARGA = 0.75;
const int CAPACIDAD_MINIMA = 3;

typedef struct elemento_tabla {
	char *clave;
	void *dato;
	bool fue_eliminado;
} elemento_tabla_t;

struct hash {
	size_t capacidad;
	size_t cantidad;
	elemento_tabla_t *tabla;
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
		hash = hash * 33 + caracter;
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

	hash->tabla = calloc(capacidad_inicial, sizeof(elemento_tabla_t));
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
	elemento_tabla_t *nueva_tabla =
		calloc(nueva_capacidad, sizeof(elemento_tabla_t));
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

	size_t clave_hash = h->funcion_hash(clave);
	size_t posicion = obtener_posicion_hash(clave_hash, h->capacidad);

	while (h->tabla[posicion].clave &&
	       strcmp(h->tabla[posicion].clave, clave) != 0) {
		posicion = obtener_posicion_hash(posicion + 1, h->capacidad);
	}

	if (h->tabla[posicion].clave) {
		if (anterior) {
			*anterior = h->tabla[posicion].dato;
		}
		h->tabla[posicion].dato = valor;
		return true;
	}

	char *clave_copia = copiar_clave(clave);
	if (!clave_copia) {
		return false;
	}

	h->tabla[posicion].clave = clave_copia;
	h->tabla[posicion].dato = valor;
	h->tabla[posicion].fue_eliminado = false;
	h->cantidad++;

	if (anterior) {
		*anterior = NULL;
	}

	return true;
}

void *hash_sacar(hash_t *h, const char *clave)
{
	if (!h || !clave || hash_tamanio(h) == 0) {
		return NULL;
	}
}

void *hash_buscar(hash_t *h, const char *clave)
{
	if (!h || !clave || hash_tamanio(h) == 0) {
		return NULL;
	}

	size_t hash_clave = h->funcion_hash(clave);
	size_t posicion = obtener_posicion_hash(hash_clave, h->capacidad);

	void *buscado = NULL;
	bool encontrado = false;
	for (size_t i = 0; i < h->capacidad && !encontrado; i++) {
		size_t actual =
			obtener_posicion_hash(posicion + i, h->capacidad);

		if (h->tabla[actual].clave && !h->tabla[actual].fue_eliminado &&
		    strcmp(h->tabla[actual].clave, clave) == 0) {
			buscado = h->tabla[actual].dato;
			encontrado = true;
		}
	}

	return buscado;
}

bool hash_existe(hash_t *h, const char *clave)
{
	return hash_buscar(h, clave) != NULL;
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
		if (h->tabla[i].clave && !h->tabla[i].fue_eliminado) {
			if (destructor) {
				destructor(h->tabla[i].dato);
			}
			free(h->tabla[i].clave);
		}
	}
	free(h->tabla);
	free(h);
}