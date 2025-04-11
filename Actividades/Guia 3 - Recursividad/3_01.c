/*
 * Empecemos con algo bien sencillo. Al igual que en la guía 0, repaso de C, programamos una pequeña función que servía en la Conjetura de Collatz, ahora vamos a programar una función que implemente la función factorial, muy utilizada en áreas como Probabilidad y Estadística en matemática.
 * Esta función recibe un número entero, y debe devolver el producto de todos los números naturales desde 1 hasta el pasado por parámetro.
 * Por ejemplo, si se recibe el número 5 por parámetro, se debe devolver el número 1 * 2 * 3 * 4 * 5 = 120.
 * 
 * Por definición, el factorial del número 0 es 1. Es decir, 0! = 1. 
 * A su vez, el factorial del número 1 es 1, o sea, 1! = 1.
 * Así que sí, 0! = 1! … cosas de matemática….
 * No es posible calcular el factorial de un número negativo. En caso de recibirlo como parámetro, la función debe devolver el valor -1 (ya fue declarada la constante ERROR en el .h ;) ).
 */

#define ERROR -1

int factorial(int num)
{
	if (num < 0) {
		return ERROR;
	}

	if (num == 0 || num == 1) {
		return 1;
	}

	return num * factorial(num - 1);
}