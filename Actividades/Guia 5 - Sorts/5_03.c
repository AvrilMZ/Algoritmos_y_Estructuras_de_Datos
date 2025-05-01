/**
 * Para finalizar los tres métodos de ordenamiento que se ven en Algo1, se pide implementar el método de inserción.
 * 
 * A saber:
 * Un string ordenado ascendentemente es "ABCDEF", mientras que uno ordenado de manera descendente es "FEDCBA".
 */

#include <stdbool.h>
#define MAX_VECTOR 20

void insertion_sort(char vector_desordenado[MAX_VECTOR],
		    char vector_ordenado[MAX_VECTOR], int tope, bool ascendente)
{
	for (int i = 0; i < tope; i++) {
		vector_ordenado[i] = vector_desordenado[i];
	}

	for (int i = 1; i < tope; i++) {
		char actual = vector_ordenado[i];
		int j = i - 1;

		while (j >= 0 &&
		       ((ascendente && vector_ordenado[j] > actual) ||
			(!ascendente && vector_ordenado[j] < actual))) {
			vector_ordenado[j + 1] = vector_ordenado[j];
			j--;
		}
		vector_ordenado[j + 1] = actual;
	}
}