# Ejercicio 1
```c
#include <stdbool.h>

void insertar_elemento(int arr[], int *tope, int elemento) 
{
	if (!arr) {
		return;
	}

	arr[*tope] = elemento;
	(*tope)++;

	bool acomodado = false;
	int actual = *tope - 1;
	while (actual > 0 && !acomodado) {
		int padre = (actual - 1) / 2;
		if (arr[actual] <= arr[padre]) {
			acomodado = true;
		} else {
			int temp = arr[actual];
			arr[actual] = arr[padre];
			arr[padre] = temp;

			actual = padre;
		}
	}
}

int eliminar_raiz(int arr[], int *tope) 
{
	if (!arr || *tope == 0) {
		return;
	}
	
	int max = arr[0];
	arr[0] = arr[*tope - 1];
	(*tope)--;

	int actual = 0;
	bool acomodado = false;
	while (!acomodado) {
		int izq = 2 * actual + 1;
		int der = 2 * actual + 2;
		int mayor = actual;

		if (izq < *tope && arr[izq] > arr[mayor]) {
			mayor = izq;
		}

		if (der < *tope && arr[der] > arr[mayor]) {
			mayor = der;
		}

		if (mayor == actual) {
			acomodado = true;
		} else {
			int temp = arr[actual];
			arr[actual] = arr[mayor];
			arr[mayor] = temp;

			actual = mayor;
		}
	}
	
	return max;
}
```
La función `insertar_elemento` inserta el elemento pasado en la ultima hoja y luego desde ahi se realiza sift up hasta ordenarlo. Esto implica comparar con los elementos padres de la rama e insercambiar posicion en caso que no cumplan con el orden. Por otro lado la función `eliminar_raiz` elimina la raiz del árbol y sube en su lugar el elemento en la ultima hoja, luego desde ahi se realiza sift down hasta ordenarlo en el árbol.

**Complejidad:**
- `insertar_elemento`: $`log(n)`$ ya que en el peor de los casos debe recorrer todos los elementos de una rama del árbol.
- `eliminar_raiz`: $`log(n)`$ ya que en el peor de los casos debe recorrer todos los elementos de una rama del árbol.

# Ejercicio 2
Quicksort es un algoritmo de ordenamiento del tipo divide y conquista el cual sigue los siguientes pasos:  
1. Se elige un elemento X de la lista L de elementos al que se le llama pivote.
2. Se particiona la lista L en tres listas:
	- L1 - contiene todos los elementos de L menos X que sean menores.
	- L2 - elemento X
	- L3 - contiene todos los elementos de L menos X que sean mayores.
3. Se repiten los primeros dos pasos sobre L1 y L3.
4. Se unen todas las soluciones para formar la lista ordenada final.

```txt
V = [6, 1, 3, 6, 8, 4, 2]

Se toma el último elemento siempre como pivote:
    [1]            [2]            [6, 3, 6, 8, 4]
                               [3]     [4]      [6, 6, 8]
                                           [6, 6]       [8]

Entonces uniendo todos los vectores unitarios (a excepcion de alguno con valores repetidos):
	[1] + [2] + [3] + [4] + [6, 6] + [8]
	=> V = [1, 2, 3, 4, 6, 6, 8]
```

# Ejercicio 3
Un AVL es un árbol autobalanceado, este contiene un campo llamado "factor de balanceo" el cual mantiene valores de -1, 0 o 1, en caso de ser mayor a dos, habria que reequilibrarlo haciendo rotaciones simples o compuestas dependiendo el caso hasta conseguir los parámetros válidos. Esto garantiza busquedas en tiempo $`log(n)`$, a diferencia de un ABB que no garantiza estar balanceado por lo que sus busquedas con de $`O(n)`$.

```txt
V = [6, 1, 3, 7, 8, 9, 1, 2]

Inserto 6:
6

Inserto 1:
1
 \
  6

Inserto 3:
  3
 / \
1   6

Inserto 7:
  3
 / \
1   6
     \
      7

Inserto 8:
  3
 / \
1   7
   / \
  6   8

Inserto 9:
  3
 / \
1   7
   / \
  6   8
       \
        9

Inserto 1 (Se toma la convencion de insertar a la izquierda repetidos):
    3
   / \
  1   7
 /   / \
1   6   8
         \
          9

Inserto 2:
     3
    / \
  1     7
 / \   / \
1   2 6   8
           \
            9
```

# Ejercicio 4
```c
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct rojo {
	int numeros[3];
	struct rojo *siguiente;
} rojo_t;

int main() 
{
	rojo_t ***vec_principal = calloc(4, sizeof(rojo_t *));
	if (!***vec_principal) {
		return -1;
	}

	bool error = false;
	for (int i = 0; i < 4 && !error; i++) {
		**vec_principal[i] = calloc(i + 1, sizeof(rojo_t *));
		if (!**vec_principal[i]) {
			error = true;
		}
	}

	if (error) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < i + 1; j++) {
				free(*vec_principal[i][j]);
			}
			free(**vec_principal[i]);
		}
		free(***vec_principal);
		return -1;
	}

	vec_principal[0][0] = calloc(1, sizeof(rojo_t));
	vec_principal[0][0]->siguiente = calloc(1, sizeof(rojo_t));
	rojo_t *nodo2 = vec_principal[0][0]->siguiente;
	nodo2->siguiente = calloc(1, sizeof(rojo_t));
	rojo_t *nodo3 = nodo2->siguiente;
	nodo3->siguiente = calloc(1, sizeof(rojo_t));
	rojo_t *nodo4 = nodo3->siguiente;
	if (!*vec_principal[0][0] || !nodo2 || !nodo3 || !nodo4) {
		free(nodo4);
		free(nodo3);
		free(nodo2);
		free(vec_principal[0][0])
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < i + 1; j++) {
				free(*vec_principal[i][j]);
			}
			free(**vec_principal[i]);
		}
		free(***vec_principal);
		return -1;
	}

	memcpy(&vec_principal[0][0]->letras, 123, 3);
	memcpy(&nodo2, 123, 3);
	memcpy(&nodo3, 456, 3);
	memcpy(&nodo4, 789, 3);

	*vec_principal[1][0] = nodo2;
	*vec_principal[1][1] = vec_principal[0][0];

	*vec_principal[2][0] = nodo3;
	*vec_principal[2][1] = nodo2;
	*vec_principal[2][2] = nodo1;

	*vec_principal[3][0] = nodo4;
	*vec_principal[3][1] = nodo3;
	*vec_principal[3][2] = nodo2;
	*vec_principal[3][3] = nodo1;

	free(nodo4);
	free(nodo3);
	free(nodo2);
	free(vec_principal[0][0])
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < i + 1; j++) {
			free(*vec_principal[i][j]);
		}
		free(**vec_principal[i]);
	}
	free(***vec_principal);

	return 0;
}
```

# Ejercicio 5
```c
const int NO_REPETIDO = 0;

char buscar(char* inicio, char* actual) {
	if (*actual == '\0') {
		if (*inicio == '\0') {
			return NO_REPETIDO;
		} else {
			return buscar(inicio + 1, inicio + 2);
		}
	}

	if (*inicio == *actual) {
		return *inicio;
	} else {
		return buscar(inicio, actual + 1);
	}
}

char primer_caracter_repetido(char* string) {
	return buscar(string, string + 1);
}
```

La complejidad seria $`O(n^2)`$ ya que por cada letra se recorre todo el string. Esta complejidad no se podria calcular con el teorema maestro ya que el problema no se divide, por lo que $`b`$ no cumpliria con la condicion de ser mayor a uno.