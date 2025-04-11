/*
 * Combinemos ahora arrays con recursividad. Recibimos un array terminado en \0 == 0, y se debe devolver el menor número de ese array.
 * 
 * Por ejemplo, si se recibe el array = [ 1, 3, -2, 14, -50, 0, -100], la respuesta debe ser -50.
 * 
 * Cuidado, se recibe un puntero por parámetro, por lo que se debe verificar que el mismo no es NULL. También es posible que se envié un array vacío. En ambos casos, devolver el valor 0, con la cte ERROR, ya declarada para estos casos ;).
 */

#define ERROR 0

int menor_valor(int *array)
{
	if (!array || *array == 0) {
		return ERROR;
	}

	int numero = menor_valor(array + 1);
	int record;
	if (*array < numero) {
		record = *array;
	} else {
		record = numero;
	}

	return record;
}