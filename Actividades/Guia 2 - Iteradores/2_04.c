/*
 * Sigamos haciendo competir a nuestros pokemones. Para eso los capturan los entrenadores, no? Y de paso, practiquemos cómo usar el iterador interno.
 * Dado un grupo de pokemones, se quiere saber cuáles ganarían la medalla de oro, plata y bronce en una carrera. 
 * Cada pokemon tiene su nivel de rapidez y por supuesto, el que mayor nivel tenga, más rápido corre.
 * 
 * Para resolver el problema, se presenta la firma de una función que recibe el listado de todos los pokemones y una lista vacía donde se insertarán los pokemones que pertenecen al podio. 
 * Se pide que los pokemones del podio estén ordenados de la siguiente manera:
 *      medalla de oro - medalla de plata - medalla de bronce
 * 
 * No olvides revisar los parámetros! Si alguno de ellos es NULL, no se realiza ninguna operación. 
 * Por último, este ejercicio no requiere que utilices memoria dinámica de ningún tipo, así que no te preocupes por liberar memoria, nosotros nos encargamos de todo.
 */

#include <stdbool.h>
#include <stddef.h>

typedef struct nodo nodo_t;
typedef struct lista lista_t;

typedef struct pokemon {
	int fuerza;
	int rapidez;
	int inteligencia;
} pokemon_t;

/*
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t *lista_crear();

/*
 * Inserta un elemento al final de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar(lista_t *lista, void *elemento);

/*
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar_en_posicion(lista_t *lista, void *elemento, size_t posicion);

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar(lista_t *lista);

/*
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento.  
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.  
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar_de_posicion(lista_t *lista, size_t posicion);

/*
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
void *lista_elemento_en_posicion(lista_t *lista, size_t posicion);

/* 
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
void *lista_ultimo(lista_t *lista);

/* 
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t *lista);

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t *lista);

/* 
 * Apila un elemento.
 * Devuelve 0 si pudo o -1 en caso contrario.
 */
int lista_apilar(lista_t *lista, void *elemento);

/* 
 * Desapila un elemento.
 * Devuelve 0 si pudo desapilar o -1 si no pudo.
 */
int lista_desapilar(lista_t *lista);

/*
 * Devuelve el elemento en el tope de la pila o NULL
 * en caso de estar vacía.
 */
void *lista_tope(lista_t *lista);

/* 
 * Encola un elemento.
 * Devuelve 0 si pudo encolar o -1 si no pudo.
 */
int lista_encolar(lista_t *lista, void *elemento);

/* 
 * Desencola un elemento.
 * Devuelve 0 si pudo desencolar o -1 si no pudo.
 */
int lista_desencolar(lista_t *lista);

/*
 * Devuelve el primer elemento de la cola o NULL en caso de estar
 * vacía.
 */
void *lista_primero(lista_t *lista);

/*
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t *lista);

/*
  * Iterador interno. Recorre la lista e invoca la funcion con cada elemento de
  * la misma. Dicha función puede devolver true si se deben seguir recorriendo
  * elementos o false si se debe dejar de iterar elementos.
  *
  * La función retorna la cantidad de elementos iterados o 0 en caso de error.
  */
size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto);

bool podio_pokemones(void *elemento, void *contexto)
{
	if (!elemento || !contexto) {
		return false;
	}

	pokemon_t *pokemon = (pokemon_t *)elemento;
	lista_t *podio = (lista_t *)contexto;

	if (lista_vacia(podio)) {
		lista_insertar(podio, pokemon);
		return true;
	}

	pokemon_t *actual = NULL;
	bool seguir = true;
	for (int i = 0; i < (int)lista_elementos(podio) && seguir; i++) {
		actual = lista_elemento_en_posicion(podio, i);
		if (pokemon->rapidez > actual->rapidez) {
			lista_insertar_en_posicion(podio, pokemon, i);
			if (lista_elementos(podio) > 3) {
				lista_borrar(podio);
			}
			seguir = false;
		}
	}

	if (lista_elementos(podio) < 3) {
		lista_insertar(podio, pokemon);
	}

	return true;
}

void podio_de_pokemones(lista_t *pokemones, lista_t *podio)
{
	if (!pokemones || !podio) {
		return;
	}

	lista_con_cada_elemento(pokemones, podio_pokemones, podio);
}