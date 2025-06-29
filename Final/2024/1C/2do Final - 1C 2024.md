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
  D  |  2  |  A
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
  D  |  2  |  A
  E  |  5  |  D
  F  | inf |  -
  G  | inf |  -
  H  |  3  |  D
  I  | 10  |  C
Visitados: [A, B, D, C]
No visitados: [E, F, G, H, I]

  V  |  D  | V.A
  A  |  0  |  -
  B  |  1  |  A
  C  |  5  |  A
  D  |  2  |  A
  E  |  5  |  D
  F  |  6  |  H
  G  | 11  |  I
  H  |  3  |  D
  I  | 10  |  C
Visitados: [A, B, D, E, C, H, I]
No visitados: [G, F]

  V  |  D  | V.A
  A  |  0  |  -    A
  B  |  1  |  A    A -> B
  C  |  5  |  A    A -> C
  D  |  2  |  A    A -> D
  E  |  5  |  D    A -> D -> E
  F  |  6  |  H    A -> D -> H -> F
  G  | 11  |  I    A -> C -> I -> G
  H  |  3  |  D    A -> D -> H
  I  | 10  |  C    A -> C -> I
Visitados: [A, B, D, E, C, H, I, F, G]
No visitados: []
```

# Ejercicio 4
```c
#include <stdlib.h>
#include <stdbool.h>

typedef struct vertice {
        void *dato;
} vertice_t;

typedef struct arista {
        vertice_t *vertice1;
        vertice_t *vertice2;
        int peso;
} arista_t;

typedef struct grafo {
        vertice_t *inicial;
        bool es_dirigido;
} grafo_t;

grafo_t *grafo_crear();
bool grafo_insertar(grafo_t *grafo, void *elemento);
bool grafo_insertar_arista(grafo_t *grafo, arista_t *arista);
bool grafo_borrar(grafo_t *grafo, void *elemento);
bool grafo_borrar_arista(grafo_t *grafo, arista_t *arista);
void grafo_destruir(grafo_t *grafo);

vertice_t *buscar_vertice(grafo_t *grafo, ) {

}

bool grafo_insertar_arista(grafo_t *grafo, arista_t *arista) {
        if (!grafo || !arista) {
                return false;
        }

        
}

bool grafo_borrar_arista(grafo_t *grafo, arista_t *arista) {
        if (!grafo || !arista) {
                return false;
        }

}
```

# Ejercicio 5
Un **diccionario** es una estructura de datos que permite almacenar pares clave-valor, donde las claves son únicas y se utilizan para acceder a los valores asociados. Una **tabla de hash**