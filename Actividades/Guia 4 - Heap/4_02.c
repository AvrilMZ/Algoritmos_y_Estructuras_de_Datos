/**
 * 
 * Ya tenemos la función sift_up, genial. Ahora sí, programemos heap_insertar. 
 * Se recibe el vector del heap, su tope y el elemento a insertar.
 * 
 * No necesitás programar sift_up de nuevo, nosotros la agregamos por vos detrás de cámara ;)
 */

#include <stdbool.h>

void sift_up(int *vector, int pos_actual)
{
	if (!vector || pos_actual == 0) {
		return;
	}

	bool seguir = true;
	while (pos_actual > 0 && seguir) {
		int padre = (pos_actual - 1) / 2;
		if (vector[pos_actual] > vector[padre]) {
			int aux = vector[padre];
			vector[padre] = vector[pos_actual];
			vector[pos_actual] = aux;
			pos_actual = padre;
		} else {
			seguir = false;
		}
	}
}

void heap_insertar(int *vector, int *tope, int elemento)
{
	if (!vector || !tope) {
		return;
	}

	vector[*tope] = elemento;
	sift_up(vector, *tope);
	(*tope)++;
}