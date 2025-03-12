/*
 * Empecemos con algo simple, pero que vas a tener que hacer mucho a lo largo de
 * la cursada: recorrer un vector y a los elementos de ese vector, aplicarles
 * una operación. Aprovechemos y repasemos los diferentes tipos de datos que C
 * provee. El primero es int, que se usa para representar números enteros. Acá
 * te dejamos la firma de una función que recibe un vector de 10 enteros y su
 * tope. Debe devolver la suma de los elementos del vector.
 */

#define MAX_ELEMENTOS 10

/*
 * Devuelve la suma de los elementos del vector, desde la posición 0 hasta el
 * tope.
 */
int suma_de_elementos(int vector[MAX_ELEMENTOS], int tope)
{
	int suma_total = 0;
	for (int i = 0; i < tope; i++) {
		suma_total += vector[i];
	}
	return suma_total;
}