# Lista Adyacencia
class Arista:
	def __init__(self, destino, peso):
		self.destino = destino
		self.peso = peso

class Vertice:
	def __init__(self, dato):
		self.aristas = []
		self.cantidad = 0
		self.dato = dato

class Grafo:
	def __init__(self):
		self.vertices = []
		self.cantidad = 0


# DFS (Depth First Search) Recursivo
def dfs_recursivo(vertice, visitados):
	visitados.add(vertice)
	for arista in vertice.aristas:
		vecino = arista.destino
		if vecino not in visitados:
			dfs_recursivo(vecino, visitados)


# BFS (Breadth First Search)
def bfs(grafo):
	visitados = set()
	visitados.add(grafo.vertices[0])
	cola = [grafo.vertices[0]]

	while cola:
		vertice = cola.pop(0)
		for arista in vertice.aristas:
			vecino = arista.destino
			if vecino not in visitados:
				visitados.add(vecino)
				cola.append(vecino)
	
	return visitados


# Grafo bipartito
class Arista_bi:
	def __init__(self, destino):
		self.destino = destino

class Vertice_bi:
	def __init__(self, color, dato):
		self.aristas = []
		self.cantidad = 0
		self.color = color
		self.dato = dato

class Grafo_bi:
	def __init__(self):
		self.vertices = []
		self.cantidad = 0

def dfs_bipartito(vertice, color, visitados):
	visitados.append(vertice)
	vertice.color = color
	for arista in vertice.aristas:
		vecino = arista.destino
		if vecino not in visitados:
			if not dfs_bipartito(vecino, not color, visitados):
				return False
		elif vecino.color is vertice.color:
			return False
	return True

def es_bipartito(grafo):
	visitados = []

	for vertice in grafo.vertices:
		if vertice not in visitados:
			if not dfs_bipartito(vertice, True, visitados):
				return False

	return True


# Orden topologico
def dfs_topo(vertice, visitados, topo):
	visitados.append(vertice)
	for arista in vertice.aristas:
		vecino = arista.destino
		if vecino not in visitados:
			dfs_topo(vecino, visitados, topo)
	topo.append(vertice)

def orden_topologico(grafo):
	visitados = []
	topo = []

	for vertice in grafo.vertices:
		if vertice not in visitados:
			dfs_topo(vertice, visitados, topo)
	
	topo.reverse()
	return topo


# Puntos de Articulacion
def dfs_puntos(vertice, eliminado, visitados):
	visitados.append(vertice)
	for arista in vertice.aristas:
		vecino = arista.destino
		if vecino not in visitados and vecino != eliminado:
			dfs_puntos(vecino, eliminado, visitados)

def puntos_articulacion(grafo):
	puntos = []

	for eliminado in grafo.vertices:
		visitados = []
		for arista in eliminado.aristas:
			vecino = arista.destino
			dfs_puntos(vecino, eliminado, visitados)
		if len(visitados) is not grafo.cantidad - 1:
			puntos.append(eliminado)

	return puntos


# Detectar si es un árbol
def dfs_arbol(vertice, padre, visitados):
	visitados.append(vertice)
	for arista in vertice.aristas:
		vecino = arista.destino
		if vecino not in visitados:
			if not dfs_arbol(vecino, vertice, visitados):
				return False
		elif vecino != padre:
			return False
	return True

def es_arbol(grafo):
	visitados = []
	for vertice in grafo.vertices:
		if vertice not in visitados:
			if not dfs_arbol(vertice, None, visitados):
				return False
	return len(visitados) == grafo.cantidad


# Encontrar todos los caminos simples
# Hacia todos los vertices
def dfs_todos_los_caminos(grafo, actual, visitados, camino, caminos):
	visitados.add(actual)
	camino.append(actual)

	caminos.append(list(camino))

	for vecino in grafo[actual]:
		if vecino not in visitados:
			dfs_todos_los_caminos(grafo, vecino, visitados, camino, caminos)

	camino.pop()
	visitados.remove(actual)

def todos_los_caminos_desde(grafo, inicio):
	caminos = []
	dfs_todos_los_caminos(grafo, inicio, set(), [], caminos)
	return caminos

# Dado un punto de inicio y de fin
def dfs_camino_simple(grafo, actual, destino, visitados, camino, caminos):
	visitados.add(actual)
	camino.append(actual)

	if actual == destino:
		caminos.append(list(camino))
	else:
		for vecino in grafo[actual]:
			if vecino not in visitados:
				dfs_camino_simple(grafo, vecino, destino, visitados, camino, caminos)

	camino.pop()
	visitados.remove(actual)

def caminos_simples(grafo, inicio, fin):
	caminos = []
	dfs_camino_simple(grafo, inicio, fin, set(), [], caminos)
	return caminos


# Verificar si un grafo es completo
def es_grafo_completo(grafo):
	for vertice in grafo.vertices:
		if len(vertice.aristas) != grafo.cantidad - 1:
			return False
	return True


# Dijkstra
def dijkstra(grafo, origen):
	distancia = {}
	padre = {}

	for v in grafo:
		distancia[v] = INF

	distancia[origen] = 0
	padre[origen] = None
	q = heap_crear()
	q.encolar(origen, 0)

	while not q.esta_vacia():
		v = q.desencolar()
		for w in grafo.adyacentes(v):
			if (distancia[v] + grafo.peso(v,w) <  distancia[w]):
				distancia[w] = distancia[v] + grafo.peso(v,w)
				padre[w] = v
				q.encolar(w, distancia[w])

	return padre, distancia


# Floyd-Warshall
INF = 9999

def preparar_matriz(copia_grafo):
	n = len(copia_grafo)
	for i in range(n):
		for j in range(n):
			if (copia_grafo[i][j] == 0 and i != j):
				copia_grafo[i][j] = INF

def floyd_warshall(matriz_distancia):
	n = len(matriz_distancia)
	for v2 in range(n):
		for v0 in range(n):
			for v1 in range(n):
				if matriz_distancia[v0][v2] < INF and matriz_distancia[v2][v1] < INF:
					if matriz_distancia[v0][v2] + matriz_distancia[v2][v1] < matriz_distancia[v0][v1]:
						matriz_distancia[v0][v1] = matriz_distancia[v0][v2] + matriz_distancia[v2][v1]


# Prim
def prim(n, grafo):
	visitado = [False] * n
	mst = []
	heap = [(0, 0, -1)]  # (peso, nodo actual, padre)

	while heap and len(mst) < n - 1:
		peso, u, padre = heapq.heappop(heap)
		if not visitado[u]:
			visitado[u] = True
			if padre != -1:
				mst.append((padre, u, peso))
			for w, v in grafo[u]:
				if not visitado[v]:
					heapq.heappush(heap, (w, v, u))
	return mst


# Kruskal
def encontrar(padre, x):
	while padre[x] != x:
		x = padre[x]
	return x

def unir(padre, x, y):
	px = encontrar(padre, x)
	py = encontrar(padre, y)
	if px != py:
		padre[px] = py
		return True
	return False

def kruskal(n, aristas):
	padre = list(range(n))
	aristas.sort()
	mst = []

	for peso, u, v in aristas:
		if unir(padre, u, v):
			mst.append((u, v, peso))
		if len(mst) == n - 1:
			break
	return mst

