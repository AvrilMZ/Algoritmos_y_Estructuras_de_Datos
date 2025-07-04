# Ejercicio 3


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

# Ejercicio 5
Un diccionario

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