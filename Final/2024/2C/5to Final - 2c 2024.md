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
Un árbol es un grafo aciclico no dirigido, y conexo. Un ejemplo seria el arbol de expansion minima conseguido gracias al algoritmo Prim o Kruskal del grafo anterior.

```python
class Arista:
	def __init__(self, peso, destino):
		self.peso = peso
		self.destino = destino

class Vertice:
	def __init__(self, dato):
		self.aristas = []
		self.dato = dato

class Grafo:
	def __init__(self):
		self.vertices = {}
		self.cantidad = 0

def dfs(vertice, padre, visitado):
	visitado.add(vertice.dato)
	for arista in vertice.aristas:
		vecino = arista.destino
		if vecino.dato not in visitado:
			if not dfs(vecino, vertice.dato, visitado):
				return False
			elif vecino.dato != padre:
				return False
	return True

def es_arbol(grafo):
	visitado = set()
	nodos = list(grafo.vertices.values())

	if not dfs(nodos[0], None, visitado):
		return False

	if len(visitado) != len(grafo.vertices):
		return False

	return True
```

El algoritmo recorre el grafo, implementado como una lista de adyacencia, mediante DFS (Depth First Search) y verifica si el vecino del nodo actual fue visitado y no es por el que viene (padre), si ocurre eso significa que es un ciclo y devuelve false. Luego se verifica que la lista de visitados tenga la misma longitud que el grafo original, ya que si no la tiene es porque se corto el recorrido en algun momento por la aparicion de un ciclo.

# Ejercicio 5
Un diccionario es una estructura de datos que almacena pares clave-valor, donde las claves son unicas y no nulas. Por otro lado una tabla de hash es una estructura de datos que tambien almacena pares y utiliza una funcion de hash para ubicarlas, ya sea en una tabla o en un TDA de eleccion. La diferencia entre ambos es que un diccionario puede ser implementado de varias maneras, siendo una tabla de hash una de ellas, pero se puede utilizar una lista simplemente enlazada, un arbol binario de busqueda, entre otros.

```c
#include <stdbool.h>
#include <stdlib.h>

const float FACTOR_MAX_CARGA = 0.75;

float calcular_factor_carga(int cantidad, int capacidad) 
{
	return (float)cantidad / (float)capacidad;
}

int calcular_posicion_hash(int clave, int capacidad) 
{
	return clave % capacidad;
}

bool hash_insertar(hash_t *hash, char *clave, void *valor, void **anterior) 
{
	if (!hash || !clave) {
		return false;
	}

	if (calcular_factor_carga(hash->cantidad, hash->capacidad) > FACTOR_MAX_CARGA) {
		rehash(hash);
	}

	int indice = hash->funcion_hash(clave);
	int posicion = calcular_posicion_hash(indice, hash->capacidad);
	int contador_vuelta = 0;

	while (hash->tabla[posicion]) {
		if (strcmp(hash->tabla[posicion].clave, clave) == 0) {
			*anterior = hash->tabla[posicion].valor;
			hash->tabla[posicion].valor = valor;
			return true;
		}

		posicion = (posicion + 1) % hash->capacidad;
		contador_vuelta++;

		if (contador_vuelta == hash->capacidad) {
			return false;
		}
	}

	par_t *par_nuevo = crear_par(clave, valor);
	hash->tabla[posicion] = par_nuevo;
	hash->cantidad++;
	*anterior = NULL;
	return true;
}
```

La funcion para insertear un elemento en una tabla de hash abierta primero en principal verifica que el factor de carga no supere el maximo, de ser asi se debe hacer rehash, luego se calcula la posicion indicada para insertar. En caso de que en esa posicion haya otra clave se recorren linealmente (probing lineal) hasta encontrar una posicion vacia, si la clave ya existe en la tabla se guarda en el puntero "anterior" y se reemplaza con el nuevo valor. Se utiliza un contador para evitar un bucle infinito buscando una posicion vacia, que de igual forma nunca deberia utilizarse, donde si la cantidad de posiciones recorridas es igual a la capacidad de la tabla se debe salir ya que se recorrieron todas las celdas y ninguna esta disponible.