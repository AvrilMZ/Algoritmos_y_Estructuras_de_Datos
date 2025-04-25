#include "abb.h"
#include "abb_estructura_privada.h"

// Reserva memoria para un nodo y devuelve su puntero.
nodo_t *reservar_memoria_nodo()
{
	nodo_t *nodo = calloc(1, sizeof(nodo_t));
	if (!nodo) {
		return NULL;
	}
	return nodo;
}

abb_t *abb_crear(int (*cmp)(const void *, const void *))
{
	if (!cmp) {
		return NULL;
	}

	abb_t *arbol = calloc(1, sizeof(abb_t));
	if (!arbol) {
		return NULL;
	}
	arbol->comparador = cmp;
	return arbol;
}

bool abb_insertar(abb_t *abb, const void *elemento)
{
	if (!abb || !elemento) {
		return false;
	}

	nodo_t *nuevo = reservar_memoria_nodo();
	if (!nuevo) {
		return false;
	}
	nuevo->elemento = elemento;

	if (!abb->raiz) {
		abb->raiz = nuevo;
		abb->nodos++;
		return true;
	}

	nodo_t *actual = abb->raiz;
	nodo_t *padre = NULL;
	int cmp = 0;
	while (actual) {
		padre = actual;
		cmp = abb->comparador(elemento, actual->elemento);
		if (cmp < 0) {
			actual = actual->izq;
		} else {
			actual = actual->der;
		}
	}

	if (cmp < 0) {
		padre->izq = nuevo;
	} else {
		padre->der = nuevo;
	}
	abb->nodos++;
	return true;
}

bool abb_existe(const abb_t *abb, const void *elemento)
{
}

void *abb_buscar(const abb_t *abb, const void *elemento)
{
}

void *abb_sacar(abb_t *abb, const void *elemento)
{
}

size_t abb_tamanio(const abb_t *abb)
{
}

bool abb_vacio(const abb_t *abb)
{
}

size_t abb_recorrer(const abb_t *abb, enum abb_recorrido modo,
		    bool (*f)(void *, void *), void *ctx)
{
}

size_t abb_vectorizar(const abb_t *abb, enum abb_recorrido modo, void **vector,
		      size_t capacidad)
{
}

void abb_destruir(abb_t *abb)
{
}

void abb_destruir_todo(abb_t *abb, void (*destructor)(void *))
{
}