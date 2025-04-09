#include "cola.h"
#include "lista.h"

struct cola {
	lista_t *lista;
};

// Reserva memoria para un struct de tipo 'cola_t'.
cola_t *reservar_memoria_cola()
{
	cola_t *cola = calloc(1, sizeof(cola_t));
	if (!cola) {
		return NULL;
	}
	return cola;
}

cola_t *cola_crear()
{
	cola_t *cola = reservar_memoria_cola();
	if (!cola) {
		return NULL;
	}

	lista_t *lista_interna = lista_crear();
	if (!lista_interna) {
		free(cola);
		cola = NULL;
		return NULL;
	}
	cola->lista = lista_interna;

	return cola;
}

bool cola_encolar(cola_t *cola, void *elemento)
{
}

void *cola_desencolar(cola_t *cola)
{
}

bool cola_vacía(cola_t *cola)
{
}

size_t cola_tamanio(cola_t *cola)
{
}

void *cola_frente(cola_t *cola)
{
}

void cola_destruir(cola_t *cola)
{
}