/**
 * Empezamos con el primero de los tres sorts que se ven en la materia Algo2Mendez. 
 * Como ya estamos en temas de Algo2, en vez de recibir un vector desordenado y otro donde ir enviando los elementos ordenados, se recibe solamente un vector. 
 * Al principio, se recibe el vector desordenado, y al finalizar el algoritmo, el mismo debe encontrarse ordenado.
 * 
 * Este algoritmo puede hacerse de manera tanto iterativa como recursiva, cualquiera está bien (mientras funcione, claro).
 * 
 * Como venimos viendo hasta ahora, se recibe también un booleano para decidir si debemos ordenar de manera ascendente o descendente el vector.
 */

#include <stdbool.h>

void merge(int *numeros, int tam_izquierda, int tam_derecha, bool ascendente)
{
	int total = tam_izquierda + tam_derecha;
	int arreglo_izquierda[tam_izquierda];
	int arreglo_derecha[tam_derecha];

	for (int i = 0; i < tam_izquierda; i++) {
		arreglo_izquierda[i] = numeros[i];
	}
	for (int i = 0; i < tam_derecha; i++) {
		arreglo_derecha[i] = numeros[tam_izquierda + i];
	}

	int i = 0;
	int j = 0;
	int k = 0;
	while (i < tam_izquierda && j < tam_derecha) {
		if ((ascendente &&
		     arreglo_izquierda[i] <= arreglo_derecha[j]) ||
		    (!ascendente &&
		     arreglo_izquierda[i] >= arreglo_derecha[j])) {
			numeros[k] = arreglo_izquierda[i];
			i++;
		} else {
			numeros[k] = arreglo_derecha[j];
			j++;
		}
		k++;
	}

	while (i < tam_izquierda) {
		numeros[k] = arreglo_izquierda[i];
		i++;
		k++;
	}

	while (j < tam_derecha) {
		numeros[k] = arreglo_derecha[j];
		j++;
		k++;
	}
}

void merge_sort(int *numeros, int tope, bool ascendente)
{
	if (!numeros || tope == 0 || tope == 1) {
		return;
	}

	int mitad = tope / 2;
	merge_sort(numeros, mitad, ascendente);
	merge_sort(numeros + mitad, tope - mitad, ascendente);

	merge(numeros, mitad, tope - mitad, ascendente);
}