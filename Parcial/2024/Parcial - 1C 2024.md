# Ejercicio 1
## 1A
Para el primer codigo dado vemos una complejidad $`O(n)`$, donde n es la cantidad de elementos de la pila. Esto es debido a que el codigo se ejecuta mientras haya elementos en la pila para quitarlos, implicando recorrer uno por uno realizando esta operación.  
Luego, para el segundo código, si bien a simple vista parece tener complejidad $`O(n^2)`$ por los dos for anidados, hay que tener en cuenta que dentro del bucle interno se incrementa manualmente la variable `i` cuando `j == 10`. Esto hace que el bucle externo avance más rápido, ya que `i` se incrementa dos veces en esa iteración: una por el for y otra por el `if`. Por lo tanto, la cantidad total de iteraciones del cuerpo interno es menor a $`n * n`$, pero está acotada superiormente por $`O(n^2)`$ que terminaria siendo la complejidad final.  
En ningúno de los dos casos es posible aplicar el teorema maestro ya que no son recursivos.

# Ejercicio 2
## 2A
Quicksort es un algoritmo de ordenamiento del tipo divide y conquista el cual sigue los siguientes pasos:  
1. Se elige un elemento X de la lista L de elementos al que se le llama pivote.
2. Se particiona la lista L en tres listas:
	- L1 - contiene todos los elementos de L menos X que sean menores.
	- L2 - elemento X
	- L3 - contiene todos los elementos de L menos X que sean mayores.
3. Se repiten los primeros dos pasos sobre L1 y L3.
4. Se unen todas las soluciones para formar la lista ordenada final.

```txt
V = [2, 3, 5, 0, 2, 1, 9, 7]

Se toma el último elemento siempre como pivote:
    [2, 3, 5, 0, 2, 1]                      [7]            [9]
  [0]       [1]      [2, 3, 5, 2]
                 [2, 2]        [3, 5]
	                         [3]    [5]

Entonces uniendo todos los vectores unitarios (a excepcion de alguno con valores repetidos):
	[0] + [1] + [2, 2] + [3] + [5] + [7] + [9]
	=> V = [0, 1, 2, 2, 3, 5, 7, 9]
```

# Ejercicio 3
## 3A
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETRAS 4

typedef struct elemento {
	char letras[MAX_LETRAS];
	char *letra;
} elemento_t;

typedef struct nodo {
	struct nodo *hermano;
	elemento_t *hijo_izquierdo;
	elemento_t *hijo_derecho;
} nodo_t;

// Devuelve un puntero a la memoria reservada para un 'nodo_t'.
nodo_t *crear_nodo() 
{
	nodo_t *nodo = calloc(1, sizeof(nodo_t));
	if (!nodo) {
		return NULL;
	}
	return nodo;
}

// Devuelve un puntero a la memoria reservada para un 'elemento_t'.
elemento_t *crear_elemento() 
{
	elemento_t *ele1 = calloc(1, sizeof(elemento_t));
	if (!ele1) {
		return NULL;
	}
	return ele1;
}

int main() 
{
	char texto[5] = "ABCD\0";

	nodo_t *nodo1 = crear_nodo();
	if (!nodo1) {
		return 0;
	}

	elemento_t *ele1 = crear_elemento();
	if (!ele1) {
		free(nodo1);
		nodo1 = NULL;
		return 0;
	}
	nodo1->hijo_izquierdo = ele1;
	strcpy(ele1->letras, "ABC");
	ele1->letra = &texto[0];

	elemento_t *ele2 = crear_elemento();
	if (!ele2) {
		free(ele1);
		ele1 = NULL;
		free(nodo1);
		nodo1 = NULL;
		return 0;
	}
	nodo1->hijo_derecho = ele2;
	strcpy(ele2->letras, "DEF");
	ele2->letra = &texto[1];

	nodo_t *nodo2 = crear_nodo();
	if (!nodo2) {
		free(ele2);
		ele2 = NULL;
		free(ele1);
		ele1 = NULL;
		free(nodo1);
		nodo1 = NULL;
		return 0;
	}
	nodo1->hermano = nodo2;
	nodo2->hijo_izquierdo = ele2;

	elemento_t *ele3 = crear_elemento();
	if (!ele3) {
		free(ele2);
		ele2 = NULL;
		free(ele1);
		ele1 = NULL;
		free(nodo2);
		nodo2 = NULL;
		free(nodo1);
		nodo1 = NULL;
		return 0;
	}
	nodo2->hijo_derecho = ele3;
	strcpy(ele3->letras, "GHI");
	ele3->letra = &texto[2];

	nodo_t *nodo3 = crear_nodo();
	if (!nodo3) {
		free(ele3);
		ele3 = NULL;
		free(ele2);
		ele2 = NULL;
		free(ele1);
		ele1 = NULL;
		free(nodo2);
		nodo2 = NULL;
		free(nodo1);
		nodo1 = NULL;
		return 0;
	}
	nodo2->hermano = nodo3;
	nodo3->hijo_izquierdo = ele3;

	elemento_t *ele4 = crear_elemento();
	if (!ele4) {
		free(ele3);
		ele3 = NULL;
		free(ele2);
		ele2 = NULL;
		free(ele1);
		ele1 = NULL;
		free(nodo3);
		nodo3 = NULL;
		free(nodo2);
		nodo2 = NULL;
		free(nodo1);
		nodo1 = NULL;
		return 0;
	}
	nodo3->hijo_derecho = ele4;
	strcpy(ele4->letras, "JKL");
	ele4->letra = &texto[3];

	free(ele4);
	ele4 = NULL;
	free(ele3);
	ele3 = NULL;
	free(ele2);
	ele2 = NULL;
	free(ele1);
	ele1 = NULL;
	free(nodo3);
	nodo3 = NULL;
	free(nodo2);
	nodo2 = NULL;
	free(nodo1);
	nodo1 = NULL;

	return 0;
}
```

## 3B (MAL -> REVISAR)
```c
#include <stdio.h>
#include <stdlib.h>

