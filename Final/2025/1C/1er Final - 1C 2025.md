# Ejercicio 3
Dijkstra es un algoritmo para determinar el camino minimo, dado un vertice de origen, hacia el resto de los vertices de un grafo ponderado. 

Inicialmente se crea una tabla con tres columnas: una que enumera todos los vertices; otra para marcar la distancia minima (donde el vertice inicial va a tener escrito cero); y por ultimo una para señalar el ultimo vertice por el que se fue para alcanzar esa distancia. Luego se crean tambien dos arreglos: uno para los verices no visitados (que inicialmente estan todos); y otro para los visitados.

Una vez que se crea el ambiente de trabajo se siguen los siguientes pasos:
1. Se visita en vertice inicial. Eso implica pasarlo a la lista de visitados, anotar las distancias hacia sus adyacentes (solo en caso de que sea menor a la ya escrita), y desde que vertice se viene.
2. Se continua visitando el vertice cuya distacia minima sea la menor y no haya sido visitado.
3. Para el resto de los vertices se repiten los pasos pero al momento de anotar las distancias se suma la distancia minima acumulada que indica su fila.

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
  B  |  5  |  A
  C  |  3  |  A
  D  |  7  |  A
  E  | inf |  -
  F  | inf |  -
  G  | inf |  -
  H  | inf |  -
  I  | inf |  -
Visitados: [A]
No visitados: [B, C, D, E, F, G, H, I]

  V  |  D  | V.A
  A  |  0  |  -
  B  |  5  |  A
  C  |  3  |  A
  D  |  7  |  A
  E  | inf |  -
  F  | inf |  -
  G  | inf |  -
  H  | inf |  -
  I  | inf |  -
Visitados: [A, C]
No visitados: [B, D, E, F, G, H, I]

  V  |  D  | V.A
  A  |  0  |  -
  B  |  5  |  A
  C  |  3  |  A
  D  |  7  |  A
  E  |  8  |  B
  F  |  9  |  B
  G  | inf |  -
  H  | inf |  -
  I  | inf |  -
Visitados: [A, C, B]
No visitados: [D, E, F, G, H, I]

  V  |  D  | V.A
  A  |  0  |  -
  B  |  5  |  A
  C  |  3  |  A
  D  |  7  |  A
  E  |  8  |  B
  F  |  9  |  B
  G  | inf |  -
  H  | inf |  -
  I  | inf |  -
Visitados: [A, C, B, D]
No visitados: [E, F, G, H, I]

  V  |  D  | V.A
  A  |  0  |  -
  B  |  5  |  A
  C  |  3  |  A
  D  |  7  |  A
  E  |  8  |  B
  F  |  9  |  B
  G  | inf |  -
  H  | inf |  -
  I  |  17 |  E
Visitados: [A, C, B, D, E]
No visitados: [F, G, H, I]

  V  |  D  | V.A
  A  |  0  |  -
  B  |  5  |  A
  C  |  3  |  A
  D  |  7  |  A
  E  |  8  |  B
  F  |  9  |  B
  G  |  12 |  F
  H  |  10 |  F
  I  |  17 |  E
Visitados: [A, C, B, D, E, F]
No visitados: [G, H, I]

  V  |  D  | V.A
  A  |  0  |  -
  B  |  5  |  A
  C  |  3  |  A
  D  |  7  |  A
  E  |  8  |  B
  F  |  9  |  B
  G  |  12 |  F
  H  |  10 |  F
  I  |  17 |  E
Visitados: [A, C, B, D, E, F, H]
No visitados: [G, I]

  V  |  D  | V.A
  A  |  0  |  -
  B  |  5  |  A
  C  |  3  |  A
  D  |  7  |  A
  E  |  8  |  B
  F  |  9  |  B
  G  |  12 |  F
  H  |  10 |  F
  I  |  15 |  G
