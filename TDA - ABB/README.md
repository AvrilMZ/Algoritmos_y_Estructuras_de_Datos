# TDA Lista, Pila y Cola

- **Alumno:** [Avril Victoria Morfeo Zerbi](https://github.com/AvrilMZ) 
- **Legajo:** 112563 
- **Mail:** amorfeo@fi.uba.ar


### Instrucciones para correr el proyecto:

- Para compilar las pruebas:
```bash
make pruebas_alumno
```

- Para ejecutar las pruebas:
```bash
./pruebas_alumno
```

- Para ejecutar con Valgrind:
```bash
make valgrind-alumno
```

<br>

##  Funcionamiento
<div style="text-align: justify">

El progrmama implementa un **árbol binario de búsqueda** (ABB), este tipo de estructura de datos permite almacenar elementos de manera ordenada, ya que los elementos del subárbol izquierdo son menores con respecto al subárbol derecho.  Esta caracteristica permite realizar búsquedas eficientes en tiempo $`O(log(n))`$, por lo que sus usos suelen ser para optimizar búsquedas.

El árbol se implementa con un puntero al nodo raíz, un contador de nodos y una función comparadora para determinar el orden de los elementos. Cada nodo del árbol contiene un elemento, un puntero al hijo izquierdo y un puntero al hijo derecho.

</div>

<div align="center">
	<img src="img/Diagrama_general_abb.png" alt="Diagrama general árbol binario de búsqueda" width="800"/>
</div>

<div style="text-align: justify">

Se implementan las siguientes primitivas para el ABB:

- `abb_crear`: Crea un árbol binario de búsqueda vacío asignandole la función comparadora pasada por parámetro.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `abb_insertar`: Se toma la convención de que si se quiere insertar un elemento que ya existe, se posiciona a la derecha del nodo existente.
	- Complejidad: $`O(log(n))`$ en tiempo y $`O(1)`$ en espacio.
- `abb_existe`: Devuelve verdadero si el elemento buscado existe en el árbol.
	- Complejidad: $`O(log(n))`$ en tiempo y $`O(1)`$ en espacio.
- `abb_buscar`: Devuelve el elemento que coincide con el buscado.
	- Complejidad: $`O(log(n))`$ en tiempo y $`O(1)`$ en espacio.
- `abb_sacar`: Devuelve y elimina la primer aparicion del nodo cuyo elemento coincida con el buscado. Si se saca un nodo con dos hijos no nulos se reemplaza dicho nodo con el predecesor inorden.
	- Complejidad: $`O(log(n))`$ en tiempo y $`O(1)`$ en espacio.
- `abb_tamanio`: Devuelve la cantidad de nodos que tiene el árbol.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `abb_vacio`: Devuelve verdadero si el árbol está vacío.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `abb_recorrer`: Recorre el árbol en el orden indicado (inorden, preorden o postorden) aplicando la función dada a cada elemento, finalmente devuelve la cantidad de elementos recorridos.
	- Complejidad: $`O(n)`$ en tiempo y $`O(1)`$ en espacio.
- `abb_vectorizar`: Crea un vector con los elementos del árbol en el orden indicado (inorden, preorden o postorden).
	- Complejidad: $`O(n)`$ en tiempo y $`O(n)`$ en espacio.
- `abb_destruir`: Destruye el árbol y libera la memoria ocupada por sus nodos.
	- Complejidad: $`O(n)`$ en tiempo y $`O(1)`$ en espacio.
- `abb_destruir_todo`: Destruye el árbol y libera la memoria ocupada por sus nodos aplicando la función dada a cada elemento.
	- Complejidad: $`O(n)`$ en tiempo y $`O(1)`$ en espacio.

</div>

<div align="center">
	<img src="img/Diagrama_abb_insertar().png" alt="Diagrama función 'abb_insertar()'" width="800"/>
</div>

<div align="center">
	<img src="img/Diagrama_abb_sacar().png" alt="Diagrama función 'abb_sacar()'" width="800"/>
</div>

<div align="center">
	<img src="img/Diagrama_abb_recorrer.png" alt="Diagrama función 'abb_recorrer()'" width="800"/>
</div>

## Contexto teórico
<div style="text-align: justify">

Si bien se implemento un árbol binario de búsqueda principalemente se debe entender el concepto de un árbol y un árbol binario. 

Un **árbol** es una estructura de datos jerárquica que consiste en nodos conectados por aristas. Cada nodo puede tener cero o más hijos, y cada nodo tiene un único padre, excepto el nodo raíz, que no tiene padre. Un ejemplo de uso es un sistema de archivos de un sistema operativo o cualquier sistema jerárquico.

</div>

<div align="center">
	<img src="img/Diagrama_general_arbol.png" alt="Diagrama general árbol" width="800"/>
</div>

<br>

<div style="text-align: justify">

Un **árbol binario** es un tipo especial de árbol en el que cada nodo tiene como máximo dos hijos, denominados hijo izquierdo e hijo derecho. Su implementación se puede encontrar en ejemplos como 

</div>

<div align="center">
	<img src="img/Diagrama_general_arbol_binario.png" alt="Diagrama general árbol binario" width="800"/>
</div>