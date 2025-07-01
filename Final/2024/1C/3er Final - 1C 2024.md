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
  A  | inf |  -
  B  | inf |  -
  C  | inf |  -
  D  | inf |  -
  E  | inf |  -
  F  | inf |  -
  G  |  0  |  -
  H  | inf |  -
  I  | inf |  -
Visitados: []
No visitados: [A, B, C, D, E, F, G, H, I]

  V  |  D  | V.A
  A  | inf |  -
  B  | inf |  -
  C  | inf |  -
  D  | inf |  -
  E  | inf |  -
  F  | inf |  -
  G  |  0  |  -
  H  |  9  |  G
  I  |  1  |  G
Visitados: [G]
No visitados: [A, B, C, D, E, F, H, I]

  V  |  D  | V.A
  A  | inf |  -
  B  | inf |  -
  C  |  6  |  I
  D  | 10  |  H
  E  | inf |  -
  F  |  9  |  I
  G  |  0  |  -
  H  |  9  |  G
  I  |  1  |  G
Visitados: [G, I, H]
No visitados: [A, B, C, D, E, F]

  V  |  D  | V.A
  A  | 11  |  C
  B  | inf |  -
  C  |  6  |  I
  D  | 10  |  H
  E  |  7  |  C
  F  |  9  |  I
  G  |  0  |  -
  H  |  9  |  G
  I  |  1  |  G
Visitados: [G, I, H, D, F, C]
No visitados: [A, B, E]

  V  |  D  | V.A
  A  | 11  |  C    G -> I -> C -> A
  B  | 12  |  E    G -> I -> C -> E -> B
  C  |  6  |  I    G -> I -> C
  D  | 10  |  H    G -> H -> D
  E  |  7  |  C    G -> I -> C -> E
  F  |  9  |  I    G -> I -> F
  G  |  0  |  -    G
  H  |  9  |  G    G -> H
  I  |  1  |  G    G -> I
Visitados: [G, I, H, D, F, C, E, A, B]
No visitados: []
```

# Ejercicio 4
El recorrido **BFS** (Breadth-First Search) es un algoritmo que explora un grafo en anchura, es decir, visita primero todos los vecinos (o nodos adyacentes) de un vértice antes de pasar a los vecinos de esos vecinos. Se implementa utilizando una cola ya que permite ir procesando los nodos en el orden en que se descubren.

```c
#include <stdlib.h>
#include <stdbool.h>

typedef struct vertice {
	void *dato;
	lista_t *adyacentes; // lista de aristas (arista_t)
} vertice_t;

typedef struct arista {
	vertice_t *destino;
	int peso;
} arista_t;

typedef struct grafo {
	lista_t *vertices; // lista de vertices (vertice_t)
	int cantidad;
	bool es_dirigido;
} grafo_t;

int bfs(grafo_t *grafo) 
{
	if (!grafo) {
		return 0;
	}

	cola_t *cola = crear_cola();
	if (!cola) {
		return 0;
	}

	

	cola_destruir();
	
	return cant_visitados;
}
```

# Ejercicio 5
Una tabla de hash cerrada (direccionamiento abierto) permite almacenar pares clave-valor en una tabla, el indice donde se ubican esos elementos es determinado por una funcion de hash, la cual deber ser eficiente y deterministica. A diferencia de una tabla de hash abierto (direccionamiento cerrado/encadenamiento) en caso de hashear una clave y haber una colision se debe buscar el proximo espacio libre, o rehashear en caso de que se supere el factor de carga, en cambio al usar un direccionamiento cerrado se agrega un elemento a la lista/arbol/etc que se este usando de ese indice.  
Para la eliminacion se pueden acudir a dos metodos: tener una flag que determine si esa posicion fue borrada; o desplazar todos los elementos siguientes (hasta encontrar una posicion vacia). Si esto no resulta bien implementado puede afectar la busqueda e insercion ya que se perderian elementos (hasheados en una misma posicion) por esa division generada por ese espacio vacio.