Visitados: [A, C, B, D, E, F, H, G]
No visitados: [I]

  V  |  D  | V.A
  A  |  0  |  -    A
  B  |  5  |  A    A -> B
  C  |  3  |  A    A -> C
  D  |  7  |  A    A -> D
  E  |  8  |  B    A -> B -> E
  F  |  9  |  B    A -> B -> F
  G  |  12 |  F    A -> B -> F -> G
  H  |  10 |  F    A -> B -> F -> H
  I  |  15 |  G    A -> B -> F -> G -> I
Visitados: [A, C, B, D, E, F, H, G, I]
No visitados: []
```

# Ejercicio 4
Los puntos de articulacion son nodos que si se eliminan del grafo me terminan quedando componentes conexas separadas.

```python
def dfs(grafo, vertice, eliminado, visitado):
	visitado.add(vertice)
	for vecino in grafo[vertice]:
		if vecino != eliminado and vecino not in visitado:
			dfs(grafo, vecino, eliminado, visitado)

def vertices_articulacion(grafo):
	puntos = set()
	nodos = list(grafo.keys())

	for eliminado in nodos:
		visitado = set()

		inicio = None
		for siguiente in nodos:
			if siguiente != eliminado:
				inicio = siguiente
				break

		if inicio is not None:
			dfs(grafo, inicio, eliminado, visitado)
			if len(visitado) < len(grafo) - 1:
				puntos.add(eliminado)

	return puntos
```

El algoritmo toma un vertice del grafo, lo considero como "eliminado" y luego realizo un recorrido DFS por todos los vertices restantes y verifico si en alguno la cantidad recorrida es distinta a la inicial menos uno, si lo es se agrega el "eliminado" a la lista de puntos de articulacion.

# Ejercicio 5
Un diccionario es una estructura de datos que almacena pares clave-valor, donde las claves son unicas y no nulas. Se utiliza en casos donde se desee almacenar datos asociados a una clave, siendo un metodo comodo ya que con tan solo buscar la clave puedo obtener el bloque asociado. Este puede ser implementado de muchas maneras (queda a criterio del programador) aunque la mas comun es a traves de una tabla de hash, que puede ser abierto o cerrado. En caso de un hash abierto (direccionamiento cerrado) se crea un arreglo de punteros a un TDA elegido (siendo el mas comun una lista simplemente enlazada) y se almacenan los datos cuya posicion fue hasheada en ese indice del arreglo. La estructura en C seria, en caso de usar una lista simplemente enlazada:

```c
typedef struct par {
	char *clave;
	void *valor;
} par_t;

typedef struct hash {
	lista_t **tabla;
	int tamaño;
	lista_t *orden_insercion;
} hash_t;
```

Donde cada elemento de las listas va a contener un tipo de dato `par_t`.

Algunas operaciones a explicar:
- Insercion: La insercion es directa ya que gracias a la funcion de hash se obtiene la posicion exacta de a que lista insertar de la tabla. Ademas se utiliza la primitiva de lista `lista_insertar()` que por tener un puntero al ultimo elemento tambien es constante la insercion. Se puede optar para mejorar la eficiencia que, llegado a un tamaño una lista, se rehashee el tamaño de la tabla asi luego tener mejor tiempo en busqueda.
	- Complejidad: En tiempo $O(1)$ gracias a lo mencionado previamente, en caso de hacer rehash $O(n)$ debido a que hay que reubicar todos los elementos.
- Eliminacion: Se hashea la posicion donde esta la clave a eliminar y se itera sobre la lista correspondiente hasta encontrarlo.
	- Complejidad: En tiempo $O(m)$ siendo $m$ la cantidad de elementos de esa lista.
- Iteracion: Se itera por cada elemento de cada lista de la tabla linealmente, o en caso de querer iterar por orden de insercion se usa directamente en la lista especifica.
	- Complejidad: En tiempo $O(n)$ siendo $n$ la cantidad total de elementos del hash.
- Busqueda: Al igual que la eliminacion, se hashea la posicion de la clave a buscar y se itera por los elementos de la lista correspondiente hasta encontrarlo.
	- Complejidad: En tiempo $O(m)$ siendo $m$ la cantidad de elementos de la lista.