/* El algoritmo babilónico para el cálculo de la raíz cuadrada de x es muy
 * simple: consiste en seleccionar una estimación inicial de la raíz a calcular
 * (por ejemplo, estimacion = x/2) e iterativamente verificar cuánto se parece
 * el cuadrado de nuestra estimación calculada al número original.
 *
 * Es decir, si la diferencia entre estimacion*estimacion y el número original x
 * difieren menos de un valor arbitrario, una precisión dada, entonces
 * consideramos que obtuvimos la raíz cuadrada del valor x original. A cada paso
 * del algoritmo, la nueva estimación se calcula de la siguiente forma
 * nueva_estimacion = (estimacion + x/estimacion) / 2.
 *
 * Si PRECISION es una constante ya dada, se pide escribir la función que
 * obtenga la raíz cuadrada de un número pasado por parámetro.
 *
 * En caso de no existir la raíz cuadrada real, devolver el valor -1, que
 * también es una constante designada, llamada ERROR.
 */

#include "solucion.h"

double raiz_cuadrada(double valor)
{
	if (valor < 0)
		return ERROR;

	if (valor == 0)
		return 0;

	double estimacion = valor / 2;
	if (valor < 1)
		estimacion = 1;

	double nueva_estimacion = estimacion;
	while (1) {
		nueva_estimacion = (estimacion + valor / estimacion) / 2;

		if ((nueva_estimacion * nueva_estimacion - valor) < PRECISION &&
		    (valor - nueva_estimacion * nueva_estimacion) < PRECISION)
			return nueva_estimacion;

		estimacion = nueva_estimacion;
	}
}