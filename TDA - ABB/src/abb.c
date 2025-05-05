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
	if (!abb) {
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
	if (!abb || !abb->raiz || !actual) {
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
	if (!abb || !abb->raiz) {
		return false;
	}
	return encontrar_nodo_rec(abb, elemento, abb->raiz, NULL) != NULL;
}

void *abb_buscar(const abb_t *abb, const void *elemento)
{
	if (!abb || !abb->raiz) {
		return NULL;
	}

	nodo_t *nodo_buscado =
		encontrar_nodo_rec(abb, elemento, abb->raiz, NULL);
	if (!nodo_buscado) {
		return NULL;
	}
	return nodo_buscado->elemento;
}

// Elimina un nodo hoja del ABB dado.
void eliminar_nodo_hoja(abb_t *abb, nodo_t *nodo, nodo_t *padre)
{
	if (padre) {
		if (padre->izq == nodo) {
			padre->izq = NULL;
		} else {
			padre->der = NULL;
		}
	} else {
		abb->raiz = NULL;
	}
	free(nodo);
	abb->nodos--;
}

// Elimina un nodo con un hijo del ABB dado.
void eliminar_nodo_con_un_hijo(abb_t *abb, nodo_t *nodo, nodo_t *padre)
{
	nodo_t *hijo;
	if (nodo->izq) {
		hijo = nodo->izq;
	} else {
		hijo = nodo->der;
	}

	if (padre) {
		if (padre->izq == nodo) {
			padre->izq = hijo;
		} else {
			padre->der = hijo;
		}
	} else {
		abb->raiz = hijo;
	}
	free(nodo);
	abb->nodos--;
}

// Elimina un nodo con dos hijos del ABB dado.
void eliminar_nodo_con_dos_hijos(abb_t *abb, nodo_t *nodo, nodo_t *padre)
{
	nodo_t *padre_reemplazo = nodo;
	nodo_t *reemplazo = nodo->izq;
	while (reemplazo->der) {
		padre_reemplazo = reemplazo;
		reemplazo = reemplazo->der;
	}

	if (padre_reemplazo == nodo) {
		nodo->izq = reemplazo->izq;
	} else {
		padre_reemplazo->der = reemplazo->izq;
	}
	nodo->elemento = reemplazo->elemento;
	free(reemplazo);
	abb->nodos--;
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
		eliminar_nodo_hoja(abb, nodo_buscado, padre);
	} else if (!nodo_buscado->der || !nodo_buscado->izq) {
		eliminar_nodo_con_un_hijo(abb, nodo_buscado, padre);
	} else {
		eliminar_nodo_con_dos_hijos(abb, nodo_buscado, padre);
	}

	return eliminar;
}

size_t abb_tamanio(const abb_t *abb)
{
	if (!abb || !abb->raiz) {
		return 0;
	}
	return abb->nodos;
}

bool abb_vacio(const abb_t *abb)
{
	return (!abb || !abb->raiz || abb_tamanio(abb) == 0);
}

/**
 * Si 'f' no es NULL, se le aplica a cada elemento.
 * Si se le pasa un 'contador' este se incrementa.
 * Si se le pasa un 'vector' el elemento se almacena en el mismo, si es que no supera su 'tope'.
 * Devuelve true si al aplicar 'f' esta no retorna false y si el contador no es igual o mayor al tope.
 */
bool aplicar_funcion_y_almacenar(nodo_t *nodo, bool (*f)(void *, void *),
				 void *ctx, size_t *contador, void **vector,
				 size_t *tope)
{
	if (contador) {
		if (tope && *contador >= *tope) {
			return false;
		}
		if (vector && tope) {
			vector[*contador] = nodo->elemento;
		}
		(*contador)++;
	}

	if (f && ctx && !f(nodo->elemento, ctx)) {
		return false;
	}

	return true;
}

/**
 * Recorre recursivamente el ABB según el modo pasado, si 'f' no es NULL, se le aplica a cada elemento.
 * Si se le pasa un 'contador' este se incrementa por cada elemento recorrido.
 * Si se le pasa un 'vector' el elemento se almacena en el mismo, si es que no supera su 'tope'.
 * Devuelve true si se recorrieron todos los elementos del ABB, en caso contrario false.
 */
bool recorrer_rec(nodo_t *raiz, enum abb_recorrido modo,
		  bool (*f)(void *, void *), void *ctx, size_t *contador,
		  void **vector, size_t *tope)
{
	if (!raiz) {
		return true;
	}

	if (modo == ABB_PREORDEN) {
		if (!aplicar_funcion_y_almacenar(raiz, f, ctx, contador, vector,
						 tope)) {
			return false;
		}
	}

	if (!recorrer_rec(raiz->izq, modo, f, ctx, contador, vector, tope)) {
		return false;
	}

	if (modo == ABB_INORDEN) {
		if (!aplicar_funcion_y_almacenar(raiz, f, ctx, contador, vector,
						 tope)) {
			return false;
		}
	}

	if (!recorrer_rec(raiz->der, modo, f, ctx, contador, vector, tope)) {
		return false;
	}

	if (modo == ABB_POSTORDEN) {
		if (!aplicar_funcion_y_almacenar(raiz, f, ctx, contador, vector,
						 tope)) {
			return false;
		}
	}

	return true;
}

size_t abb_recorrer(const abb_t *abb, enum abb_recorrido modo,
		    bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !abb->raiz || !f || abb_tamanio(abb) == 0) {
		return 0;
	}

	size_t contador = 0;
	recorrer_rec(abb->raiz, modo, f, ctx, &contador, NULL, NULL);
	return contador;
}

size_t abb_vectorizar(const abb_t *abb, enum abb_recorrido modo, void **vector,
		      size_t capacidad)
{
	if (!abb || !abb->raiz || !vector || capacidad == 0) {
		return 0;
	}

	size_t contador = 0;
	recorrer_rec(abb->raiz, modo, NULL, NULL, &contador, vector,
		     &capacidad);
	return contador;
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