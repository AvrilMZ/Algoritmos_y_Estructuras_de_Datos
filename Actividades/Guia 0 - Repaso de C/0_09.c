/*
 * Ahora que vimos la diferencia entre vector de chars y strings, incluyamos la
 * biblioteca de strings y aprovechémosla!
 *
 * Se reciben tres strings (como avisamos que son strings, se puede asumir que
 * poseen el '\0'). Se pide que el primero se concatene con el segundo, y que se
 * devuelva el resultado de comparar este nuevo string con el tercero. Cuál iría
 * antes en el diccionario? Si el string concatenado aparecería primero o ambos
 * son iguales, se devuelve la letra 'C' . Si el tercer string pasado por
 * parámetro aparecería primero, se devuelve la letra 'S'.
 *
 * Veamos un ejemplo. Recibo los strings "Algo", "ritmo" y "Programación". Si
 * concateno el primer y segundo string, obtengo "Algoritmo". Comparo
 * "Algoritmo" con "Programación" y obtengo que "Algoritmo" debería ir primero
 * en el diccionario, así que debo devolver la letra 'C'.
 *
 * Ya incluimos por vos la librería en solucion.h ;)
 *
 * Ayudita: buscá qué funciones interesantes hay en la biblioteca string.h ;)
 */

#include "solucion.h"

const char IGUALES_O_CONCATENADO_PRIMERO = 'C';
const char STRING3_PRIMERO = 'S';

char ejercicio(char string1[MAX_STRING], char string2[MAX_STRING],
	       char string3[MAX_STRING])
{
	char concatenacion[MAX_STRING * 2];
	strcpy(concatenacion, string1);
	strcat(concatenacion, string2);

	if (strcmp(concatenacion, string3) <= 0)
		return IGUALES_O_CONCATENADO_PRIMERO;
	return STRING3_PRIMERO;
}