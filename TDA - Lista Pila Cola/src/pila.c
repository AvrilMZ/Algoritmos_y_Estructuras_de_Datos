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

bool pila_apilar(pila_t *pila, void *elemento)
{
	if (!pila) {
		return false;
	}
	return lista_insertar_en_posicion(pila->lista, 0, elemento);
}

void *pila_desapilar(pila_t *pila)
{
	if (!pila || lista_esta_vacia(pila->lista)) {
		return NULL;
	}
	return lista_sacar_de_posicion(pila->lista, 0);
}

bool pila_vacía(pila_t *pila)
{
	if (!pila) {
		return true;
	}
	return lista_tamanio(pila->lista) == 0;
}

size_t pila_tamanio(pila_t *pila)
{
	if (!pila) {
		return 0;
	}
	return lista_tamanio(pila->lista);
}

void *pila_tope(pila_t *pila)
{
	if (!pila || lista_esta_vacia(pila->lista)) {
		return NULL;
	}
	return lista_obtener_elemento(pila->lista, 0);
}

void pila_destruir(pila_t *pila)
{
}