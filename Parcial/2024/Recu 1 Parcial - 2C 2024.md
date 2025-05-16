# Ejercicio 1
El toerema maestro es una fórmula que permite resolver problemas de recurrencia del tipo divide y conquista. Es del formato:

$`F(n) = a \cdot f(\frac{n}{b}) + O(f(n))`$

donde:
- $`a`$ es la cantidad de llamadas recursivas dentro de la función. ($`a >= 1`$)
- $`b`$ es la cantidad por la que se divide el problema. ($`b > 1`$)
- $`f(n)`$ es el costo en tiempo al momento de juntar todo el procesamiento previo.

Una vez planteada se analiza:
- Si $`f(n) = n^{log_b(a)} \Rightarrow f(n) \cdot log(n)`$;
- Si $`f(n) > n^{log_b(a)} \Rightarrow f(n)`$;
- Y si $`f(n) < n^{log_b(a)} \Rightarrow n^{log_b(a)}`$.

Resultando en la complejidad final.

```c
int buscar_menor(int* vector, int tamaño) 
{
	if (tamaño == 1) {
		return vector[0];
	}

	int mitad = tamaño / 2;
	int mitad_izq = buscar_menor(vector, mitad);
	int mitad_der = buscar_menor(vector + mitad, tamaño - mitad);

	if (mitad_izq < mitad_der) {
		return mitad_izq;
	}
	return mitad_der;
}
```
**Complejidad:**

$`F(n) = 2 \cdot f(\frac{n}{2}) + O(1)`$

$`1 < n^{log_2(2)} \Rightarrow n`$

# Ejercicio 2
Un árbol B es una variación del TDA árbol, el cúal almacena una gran cantidad de claves por nodo, a diferencia de un ABB de una clave. Estos cumplen las siguientes caracteristicas:
- Las claves estan ordenadas;
- La cantidad mínima de claves es $`\frac{n}{2}`$, excepto la raiz;
- Un nodo con $`n`$ claves tiene un máximo de $`n + 1`$ descendientes;
- La cantiadad mínima de descendientes es $`\frac{n + 1}{2}`$, excepto hojas y raiz.

```txt
Inserto elementos:
J:
      [ · J · - · - · ]

L:
      [ · J · L · - · ]

A:
      [ · A · J · L · ]

B: (Overflow)
      [ · J · - · - · ]
       /     \
      /   [ · L · - · - · ]
 [ · A · B · - · ]

T:
      [ · J · - · - · ]
       /     \
      /   [ · L · T · - · ]
 [ · A · B · - · ]

M:
      [ · J · - · - · ]
       /     \
      /   [ · L · M · T · ]
 [ · A · B · - · ]

P: (Overflow)
      [ · J · M · - · ]
        /    \   \
       /      \[ · P · T · - · ]
      /        \
     /      [ · L · - · - · ]
[ · A · B · - · ]

R:
      [ · J · M · - · ]
        /    \   \
       /      \[ · P · R · T · ]
      /        \
     /      [ · L · - · - · ]
[ · A · B · - · ]

Luego de insertar los elementos:
      [ · J · M · - · ]
        /    \   \
       /      \[ · P · R · T · ]
      /        \
     /      [ · L · - · - · ]
[ · A · B · - · ]

Elimino L:
      [ · J · P · - · ]
        /    \   \
       /      \[ · R · T · - · ]
      /        \
     /      [ · M · - · - · ]
[ · A · B · - · ]

Elimino M:
      [ · J · R · - · ]
        /    \   \
       /      \[ · T · - · - · ]
      /        \
     /      [ · P · - · - · ]
[ · A · B · - · ]
```

