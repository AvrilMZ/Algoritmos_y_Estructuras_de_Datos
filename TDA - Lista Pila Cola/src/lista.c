#include "lista.h"

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

// Reserva memoria para un 'lista_t' y devuelve su puntero.
lista_t *reservar_memoria_lista()
{
	lista_t *lista = calloc(1, sizeof(lista_t));
	if (!lista) {
		return NULL;
	}
	return lista;
}

// Reserva memoria para un nodo y le asigna el dato pasado por parámetro.
nodo_t *crear_nodo_con_dato(void *dato)
{
	nodo_t *nodo = reservar_memoria_nodo();
	if (!nodo) {
		return NULL;
	}
	nodo->dato = dato;
	return nodo;
}

// Elimina el nodo pasado por parámetro.
void eliminar_nodo(nodo_t *anterior, nodo_t *eliminar)
{
	if (!anterior || !eliminar) {
		return;
	}
	anterior->nodo_siguiente = eliminar->nodo_siguiente;
	free(eliminar);
}

// Devuelve el nodo en la posición indicada o NULL si la posición es inválida.
nodo_t *nodo_en_posicion(lista_t *lista, int posicion)
{
	if (!lista || posicion < 0 || posicion >= lista->cantidad) {
		return NULL;
	}

	if (posicion == 0) {
		return lista->primero;
	}

	nodo_t *actual = lista->primero;
	for (int i = 0; i < posicion; i++) {
		actual = actual->nodo_siguiente;
	}
	return actual;
}

lista_t *lista_crear()
{
	lista_t *lista = reservar_memoria_lista();
	if (!lista) {
		return NULL;
	}
	return lista;
}

bool lista_insertar_en_posicion(lista_t *lista, int posicion, void *elemento)
{
	if (!lista || posicion < 0 || posicion > lista->cantidad) {
		return false;
	}

	nodo_t *nodo_nuevo = crear_nodo_con_dato(elemento);
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

	nodo_t *nodo_nuevo = crear_nodo_con_dato(elemento);
	if (!lista->primero) {
		lista->primero = nodo_nuevo;
		lista->ultimo = nodo_nuevo;
	} else {
		lista->ultimo->nodo_siguiente = nodo_nuevo;
		lista->ultimo = nodo_nuevo;
	}
	lista->cantidad++;
	return true;
}

size_t lista_tamanio(lista_t *lista)
{
	if (!lista) {
		return 0;
	}
	return (size_t)lista->cantidad;
}

void *lista_obtener_elemento(lista_t *lista, int posicion)
{
	if (!lista || posicion < 0 || posicion >= lista->cantidad) {
		return NULL;
	}

	nodo_t *nodo_sig = nodo_en_posicion(lista, posicion);
	if (nodo_sig) {
		return nodo_sig->dato;
	}
	return NULL;
}

void *lista_sacar_de_posicion(lista_t *lista, int posicion)
{
	if (!lista || posicion < 0 || posicion >= lista->cantidad) {
		return NULL;
	}

	nodo_t *eliminar = NULL;
	void *dato = NULL;
	if (posicion == 0) {
		eliminar = lista->primero;
		dato = eliminar->dato;
		lista->primero = lista->primero->nodo_siguiente;
		if (lista->cantidad == 1) {
			lista->ultimo = NULL;
		}
		free(eliminar);
	} else {
		nodo_t *nodo_ant = nodo_en_posicion(lista, posicion - 1);
		eliminar = nodo_ant->nodo_siguiente;
		dato = eliminar->dato;
		if (eliminar == lista->ultimo) {
			lista->ultimo = nodo_ant;
		}
		eliminar_nodo(nodo_ant, eliminar);
	}
	lista->cantidad--;
	return dato;
}

int lista_buscar_posicion(lista_t *lista, void *elemento)
{
	if (!lista || lista->cantidad == 0) {
		return -1;
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
		return posicion;
	}
	return -1;
}

void *lista_sacar_elemento(lista_t *lista, void *elemento)
{
	if (!lista || lista->cantidad == 0) {
		return NULL;
	}

	if (lista->primero->dato == elemento) {
		return lista_sacar_de_posicion(lista, 0);
	}

	bool encontrado = false;
	void *dato = NULL;
	nodo_t *anterior = lista->primero;
	nodo_t *actual = lista->primero->nodo_siguiente;
	while (actual && !encontrado) {
		if (actual->dato == elemento) {
			dato = actual->dato;
			if (actual == lista->ultimo) {
				lista->ultimo = anterior;
			}
			eliminar_nodo(anterior, actual);
			lista->cantidad--;
			encontrado = true;
		}
		anterior = actual;
		actual = actual->nodo_siguiente;
	}

	if (encontrado) {
		return dato;
	}
	return NULL;
}

void *lista_buscar(lista_t *lista, bool (*criterio)(void *, void *),
		   void *contexto)
{
	if (!lista || !criterio || lista->cantidad == 0) {
		return NULL;
	}

	nodo_t *actual = lista->primero;
	void *resultado = NULL;
	while (actual && !resultado) {
		if (criterio(actual->dato, contexto)) {
			resultado = actual->dato;
		} else {
			actual = actual->nodo_siguiente;
		}
	}
	return resultado;
}

int lista_iterar(lista_t *lista, bool (*f)(void *, void *), void *contexto)
{
	if (!lista || !f || lista->cantidad == 0) {
		return 0;
	}

	nodo_t *actual = lista->primero;
	int elementos_recorridos = 0;
	bool detener = false;
	while (actual && !detener) {
		elementos_recorridos++;
		if (!f(actual->dato, contexto)) {
			detener = true;
		} else {
			actual = actual->nodo_siguiente;
		}
	}
	return elementos_recorridos;
}

// Destruye los nodos.
void destruir_nodos(nodo_t *nodo)
{
	while (nodo) {
		nodo_t *siguiente = nodo->nodo_siguiente;
		free(nodo);
		nodo = siguiente;
	}
}

void lista_destruir(lista_t *lista)
{
	if (!lista) {
		return;
	}
	destruir_nodos(lista->primero);
	free(lista);
	lista = NULL;
}

// Reserva memoria para un 'lista_iterador_t' y devuelve su puntero.
lista_iterador_t *reservar_memoria_iterador()
{
	lista_iterador_t *iterador = calloc(1, sizeof(lista_iterador_t));
	if (!iterador) {
		return NULL;
	}
	return iterador;
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista) {
		return NULL;
	}

	lista_iterador_t *iterador = reservar_memoria_iterador();
	if (!iterador) {
		return NULL;
	}
	iterador->actual = lista->primero;
	return iterador;
}

bool lista_iterador_quedan_elementos_por_recorrer(lista_iterador_t *iterador)
{
	if (!iterador) {
		return false;
	}
	return iterador->actual != NULL;
}

void lista_iterador_proxima_iteracion(lista_iterador_t *iterador)
{
	if (!iterador || !iterador->actual) {
		return;
	}
	iterador->actual = iterador->actual->nodo_siguiente;
}

void *lista_iterador_obtener_elemento(lista_iterador_t *iterador)
{
	if (!iterador || !iterador->actual) {
		return NULL;
	}
	return iterador->actual->dato;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if (!iterador) {
		return;
	}
	free(iterador);
	iterador = NULL;
}