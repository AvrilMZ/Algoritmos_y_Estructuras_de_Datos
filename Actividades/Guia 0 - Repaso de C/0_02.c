/*
 * Ahora, les damos la firma de una función que recibe un vector, su tope y
 * la letra a buscar. Devolver en dónde se encuentra la letra o -1 si no se
 * encuentra en el vector. Para seguir las buenas prácticas, ya les definimos la
 * variable ERROR en solucion.h ;)
 */

#include "solucion.h"

/*
 * Se recibe un vector de letras, su tope y la letra a buscar.
 * Se devuelve la posición de la letra o -1 en caso de que no se encuentre.
 */
int posicion_letra(char vector[MAX_VECTOR], int tope, char letra)
{
	bool letra_encontrada = false;
	int indice_encontrado = ERROR;
	for (int i = 0; i < tope && !letra_encontrada; i++) {
		if (vector[i] == letra) {
			letra_encontrada = true;
			indice_encontrado = i;
		}
	}
	return indice_encontrado;
}