# Ejercicio 3
```c
#include <stdlib.h>
#include <stdbool.h>

typedef struct azul azul_t;

typedef struct rojo {
	azul_t *azul_sig;
	azul_t *azul_ant;
} rojo_t;

struct azul {
	char *letras;
	rojo_t *rojo;
};

int main() 
{
	char letras1[3];
	char letras2[3];
	char letras3[3];
	char letras4[3];

	memcpy(&letras1, "ABC", 3);
	memcpy(&letras2, "DEF", 3);
	memcpy(&letras3, "GHI", 3);
	memcpy(&letras4, "JKL", 3);

	azul_t *puntero = calloc(1, sizeof(azul_t));
	if (!puntero) {
		return -1;
	}
	puntero->letras = letras1;

	azul_t *azul_aux = puntero;
	rojo_t *rojo_aux = puntero->rojo;
	azul_t *azul_previo;
	bool error = false;
	for (int i = 0; i < 3 && !error; i++) {
		rojo_aux = calloc(1, sizeof(rojo_t));
		if (i != 0) {
			rojo_aux->azul_ant = azul_previo;
		}

		azul_previo = azul_aux;
		azul_aux = rojo_aux->azul_sig;
		azul_aux = calloc(1, sizeof(azul_t));
		if (i == 0) {
			azul_aux->letras = letras2;
		} else if (i == 1) {
			azul_aux->letras = letras3;
		} else if (i == 2) {
			azul_aux->letras = letras4;
		}
		

		rojo_aux = azul_aux->rojo;
		if (!rojo_aux || !azul_aux) {
			error = true;
		}

		if (i == 2) {
			rojo_aux = calloc(1, sizeof(rojo_t));
		}
		if (!rojo_aux) {
			error = true;
		}
	}

	if (!error) {
		rojo_aux->azul_ant = puntero;
		puntero->rojo->azul_ant = azul_aux;
	}

	for (int i = 0; i < 4; i++) {
		if (i != 0 && i != 3) {
			azul_aux = rojo_aux->azul_ant;
			rojo_aux = azul_aux->rojo;
		}
		free(rojo_aux);
		free(azul_aux);
	}
	free(puntero->rojo);
	free(puntero);

	return 0;
}
```

# Ejercicio 4
1- Un árbol Rojo/Negro es mas eficiente que uno AVL para insertar, eliminar y buscar datos.  
2- Un algoritmo de ordenamiento nunca puede ser mas eficiente en tiempo que n*log(n).  
3- Insertar al final en una lista enlazada (sin referencia al último nodo) y en un vector dinámico tienen la misma complejidad.  
4- La complejidad de un TDA depende de la implementación.  

1- Falso, ambos tienen distintos criteros para detectar si el árbol esta desbalanceado para luego realizar las rotaciones necesarias, pero son igual de eficientes.  
2- Falso, ya que existen algoritmos de ordenamiento como counting sort con complejidad $`O(n)`$.  
3- Verdadero, ya que para insertar un elemento al final de la lista enlazada habria que recorrer todos los nodos hasta encontrar el ultimo que apunta a NULL, teniendo complejidad $`O(n)`$, y en el caso del vector dinamico, aunque la insersion en sí tiene un coste $`O(1)`$ debido a que se conoce el tamaño, probablemente haya que realocar la memoria en el heap con `realloc`, el cual tiene una complejidad $`O(n)`$.  
4- Verdadero, ya que depende de como fueron implementadas las primitivas y la estructura en si. Un ejemplo seria parte de la afirmacion tres, ya que si una lista enlazada se la implementa sin un puntero al ultimo nodo, al momento de insertar, se deberan recorrer todos hasta encontrar el ultimo haciendolo en tiempo $`O(n)`$, en cambio al tener el puntero se haria en $`O(1)`$.   

# Ejercicio 5
```c
#include <stdlib.h>

typedef struct nodo {
	struct nodo *hijo_izq;
	struct nodo *hijo_der;
	void *elemento;
} nodo_t;

typedef struct abb {
	nodo_t *raiz;
	int cant_nodos;
	int (*comparador)(void *, void *);
} abb_t;

nodo_t *buscar_hoja_cercana(nodo_t *nodo) 
{
	if (!abb) {
		return NULL;
	} else if (!nodo->hijo_izq && !nodo->hijo_der) {
		return nodo;
	}

	nodo_t *izq = buscar_hoja_cercana(nodo->hijo_izq);
	if (izq) {
		return izq;
	}
	return buscar_hoja_cercana(nodo->hijo_der);
}

nodo_t *hoja_cercana_raiz(abb_t *abb) 
{
	if (!abb) {
		return NULL;
	}
	return buscar_hoja_cercana(abb->raiz);
}
```