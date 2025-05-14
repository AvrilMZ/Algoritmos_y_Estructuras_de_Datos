/**
 * Finalmente, llegamos a lo más genérico de lo genérico. 
 * Ahora no recibimos un puntero de void*s, ahora recibimos directamente un void*. 
 * Sabemos que se apunta a un vector, pero no sabemos de qué tipo de dato. 
 * Por fortuna, también recibimos la cantidad de elementos que hay en el vector y el tamaño de los elementos almacenados. 
 * También se recibe la función comparadora, que se comporta de la misma manera que la función anterior, a saber:
 * La función comparadora devuelve un valor positivo si el primer elemento debería ir primero o un valor negativo si el segundo debería ir primero. 
 * En caso de que sean iguales, se devuelve 0.
 */

#include <string.h>

void swap(void *a, void *b, int size)
{
	char temp[size];
	memcpy(temp, a, size);
	memcpy(a, b, size);
	memcpy(b, temp, size);
}

void sort_generico(void *vector, int n, int size,
		   int (*comparador)(const void *, const void *))
{
	char *arr = (char *)vector;
	int i, j;

	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - 1 - i; j++) {
			void *elem1 = arr + j * size;
			void *elem2 = arr + (j + 1) * size;

			if (comparador(elem1, elem2) < 0) {
				swap(elem1, elem2, size);
			}
		}
	}
}