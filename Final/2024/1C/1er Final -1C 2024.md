# Ejercicio 3
**Dijkstra** se utiliza para determinar el camino mas corto dado un vertice de origen hacia el resto. Este algoritmo sirve para grafos pesados y no funciona para grafos con aristas de peso negativo. Se siguen los siguientes pasos:
1. Se elige el vertice V sobre el cual se quiera aplizar el algoritmo.
2. Se crean dos listas de nodos, una lista para los nodos visitados y otra para los no visitados.
3. Se crea una tabla de tres columnas: vertice; distancia minima V; y el nodo anterior por el cual llego.
4. Se toma el vertice V como vertice inicial y se calcula su distancia a si mismo, que es cero.
5. Se actualiza la tabla, en la cual todas las distancias de los demas vertices a V se marcan como infinito.
6. Se visita el vertice no visitado con menor distancia conocida desde el primer vertice V, ya que la distancia es cero y las demas infinito.
7. Se calcula la distancia entre los vertices sumando los pesos de cada una con la distancia de V.
8. Si la distancia calculada de los vertices conocidos es menor a la que esta en la tavla se actualiza y tambien los verices desde donde se llego.
9. Se pasa el vertice V a la lista de verices visitados.
10. Se continua con el vertice no visitado con menor distancia desde este.

Los primeros cinco pasos son preparatorios mientras que los siguientes se repiten hasta visitar el ultimo vertice, generando un loop.

```txt
  V  |  D  | V.A
  A  | inf |  -
  B  | inf |  -
  C  |  0  |  -
  D  | inf |  -
  E  | inf |  -
  F  | inf |  -
  G  | inf |  -
  H  | inf |  -
  I  | inf |  -
Visitados: []
No visitados: [A, B, C, D, E, F, G, H, I]

  V  |  D  | V.A
  A  |  4  |  C
  B  | inf |  -
  C  |  0  |  -
  D  | inf |  -
  E  |  1  |  C
  F  |  2  |  C
  G  | inf |  -
  H  | inf |  -
  I  | inf |  -
Visitados: [C]
No visitados: [A, B, D, E, F, G, H, I]

  V  |  D  | V.A
  A  |  4  |  C
  B  |  8  |  E
  C  |  0  |  -
  D  |  7  |  A
  E  |  1  |  C
  F  |  2  |  C
  G  | 10  |  F
  H  |  2  |  E
  I  |  7  |  F
Visitados: [C, A, E, F]
No visitados: [B, D, G, H, I]

  V  |  D  | V.A
  A  |  4  |  C    C -> A
  B  |  4  |  H    C -> E -> H -> B
  C  |  0  |  -    C
  D  |  6  |  H    C -> E -> H -> D
  E  |  1  |  C    C -> E
  F  |  2  |  C    C -> F
  G  |  9  |  I    C -> F -> I -> G
  H  |  2  |  E    C -> E -> H
  I  |  7  |  F    C -> F -> I
Visitados: [C, A, E, F, D, B, H, G, I]
No visitados: []
```

# Ejercicio 4
```c
char *primer_repetido(char **vector) {
        char *repetido;

        return repetido;
}
```

# Ejercicio 5
Un **diccionario** es una estructura de datos que permite almacenar pares clave-valor, donde las claves son únicas y se utilizan para acceder a los valores asociados. Existen varias formas de implementar un diccionario, entre ellas:
- **Tabla de hash**: Utiliza una función de hash para mapear las claves a índices en un arreglo.
	- Ventajas: Acceso rápido a los valores, en promedio $O(1)$.
	- Desventajas: Puede requerir un mayor tamaño de tabla para evitar demasiadas colisiones y la función de hash debe ser deterministica y eficiente para que la complejidad no resulte en $O(n)$.
- **Árbol binario de búsqueda**: Almacena los pares clave-valor en un árbol, donde las claves se organizan de manera que los elementos del subárbol izquierdo son menores que los del subárbol derecho.
	- Ventajas: Permite búsquedas eficientes en tiempo $O(log(n))$.
	- Desventajas: En promedio es menos eficiente en tiempo que una tabla de hash y requiere estar balanceado para mantener la eficiencia y no resultar en $O(n)$, además de que en caso de estar implementado recursivamente puede generar un stack overflow si el árbol es muy grande.

```c

```