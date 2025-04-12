/*
 * Último ejercicio con iterador interno. Ahora, queremos buscar los entrenadores que ganaron más de cierta cantidad de batallas. 
 * Para eso, se recibe la lista de todos los entrenadores y una lista vacía a la cual se le debe agregar cada entrenador que cumpla las condiciones. 
 * Ah, que cuántas batallas tienen que haber ganado? Eso lo recibís por parámetro ;)
 * 
 * No olvides revisar los parámetros! Si alguna de las listas es NULL, no se realiza ninguna operación. 
 * Si la cantidad de batallas es menor a 0, tampoco se realiza ninguna operación. 
 * Por último, este ejercicio no requiere que pidas ni liberes memoria dinámica, así que no te preocupes por eso, nosotros lo resolvemos.
 */

#include <stdbool.h>
#include <stddef.h>

typedef struct entrenador {
	int b_ganadas;
	int b_perdidas;
	int b_empatadas;
} entrenador_t;

typedef struct nodo nodo_t;
typedef struct lista lista_t;

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

typedef struct {
	int batallas_objetivo;
	lista_t *entrenadores_ganadores;
} contexto_filtro_t;

bool ganaron_cantidad_deseada(void *elemento, void *contexto)
{
	if (!elemento || !contexto) {
		return false;
	}

	entrenador_t *entrenador = (entrenador_t *)elemento;
	contexto_filtro_t *datos = (contexto_filtro_t *)contexto;

	if (entrenador->b_ganadas > datos->batallas_objetivo) {
		lista_insertar(datos->entrenadores_ganadores, entrenador);
	}

	return true;
}

void entrenadores_con_muchas_victorias(lista_t *entrenadores,
				       lista_t *entrenadores_ganadores,
				       int batallas_ganadas)
{
	if (!entrenadores || !entrenadores_ganadores || batallas_ganadas < 0) {
		return;
	}

	contexto_filtro_t contexto;
	contexto.batallas_objetivo = batallas_ganadas;
	contexto.entrenadores_ganadores = entrenadores_ganadores;

	lista_con_cada_elemento(entrenadores, ganaron_cantidad_deseada,
				&contexto);
}