#define TAM_LISTA 4

typedef struct nodo {
	struct nodo *anterior;
	struct nodo *siguiente;
	void *elemento;
} nodo_t;

// Devuelve un puntero al 'nodo_t' reservado.
nodo_t *crear_nodo() {
	nodo_t *nodo = calloc(1, sizeof(nodo_t));
	if (!nodo) {
		return NULL;
	}
	return nodo;
}

// Libera todos los elementos reservados en el arreglo 'lista'.
void liberar_arreglo(nodo_t **lista) 
{
	if (!lista) {
		return;
	}

	for (int i = 0; i < TAM_LISTA; i++) {
		free(lista[i]);
	}
	free(lista);
	*lista = NULL;
}

int main() 
{
	void **lista = calloc(TAM_LISTA, sizeof(void *));
	if (!lista) {
		return 0;
	}

	nodo_t *nodo1 = crear_nodo();
	if (!nodo1) {
		liberar_arreglo(lista);
		return 0;
	}
	nodo1->elemento = lista[2];
	lista[0] = nodo1;

	nodo_t *nodo2 = crear_nodo();
	if (!nodo2) {
		liberar_arreglo(lista);
		free(nodo1);
		return 0;
	}
	nodo2->anterior = nodo1;
	nodo1->siguiente = nodo2;
	nodo2->elemento = lista[3];
	lista[1] = nodo2;

	nodo_t *nodo3 = crear_nodo();
	if (!nodo3) {
		liberar_arreglo(lista);
		free(nodo1);
		free(nodo2);
		return 0;
	}
	nodo3->anterior = nodo2;
	nodo2->siguiente = nodo3;
	nodo3->elemento = lista[0];
	lista[2] = nodo3;

	nodo_t *nodo4 = crear_nodo();
	if (!nodo4) {
		liberar_arreglo(lista);
		free(nodo1);
		free(nodo2);
		free(nodo3);
		return 0;
	}
	nodo4->anterior = nodo3;
	nodo3->siguiente = nodo4;
	nodo1->anterior = nodo4;
	nodo4->elemento = lista[1];
	lista[3] = nodo4;

	liberar_arreglo(lista);
	free(nodo1);
	free(nodo2);
	free(nodo3);
	free(nodo4);

	return 0;
}
```

# Ejercicio 4
## 4A
La linea que falta mostrar por pantalla es la de postorden. Para saber cuales serian sus valores de salida podemos reconstruir el árbol usando la salida de preorden y respetando el orden de la salida de inorden:
```txt
Árbol original:
   0
  / \
 1   9
  \   \
  6    13
 /     / \
8    18   25
```
Por lo que la salida postorden seria [8, 6, 1, 18, 25, 13, 9, 0], ya que se sigue la logica IDN (hijo izquierda, hijo derecha, nodo).


# Ejercicio 5
```c
void swap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

void bubble_sort(int arreglo[], int tope)
{
	if (tope == 1) {
		return;
	}
	
	int contador = 0;
	for (int i = 0; i < tope - 1; i++) {
		if (arreglo[i] > arreglo[i + 1]) {
			swap(&arreglo[i], &arreglo[i + 1]);
			contador++;
		}
	}

	if (contador == 0) {
		return;
	}

	bubble_sort(arreglo, tope - 1);
}
```