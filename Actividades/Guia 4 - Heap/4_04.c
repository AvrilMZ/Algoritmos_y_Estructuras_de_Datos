/**
 * Finalmente llegamos a la temida función heap_borrar, o heap_extraer_raiz en este caso. 
 * Se debe quitar el elemento raíz del heap, que por propiedad de heap maximal, será el mayor elemento del heap. 
 * Sin más preámbulo, implementémosla.
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

int heap_extraer_raiz(int *vector, int *tope)
{
	if (!vector || !tope || *tope <= 0) {
		return 0;
	}

	int raiz = vector[0];
	vector[0] = vector[*tope - 1];
	(*tope)--;

	sift_down(vector, *tope, 0);
	return raiz;
}