#include "src/lista.h"

typedef struct nodo {
	struct nodo *nodo_siguiente;
	void *dato;
} nodo_t;

struct lista {
	nodo_t *primero;
	nodo_t *ultimo;
	int cantidad;
};

struct lista_iterador {
	nodo_t *actual;
};

lista_t *lista_crear()
{
}

bool lista_insertar(lista_t *lista, void *elemento)
{
}

bool lista_insertar_en_posicion(lista_t *lista, int posicion, void *elemento)
{
}

size_t lista_tamanio(lista_t *lista)
{
	return lista->cantidad;
}

void *lista_obtener_elemento(lista_t *lista, int posicion)
{
	if (!lista || posicion < 0 || posicion >= lista->cantidad)
		return NULL;

	nodo_t *nodo_sig = lista->primero;
	for (int i = 0; i < posicion; i++) {
		nodo_sig = nodo_sig->nodo_siguiente;
	}

	return nodo_sig->dato;
}

void *lista_sacar_de_posicion(lista_t *lista, int posicion)
{
}

void *lista_sacar_elemento(lista_t *lista, void *elemento)
{
}

int lista_buscar_posicion(lista_t *lista, void *elemento)
{
}

void *lista_buscar(lista_t *lista, bool (*criterio)(void *, void *),
		   void *contexto)
{
}

int lista_iterar(lista_t *lista, bool (*f)(void *, void *), void *contexto)
{
}

void lista_destruir(lista_t *lista)
{
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
}

bool lista_iterador_quedan_elementos_por_recorrer(lista_iterador_t *iterador)
{
}

void lista_iterador_proxima_iteracion(lista_iterador_t *iterador)
{
}

void *lista_iterador_obtener_elemento(lista_iterador_t *iterador)
{
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
}