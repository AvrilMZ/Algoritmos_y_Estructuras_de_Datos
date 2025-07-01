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
  F  |  0  |  -
  G  | inf |  -
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
  F  |  0  |  -
  G  | 10  |  F
  H  | inf |  -
  I  |  8  |  F
Visitados: [F]
No visitados: [A, B, C, D, E, G, H, I]

  V  |  D  | V.A
  A  | inf |  -
  B  | inf |  -
  C  | 13  |  I
  D  | inf |  -
  E  | inf |  -
  F  |  0  |  -
  G  |  9  |  I
  H  | 18  |  G
  I  |  8  |  F
Visitados: [F, I, G]
No visitados: [A, B, C, D, E, H]

  V  |  D  | V.A
  A  | 18  |  C
  B  | inf |  -
  C  | 13  |  I
  D  | 19  |  H
  E  | 16  |  C
  F  |  0  |  -
  G  |  9  |  I
  H  | 18  |  G
  I  |  8  |  F
Visitados: [F, I, G, C, H]
No visitados: [A, B, D, E]

  V  |  D  | V.A
  A  | 18  |  C
  B  | 19  |  A
  C  | 13  |  I
  D  | 19  |  H
  E  | 16  |  C
  F  |  0  |  -
  G  |  9  |  I
  H  | 18  |  G
  I  |  8  |  F
Visitados: [F, I, G, C, H, E, A, D]
No visitados: [B]

  V  |  D  | V.A
  A  | 18  |  C    F -> I -> C -> A
  B  | 19  |  A    F -> I -> C -> A -> B 
  C  | 13  |  I    F -> I -> C
  D  | 19  |  H    F -> I -> G -> H -> D
  E  | 16  |  C    F -> I -> C -> E
  F  |  0  |  -    F
  G  |  9  |  I    F -> I -> G
  H  | 18  |  G    F -> I -> G -> H
  I  |  8  |  F    F -> I
Visitados: [F, I, G, C, H, E, A, D, B]
No visitados: []
```

# Ejercicio 4
Una **matriz de adyacencia** es una manera de representar un grafo, al igual que una lista de adyacencia. La matriz es cuadrada de tamaño (cant. vertices) * (cant. vertices) y sigue los pasos:
1. Me paro en el vertice.
2. Me fijo desde ese cuantas aristas conectan con otro vertice.
3. Completo la matriz.  
En caso de que el grafo sea no dirigido queda una matriz simetrica, si la traza no es igual a cero entonces el grafo no es simple y si el grafo es ponderado en vez de guardar la cantidad de conexiones guarda el peso.

Para el caso de una **lista de adyacencia** se siguen la misma logica que una matriz de adyacencia solo que se utiliza una lista simplemente enlazada. Cada arista posee su propia lista donde guarda a que vertices esta unida.  
Ambas se utilizan para representar lo mismo, aunque la matriz puede tener un mejor uso analitico y la lista uno practico ya que la implementacion con la lista es mucho mas grafica y mas sencilla de utilizar al momento de pensar un algoritmo.

```c
#define CANT_VERTICES 5

typedef struct valor {
	int vertice;
	int peso;
} valor_t;

lista_t **matriz_a_lista(int matriz[CANT_VERTICES][CANT_VERTICES]) 
{
	if (!matriz) {
		return NULL;
	}

	lista_t **lista = calloc(CANT_VERTICES, sizeof(lista_t *));
	for (int i = 0; i < CANT_VERTICES; i++) {
		lista[i] = lista_crear();

		for (int j = 0; j < CANT_VERTICES; j++) {
			if (matriz[i][j] != 0) {
				valor_t *dato = calloc(1, sizeof(valor_t));
				dato->vertice = j;
				dato->peso = matriz[i][j];
				lista_insertar(lista[i], dato);
			}
		}
	}

	return lista;
}
```

Este algoritmo tiene una complejidad $O(n)$, siendo $n$ la cantidad de elementos totales en la matriz, ya que al momento de crear la lista asociada al vertice correspondiente se recorre la fila añadiendo solo los valores ponderados correspondientes, resultando en un unico recorrido.

# Ejercicio 5
Suponiendo que el factor de carga es 0,75:
```txt
0 [     ]
1 [     ]
2 [     ]
3 [     ]

f(66) = 2(66) - 5 = 127 % 4 = 3
0 [     ]
1 [     ]
2 [     ]
3 [ B;2 ]

f(67) = 2(67) - 5 = 129 % 4 = 1
0 [     ]
1 [ C;1 ]
2 [     ]
3 [ B;2 ]

f(65) = 2(65) - 5 = 125 % 4 = 1
0 [     ]
1 [ C;1 ] -> Ocupado, busco la siguiente posicion vacia
2 [ A;8 ]
3 [ B;2 ]

f(74) = 2(74) - 5 = 143 % 4 = 3 (Supera factor de carga)
0 [     ]
1 [ C;1 ]
2 [ A;8 ]
3 [ B;2 ]

Rehash (Duplico tamaño de tabla anterior y rehasheo claves anteriores)
0 [ J;3 ]
1 [ C;1 ]
2 [     ]
3 [     ]
4 [     ]
5 [ A;8 ]
6 [     ]
7 [ B;2 ]

Elimino M (no pasa nada porque no existe)
0 [ J;3 ]
1 [ C;1 ]
2 [     ]
3 [     ]
4 [     ]
5 [ A;8 ]
6 [     ]
7 [ B;2 ]

Elimino B
0 [ J;3 ]
1 [ C;1 ]
2 [     ]
3 [     ]
4 [     ]
5 [ A;8 ]
6 [     ]
7 [  *  ] -> Activo flag de eliminado

Elimino A
0 [ J;3 ]
1 [ C;1 ]
2 [     ]
3 [     ]
4 [     ]
5 [  *  ] -> Activo flag de eliminado
6 [     ]
7 [  *  ]

f(74) = 2(74) - 5 = 143 % 8 = 7
0 [ J;1 ] -> Puedo guardar el valor anterior en un puntero (*anterior = 3)
1 [ C;1 ]
2 [     ]
3 [     ]
4 [     ]
5 [  *  ]
6 [     ]
7 [  *  ] -> Eliminado, sigo buscando

f(65) = 2(65) - 5 = 125 % 8 = 5
0 [ J;1 ]
1 [ C;1 ]
2 [     ]
3 [     ]
4 [     ]
5 [ A;8 ]
6 [     ]
7 [  *  ]
```