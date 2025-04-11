/*
 * En este ejercicio de recursividad vamos a confeccionar una función que determine si una palabra es palíndromo o no. Es decir, si la palabra tiene el mismo significado leyéndola de izquierda a derecha que de derecha a izquierda.
 * 
 * Acordate que recibís un puntero, y como todo puntero, puede ser NULL. En ese caso, se debe devolver false.
 */

#include <stdbool.h>
#include <stdio.h>

bool letras_iguales(const char *cadena, size_t inicio, size_t fin)
{
	if (inicio >= fin) {
		return true;
	}

	if (cadena[inicio] != cadena[fin]) {
		return false;
	}

	return letras_iguales(cadena, inicio + 1, fin - 1);
}

bool es_palindromo(const char *cadena, size_t tope)
{
	if (!cadena) {
		return false;
	}

	return letras_iguales(cadena, 0, tope - 1);
}