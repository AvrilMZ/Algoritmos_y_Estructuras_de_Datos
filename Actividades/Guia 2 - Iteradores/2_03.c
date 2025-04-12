/*
 * Al hacer el ejercicio anterior, tal vez te preguntaste si era más sencillo resolverlo con un iterador interno, en vez del externo. 
 * Bueno, no hace falta que te lo sigas preguntando, lo vamos a hacer ahora!
 * 
 * Sí, les estamos pidiendo resolver el mismo ejercicio del punto pasado, pero ahora con un iterador interno. 
 * Así entendemos bien la diferencia entre ambos y aprendemos cuándo conviene usar uno vs el otro.
 * 
 * Se recibe la lista de entrenadores y se pide programar la función entrenador_con_mas_victorias, de la cual ya reciben la firma, y una función para comparar entrenadores con el siguiente criterio:
 *      - Devolver el entrenador con más batallas ganadas.
 *      - Si hay más de uno con la misma cantidad de batallas ganadas, devolver el que menor cantidad de batallas perdió.
 * Nosotros nos aseguramos de que haya un solo entrenador en la lista que cumpla estas condiciones.
 * 
 * En este ejercicio, aunque no es necesario, te permitimos pispear el archivo lista.h y usar la función lista_primero;) 
 * A su vez, tenemos acceso al archivo lista_iterador.h, donde está la firma del iterador interno.
 * No olvides verificar parámetros! Si se recibe una lista NULL, devolver NULL.
 * Por último y como siempre, no te preocupes por liberar la lista, nosotros nos ocupamos de eso detrás de cámara.
 */

#include <stdbool.h>
#include <stddef.h>

typedef struct nodo nodo_t;
typedef struct lista lista_t;

typedef struct entrenador {
	int b_ganadas;
	int b_perdidas;
	int b_empatadas;
} entrenador_t;

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

bool tiene_mas_victorias(void *elemento, void *contexto)
{
	if (!elemento || !contexto) {
		return false;
	}

	entrenador_t *actual = (entrenador_t *)elemento;
	entrenador_t **record = (entrenador_t **)contexto;

	if (actual->b_ganadas > (*record)->b_ganadas ||
	    (actual->b_ganadas == (*record)->b_ganadas &&
	     actual->b_perdidas < (*record)->b_perdidas)) {
		*record = actual;
	}
	return true;
}

entrenador_t *entrenador_con_mas_victorias(lista_t *entrenadores)
{
	if (!entrenadores) {
		return NULL;
	}

	entrenador_t *record = lista_primero(entrenadores);
	lista_con_cada_elemento(entrenadores, tiene_mas_victorias, &record);

	return record;
}