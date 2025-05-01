/**
 * Continuamos con strings, pero ahora con una vuelta de tuerca. 
 * Recibimos un string desordenado y debemos ordenarlo de manera ascendente o descendente según el booleano pasado por parámetro. 
 * El string ordenado se devuelve en el segundo vector pasado por parámetro.
 * 
 * Recordemos que un string ordenado ascendentemente es "ABCDEF".
 * Mientras que uno ordenado de manera descendente es "FEDCBA".
 */

#include <stdbool.h>
#include <string.h>
#define MAX_VECTOR 20

void bubble_sort(char string_desordenado[MAX_VECTOR],
		 char string_ordenado[MAX_VECTOR], bool ascendente)
{
	size_t tope = strlen(string_desordenado);
	for (size_t i = 0; i < tope; i++) {
		string_ordenado[i] = string_desordenado[i];
	}
	string_ordenado[tope] = '\0';

	for (size_t i = 0; i < tope - 1; i++) {
		for (size_t j = 0; j < tope - i - 1; j++) {
			if (ascendente) {
				if (string_ordenado[j] >
				    string_ordenado[j + 1]) {
					char aux = string_ordenado[j];
					string_ordenado[j] =
						string_ordenado[j + 1];
					string_ordenado[j + 1] = aux;
				}
			} else {
				if (string_ordenado[j] <
				    string_ordenado[j + 1]) {
					char aux = string_ordenado[j];
					string_ordenado[j] =
						string_ordenado[j + 1];
					string_ordenado[j + 1] = aux;
				}
			}
		}
	}
}