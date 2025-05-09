# Ejercicio 1
## 1A y 1B
Para el primer codigo dado vemos una complejidad $`O(n)`$, donde n es la cantidad de elementos de la pila. Esto es debido a que el codigo se ejecuta mientras haya elementos en la pila para quitarlos, implicando recorrer uno por uno realizando esta operación.  
Luego, para el segundo código, si bien a simple vista parece tener complejidad $`O(n^2)`$ por los dos for anidados, hay que tener en cuenta que dentro del bucle interno se incrementa manualmente la variable `i` cuando `j == 10`. Esto hace que el bucle externo avance más rápido, ya que `i` se incrementa dos veces en esa iteración: una por el for y otra por el `if`. Por lo tanto, la cantidad total de iteraciones del cuerpo interno es menor a $`n * n`$, pero está acotada superiormente por $`O(n^2)`$ que terminaria siendo la complejidad final.  
En ningúno de los dos casos es posible aplicar el teorema maestro ya que no son recursivos.

# Ejercicio 2
## 2A y 2B



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
		return 0;
	}
	nodo1->hijo_izquierdo = ele1;
	strcpy(ele1->letras, "ABC");
	ele1->letra = &texto[0];

	elemento_t *ele2 = crear_elemento();
	if (!ele2) {
		free(ele1);
		free(nodo1);
		return 0;
	}
	nodo1->hijo_derecho = ele2;
	strcpy(ele2->letras, "DEF");
	ele2->letra = &texto[1];

	nodo_t *nodo2 = crear_nodo();
	if (!nodo2) {
		free(ele2);
		free(ele1);
		free(nodo1);
		return 0;
	}
	nodo1->hermano = nodo2;
	nodo2->hijo_izquierdo = ele2;

	elemento_t *ele3 = crear_elemento();
	if (!ele3) {
		free(ele2);
		free(ele1);
		free(nodo2);
		free(nodo1);
		return 0;
	}
	nodo2->hijo_derecho = ele3;
	strcpy(ele3->letras, "GHI");
	ele3->letra = &texto[2];

	nodo_t *nodo3 = crear_nodo();
	if (!nodo3) {
		free(ele3);
		free(ele2);
		free(ele1);
		free(nodo2);
		free(nodo1);
		return 0;
	}
	nodo2->hermano = nodo3;
	nodo3->hijo_izquierdo = ele3;

	elemento_t *ele4 = crear_elemento();
	if (!ele4) {
		free(ele3);
		free(ele2);
		free(ele1);
		free(nodo3);
		free(nodo2);
		free(nodo1);
		return 0;
	}
	nodo3->hijo_derecho = ele4;
	strcpy(ele4->letras, "JKL");
	ele4->letra = &texto[3];

	free(ele4);
	free(ele3);
	free(ele2);
	free(ele1);
	free(nodo3);
	free(nodo2);
	free(nodo1);

	return 0;
}
```

## 3B
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

// Libera la memoria reservada de todos los nodos enlazados.
void liberar_nodos(nodo_t *nodo) 
{
	if (!nodo) {
		return;
	}
	liberar_nodos(nodo->siguiente);
	free(nodo);
	nodo = NULL;
}

// Libera todos los elementos reservados en el arreglo 'lista'.
void liberar_arreglo(void **lista) 
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
		liberar_nodos(nodo1);
		liberar_arreglo(lista);
		return 0;
	}
	nodo2->anterior = nodo1;
	nodo1->siguiente = nodo2;
	nodo2->elemento = lista[3];
	lista[1] = nodo2;

	nodo_t *nodo3 = crear_nodo();
	if (!nodo3) {
		liberar_nodos(nodo1);
		liberar_arreglo(lista);
		return 0;
	}
	nodo3->anterior = nodo2;
	nodo2->siguiente = nodo3;
	nodo3->elemento = lista[0];
	lista[2] = nodo3;

	nodo_t *nodo4 = crear_nodo();
	if (!nodo4) {
		liberar_nodos(nodo1);
		liberar_arreglo(lista);
		return 0;
	}
	nodo4->anterior = nodo3;
	nodo3->siguiente = nodo4;
	nodo1->anterior = nodo4;
	nodo4->elemento = lista[1];
	lista[3] = nodo4;

	liberar_nodos(nodo1);
	liberar_arreglo(lista);

	return 0;
}
```

# Ejercicio 4
## 4A

## 4B


# Ejercicio 5
