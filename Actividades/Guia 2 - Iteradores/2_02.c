/*
 * Afiancemos nuestros conocimientos del iterador externo con este ejercicio. Tenemos una lista de entrenadores, y queremos saber cuál es el que ganó más batallas. 
 * En caso de que dos entrenadores hayan ganado la misma cantidad de batallas, se debe devolver el que menos batallas perdió de los dos. 
 * Al igual que en el ejercicio anterior, se recibe el iterador de la lista.
 * 
 * La estructura del entrenador se encuentra en el archivo solucion.h. 
 * No olvidar revisar los parámetros recibidos! Se puede recorrer una lista con el iterador, si ese iterador es nulo? 
 * En caso de recibirse un parámetro NULL, devolver NULL.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

typedef struct lista_iterador {
	nodo_t *corriente;
	lista_t *lista;
} lista_iterador_t;

typedef struct entrenador {
	int b_ganadas;
	int b_perdidas;
	int b_empatadas;
} entrenador_t;

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador);

/*
 * Avanza el iterador al siguiente elemento.
 * Devuelve true si pudo avanzar el iterador o false en caso de
 * que no queden elementos o en caso de error.
 *
 * Una vez llegado al último elemento, si se invoca a
 * lista_iterador_elemento_actual, el resultado siempre será NULL.
 */
bool lista_iterador_avanzar(lista_iterador_t *iterador);

/*
 * Devuelve el elemento actual del iterador o NULL en caso de que no
 * exista dicho elemento o en caso de error.
 */
void *lista_iterador_elemento_actual(lista_iterador_t *iterador);

entrenador_t *entrenador_con_mas_victorias(lista_iterador_t *it_lista)
{
	if (!it_lista) {
		return NULL;
	}

	entrenador_t *record = NULL;
	entrenador_t *actual = lista_iterador_elemento_actual(it_lista);
	while (actual) {
		if (!record) {
			record = actual;
		} else if (actual->b_ganadas > record->b_ganadas ||
			   (actual->b_ganadas == record->b_ganadas &&
			    actual->b_perdidas < record->b_perdidas)) {
			record = actual;
		}
		if (lista_iterador_tiene_siguiente(it_lista)) {
			lista_iterador_avanzar(it_lista);
			actual = lista_iterador_elemento_actual(it_lista);
		}
	}

	return record;
}