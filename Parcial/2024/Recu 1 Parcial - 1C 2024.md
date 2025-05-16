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

La complejidad de mergesort puede ser calculada mediante el teorema maestro ya que su problema se divide siempre en dos partes iguales, en cambio quicksort elige un pivote y realiza tres subdivisiones desiguales que dependen de la posición del pivote elegido, siendo imposible definir un $`b`$ para el teorema.

# Ejercicio 2
Heapsort es un algortimo de ordenamiento que trabaja sobre un heap binario, en donde siempre retira la raiz del mismo y luego la reemplaza con el último elemento. El elemento retirado se lo excuye y considera ordenado, mientras que el reemplazo se lo acomoda realizando sift down. El proceso se repite hasta haber sacado todos los elementos.

```txt
V = [6, 1, 3, 6, 8, 4, 2]

Construyo un heap minimal: (Me pedian de menor a mayor asi que era con un heap maximal)
      1
     / \
  2       3
 / \     / \
8   6   4   6
V = [1, 2, 3, 8, 6, 4, 6]

      6
     / \
  2       3
 / \     /
8   6   4
V = [6, 2, 3, 8, 6, 4] [1]

Sift down:
      2
     / \
  3       4
 / \     /
8   6   6
V = [2, 3, 4, 8, 6, 6] [1]

      6
     / \
  3       4
 / \     
8   6  
V = [6, 3, 4, 8, 6] [2, 1]

Sift down:
      3
     / \
  4       6
 / \     
8   6  
V = [3, 4, 6, 8, 6] [2, 1]

      6
     / \
  4       6
 /   
8  
V = [6, 4, 6, 8] [3, 2, 1]

Sift down:
      4
     / \
  6       6
 /   
8  
V = [4, 6, 6, 8] [3, 2, 1]

      8
     / \
  6       6  
V = [8, 6, 6] [4, 3, 2, 1]

Sift down:
      6
     / \
  6       8  
V = [6, 6, 8] [4, 3, 2, 1]

      8
     /
  6  
V = [8, 6] [6, 4, 3, 2, 1]

Sift down:
      6
     /
  8  
V = [6, 8] [6, 4, 3, 2, 1]

      8
V = [8] [6, 6, 4, 3, 2, 1]

=> V = [8, 6, 6, 4, 3, 2, 1]

```

# Ejercicio 3
```c
```

# Ejercicio 4
Un árbol rojo/negro es similar a un ABB solo con la diferencia de un campo en sus nodos que determina si este es rojo o negro. Ese color se utiliza para seguir ciertas reglas de este TDA y conseguir un árbol balanceado. Las reglas son:
- Un árbol no puede ser todo rojo;
- No pueden haber dos nodos rojos consecutivos;
- La raiz tiene que ser negra;
- Debe haber la misma cantidad de nodos negros en cada rama;
- Las hojas nulas se consideran negras.

```c
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo {
	struct nodo *hijo_izquierdo;
	struct nodo *hijo_derecho;
	bool rojo;
	void *elemento;
} nodo_t;

typedef struct arbol_rn {
	nodo_t *raiz;
	int cant_nodos;
	int (*comparador)(void *, void *);
} arbolrn_t;

bool raiz_negra(nodo_t *raiz) 
{
	if (!raiz) {
		return false;
	}
	return !raiz->roja;
}

bool sin_dos_rojos_consecutivos(nodo_t *nodo, bool padre_rojo) 
{
	if (!nodo) {
		return true;
	}else if (padre_rojo && nodo->rojo) {
		return false;
	}

	if (!sin_dos_rojos_consecutivos(nodo->izq, nodo->rojo)) {
		return false;
	}
	if (!sin_dos_rojos_consecutivos(nodo->der, nodo->rojo)) {
		return false;
	}

	return true;
}

int contar_negros(nodo_t *nodo, int *valido) 
{
	if (!nodo) {
		return 1;
	}

	int izq = contar_negros(nodo->izq, valido);
	int der = contar_negros(nodo->der, valido);

	if (izq != der) {
		*valido = 0;
	}

	if (nodo->rojo) {
		return izq;
	}
	return izq + 1;
}

bool caminos_con_mismos_negros(nodo_t *raiz) 
{
	int valido = 1;
	contar_negros(raiz, &valido);
	return valido;
}

bool arbolrn_valido(arbolrn_t *arbol) 
{
	if (!arbol) {
		return false;
	}

	return raiz_negra(arbol->raiz) && sin_dos_rojos_consecutivos(arbol->raiz, false) && caminos_con_mismos_negros(arbol->raiz);
}
```

# Ejercicio 5
```c
void eliminar_impares_recursivo(char* str, int n) 
{
	if (str[n] == '\0') {
		str[n / 2] = '\0';
		return;
	}
	if (n % 2 == 0) {
		str[n / 2] = str[n];
	}
	eliminar_impares_recursivo(str, n + 1);
}

char* eliminar_impares(char* str) 
{
	if (!str) {
		return NULL;
	}
	eliminar_impares_recursivo(str, 0);
	return str;
}
```
El algoritmo tiene una complejidad $`O(n)`$ en tiempo, siendo $`n`$ la cantidad de caracteres del string. Porque si bien internamente en el procesamiento se omiten los caracteres cuyo indice sea impar, estos se recorren, por lo que es correcto contabilizarlos. En espacio tambien consigue una complejidad $`O(h)`$, siendo $`h`$ la altura de los stackframes.