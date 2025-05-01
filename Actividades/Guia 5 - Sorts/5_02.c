/**
 * Seguimos con otro método de ordenamiento, el llamado Selección. 
 * Al igual que en el ejercicio pasado, se recibe un vector de caracteres, que se desea ordenar de manera ascendente o descendente, 
 * dependiendo del booleano valor pasado por parámetro. 
 * También se recibe el vector donde se espera que estén los elementos ordenados.
 * 
 * A saber:
 * Un string ordenado ascendentemente es "ABCDEF".
 * Mientras que uno ordenado de manera descendente es "FEDCBA".
 */

#include <stdbool.h>
#define MAX_VECTOR 20

void selection_sort(char vector_desordenado[MAX_VECTOR],
		    char vector_ordenado[MAX_VECTOR], int tope, bool ascendente)
{
	for (int i = 0; i < tope; i++) {
		vector_ordenado[i] = vector_desordenado[i];
	}

	for (int i = 0; i < tope - 1; i++) {
		int pos_mejor = i;
		for (int j = i + 1; j < tope; j++) {
			if ((ascendente &&
			     vector_ordenado[j] < vector_ordenado[pos_mejor]) ||
			    (!ascendente &&
			     vector_ordenado[j] > vector_ordenado[pos_mejor])) {
				pos_mejor = j;
			}
		}
		char aux = vector_ordenado[i];
		vector_ordenado[i] = vector_ordenado[pos_mejor];
		vector_ordenado[pos_mejor] = aux;
	}
}