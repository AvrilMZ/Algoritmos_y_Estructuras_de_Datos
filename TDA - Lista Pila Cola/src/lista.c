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

// Reserva memoria para un 'nodo_t' y devuelve su puntero.
nodo_t *reservar_memoria_nodo()
{
	nodo_t *nodo = calloc(1, sizeof(nodo_t));
	if (!nodo) {
		return NULL;
	}
	return nodo;
}

lista_t *lista_crear()
{
}

bool lista_insertar_en_posicion(lista_t *lista, int posicion, void *elemento)
{
	if (!lista || posicion < 0 || posicion >= lista->cantidad) {
		return false;
	}

	nodo_t *nodo_nuevo = reservar_memoria_nodo();
	if (!nodo_nuevo) {
		return false;
	}
	nodo_nuevo->dato = elemento;

	if (posicion == 0) {
		nodo_nuevo->nodo_siguiente = lista->primero;
		lista->primero = nodo_nuevo;
		if (lista->cantidad == 0) {
			lista->ultimo = nodo_nuevo;
		}
	} else {
		nodo_t *nodo_ant = lista->primero;
		for (int i = 0; i < posicion - 1; i++) {
			nodo_ant = nodo_ant->nodo_siguiente;
		}
		nodo_nuevo->nodo_siguiente = nodo_ant->nodo_siguiente;
		nodo_ant->nodo_siguiente = nodo_nuevo;

		if (nodo_nuevo->nodo_siguiente == NULL) {
			lista->ultimo = nodo_nuevo;
		}
	}

	lista->cantidad++;
	return true;
}

bool lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista) {
		return false;
	}

	return lista_insertar_en_posicion(lista, lista->cantidad, elemento);
}

size_t lista_tamanio(lista_t *lista)
{
	if (!lista) {
		return 0;
	}

	return lista->cantidad;
}

void *lista_obtener_elemento(lista_t *lista, int posicion)
{
	if (!lista || posicion < 0 || posicion >= lista->cantidad) {
		return NULL;
	}

	nodo_t *nodo_sig = lista->primero;
	for (int i = 0; i < posicion; i++) {
		nodo_sig = nodo_sig->nodo_siguiente;
	}

	return nodo_sig->dato;
}

void *lista_sacar_de_posicion(lista_t *lista, int posicion)
{
	if (!lista || posicion < 0 || posicion >= lista->cantidad) {
		return NULL;
	}

	nodo_t *eliminar = NULL;
	if (posicion == 0) {
		eliminar = lista->primero;
		lista->primero = lista->primero->nodo_siguiente;
		if (lista->cantidad == 1) {
			lista->ultimo = NULL;
		}
	} else {
		nodo_t *nodo_ant = lista->primero;
		for (int i = 0; i < posicion - 1; i++) {
			nodo_ant = nodo_ant->nodo_siguiente;
		}
		eliminar = nodo_ant->nodo_siguiente;
		nodo_ant->nodo_siguiente =
			nodo_ant->nodo_siguiente->nodo_siguiente;
		if (eliminar == lista->ultimo) {
			lista->ultimo = nodo_ant;
		}
	}

	void *dato = eliminar->dato;
	free(eliminar);
	lista->cantidad--;
	return dato;
}

void *lista_sacar_elemento(lista_t *lista, void *elemento)
{
	if (!lista) {
		return NULL;
	}

	nodo_t *nodo_actual = lista->primero;
	int posicion = 0;
	bool encontrado = false;
	while (nodo_actual && !encontrado) {
		if (nodo_actual->dato == elemento) {
			encontrado = true;
		} else {
			nodo_actual = nodo_actual->nodo_siguiente;
			posicion++;
		}
	}

	if (encontrado) {
		return lista_sacar_de_posicion(lista, posicion);
	}
	return NULL;
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