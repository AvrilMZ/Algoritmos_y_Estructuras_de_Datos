/**
 * En el apunte de punteros a función y en las clases prácticas se vio que es posible programar un sort que pueda ordenar cualquier vector,
 * independientemente del tipo de dato que él almacene.
 * 
 * Como siempre, para realmente entender un concepto, hay que ponerlo en práctica. 
 * Así que programemos un sort que pueda ordenar un vector de punteros a void*; 
 * es decir, un sort que pueda ordenar un vector de punteros, y esos punteros pueden apuntar a cualquier tipo de dato.
 * 
 * Para lograrlo, se tiene la firma de esta función, que recibe el vector de punteros, el tope de ese vector y una función que compara dos elementos del vector. 
 * La función comparadora devuelve un valor positivo si el primer elemento debería ir primero o un valor negativo si el segundo debería ir primero. 
 * En caso de que sean iguales, se devuelve 0. 
 * Es decir, si a la función comparadora le llega A como primer parámetro y B como segundo, y A debe ir primero, se devuelve un valor positivo; 
 * si B debe ir primero, se devuelve un número negativo.
 */

#include <stddef.h>

void quick_sort_rec(void **vector, int inicio, int fin,
		    int (*comparador)(void *, void *))
{
	if (inicio >= fin) {
		return;
	}

	void *pivote = vector[fin];
	int i = inicio;

	for (int j = inicio; j < fin; j++) {
		if (comparador(vector[j], pivote) > 0) {
			void *temp = vector[i];
			vector[i] = vector[j];
			vector[j] = temp;
			i++;
		}
	}

	void *temp = vector[i];
	vector[i] = vector[fin];
	vector[fin] = temp;

	quick_sort_rec(vector, inicio, i - 1, comparador);
	quick_sort_rec(vector, i + 1, fin, comparador);
}

void sort_semi_generico(void **vector, int cant_elementos,
			int (*comparador)(void *, void *))
{
	if (!vector || cant_elementos <= 1 || !comparador) {
		return;
	}
	quick_sort_rec(vector, 0, cant_elementos - 1, comparador);
}