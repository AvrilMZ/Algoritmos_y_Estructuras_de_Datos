/*
 * Ash Ketchum quiere convertirse en Maestro Pokémon, el más alto grado de entrenamiento Pokémon.
 * Para lograrlo necesita entrenar a sus pokémones en batallas y estar también físicamente en forma, así que decide seguir el consejo del doctor Proctor y hacer sentadillas. 
 * El tema es que la cantidad que debe hacer tiene que ser un número primo… y como a veces se olvida si un número es primo o no, te pide ayuda para que crees un programa que, dada la cantidad de sentadillas que Ash quiere hacer, devuelva ese mismo número si éste es primo, o el siguiente número primo, el mayor número primo más próximo al ingresado.
 * 
 * Por ejemplo, si Ash ingresa el número 3, la función devuelve el número 3. Si Ash ingresa el número 4, la función devuelve el número 5.
 */

#include <stdio.h>
#include <stdbool.h>

bool es_primo(size_t num, size_t divisor_chequeo)
{
	if (num <= 1) {
		return false;
	}

	if (num % divisor_chequeo == 0) {
		return false;
	} else if (divisor_chequeo * divisor_chequeo > num) {
		return true;
	}

	return es_primo(num, divisor_chequeo + 1);
}

int cantidad_sentadillas(size_t sentadillas_ingresadas)
{
	if (sentadillas_ingresadas <= 1) {
		return 2;
	}

	if (!es_primo(sentadillas_ingresadas, 2)) {
		return cantidad_sentadillas(sentadillas_ingresadas + 1);
	}
	return (int)sentadillas_ingresadas;
}