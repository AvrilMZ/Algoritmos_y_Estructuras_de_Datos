# Ejercicio 1
El teorema maestro es una formula que nos permite resolver problemas de recurrencia del tipo divide y conquista. El mismo tiene la forma:

$`T(n) = a \cdot T(\frac{n}{b}) + O(f(n))`$

donde:
- $`a`$ es la cantidad de llamadas recursivas ($`a >= 1`$);
- $`b`$ es la cantidad por la que se divide el problema ($`b > 1`$);
- $`f(n)`$ es el costo en tiempo al momento de juntar todo el procesamiento previo.

Una vez planteada se analiza:
- Si $`f(n) = n^{log_b(a)} \Rightarrow f(n) \cdot log(n)`$;
- Si $`f(n) > n^{log_b(a)} \Rightarrow f(n)`$;
- Y si $`f(n) < n^{log_b(a)} \Rightarrow n^{log_b(a)}`$.

Resultando en la complejidad final.

```c
#include <stdlib.h>

typedef struct salida {
	void *minimo;
	void *maximo;
} salida_t;

void *recorrer_y_obtener_minimo_y_maximo(void **vec, int tope, int (*cmp)(void*, void*), salida_t *salida)
{
	if (!vec || tope <= 0 || !salida) {
		return NULL;
	} else if (tope == 1) {
		if (cmp(vec[0], salida->minimo) < 0) {
			salida->minimo = vec[0];
		}
		if (cmp(vec[0], salida->maximo) > 0) {
			salida->maximo = vec[0];
		}
		return vec[0];
	}

	int mitad = tope / 2;

	recorrer_y_obtener_minimo_y_maximo(vec, mitad, cmp, salida);
	recorrer_y_obtener_minimo_y_maximo(vec + mitad, tope - mitad, cmp, salida);

	return salida->minimo;
}

salida_t obtener_minimo_y_maximo(void **vec, int tope, int (*cmp)(void*, void*)) 
{
	salida_t max_min;
	max_min.minimo = NULL;
	max_min.maximo = NULL;

	if (!vec || tope <= 0) {
		return max_min;
	}

	max_min.minimo = vec[0];
	max_min.maximo = vec[0];

	recorrer_y_obtener_minimo_y_maximo(vec, tope, cmp, &max_min);
	return max_min;
}
```
La funcion principal `obtener_minimo_y_maximo` se le pasa un vector generico con su tope y un comparador por ser un arreglo generico. Se implementa una funcion auxiliar llamada `recorrer_y_obtener_minimo_y_maximo` la cual divide el arreglo en mitades hasta llegar a un elemento, luego con el comparador se fija si es mayor al maximo o menor al minimo almacenados en `salida` (inicialmente ambos son el primer elemento del arreglo), si lo son los reemplaza.

**Complejidad:**  
Planteo el teorema maestro:

$`T(n) = 2 \cdot T(\frac{n}{2}) + O(1)`$

- $`a = 2`$ porque hay dos llamadas recursivas.
- $`b = 2`$ porque el vector se divide en mitades.
- $`f(n) = 1`$ ya que la comparacion de elementos es constante.

Por lo que finalmente $`n^0 < n^{log_2 2} \Rightarrow n`$

# Ejercicio 2
Heapsort es un algortimo de ordenamiento que trabaja sobre un heap binario, en donde siempre retira la raiz del mismo y luego la reemplaza con el último elemento. El elemento retirado se lo excuye y considera ordenado, mientras que el reemplazo se lo acomoda realizando sift down. El proceso se repite hasta haber sacado todos los elementos.

**Complejidad**  
La complejidad de heap sort es $`O(n \cdot log(n))`$, esto es gracias a que se sacan $`n`$ elementos y por cada uno se realiza un sift down de complejidad $`log(n)`$.

```txt
V = [4, 5, 9, 8, 7, 6, 5]

Construyo un heap minimal:
      4
     / \
  5       5
 / \     / \
8   7   6   9
V = [4, 5, 5, 8, 7, 6, 9]

      9
     / \
  5       5
 / \     /
8   7   6   
V = [9, 5, 5, 8, 7, 6] [4]

Sift down:
      5
     / \
  5       6
 / \     /
8   7   9   
V = [5, 5, 8, 7, 6, 9] [4]

      9
     / \
  5       6
 / \     
8   7     
V = [9, 5, 8, 7, 6] [5, 4]

Sift down:
      5
     / \
  6       9
 / \     
8   7     
V = [5, 6, 9, 8, 7] [5, 4]

      7
     / \
  6       9
 /    
8     
V = [7, 6, 9, 8] [5, 5, 4]

Sift down:
      6
     / \
  7       9
 /    
8     
V = [6, 7, 9, 8] [5, 5, 4]

      8
     / \
  7       9
V = [8, 7, 9] [6, 5, 5, 4]

Sift down:
      7
     / \
  8       9
V = [7, 8, 9] [6, 5, 5, 4]

      9
     / 
  8 
V = [9, 8] [7, 6, 5, 5, 4]

Sift down:
      8
     / 
  9 
V = [8, 9] [7, 6, 5, 5, 4]


  9 
V = [9] [8, 7, 6, 5, 5, 4]

=> V = [9, 8, 7, 6, 5, 5, 4]
```

