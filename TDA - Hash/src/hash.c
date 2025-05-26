#include "hash.h"
#include "lista.h"

const int CAPACIDAD_MINIMA = 3;

typedef struct elemento_hash {
	char *clave;
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

bool hash_insertar(hash_t *h, const char *clave, void *valor, void **anterior)
{
}

void *hash_sacar(hash_t *h, const char *clave)
{
}

void *hash_buscar(hash_t *h, const char *clave)
{
}

bool hash_existe(hash_t *h, const char *clave)
{
}

size_t hash_tamanio(hash_t *h)
{
	if (!h) {
		return 0;
	}
	return h->cantidad;
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

size_t hash_iterar_claves(hash_t *h, bool (*f)(const char *, void *), void *ctx)
{
}