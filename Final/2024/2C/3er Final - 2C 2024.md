# Ejercicio 3
**Dijkstra** se utiliza para determinar el camino mas corto dado un vertice de origen hacia el resto. Este algoritmo sirve para grafos pesados y no funciona para grafos con aristas de peso negativo. Se siguen los siguientes pasos:
1. Se elige el vertice V sobre el cual se quiera aplizar el algoritmo.
2. Se crean dos listas de nodos, una lista para los nodos visitados y otra para los no visitados.
3. Se crea una tabla de tres columnas: vertice; distancia minima V; y el nodo anterior por el cual llego.
4. Se toma el vertice V como vertice inicial y se calcula su distancia a si mismo, que es cero.
5. Se actualiza la tabla, en la cual todas las distancias de los demas vertices a V se marcan como infinito.
6. Se visita el vertice no visitado con menor distancia conocida desde el vertice V.
7. Se calcula la distancia entre los vertices sumando los pesos de cada una con la distancia de V.
8. Si la distancia calculada de los vertices conocidos es menor a la que esta en la tabla se actualiza y tambien los verices desde donde se llego.
9. Se pasa el vertice V a la lista de verices visitados.
10. Se continua con el vertice no visitado con menor distancia desde este.

```txt

```

# Ejercicio 4
```python
def bfs(grafo, inicio):
	visitados = set()
	cola = deque([inicio])

	while cola:
		nodo = cola.pop(0)
		if nodo not in visitados:
			visitados.add(nodo)
			cola.extend(grafo[nodo])

	return visitados
```

El algoritmo realiza un recorrido BFS (Breadth First Search) el cual recorre el grafo a lo ancho y es justo lo que se buscaria aca, ya que a medida que mas niveles se vayan recorriendo el pesos de las aristas irian incrementando, por lo que recorrer primero todas las del nivel y luego seguir seria lo correcto. La solucion no seria unica, ya que hay varios nodos vecinos que tienen el mismo peso, asi que dependeria de por cual de ellos comenzaria.

Una salida seria: [A, D, C, F, G, I, B, E, H]  
D, C y F con distancia 1, G e I con distancia 2, y B, E y H con distancia 3.

# Ejercicio 5
Un diccionario es una estructura de datos que almacena pares clave-valor, donde las claves son unicas. Este puede ser implementado de distintas maneras aunque la mas común es a traves de una tabla de hash. Una tabla de hash es una estructura de datos que utiliza pares clave-valor y los almacena una tabla (hash cerrado) o utiliza un arreglo donde cada celda apunta a otra estructura de datos, que por lo general se utiliza una lista simplemente enlazada. La diferencia entre ambos es que un diccionario puede ser implementado como se necesite y no sigue una estructura tradicional, sino que solo se mantiene la logica de un par como tipo de dato, en cambio en una tabla de hash es una implementacion posible de un diccionario.

```c
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct par {
	char *clave;
	void *valor;
} par_t;

typedef struct hash {
	lista_t **tabla;
	int cant_indices;
} hash_t;

bool hash_insertar(hash_t *hash, char *clave, void *valor) 
{
	if (!hash || !clave) {
		return false;
	}

	par_t *nuevo = calloc(1, sizeof(par_t));
	if (!nuevo) {
		return false;
	}
	nuevo->valor = valor;

	size_t largo = strlen(clave) + 1;
	nuevo->clave = calloc(largo, sizeof(char));
	if (!nuevo->clave) {
		free(nuevo);
		return false;
	}
	memcpy(nuevo->clave, clave, largo);

	int posicion = funcion_hash(clave);
	int indice = posicion % hash->cant_indices;
	if (lista_insertar(hash->tabla[indice], nuevo)) {
		return true;
	}

	free(nuevo->clave);
	free(nuevo);
	return false;
}
```

Para esta funcion principalmente se implementa el struct `hash_t` con un arreglo de punteros a listas simplemente enlazadas y un contador de indices que esta tiene. La logica es principalmente la misma que un hash cerrado pero mas sencilla, ya que no habria que contemplar ninguna colision. Primero se crea el `par_t` correspondiente al clave-valor a insertar, luego se calcula el indice de la lista que corresponde agregar el elemento, y finalmente se inserta al final de la misma.