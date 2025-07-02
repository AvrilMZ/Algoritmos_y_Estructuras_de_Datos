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

Los primeros cinco pasos son preparatorios mientras que los siguientes se repiten hasta visitar el ultimo vertice, generando un loop.

```txt
  V  |  D  | V.A
  A  |  0  |  -
  B  | inf |  -
  C  | inf |  -
  D  | inf |  -
  E  | inf |  -
  F  | inf |  -
  G  | inf |  -
  H  | inf |  -
  I  | inf |  -
Visitados: []
No visitados: [A, B, C, D, E, F, G, H, I]

  V  |  D  | V.A
  A  |  0  |  -
  B  | inf |  -
  C  |  4  |  A
  D  | inf |  -
  E  | inf |  -
  F  |  8  |  A
  G  | inf |  -
  H  | inf |  -
  I  | inf |  -
Visitados: [A]
No visitados: [B, C, D, E, F, G, H, I]

  V  |  D  | V.A
  A  |  0  |  -
  B  |  7  |  C
  C  |  4  |  A
  D  | inf |  -
  E  | 11  |  C
  F  |  6  |  C
  G  | 10  |  F
  H  | inf |  -
  I  | 11  |  F
Visitados: [A, C, F]
No visitados: [B, D, E, G, H, I]

  V  |  D  | V.A
  A  |  0  |  -    A
  B  |  7  |  C    A -> C -> B
  C  |  4  |  A    A -> C
  D  |  8  |  B    A -> C -> B -> D
  E  | 11  |  C    A -> C -> E
  F  |  6  |  C    A -> C -> F
  G  | 10  |  F    A -> C -> F -> G
  H  | 12  |  B    A -> C -> B -> H
  I  | 11  |  F    A -> C -> F -> I
Visitados: [A, C, F, B, D, G, E, I, H]
No visitados: []
```

# Ejercicio 4
El **orden topologico** procesa los vertices de un grafo aciclico de forma tal que si el grafo contiene la arista dirigida a un vertice entonces el nodo inicial aparece antes que el de destino, en otras palabras se utiliza para secuenciar todos los pasos para que no haya ninguna dependencia.

Un ejemplo de orden topologico seria el plan de estudios de una carrera, ya que esta diseñado de manera que no hayan problemas con correlativas a materias en caso de seguirlo.

```c
#include <stdlib.h>
#include <stdbool.h>

typedef struct vertice {
	lista_t *aristas;
	void *dato;
} vertice_t;

typedef struct arista {
	vertice_t *destino;
	int peso;
} arista_t;

typedef struct grafo {
	lista_t *vertices;
	int cantidad;
} grafo_t;

bool esta_visitado(vertice_t *v, vertice_t **visitados, int cant) 
{
	for (int i = 0; i < cant; i++) {
		if (visitados[i] == v) {
			return true;
		}
	}
	return false;
}

void dfs_recursivo(vertice_t *v, vertice_t **visitados, int *cant_visitados, vertice_t **topo, int *tope_topo) 
{
	if (esta_visitado(v, visitados, *cant_visitados))
		return;

	visitados[(*cant_visitados)++] = v;

	lista_iterador_t *it = lista_iterador_crear(v->aristas);
	while (lista_iterador_quedan_elementos_por_recorrer(it)) {
		arista_t *arista = lista_iterador_obtener_elemento(it);
		dfs_recursivo(arista->destino, visitados, cant_visitados, topo, tope_topo);
		lista_iterador_proxima_iteracion(it);
	}
	lista_iterador_destruir(it);

	topo[(*tope_topo)++] = v;
}

void invertir_arreglo(vertice_t **arr, int tope) 
{
	for (int i = 0; i < tope / 2; i++) {
		vertice_t *aux = arr[i];
		arr[i] = arr[tope - 1 - i];
		arr[tope - 1 - i] = aux;
	}
}

vertice_t *orden_topo(grafo_t *grafo) 
{
	if (!grafo) {
		return;
	}

	vertice_t **visitados = calloc(grafo->cantidad, sizeof(vertice_t *));
	if (!visitados) {
		return NULL;
	}

	vertice_t **topo = calloc(grafo->cantidad, sizeof(vertice_t *));
	if (!topo) {
		free(visitados);
		return NULL;
	}

	int cant_visitados = 0;
	int tope_topo = 0;

	lista_iterador_t *it = lista_iterador_crear(grafo->vertices);
	while (lista_iterador_quedan_elementos_por_recorrer(it)) {
		vertice_t *v = lista_iterador_obtener_elemento(it);
		if (!esta_visitado(v, visitados, cant_visitados)) {
			dfs_recursivo(v, visitados, &cant_visitados, topo, &tope_topo);
		}
		lista_iterador_proxima_iteracion(it);
	}
	lista_iterador_destruir(it);

	invertir_arreglo(topo, tope_topo);
	free(visitados);
	return topo;
}
```

