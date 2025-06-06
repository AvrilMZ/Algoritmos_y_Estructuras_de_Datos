# TDA HASH

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

## Funcionamiento
<div style="text-align: justify">

- ¿Qué es una función de hash y qué características debe tener para nuestro problema en particular?
- ¿Qué es una tabla de Hash y los diferentes métodos de resolución de colisiones vistos?
- ¿Por qué es importante el tamaño de la tabla (tanto para tablas abiertas como cerradas)
- Dado que en una tabla abierta se pueden encadenar colisiones sin importar el tamaño de la tabla, ¿Realmente importa el tamaño?

El programa implementa una **tabla de hash** que permite almacenar pares clave-valor, donde las claves son únicas y se utilizan para acceder a los valores asociados. La tabla de hash utiliza una función de hash para mapear las claves a índices en un arreglo, lo que permite un acceso rápido a los valores.

Una **función de hash** es una función que toma una entrada (en este caso, una clave) y devuelve un número entero que representa un índice en la tabla. Para nuestro problema, la función de hash debe ser eficiente, distribuir uniformemente las claves en la tabla y minimizar las colisiones. En caso de resultar en una colisión hay dos métodos de resolución: encadenamiento y direccionamiento abierto.

El encadenamiento (hash abierto) consiste en almacenar múltiples elementos en una misma posición de la tabla utilizando una lista enlazada, lo que permite manejar colisiones sin necesidad de redimensionar la tabla. Por otro lado, el direccionamiento abierto (hash cerrado) implica buscar otra posición en la tabla para almacenar el elemento en caso de colisión, lo que puede requerir un mayor tamaño de tabla para evitar demasiadas colisiones. **(feo no me gusta)**

<div id="imagen1" align="center">
	<img src="img/Diagrama_general_hash_abierto().png" alt="Diagrama general de una tabla de hash abierta" width="1000"/>

<sup>Figura 1. Ejemplo de implementación de una tabla de hash abierta (direccionamiento cerrado).</sup>
</div>

En este caso, el hash implementado fue con direccionamiento abierto y se utilizaron los campos:
- `capacidad`: Cantidad de posiciones que tiene la tabla.
- `cantidad`: Cantidad de elementos que tiene la tabla.
- `tabla`: Arreglo de elementos de tipo `elemento_tabla_t`, que contiene la clave, el valor y un booleano que indica si la posición fue eliminada.
- `funcion_hash`: Función de hash que se utiliza para mapear las claves a índices en la tabla.

<div id="imagen2" align="center">
	<img src="img/Diagrama_general_hash_cerrado().png" alt="Diagrama general de una tabla de hash cerrada" width="1000"/>

<sup>Figura 2. Ejemplo de implementación de una tabla de hash cerrada (direccionamiento abierto).</sup>
</div>

Se implementan las siguientes primitivas para el hash:
- `hash_crear()`: 
	- Complejidad: 
- `hash_crear_con_funcion()`: 
	- Complejidad: 
- `hash_insertar()`: 
	- Complejidad: 
- `hash_sacar()`: 
	- Complejidad: 
- `hash_buscar()`: 
	- Complejidad: 
- `hash_existe()`: 
	- Complejidad: 
- `hash_tamanio()`: 
	- Complejidad: 
- `hash_iterar_claves()`: 
	- Complejidad: 
- `hash_destruir()`: 
	- Complejidad: 
- `hash_destruir_todo()`: 
	- Complejidad: 

</div>

<div id="imagen3" align="center">
	<img src="img/Diagrama_hash_djb2().png" alt="Diagrama de flujo del algoritmo DJB2" width="500"/>

<sup>Figura 3. Diagrama de flujo del algoritmo DJB2.</sup>
</div>

<div id="imagen4" align="center">
	<img src="img/Diagrama_hash_insertar().png" alt="Diagrama función hash_insertar()" width="1000"/>

<sup>Figura 4. Ejemplo de implementación de la función hash_insertar().</sup>
</div>

<div id="imagen5" align="center">
	<img src="img/Diagrama_hash_sacar().png" alt="Diagrama función hash_sacar()" width="1000"/>

<sup>Figura 5. Ejemplo de implementación de la función hash_sacar().</sup>
</div>

<div id="imagen6" align="center">
	<img src="img/Diagrama_hash_recorrer().png" alt="Diagrama función hash_recorrer()" width="1000"/>

<sup>Figura 6. Ejemplo de implementación de la función hash_recorrer().</sup>
</div>

## Conceptos teóricos
<div style="text-align: justify">

### Diccionarios
- ¿Qué es un diccionario? 
- Explicar 3 formas diferentes de implementar un diccionario (tabla de hash cuenta como 1). 
- Ventajas y desventajas.

Un **diccionario** es una estructura de datos que permite almacenar pares clave-valor, donde las claves son únicas y se utilizan para acceder a los valores asociados. Existen varias formas de implementar un diccionario, entre ellas:
- **Tabla de hash**: Utiliza una función de hash para mapear las claves a índices en un arreglo, lo que permite un acceso rápido a los valores. Las colisiones se manejan mediante encadenamiento o dirección abierta.
- **Árbol binario de búsqueda**: Almacena los pares clave-valor en un árbol, donde las claves se organizan de manera que los elementos del subárbol izquierdo son menores que los del subárbol derecho. Permite búsquedas eficientes, pero puede ser menos eficiente que una tabla de hash en términos de tiempo de acceso.
- **Lista enlazada**: Almacena los pares clave-valor en una lista, donde cada nodo contiene una clave y un valor. Permite una implementación simple, pero las búsquedas son menos eficientes que en una tabla de hash o un árbol binario de búsqueda.
- **Ventajas y desventajas**:
	- Tabla de hash: 
		- Ventajas: Acceso rápido a los valores, manejo eficiente de colisiones.
		- Desventajas: Puede requerir un mayor tamaño de tabla para evitar demasiadas colisiones, la función de hash debe ser bien diseñada.
	- Árbol binario de búsqueda: 
		- Ventajas: Permite búsquedas eficientes, fácil de implementar.
		- Desventajas: Puede ser menos eficiente que una tabla de hash en términos de tiempo de acceso, requiere un árbol balanceado para mantener la eficiencia.
	- Lista enlazada: 
		- Ventajas: Implementación simple, fácil de entender.
		- Desventajas: Búsquedas menos eficientes, no es ideal para grandes volúmenes de datos.

</div>

<div id="imagen7" align="center">
	<img src="img/Diccionario_abb().png" alt="Diagrama diccionario implementado con un ABB" width="1000"/>

<sup>Figura 7. Ejemplo de implementación de un diccionario utilizando un árbol binario de búsqueda (ABB).</sup>
</div>

<div id="imagen8" align="center">
	<img src="img/Diccionario_lista().png" alt="Diagrama diccionario implementado con una lista enlazada" width="1000"/>

<sup>Figura 8. Ejemplo de implementación de un diccionario utilizando una lista enlazada.</sup>
</div>