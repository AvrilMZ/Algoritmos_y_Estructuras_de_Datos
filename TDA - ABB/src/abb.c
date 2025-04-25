#include "abb.h"
#include "abb_estructura_privada.h"

typedef struct abb_vectorizado {
	void **vector;
	size_t capacidad;
	size_t tope;
} abb_vectorizado_t;

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
 * Recorre recursivamente el abb hasta encontrar el nodo con el elemento pasado por parametro y lo devuelve.
 * En caso de no encontrarlo devuelve NULL.
 */
nodo_t *encontrar_nodo_rec(const abb_t *abb, const void *elemento,
			   nodo_t *actual)
{
	if (!abb || !elemento || !actual) {
		return NULL;
	}

	int cmp = abb->comparador(elemento, actual->elemento);
	if (cmp == 0) {
		return actual;
	} else if (cmp < 0) {
		return encontrar_nodo_rec(abb, elemento, actual->izq);
	}
	return encontrar_nodo_rec(abb, elemento, actual->der);
}

bool abb_existe(const abb_t *abb, const void *elemento)
{
	if (!abb || !elemento) {
		return false;
	}
	return encontrar_nodo_rec(abb, elemento, abb->raiz) != NULL;
}

void *abb_buscar(const abb_t *abb, const void *elemento)
{
	if (!abb || !elemento) {
		return NULL;
	}

	nodo_t *nodo_buscado = encontrar_nodo_rec(abb, elemento, abb->raiz);
	if (!nodo_buscado) {
		return NULL;
	}
	return nodo_buscado->elemento;
}

void *abb_sacar(abb_t *abb, const void *elemento)
{
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

	if (!recorrer_rec(raiz->izq, modo, f, ctx, contador)) {
		return false;
	}

	if (modo == ABB_INORDEN) {
		if (!f(raiz->elemento, ctx)) {
			return false;
		}
		if (contador) {
			(*contador)++;
		}
	}

	if (!recorrer_rec(raiz->der, modo, f, ctx, contador)) {
		return false;
	}

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

// Agrega el elemento al vector pasados por parámetro.
bool agregar_elemento_vector(void *vector, void *elemento)
{
	if (!vector || !elemento) {
		return false;
	}

	abb_vectorizado_t *vec = (abb_vectorizado_t *)vector;

	if (vec->tope >= vec->capacidad) {
		return false;
	}
	vec->vector[vec->tope] = elemento;
	return true;
}

size_t abb_vectorizar(const abb_t *abb, enum abb_recorrido modo, void **vector,
		      size_t capacidad)
{
	if (!abb || !vector || capacidad == 0) {
		return 0;
	}

	abb_vectorizado_t vec = {
		.vector = vector,
		.capacidad = capacidad,
		.tope = 0,
	};
	recorrer_rec(abb->raiz, modo, agregar_elemento_vector, &vec, &vec.tope);
	return vec.tope;
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