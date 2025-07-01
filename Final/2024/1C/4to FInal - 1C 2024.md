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
  B  |  1  |  A
  C  |  5  |  A
  D  |  5  |  A
  E  | inf |  -
  F  | inf |  -
  G  | inf |  -
  H  | inf |  -
  I  | inf |  -
Visitados: [A]
No visitados: [B, C, D, E, F, G, H, I]

  V  |  D  | V.A
  A  |  0  |  -
  B  |  1  |  A
  C  |  5  |  A
  D  |  4  |  B
  E  |  6  |  B
  F  | inf |  -
  G  | inf |  -
  H  | 10  |  D
  I  | 10  |  C
Visitados: [A, B, C, D]
No visitados: [E, F, G, H, I]

  V  |  D  | V.A
  A  |  0  |  -
  B  |  1  |  A
  C  |  5  |  A
  D  |  4  |  B
  E  |  6  |  B
  F  | 18  |  I
  G  | 11  |  I
  H  | 10  |  D
  I  | 10  |  C
Visitados: [A, B, C, D, E, H, I]
No visitados: [F, G]

  V  |  D  | V.A
  A  |  0  |  -
  B  |  1  |  A    A -> B
  C  |  5  |  A    A -> C
  D  |  4  |  B    A -> B -> D
  E  |  6  |  B    A -> B -> E
  F  | 18  |  I    A -> C -> I -> F
  G  | 11  |  I    A -> C -> I -> G
  H  | 10  |  D    A -> B -> D -> H
  I  | 10  |  C    A -> C -> I
Visitados: [A, B, C, D, E, H, I, G, F]
No visitados: []
```

# Ejercicio 4
El algoritmo Floyd-Warshall se utiliza para encontrar el camino minimo entre todos los vertices de un grafo ponderado. Este usa una matriz de distancias cuyo tamaño es (cant. vertices) * (cant.vertices). Se siguen los siguientes pasos:
1. Tomo un vertice $V_0$ y otro par de vertices $V_1$ y $V_2$.
2. Me quedo con la menor distancia entre $V_1$ & $V_2$ y $V_1$ & $V_0$ & $V_2$, en otras palabras estoy analizando si me conviene ir directo o desvierme por otro vertice.

Lo implemento usando una representacion para el grafo de listas de adyacencia:
```c
#include <stdlib.h>

#define INFINITO -1

typedef struct vertice {
	lista_t *aristas;
	void *dato;
} vertrice_t;

typedef struct arista {
	vertice_t *destino;
	int peso;
} arista_t;

typedef struct grafo {
	lista_t *vertices;
	int cantidad;
} grafo_t;

int **floyd_warshall(grafo_t *grafo) 
{
	if (!grafo) {
		return NULL;
	}

	int **matriz = calloc(grafo->cantidad, sizeof(int *));
	if (!matriz) {
		return NULL;
	}

	for (int i = 0; i < grafo->cantidad; i++) {
		*matriz[i] = calloc(grafo->cantidad, sizeof(int));
		if (!*matriz[i]) {
			free(matriz);
			return NULL;
		}
	}



	return matriz;
}
```

# Ejercicio 5
Suponiendo que el factor de carga es 0,75:
```txt
[   ]
[   ]
[   ]
[   ]

f(65) = 3(65) - 1 = 194 % 4 = 2
[     ]
[     ]
[ A;3 ]
[     ]

f(68) = 3(68) - 1 = 203 % 4 = 3
[     ]
[     ]
[ A;3 ]
[ D;6 ]

f(71) = 3(71) - 1 = 212 % 4 = 0
[ G;9 ]
[     ]
[ A;3 ]
[ D;6 ]

f(74) = 3(74) - 1 = 221 % 4 = 1 (supera factor de carga)
[ G;9 ]
[     ]
[ A;3 ]
[ D;6 ]

Rehash (duplicando el tamaño de la tabla anterior y hasheando nuevamente las claves):
[     ]
[     ]
[ A;3 ]
[ D;6 ]
[ G;9 ]
[ J;3 ]
[     ]
[     ]

f(77) = 3(77) - 1 = 230 % 8 = 6
[     ]
[     ]
[ A;3 ]
[ D;6 ]
[ G;9 ]
[ J;3 ]
[ M;1 ]
[     ]

Borro B (No existe asi que no pasa nada):
[     ]
[     ]
[ A;3 ]
[ D;6 ]
[ G;9 ]
[ J;3 ]
[ M;1 ]
[     ]

Borro G:
[     ]
[     ]
[ A;3 ]
[ D;6 ]
[  *  ] <- Activo la flag de eliminado
[ J;3 ]
[ M;1 ]
[     ]

Borro A:
[     ]
[     ]
[  *  ] <- Activo la flag de eliminado
[ D;6 ]
[  *  ]
[ J;3 ]
[ M;1 ]
[     ]

f(68) = 3(68) - 1 = 203 % 8 = 3
[     ]
[     ]
[  *  ]
[ D;1 ] <- Puedo guardar el valor anterior en un puntero (*anterior = 6)
[  *  ]
[ J;3 ]
[ M;1 ]
[     ]
```