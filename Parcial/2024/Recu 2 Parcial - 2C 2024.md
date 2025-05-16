# Ejercicio 1
```c
#include <stdbool.h>

bool esta_desordenado(int a, int b, int c) {
   	return !(a <= b && b <= c);
}

int elemento_desordenado(int *vec, int tope) {
	if (tope <= 2) {
		return -1;
	}

	if (tope == 3) {
		if (esta_desordenado(vec[0], vec[1], vec[2])) {
			return vec[1];
		}
		return -1;
	}

	int mitad = tope / 2;
	int izq = elemento_desordenado(vec, mitad + 1);
	if (izq != -1) {
		return izq;
	}

	int der = elemento_desordenado(vec + mitad - 1, tope - mitad + 1);
	return der;
}
```
Para calcular la complejidad se puede plantear el teorema maestro:
$`T(n) = 2 f(\frac{n}{2}) + O(1)`$  
- $`a = 2`$, ya que hay dos llamadas recursivas.
- $`b = 2`$, ya que el vector se divide en dos.
- $`f(n) = 1`$, ya que no hay un coste extra en tiempo al momento de procesar los datos.

Por lo que $`n^1 = n^{log_2 2} \Rightarrow n\cdot log(n)`$

# Ejercicio 2

# Ejercicio 3

# Ejercicio 4
La diferencia de usar una matriz estatica a una dinamica principlamente es donde se almacenam los datos: la estatica en el stack y a dinamica en el heap. Luego, en el heap, la matriz no necesariamente se encuentra en posiciones contiguas de memoria, ya que las celdas pueden estar compuestas de punteros que apuntan a otra fila o columna.

Sin memoria contigua:
```c
int** matriz = malloc(filas * sizeof(int*));
for (int i = 0; i < filas; i++) {
	matriz[i] = malloc(columnas * sizeof(int));
}
```
Con memoria contigua:
```c
int* datos = malloc(filas * columnas * sizeof(int));
int** matriz = malloc(filas * sizeof(int*));
for (int i = 0; i < filas; i++) {
	matriz[i] = datos + i * columnas;
}
```
Al momento de liberar memoria se debe tener en cuenta que tipo de matriz dinamica se realizo, ya que la memoria contigua se liberaria toda junta mientras que los punteros deben recorrer todas sus filas para liberar sus columnas.

# Ejercicio 5
```c

```