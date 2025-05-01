/**
 * Ahora sí, empecemos con el método de ordenamiento más conocido: Bubblesort.
 * 
 * Se recibe un vector de caracteres, que deseo ordenar de manera ascendente o descendente, dependiendo del booleano pasado por parámetro. 
 * También se recibe el vector donde quiero que estén los elementos ordenados.
 * 
 * A saber, un string ordenado ascendentemente es "ABCDEF", mientras que uno ordenado de manera descendente es "FEDCBA".
 */

#include <stdbool.h>
#define MAX_VECTOR 20

void bubble_sort(char vector_desordenado[MAX_VECTOR],
		 char vector_ordenado[MAX_VECTOR], int tope, bool ascendente)
{
	for (int i = 0; i < tope; i++) {
		vector_ordenado[i] = vector_desordenado[i];
	}

	for (int i = 0; i < tope - 1; i++) {
		for (int j = 0; j < tope - i - 1; j++) {
			if ((ascendente &&
			     vector_ordenado[j] > vector_ordenado[j + 1]) ||
			    (!ascendente &&
			     vector_ordenado[j] < vector_ordenado[j + 1])) {
				char aux = vector_ordenado[j];
				vector_ordenado[j] = vector_ordenado[j + 1];
				vector_ordenado[j + 1] = aux;
			}
		}
	}
}