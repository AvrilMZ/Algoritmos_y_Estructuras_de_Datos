/**
 * Habiendo repasado los iteradores de la lista, pasamos ahora al iterador de árbol. 
 * Misma idea que para los iteradores de lista; cuando usamos el árbol, no podemos acceder a la estructura del mismo.
 * Entonces, si queremos aplicar cierta función a cada nodo del árbol, tenemos el iterador de abb.
 * 
 * Empecemos con algo simple. Tenemos un árbol de números (ints), y queremos meter los números impares en un nuevo árbol.
 * 
 * Aviso, este ejercicio no implica manejo de memoria dinámica. 
 * No te preocupes por crear o liberar memoria, nosotros nos ocupamos de eso.
 * No olvides revisar los parámetros!
 */

#define ABB_RECORRER_INORDEN 0
#define ABB_RECORRER_PREORDEN 1
#define ABB_RECORRER_POSTORDEN 2

#include <stdbool.h>
#include <stdlib.h>

/*
  * Comparador de elementos. Recibe dos elementos del arbol y devuelve
  * 0 en caso de ser iguales, >0 si el primer elemento es mayor al
  * segundo o <0 si el primer elemento es menor al segundo.
  */
typedef int (*abb_comparador)(void *, void *);

/*
  * Destructor de elementos. Cada vez que un elemento deja el arbol
  * (arbol_borrar o arbol_destruir) se invoca al destructor pasandole
  * el elemento.
  */
typedef void (*abb_liberar_elemento)(void *);

typedef struct nodo_abb nodo_abb_t;

typedef struct abb abb_t;

/*
  * Crea el arbol y reserva la memoria necesaria de la estructura.
  * Comparador se utiliza para comparar dos elementos.
  * Destructor es invocado sobre cada elemento que sale del arbol,
  * puede ser NULL indicando que no se debe utilizar un destructor.
  *
  * Devuelve un puntero al arbol creado o NULL en caso de error.
  */
abb_t *arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor);

/*
  * Inserta un elemento en el arbol.
  * Devuelve 0 si pudo insertar o -1 si no pudo.
  * El arbol admite elementos con valores repetidos.
  */
int arbol_insertar(abb_t *arbol, void *elemento);

/*
  * Busca en el arbol un elemento igual al provisto (utilizando la
  * funcion de comparación) y si lo encuentra lo quita del arbol.
  * Adicionalmente, si encuentra el elemento, invoca el destructor con
  * dicho elemento.
  * Devuelve 0 si pudo eliminar el elemento o -1 en caso contrario.
  */
int arbol_borrar(abb_t *arbol, void *elemento);

/*
  * Busca en el arbol un elemento igual al provisto (utilizando la
  * funcion de comparación).
  *
  * Devuelve el elemento encontrado o NULL si no lo encuentra.
  */
void *arbol_buscar(abb_t *arbol, void *elemento);

/*
  * Devuelve el elemento almacenado como raiz o NULL si el árbol está
  * vacío o no existe.
  */
void *arbol_raiz(abb_t *arbol);

/*
  * Determina si el árbol está vacío.
  * Devuelve true si está vacío o el arbol es NULL, false si el árbol tiene elementos.
  */
bool arbol_vacio(abb_t *arbol);

/*
  * Llena el array del tamaño dado con los elementos de arbol
  * en secuencia inorden.
  * Devuelve la cantidad de elementos del array que pudo llenar (si el
  * espacio en el array no alcanza para almacenar todos los elementos,
  * llena hasta donde puede y devuelve la cantidad de elementos que
  * pudo poner).
  */
size_t arbol_recorrido_inorden(abb_t *arbol, void **array,
			       size_t tamanio_array);

/*
  * Llena el array del tamaño dado con los elementos de arbol
  * en secuencia preorden.
  * Devuelve la cantidad de elementos del array que pudo llenar (si el
  * espacio en el array no alcanza para almacenar todos los elementos,
  * llena hasta donde puede y devuelve la cantidad de elementos que
  * pudo poner).
  */
size_t arbol_recorrido_preorden(abb_t *arbol, void **array,
				size_t tamanio_array);

/*
  * Llena el array del tamaño dado con los elementos de arbol
  * en secuencia postorden.
  * Devuelve la cantidad de elementos del array que pudo llenar (si el
  * espacio en el array no alcanza para almacenar todos los elementos,
  * llena hasta donde puede y devuelve la cantidad de elementos que
  * pudo poner).
  */
size_t arbol_recorrido_postorden(abb_t *arbol, void **array,
				 size_t tamanio_array);

/*
  * Destruye el arbol liberando la memoria reservada por el mismo.
  * Adicionalmente invoca el destructor con cada elemento presente en
  * el arbol.
  */
void arbol_destruir(abb_t *arbol);

/*
 * Iterador interno. Recorre el arbol e invoca la funcion con cada
 * elemento del mismo. El puntero 'extra' se pasa como segundo
 * parámetro a la función. Si la función devuelve false, se finaliza el
 * recorrido aun si quedan elementos por recorrer. Si devuelve true
 * se sigue recorriendo mientras queden elementos.
 * El recorrido se realiza de acuerdo al recorrido solicitado.  Los
 * recorridos válidos son: ABB_RECORRER_INORDEN, ABB_RECORRER_PREORDEN
 * y ABB_RECORRER_POSTORDEN.
*/
void abb_con_cada_elemento(abb_t *arbol, int recorrido,
			   bool (*funcion)(void *, void *), void *extra);

bool guardar_si_es_impar(void *numero, void *arbol)
{
	int *valor = (int *)numero;
	abb_t *arbol_impares = (abb_t *)arbol;
	if (*valor % 2 != 0) {
		arbol_insertar(arbol_impares, valor);
	}
	return true;
}

void elementos_impares(abb_t *abb_original, abb_t *abb_impares)
{
	if (!abb_original || !abb_impares) {
		return;
	}

	abb_con_cada_elemento(abb_original, ABB_RECORRER_PREORDEN,
			      guardar_si_es_impar, abb_impares);
}