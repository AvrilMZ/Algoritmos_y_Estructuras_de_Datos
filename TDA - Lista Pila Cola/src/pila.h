#ifndef PILA_H_
#define PILA_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct pila pila_t;

/**
 * Crea una pila vacía.
 */
pila_t *pila_crear();

/**
 * Apila un elemento en la pila.
 *
 * Devuelve true si pudo apilar o false si no pudo.
 */
bool pila_apilar(pila_t *, void *elemento);

/**
 * Desapila un elemento de la pila y lo devuelve.
 *
 * Devuelve NULL si no hay elementos en la pila.
 */
void *pila_desapilar(pila_t *);

/**
 * Devuelve true si la pila está vacía.
 *
 * Devuelve false si no lo está.
 */
bool pila_vacía(pila_t *);

/**
 * Devuelve la cantidad de elementos presentes en la pila.
 *
 * Devuelve 0 si no existe la pila.
 */
size_t pila_tamanio(pila_t *);

/**
 * Devuelve el elemento en el tope de la pila sin desapilarlo.
 *
 * Devuelve NULL si no hay elementos en la pila.
 */
void *pila_tope(pila_t *);

/**
 * Destruye la pila.
 */
void pila_destruir(pila_t *);

#endif // PILA_H_
