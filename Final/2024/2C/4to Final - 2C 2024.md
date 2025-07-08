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
El algoritmo Floyd-Warshall busca los caminos minimos entre todos los pares de vertices. Este utiliza una matriz de distancias en la que, a medida que recorre los vertices, actualiza el valor de las celdas con la menor distancia, que puede ser entre $V_0$ y $V_1$ o conviene desviarse a traves de un $V_2$ tal que el recorrido quedaria $V_0$, $V_2$ y $V_1$.

Para este algoritmo conviene utilizar una matriz de adyacencia para representar el grafo, ya que su estructura es muy similar a la matriz de distancias ($n \cdot n$, donde $n$ es la cantidad de vertices) y ademas contiene los pesos entre vertices. Se debe modificar unicamente que las celdas de la diagonal sean cero y que los ceros restantes pasen a ser infinito.

```python
INF = float('inf')

def preparar_matriz_adyacencia(matriz):
	n = len(matriz)
	for i in range(n):
		for j in range(n):
			if i == j:
				matriz[i][j] = 0
			elif matriz[i][j] == 0:
				matriz[i][j] = INF

def floyd_warshall(matriz):
	n = len(matriz)
	for k in range(n):
		for i in range(n):
			for j in range(n):
				if matriz[i][k] != INF and matriz[k][j] != INF:
					matriz[i][j] = min(matriz[i][j], matriz[i][k] + matriz[k][j])
```

# Ejercicio 5
Un diccionario es una estructura de datos que almacena pares clave-valor, donde cada clave es unica. Este se puede implementar de muchas maneras, aunque la mas comun es a traves de una tabla de hash dado a que tiene una mejor complejidad respecto a una implementacion a traves de una lista simplemente enlazada o un ABB.

Posibles implementaciones:
- Lista simplemente enlazada:
	- Insercion: $O(n)$ en tiempo en caso de no tener un puntero al ultimo elemento, de tenerlo $O(1)$.
	- Busqueda: $O(n)$ ya que se deben recorrer todos los elementos.
	- Colisiones: No aplica porque no se usa hashing.
	- Memoria: 16 bytes * cantidad de nodos en la lista (8 para el puntero al siguiente y 8 para apuntar al dato), sin contar los otros 16 bytes que ocuparia un tipo de dato par (8 para la clave y 8 para el valor).
- Árbol binario de busqueda:
	- Insercion: $O(log(n))$ en caso de que el arbol este balanceado, ya que habria que recorrer las ramas correspondientes hasta encontrar la posicion adecuada.
	- Busqueda: $O(log(n))$ en caso de que el arbol este balanceado, ya que, al igual que la insercion, se debe recorrer las ramas correspondientes hasta encontrar el elemento buscado.
	- Colisiones: No aplica porque no se usa hashing.
	- Memoria: 24 bytes * cantidad de nodos en el arbol (8 para el dato, 8 para el hijo izquierdo y 8 para el derecho), al igual que la lista esta cantidad seria sin contemplar el par al que apunta el dato.
- Tabla de hash:
	- Insercion: $O(1)$ en caso de que la funcion de hash sea deterministica y eficiente.
	- Busqueda: $O(1)$ ya que la funcion de hash devuelve la posicion exacta en donde se encuentra el dato, aunque en caso de haber colision se podria contemplar unos $m$ elementos a recorrer que fueron hasheados en el mismo lugar. Como ese $m$ es muy chico se lo puede distriminar al momento de calcular la complejidad final.
	- Colisiones: Hay dos maneras de resolverlas: mediante un hash abierto o uno cerrado. En el caso del cerrado se utiliza un probing (lineal, cuadratico, etc) para buscar la siguiente posicion libre de la tabla, mientras que para el abierto se inserta al final del TDA elegido.
	- Memoria: Depende de la implementacion, en caso de usar una tabla de hash cerrada serian 16 bytes * capacidad de la tabla, y en caso de usar una flag de eliminacion se agregarian otros 4 bytes ya que es un int de 32 bits (que por lo general sistemas de 64 tambien suelen usar por defecto al menos que sea especificado como int64_t). Si se implementa como un hash abierto serian inicialmente 8 bytes * el tamaño del arreglo de punteros, y luego depende de con que TDA se implementa.