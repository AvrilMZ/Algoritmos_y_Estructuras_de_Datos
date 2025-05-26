#include "hash.h"
#include "lista.h"

typedef struct elemento_hash {
	char *clave;
	void *valor;
} elemento_hash_t;

struct hash {
	size_t capacidad;
	size_t cantidad;
	lista_t **indices;
};

hash_t *hash_crear(size_t capacidad_inicial)
{
	if (capacidad_inicial < 3) {
		capacidad_inicial = 3;
	}
	hash_t *hash = calloc(1, sizeof(hash_t));
	if (!hash) {
		return NULL;
	}
	hash->capacidad = capacidad_inicial;
	hash->indices = calloc(capacidad_inicial, sizeof(lista_t *));
	if (!hash->indices) {
		free(hash);
		return NULL;
	}
	return hash;
}

hash_t *hash_crear_con_funcion(size_t capacidad_inicial,
			       size_t (*f)(const char *))
{
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
}

void hash_destruir(hash_t *h)
{
}

void hash_destruir_todo(hash_t *h, void (*destructor)(void *))
{
}

size_t hash_iterar_claves(hash_t *h, bool (*f)(const char *, void *), void *ctx)
{
}