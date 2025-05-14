/**
 * Terminamos los tres métodos de ordenamiento con quick sort. 
 * Programar ahora este algoritmo, cumpliendo las mismas condiciones de los ejercicios anteriores.
 */

#include <stdbool.h>

void quick_sort_rec(int *numeros, int inicio, int fin, bool ascendente)
{
	if (inicio >= fin) {
		return;
	}

	int pivote = numeros[fin];
	int i = inicio;
	for (int j = inicio; j < fin; j++) {
		if ((ascendente && numeros[j] < pivote) ||
		    (!ascendente && numeros[j] > pivote)) {
			int temp = numeros[i];
			numeros[i] = numeros[j];
			numeros[j] = temp;
			i++;
		}
	}

	int temp = numeros[i];
	numeros[i] = numeros[fin];
	numeros[fin] = temp;

	quick_sort_rec(numeros, inicio, i - 1, ascendente);
	quick_sort_rec(numeros, i + 1, fin, ascendente);
}

void quick_sort(int *numeros, int tope, bool ascendente)
{
	if (!numeros || tope == 0 || tope == 1) {
		return;
	}
	quick_sort_rec(numeros, 0, tope - 1, ascendente);
}