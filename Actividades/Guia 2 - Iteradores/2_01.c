/**
 * Entendemos que el concepto de iterador, y su uso, es difícil de entender al principio. Por eso, dedicamos una guía especialmente para ellos.
 * 
 * En este primer ejercicio, resulta que tenemos una lista de números, y queremos saber si el número pasado por parámetro está en ella. 
 * Peeero, no tenemos acceso a la lista, directamente recibimos un iterador. Más específicamente, el iterador externo. Las funciones del iterador externo se muestran en el .h correspondiente.
 * 
 * No olvidar verificar los parámetros. Si el it_lista pasado es NULL, devolver false.
 * 
 * Aclaración: el iterador pasado por parámetro ya fue creado previamente, y no se debe destruir en esta función. Nosotros nos ocupamos de eso ;)
 */

#include <stdbool.h>
#include <stddef.h>

typedef struct lista_iterador {
	nodo_t *corriente;
	lista_t *lista;
} lista_iterador_t;

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

bool se_encuentra_el_elemento(lista_iterador_t *it_lista, int numero)
{
	if (!it_lista) {
		return false;
	}

	bool encontrado = false;
	void *elemento_actual = lista_iterador_elemento_actual(it_lista);
	while (!encontrado && elemento_actual != NULL) {
		if (*(int *)elemento_actual == numero) {
			encontrado = true;
		} else if (lista_iterador_tiene_siguiente(it_lista)) {
			lista_iterador_avanzar(it_lista);
			elemento_actual =
				lista_iterador_elemento_actual(it_lista);
		} else {
			elemento_actual = NULL;
		}
	}

	return encontrado;
}