# Ejercicio 3
```c
#include <stdlib.h>
#include <string.h>

typedef struct azul azul_t;

typedef struct rojo {
	azul_t *azul;
	char *letra;
} rojo_t;

struct azul {
	int numeros[3];
	azul_t *siguiente;
	rojo_t *rojo;
} azul_t;

int main() 
{
	azul_t *azul1 = calloc(1, sizeof(azul_t));
	if (!azul1) {
		return -1;
	}

	azul1->siguiente = calloc(1, sizeof(azul_t));
	if (!azul1->siguiente) {
		free(azul1);
		return -1;
	}

	azul1->siguiente->siguiente = calloc(1, sizeof(azul_t));
	if (!azul1->siguiente->siguiente) {
		free(azul1->siguiente);
		free(azul1);
		return -1;
	}
	azul1->siguiente->siguiente->siguiente = azul1;

	rojo_t arr_rojos[3];
	char letras[3];
	memcpy(&letras, "ALG", 3);
	
	azul1->numeros[0] = 1;
	azul1->numeros[1] = 2;
	azul1->numeros[2] = 3;

	azul1->siguiente->numeros[0] = 4;
	azul1->siguiente->numeros[1] = 5;
	azul1->siguiente->numeros[2] = 6;

	azul1->siguiente->siguiente->numeros[0] = 7;
	azul1->siguiente->siguiente->numeros[1] = 8;
	azul1->siguiente->siguiente->numeros[2] = 9;

	azul1->rojo = &arr_rojos[1];
	azul1->siguiente->rojo = &arr_rojos[2];
	azul1->siguiente->siguiente->rojo = &arr_rojos[0];

	arr_rojos[0].letra = &letras[0];
	arr_rojos[1].letra = &letras[1];
	arr_rojos[2].letra = &letras[2];

	arr_rojos[0].azul = azul1->siguiente;
	arr_rojos[1].azul = azul1;
	arr_rojos[2].azul = azul1->siguiente->siguiente;
	
	free(azul1->siguiente->siguiente);
	free(azul1->siguiente);
	free(azul1);

	return 0;
}
```

# Ejercicio 4
1- Un árbol binario es ordenado de izquierda a derecha.  
2- Un árbol rojo/negro es también AVL.  
3- Counting sort es mas eficiente para ordenar que quicksort.  
4- Los algoritmos del tipo divide y conquista no pueden tener complejidad lineal.  

1- Falso, un arbol binario no tiene ordenados los nodos bajo ningun criterio, un arbol binario de busqueda si.  
2- Falso, un AVL lleva un campo para el factor de equilibrio por lo que seria imposible que un arbol rojo/negro se comporte igual, sabiendo que ademas la logica para mantener el arbol balanceado es completamente distinta.  
3- Verdadero, ya que quicksort en el peor de los casos tiene una complejidad $`O(n^2)`$ o $`n \cdot log(n)`$ en promedio, $`n`$ la cantidad de elementos del arreglo, dependiendo del privote elegido, mientras que counting sort $`O(n + k)`$ siendo $`n`$ la cantidad de elementos del arreglo y $`k`$ el valor mayor posible en el arreglo.  
4- Falso, ya que depende de como se divide el problema y que procesamiento se hace internamente.

# Ejercicio 5
```c
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo {
	struct nodo *nodo_siguiente;
	void *dato;
} nodo_t;

typedef struct lista {
	nodo_t *primero;
	nodo_t *ultimo;
	int cantidad;
} lista_t;

lista_t *lista_crear();
bool lista_insertar(lista_t *lista, void *elemento);
void lista_destruir(lista_t *lista);

lista_t *conseguir_elementos_multiplos_de_tres(nodo_t *nodo, size_t indice)
{
	if (!nodo) {
		return lista_crear();
	}

	lista_t *resultado = conseguir_elementos_multiplos_de_tres(nodo->nodo_siguiente, indice + 1);
	if (!resultado) {
		return NULL;
	}

	if (indice % 3 == 0) {
		if (!lista_insertar(resultado, nodo->dato)) {
			lista_destruir(resultado);
			return NULL;
		}
	}

	return resultado;
}

lista_t *elementos_multiplos_de_tres(lista_t *lista) 
{
	if (!lista) {
		return NULL;
	}
	return conseguir_elementos_multiplos_de_tres(lista->primero, 0);
}
```
Se implementa principalmente la funcion `elementos_multiplos_de_tres` que utiliza `conseguir_elementos_multiplos_de_tres` para procesar los multiplos de tres recursivamente. Esta trabaja sobre los strackframes ya que inicialmente se plantea como condicion de corte que, cuando se llegue al ultimo nodo, se cree una nueva lista para empezar a guardarlos. Se mira si el indice es multiplo de tres, si lo es se guarda el nodo en la nueva lista.

**Complejidad:**  
No se puede usar el teorema maestro ya que no es un problema del tipo divide y conquista, aunque se puede ver que la cota superior en este caso seria $`O(n)`$, siendo $`n`$ la cantidad de nodos, ya que se recorre la lista solo una vez.