```python
def dfs_recursivo(grafo, vertice, visitados, topologico):
	visitados[vertice] = True
	for vecino in grafo[vertice]:
		if vecino not in visitados:
			dfs_recursivo(grafo, vecino, visitados, topologico)
	topologico.append(vertice)

def topologico(grafo):
	visitados = {}
	topologico = []
	for vertice in grafo.keys():
		if vertice not in visitados:
			dfs_recursivo(grafo, vertice, visitados, topologico)
	topologico.reverse()
	return topologico
```

En la implementacion que utiliza el recorrido dfs para visitar todos los vertices del grafo, a medida que los visita los agrega a un vector. Tambien se usa un vector para almacenar el recorrido en profundidad, pero gracias a que fue implementada recursivamente se guarda desde el ultimo vertice visitado hasta el primero, es asi que debemos invertir el orden, resultando en un arreglo con el orden topologico del grafo dado.

# Ejercicio 5
a. Un diccionario es un tipo de dato utilizado para almacenar pares clave-valor, este puede ser implementado de varias maneras. Una de ellas es mediante un hash el cual utiliza una funcion de hash para ubicar los pares en la tabla. Si dos elementos de distintas claves hashean en una misma posicion ocurre una colision, la cual se puede solucionar de dos maneras:
- Hash cerrado (direccionamiento abierto): Se sigue iterando sobre la tabla utilizando un probing elegido, por ejemplo en caso de usar un probing lineal se sigue recorriendo hasta encontrar un a posicion vacia.
- Hash abierto (direccionamiento cerrado): En este caso se utiliza un TDA a eleccion para almacenar las claves, por lo general una lista simplemente enlazada. Se crea un arreglo que apunta cada uno a una lista propia, por lo que en caso de que dos claves distintas hashen a una misma posicion no tiene importancia ya que seria solo agregar un elemento a la lista.

b. Optar por una resolucion de colisiones depende de como se decide implementar el diccionario, por ejemplo en caso de querer implementarlo con un ABB o una lista simplemente enlazada no se "hashea" ningun elemento a una posicion en especifica, por lo que no ocurriria nunca una colision, simplemente se añade el par.

c.
Si lo implemento con un hash abierto (suponiendo alguna funcion de hash que de estos resultados): 
```txt
| 0 | → [ ("D", [ ("B", 3), ("C", 1) ]) ]
| 1 | → [ ("A", [ ("B", 2), ("C", 4) ]), ("C", [ ("A", 4), ("D", 1) ]) ]
| 2 | → [ ]
| 3 | → [ ("B", [ ("A", 2), ("D", 3) ]) ]
| 4 | → [ ]
```
La complejidad para acceder a los vecinos seria $O(1)$ ya que son datos que se encuentran guardados junto la clave buscada (hashear una clave es constante), en caso de querer recorrer todos los vecinos seria $O(n)$, siendo $n$ la cantidad de vecinos que tiene el vertice.