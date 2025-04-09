#include "pila.h"
#include "lista.h"

struct pila {
	lista_t *lista;
};

// Reserva memoria para un struct de tipo 'pila_t'.
pila_t *reservar_memoria_pila()
{
	pila_t *pila = calloc(1, sizeof(pila_t));
	if (!pila) {
		return NULL;
	}
	return pila;
}

pila_t *pila_crear()
{
	pila_t *pila = reservar_memoria_pila();
	if (!pila) {
		return NULL;
	}

	lista_t *lista_interna = lista_crear();
	if (!lista_interna) {
		free(pila);
		pila = NULL;
		return NULL;
	}
	pila->lista = lista_interna;

	return pila;
}

bool pila_apilar(pila_t *, void *elemento)
{
}

void *pila_desapilar(pila_t *)
{
}

bool pila_vacía(pila_t *)
{
}

size_t pila_tamanio(pila_t *)
{
}

void *pila_tope(pila_t *)
{
}

void pila_destruir(pila_t *)
{
}