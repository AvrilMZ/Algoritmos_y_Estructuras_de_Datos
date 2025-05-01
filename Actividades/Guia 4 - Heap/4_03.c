/**
 * Ya entendimos sift_up y cómo usarla en heap_insertar. 
 * Pasemos a entender sift_down, que de manera análoga nos sirve para heap_extraer_raiz.
 * 
 * Se recibe el vector de enteros, el tope del mismo y la posición a partir de la cual hay que aplicar la función.
 */

#include <stdbool.h>

void sift_down(int *vector, int tope, int pos_actual)
{
	if (!vector || tope == 0 || pos_actual >= tope) {
		return;
	}

	int hijo_izq = -1;
	int hijo_der = -1;
	int mayor = -1;
	while (2 * pos_actual + 1 < tope) {
		hijo_izq = 2 * pos_actual + 1;
		hijo_der = 2 * pos_actual + 2;
		mayor = pos_actual;

		if (hijo_izq < tope && vector[hijo_izq] > vector[mayor]) {
			mayor = hijo_izq;
		}

		if (hijo_der < tope && vector[hijo_der] > vector[mayor]) {
			mayor = hijo_der;
		}

		if (mayor == pos_actual) {
			pos_actual = tope;
		} else {
			int aux = vector[pos_actual];
			vector[pos_actual] = vector[mayor];
			vector[mayor] = aux;
			pos_actual = mayor;
		}
	}
}