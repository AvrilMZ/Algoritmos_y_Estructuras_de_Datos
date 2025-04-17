# TDA Lista, Pila y Cola

- **Alumno:** [Avril Victoria Morfeo Zerbi](https://github.com/AvrilMZ) 
- **Legajo:** 112563 
- **Mail:** amorfeo@fi.uba.ar


### Instrucciones para correr el proyecto:

- Para compilar:
```bash
make main
```

- Para ejecutar:
```bash
./main
```

- Para ejecutar con Valgrind:
```bash
valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes -s ./main
```

<br>

##  Funcionamiento
<div style="text-align: justify">

El programa implementa tres estructuras de datos: una lista simplemente enlazada, una pila y una cola. La lista, que sirve de base para las otras dos, se representa mediante una estructura que incluye un puntero al primer nodo, otro al último y un contador de elementos. Cada nodo contiene un puntero a sus datos y otro al siguiente nodo.

<div align="center">
	<img src="img/Diagrama_lista_simplemente_enlazada.png" alt="Diagrama general lista simplemente enlazada" width="800"/>
</div>

### Lista simplemente enlazada
<div style="text-align: justify">

Una **lista** es una estructura de datos que almacena elementos en un orden específico, permitiendo la inserción, eliminación y acceso a elementos según su posición. No requiere un tamaño fijo y gestiona la memoria de manera dinámica, lo que le otorga flexibilidad. Además, puede implementarse de distintas formas según las necesidades del problema.

Una **lista simplemente enlazada** es una implementación específica de una lista, en la que cada elemento (nodo) contiene un valor y un puntero al siguiente nodo. Esta estructura permite insertar y eliminar elementos de forma eficiente, ya que solo es necesario ajustar los punteros de los nodos vecinos. Sin embargo, el acceso a un nodo específico es secuencial, ya que se deben recorrer los nodos desde el principio hasta encontrar el deseado. A diferencia de las listas implementadas con arreglos, no requiere memoria contigua, lo que la hace más flexible. No obstante, cada nodo necesita espacio adicional para almacenar el puntero, lo que implica un mayor consumo de memoria en comparación con un arreglo. Se siguieron las siguientes primitivas:
- `lista_crear()`: crea una lista simplemente enlazada vacía.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `lista_insertar()`: inserta un elemento al final de la lista.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `lista_insertar_en_posicion()`: inserta un elemento en una posición específica de la lista.
	- Complejidad: $`O(1)`$ en tiempo si la posicion es cero, $`O(n)`$ en otras posiciones, y $`O(1)`$ en espacio.
- `lista_tamanio()`: devuelve el tamaño de la lista.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `lista_obtener_elemento()`: devuelve el elemento en una posición específica de la lista.
	- Complejidad: $`O(1)`$ en tiempo si la posicion es cero, $`O(n)`$ en otras posiciones, y $`O(1)`$ en espacio.
- `lista_sacar_de_posicion()`: saca un elemento de una posición específica de la lista.
	- Complejidad: $`O(1)`$ en tiempo si la posicion es cero, $`O(n)`$ en otras posiciones, y $`O(1)`$ en espacio.
- `lista_sacar_elemento()`: busca y saca un elemento de la lista.
	- Complejidad: $`O(n)`$ en tiempo y $`O(1)`$ en espacio.
- `lista_buscar_posicion()`: busca un elemento en la lista y devuelve su posición.
	- Complejidad: $`O(n)`$ en tiempo y $`O(1)`$ en espacio.
- `lista_buscar()`: busca un elemento de la lista aplicando una función de comparación.
	- Complejidad: $`O(n)`$ en tiempo y $`O(1)`$ en espacio.
- `lista_iterar()`: itera sobre los elementos de la lista y aplica una función a cada elemento.
	- Complejidad: $`O(n)`$ en tiempo y $`O(1)`$ en espacio.
- `lista_destruir()`: destruye la lista y libera la memoria ocupada por los nodos y los datos.
	- Complejidad: $`O(n)`$ en tiempo y $`O(1)`$ en espacio.

</div>

<div align="center">
	<img src="img/Diagrama_lista_insertar().png" alt="Diagrama función 'lista_insertar()'" width="800"/>
</div>

<div align="center">
	<img src="img/Diagrama_lista_insertar_en_posicion().png" alt="Diagrama función 'lista_insertar_en_posicion()'" width="800"/>
</div>

<div align="center">
	<img src="img/Diagrama_lista_sacar_de_posicion().png" alt="Diagrama función 'lista_sacar_de_posicion()'" width="800"/>

<sup>(El color gris representa lo eliminado)</sup>

</div>

<br>

<div style="text-align: justify">

Por otro lado se implementaron dos tipos de iteradores para la lista simplemente enlazada: un iterador interno y un iterador externo.

El **iterador interno** permite que la lista recorra automáticamente sus elementos. Esto significa que el proceso de iteración es gestionado por la propia lista y el usuario no necesita interactuar con el recorrido, esto facilita su uso ya que el código que recorre los elementos está encapsulado en la estructura de la lista misma. En el caso de la lista simplemente enlazada, el iterador interno comenzaría desde el primer nodo y avanzaría automáticamente hasta el último.

En contraste, el **iterador externo** es diseñado para darle mayor control al usuario sobre el recorrido de la lista. A diferencia del iterador interno, éste permite al usuario manejar directamente cómo y cuándo recorrer los nodos. El usuario puede, por ejemplo, decidir en qué punto comenzar o terminar la iteración, o incluso interrumpirla en cualquier momento, por lo que proporciona flexibilidad y control sobre el proceso de iteración.

Las principales diferencias entre los dos tipos de iteradores radican en el control que tienen sobre el proceso de recorrido: el iterador interno se encarga de todo automáticamente, mientras que el iterador externo le permite al usuario gestionarlo y personalizarlo. El iterador interno fue implementado con la función `lista_iterar()`, mientras que el iterador externo utiliza las siguientes primitivas:
- `lista_iterador_crear()`: crea un iterador externo para la lista.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `lista_iterador_quedan_elementos_por_recorrer()`: verifica si quedan elementos por recorrer.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `lista_iterador_proxima_iteracion()`: devuelve el siguiente elemento en la iteración.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `lista_iterador_obtener_elemento()`: devuelve el elemento actual en la iteración.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `lista_iterador_destruir()`: destruye el iterador externo y libera la memoria ocupada por el iterador.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.

</div>

### Pila
<div style="text-align: justify">

Una pila es una estructura de datos que sigue el principio LIFO (Last In, First Out), donde el último elemento en ingresar es el primero en salir.  Este tipo de estructura es clave en la ejecución de programas, ya que se usa para almacenar los _stack frames_ de las funciones. Cada vez que una función se llama, se apila un nuevo frame con sus variables y contexto; cuando termina, se desapila y se retoma la ejecución anterior. En este caso se llevo a cabo utilizando una lista simplemente enlazada, con el objetivo de simplificar su implementación. Se siguieron las siguientes primitivas:
- `pila_crear()`: crea una pila vacía.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `pila_apilar()`: apila un elemento en la pila.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `pila_desapilar()`: desapila un elemento de la pila.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `pila_vacia()`: verifica si la pila está vacía.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `pila_tamanio()`: devuelve el tamaño de la pila.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `pila_tope()`: devuelve el elemento en el tope de la pila.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `pila_destruir()`: destruye la pila y libera la memoria ocupada por los nodos y los datos.
	- Complejidad: $`O(n)`$ en tiempo y $`O(1)`$ en espacio.

</div>

### Cola
<div style="text-align: justify">

Una cola es una estructura de datos que sigue el principio FIFO (First In, First Out), donde el primer elemento en ingresar es el primero en salir, siendo útil para procesar elementos en el mismo orden en que fueron agregados. En este caso se llevo a cabo utilizando una lista simplemente enlazada, manteniendo referencias al primer y último nodo para permitir inserciones al final y eliminaciones al inicio de manera eficiente. A diferencia de la pila, que opera sobre un único extremo de la lista, la cola requiere operar en ambos extremos para preservar el orden de llegada. Se siguieron las siguientes primitivas:
- `cola_crear()`: crea una cola vacía.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `cola_encolar()`: encola un elemento en la cola.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `cola_desencolar()`: desencola un elemento de la cola.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `cola_vacia()`: verifica si la cola está vacía.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `cola_tamanio()`: devuelve el tamaño de la cola.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `cola_frente()`: devuelve el elemento en el frente de la cola.
	- Complejidad: $`O(1)`$ en tiempo y $`O(1)`$ en espacio.
- `cola_destruir()`: destruye la cola y libera la memoria ocupada por los nodos y los datos.
	- Complejidad: $`O(n)`$ en tiempo y $`O(1)`$ en espacio.

</div>

<br>

##  Conceptos teoricos
<div style="text-align: justify">

Hay algunos conceptos, que si bien no fueron implementados en este trabajo practico, son de alta relevancia mencionar.

</div>

### Lista doblemente enlazada
<div style="text-align: justify">

Una lista doblemente enlazada es una implementación específica de una lista en la que cada nodo contiene dos punteros: uno que apunta al siguiente nodo y otro que apunta al nodo anterior. Esto permite recorrer la lista en ambas direcciones, lo que la hace más flexible que una lista simplemente enlazada. A pesar de esta ventaja, la lista doblemente enlazada utiliza más memoria por nodo, ya que debe almacenar dos punteros en lugar de uno, lo que incrementa el uso de memoria en comparación con las listas simplemente enlazadas. Las operaciones de inserción y eliminación son más eficientes en cualquier lugar de la lista, ya que se puede acceder al nodo anterior de manera inmediata, sin necesidad de recorrer la lista desde el principio.

</div>

<div align="center">
	<img src="img/Diagrama_lista_doblemente_enlazada.png" alt="Diagrama general lista doblemente enlazada" width="800"/>

<sup>(El color gris representa la implementación de una lista simplemente enlazada previamente explicada)</sup>

</div>

### Lista circular
<div style="text-align: justify">

Una lista circular es una lista donde el último nodo está conectado de nuevo al primero, creando un ciclo. Esto se aplica tanto a las listas simplemente enlazadas como a las doblemente enlazadas, generando una estructura donde, al llegar al final de la lista, se puede volver al inicio sin necesidad de verificar si se ha llegado al final. En una lista circular simplemente enlazada, el último nodo apunta al primer nodo, mientras que en una lista circular doblemente enlazada, el primer nodo apunta al último y el último apunta al primero. La principal ventaja de las listas circulares es que no es necesario realizar verificaciones adicionales para determinar el fin de la lista, lo que puede simplificar algunas operaciones, como la inserción y eliminación de nodos en una estructura cíclica, pero también implica que no sabés fácilmente cuándo termina el recorrido.

</div>

<div align="center">
	<img src="img/Diagrama_lista_circular_simplemente_enlazada.png" alt="Diagrama general lista circular simplemente enlazada" width="800"/>

<sup>(El color gris representa la implementación de una lista simplemente enlazada previamente explicada)</sup>

</div>

<div align="center">
	<img src="img/Diagrama_lista_circular_doblemente_enlazada.png" alt="Diagrama general lista circular doblemente enlazada" width="800"/>

<sup>(El color gris representa la implementación de una lista doblemente enlazada previamente explicada)</sup>

</div>