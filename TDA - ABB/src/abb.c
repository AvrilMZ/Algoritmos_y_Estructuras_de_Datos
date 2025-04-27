#include "abb.h"
#include "abb_estructura_privada.h"

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

	nodo_t *nuevo = calloc(1, sizeof(nodo_t));
	if (!nuevo) {
		return false;
	}
	nuevo->elemento = (void *)elemento;

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

/**
 * Recorre recursivamente el abb hasta encontrar el nodo con el elemento pasado por parámetro y lo devuelve.
 * En caso de no encontrarlo devuelve NULL.
 * En caso que se le pase un doble puntero 'padre' lo actualiza.
 */
nodo_t *encontrar_nodo_rec(const abb_t *abb, const void *elemento,
			   nodo_t *actual, nodo_t **padre)
{
	if (!abb || !elemento || !actual) {
		return NULL;
	}

	int cmp = abb->comparador(elemento, actual->elemento);
	if (cmp == 0) {
		return actual;
	} else if (cmp < 0) {
		if (padre) {
			*padre = actual;
		}
		return encontrar_nodo_rec(abb, elemento, actual->izq, padre);
	}
	if (padre) {
		*padre = actual;
	}
	return encontrar_nodo_rec(abb, elemento, actual->der, padre);
}

bool abb_existe(const abb_t *abb, const void *elemento)
{
	if (!abb || !elemento) {
		return false;
	}
	return encontrar_nodo_rec(abb, elemento, abb->raiz, NULL) != NULL;
}

void *abb_buscar(const abb_t *abb, const void *elemento)
{
	if (!abb || !elemento) {
		return NULL;
	}

	nodo_t *nodo_buscado =
		encontrar_nodo_rec(abb, elemento, abb->raiz, NULL);
	if (!nodo_buscado) {
		return NULL;
	}
	return nodo_buscado->elemento;
}

void *abb_sacar(abb_t *abb, const void *elemento)
{
	if (!abb || !abb->raiz || !elemento) {
		return NULL;
	}

	nodo_t *padre = NULL;
	nodo_t *nodo_buscado =
		encontrar_nodo_rec(abb, elemento, abb->raiz, &padre);
	if (!nodo_buscado) {
		return NULL;
	}

	void *eliminar = nodo_buscado->elemento;

	if (!nodo_buscado->der && !nodo_buscado->izq) {
		if (padre) {
			if (padre->izq == nodo_buscado) {
				padre->izq = NULL;
			} else {
				padre->der = NULL;
			}
		} else {
			abb->raiz = NULL;
		}
	} else if (!nodo_buscado->der) {
		if (padre) {
			if (padre->izq == nodo_buscado) {
				padre->izq = nodo_buscado->izq;
			} else {
				padre->der = nodo_buscado->izq;
			}
		} else {
			abb->raiz = nodo_buscado->izq;
		}
	} else if (!nodo_buscado->izq) {
		if (padre) {
			if (padre->izq == nodo_buscado) {
				padre->izq = nodo_buscado->der;
			} else {
				padre->der = nodo_buscado->der;
			}
		} else {
			abb->raiz = nodo_buscado->der;
		}
	} else {
		nodo_t *padre_reemplazo = nodo_buscado;
		nodo_t *reemplazo = nodo_buscado->izq;
		while (reemplazo->der) {
			padre_reemplazo = reemplazo;
			reemplazo = reemplazo->der;
		}
		if (padre_reemplazo == nodo_buscado) {
			nodo_buscado->izq = reemplazo->izq;
		} else {
			padre_reemplazo->der = reemplazo->izq;
		}
		nodo_buscado->elemento = reemplazo->elemento;
		free(reemplazo);
		abb->nodos--;
		return eliminar;
	}

	free(nodo_buscado);
	abb->nodos--;
	return eliminar;
}

size_t abb_tamanio(const abb_t *abb)
{
	if (!abb) {
		return 0;
	}
	return abb->nodos;
}

bool abb_vacio(const abb_t *abb)
{
	return !abb || !abb->raiz;
}

// Recorre recursivamente el abb según el modo pasado e incrementa, en caso de pasarlo por parámetro, un contador.
bool recorrer_rec(nodo_t *raiz, enum abb_recorrido modo,
		  bool (*f)(void *, void *), void *ctx, size_t *contador)
{
	if (!raiz) {
		return true;
	}

	if (modo == ABB_PREORDEN) {
		if (!f(raiz->elemento, ctx)) {
			return false;
		}
		if (contador) {
			(*contador)++;
		}
	}

	recorrer_rec(raiz->izq, modo, f, ctx, contador);

	if (modo == ABB_INORDEN) {
		if (!f(raiz->elemento, ctx)) {
			return false;
		}
		if (contador) {
			(*contador)++;
		}
	}

	recorrer_rec(raiz->der, modo, f, ctx, contador);

	if (modo == ABB_POSTORDEN) {
		if (!f(raiz->elemento, ctx)) {
			return false;
		}
		if (contador) {
			(*contador)++;
		}
	}

	return true;
}

size_t abb_recorrer(const abb_t *abb, enum abb_recorrido modo,
		    bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !f || abb->nodos == 0) {
		return 0;
	}

	size_t contador = 0;
	recorrer_rec(abb->raiz, modo, f, ctx, &contador);
	return contador;
}

size_t abb_vectorizar(const abb_t *abb, enum abb_recorrido modo, void **vector,
		      size_t capacidad)
{
	if (!abb || !vector || capacidad == 0) {
		return 0;
	}
	return 0;
}

// Destruye los nodos aplicandoles una función destructora, si es que se pasa.
void destruir_todo_el_nodo_rec(nodo_t *nodo, void (*destructor)(void *))
{
	if (!nodo) {
		return;
	}

	destruir_todo_el_nodo_rec(nodo->izq, destructor);
	destruir_todo_el_nodo_rec(nodo->der, destructor);

	if (destructor) {
		destructor(nodo->elemento);
	}
	free(nodo);
}

void abb_destruir(abb_t *abb)
{
	if (!abb) {
		return;
	}
	destruir_todo_el_nodo_rec(abb->raiz, NULL);
	free(abb);
	abb = NULL;
}

void abb_destruir_todo(abb_t *abb, void (*destructor)(void *))
{
	if (!abb) {
		return;
	}
	destruir_todo_el_nodo_rec(abb->raiz, destructor);
	free(abb);
	abb = NULL;
}