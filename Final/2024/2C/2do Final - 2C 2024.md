# Ejercicio 3
El algoritmo **Kruskal** se utiliza para buscar un árbol de expansion mínimo de un grafo no dirigido ponderado. Se crea un arbol separado para cada vertice y voy tomando las aristas con peso de forma ascendente, si al tomar una arista se genera un ciclo se rechaza, finalmente se unen los arboles.

```txt
  H     D
 / \ /       \
E - B  A - F - G
 \   \ |  / \ /
       C     I

Aristas de peso 1:
  H     D
     /       
E - B  A   F   G

       C     I

Aristas de peso 2:
  H     D
 /   /       \
E - B  A   F   G
         /
       C     I

Aristas de peso 3:
  H     D
 /   /       \
E - B  A   F   G
     \    /
       C     I

Aristas de peso 4:
  H     D
 /   /       \
E - B  A   F   G  (F y G no unimos porque se genera un ciclo)
     \ |  /
       C     I

Aristas de peso 5:
  H     D
 /   /       \
E - B  A   F   G
     \ |  /   /
       C     I

Entonces queda reordenado:
  H      D
 /   /       \
E - B         G
     \         \
      C         I
     / \
    A   F     
```

# Ejercicio 4
Un árbol es un grafo no dirigido, conexo y acíclico. Un ejemplo es el árbol de expancion minima generado por el algoritmo Kruskal del ejercicio anterior.

```python
class Arista:
	def __init__(self, destino, peso):
		self.destino = destino
		self.peso = peso

class Vertice:
	def __init__(self, dato):
		self.aristas = []
		self.dato = dato

class Grafo:
	def __init__(self):
		self.vertices = []
		self.cantidad = 0

def dfs(vertice, visitados):
	visitados.add(vertice)
	for arista in vertice.aristas:
		vecino = arista.destino
		if vecino not in visitados:
			dfs(vecino, visitados)

def es_arbol(grafo):
	visitados = set()
	eliminar_vertice(grafo, grafo.vertices[0])
	dfs(grafo.vertices[0], visitados)
	return len(visitados) == (grafo.cantidad - 1)
```

El algoritmo se implemento como una lista de adyacencia para poder acceder a la cantidad y la lista de vertices del grafo. La idea principal es, ya conociendo la cantidad total de vertices que tiene el grafo, eliminar uno arbitrario y luego verificar si la cantidad es igual a la anterior menos uno. Si es un arbol esto no se va a cumplir, mientras que si es un grafo si gracias a los ciclos que este tiene.

# Ejercicio 5
Un diccionario es una estructura de datos que almacena pares clave-valor, la misma puede ser implementada de varias maneras aunque la mas comun es a traves de un hash. El mostrado es una tabla de hash cerrada ya que los elementos se guardan en un arreglo, en cambio si fuera una tabla de hash abierta el arreglo seria de punteros a un TDA, por lo general se utiliza una lista simplemente enlazada, que guardaria todas las claves hasheadas a ese indice.

Suponiendo que A = 0, B = 1, etc. Se puede deducir, gracias a los datos ya incluidos en la tabla, que la funcion de hash es:
$f(k) = 2k + 1$

```txt
0 [ C;0 ]
1 [ A;1 ]
2 [     ]
3 [ B;3 ]
4 [     ]

Suponiendo que el factor de carga es 0,75:
Inserto <F;3>: (Debo rehashear)
Rehasheo (al doble del tamaño anterior):
0 [     ]
1 [ A;1 ]
2 [ B;3 ]
3 [     ]
4 [     ]
5 [ C;0 ]
6 [ F;3 ]
7 [     ]
8 [     ]
9 [     ]

Inserto <M;1>:
0 [     ]
1 [ A;1 ]
2 [ B;3 ] <- Ocupada, uso probing lineal para buscar posicion libre
3 [ M;1 ]
4 [     ]
5 [ C;0 ]
6 [ F;3 ]
7 [     ]
8 [     ]
9 [     ]

Inserto <C;2>:
0 [     ]
1 [ A;1 ]
2 [ B;3 ]
3 [ M;1 ]
4 [     ]
5 [ C;2 ] -> Puedo guardar el valor anterior en un puntero (*anterior = 0)
6 [ F;3 ]
7 [     ]
8 [     ]
9 [     ]

Inserto <H;3>:
0 [     ]
1 [ A;1 ]
2 [ B;3 ]
3 [ M;1 ]
4 [     ]
5 [ C;2 ]
6 [ F;3 ]
7 [ H;3 ]
8 [     ]
9 [     ]

Elimino B:
0 [     ]
1 [ A;1 ]
2 [  *  ] -> Activo la flag de eliminado
3 [ M;1 ]
4 [     ]
5 [ C;2 ]
6 [ F;3 ]
7 [ H;3 ]
8 [     ]
9 [     ]

Elimino A:
0 [     ]
1 [  *  ] -> Activo la flag de eliminado
2 [  *  ]
3 [ M;1 ]
4 [     ]
5 [ C;2 ]
6 [ F;3 ]
7 [ H;3 ]
8 [     ]
9 [     ]


Inserto <D;1>:
0 [     ]
1 [  *  ]
2 [  *  ]
3 [ M;1 ] <- Ocupada, uso probing lineal para buscar posicion libre
4 [ D;1 ]
5 [ C;2 ]
6 [ F;3 ]
7 [ H;3 ]
8 [     ]
9 [     ]

Inserto <B;2>:
0 [     ]
1 [  *  ]
2 [ B;2 ]
3 [ M;1 ]
4 [ D;1 ]
5 [ C;2 ]
6 [ F;3 ]
7 [ H;3 ]
8 [     ]
9 [     ]
```