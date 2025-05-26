#include "hash.h"
#include "lista.h"
#include <string.h>

const float MAX_FACTOR_DE_CARGA = 0.75;
const int CAPACIDAD_MINIMA = 3;

typedef struct elemento_hash {
	const char *clave;
	void *valor;
} elemento_hash_t;

struct hash {
	size_t capacidad;
	size_t cantidad;
	lista_t **indices;
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
	hash->indices = calloc(capacidad_inicial, sizeof(lista_t *));
	if (!hash->indices) {
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
 * Crea un 'elemento_hash_t' con la clave y valor pasados.
 */
elemento_hash_t *crear_elemento_hash(const char *clave, void *valor)
{
	if (!clave) {
		return NULL;
	}

	elemento_hash_t *elemento = calloc(1, sizeof(elemento_hash_t));
	if (!elemento) {
		return NULL;
	}

	char *clave_copia = calloc(strlen(clave) + 1, sizeof(char));
	if (!clave_copia) {
		free(elemento);
		return NULL;
	}
	strcpy(clave_copia, clave);

	elemento->clave = clave_copia;
	elemento->valor = valor;

	return elemento;
}

/**
 * Crea y devuelve una lista, de la capacidad dada, de punteros a listas simplemente enlazadas.
 * 
 * Devuelve NULL en caso de error.
 */
lista_t **crear_indices(size_t capacidad)
{
	lista_t **indices = calloc(capacidad, sizeof(lista_t *));
	if (!indices) {
		return NULL;
	}

	for (size_t i = 0; i < capacidad; i++) {
		indices[i] = lista_crear();
		if (!indices[i]) {
			for (size_t j = 0; j < i; j++) {
				lista_destruir(indices[j]);
			}
			free(indices);
			return NULL;
		}
	}

	return indices;
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

	size_t capacidad_nueva = hash->capacidad * 2;
	lista_t **nuevos_indices = crear_indices(capacidad_nueva);
	if (!nuevos_indices) {
		return false;
	}

	for (size_t i = 0; i < hash->capacidad; i++) {
		lista_t *lista_actual = hash->indices[i];
		for (size_t j = 0; j < lista_tamanio(lista_actual); j++) {
			elemento_hash_t *elemento =
				(elemento_hash_t *)lista_obtener_elemento(
					lista_actual, (int)j);
			size_t clave_nueva =
				hash->funcion_hash(elemento->clave);
			size_t nueva_pos = obtener_posicion_hash(
				clave_nueva, capacidad_nueva);
			lista_insertar(nuevos_indices[nueva_pos], elemento);
		}
		lista_destruir(lista_actual);
	}

	free(hash->indices);
	hash->indices = nuevos_indices;
	hash->capacidad = capacidad_nueva;

	return true;
}

/**
 * Función destructora para un dato tipo 'elemento_hash_t'.
 */
void destruir_elemento_hash(void *dato)
{
	if (!dato) {
		return;
	}
	elemento_hash_t *elemento = (elemento_hash_t *)dato;
	free(elemento->valor);
	free(elemento->clave);
	free(elemento);
}

bool hash_insertar(hash_t *h, const char *clave, void *valor, void **anterior)
{
	if (!h || !clave) {
		return false;
	}

	if (factor_carga(h->cantidad, h->capacidad) >= MAX_FACTOR_DE_CARGA) {
		if (!rehash(h)) {
			return false;
		}
	}

	size_t posicion =
		obtener_posicion_hash(h->funcion_hash(clave), h->capacidad);
	lista_t *lista = h->indices[posicion];
	for (size_t i = 0; i < lista_tamanio(lista); i++) {
		elemento_hash_t *elemento =
			(elemento_hash_t *)lista_obtener_elemento(lista,
								  (int)i);
		if (strcmp(elemento->clave, clave) == 0) {
			if (anterior) {
				*anterior = elemento->valor;
			}
			elemento->valor = valor;
			return true;
		}
	}

	elemento_hash_t *nuevo = crear_elemento_hash(clave, valor);
	if (!nuevo) {
		return false;
	}

	if (!lista_insertar(lista, nuevo)) {
		destruir_elemento_hash(nuevo);
		return false;
	}

	if (anterior) {
		*anterior = NULL;
	}

	h->cantidad++;
	return true;
}

void *hash_sacar(hash_t *h, const char *clave)
{
}

void *hash_buscar(hash_t *h, const char *clave)
{
	if (!h || !clave) {
		return NULL;
	}

	size_t clave_hash = h->funcion_hash(clave);
	size_t posicion = obtener_posicion_hash(clave_hash, h->capacidad);
	lista_t *lista = h->indices[posicion];

	elemento_hash_t *buscado = NULL;
	bool encontrado = false;
	for (size_t i = 0; i < lista_tamanio(lista) && !encontrado; i++) {
		elemento_hash_t *elemento =
			lista_obtener_elemento(lista, (int)i);
		if (strcmp(elemento->clave, clave) == 0) {
			buscado = elemento;
			encontrado = true;
		}
	}

	if (buscado) {
		return buscado;
	}
	return NULL;
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
}

void hash_destruir(hash_t *h)
{
	if (!h) {
		return;
	}
	hash_destruir_todo(h, destruir_elemento_hash);
}

void hash_destruir_todo(hash_t *h, void (*destructor)(void *))
{
	if (!h) {
		return;
	}
	for (size_t i = 0; i < h->capacidad; i++) {
		if (h->indices[i]) {
			lista_destruir_todo(h->indices[i], destructor);
		}
	}
	free(h->indices);
	free(h);
}