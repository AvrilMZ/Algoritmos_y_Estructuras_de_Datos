#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

bool es_elemento_buscado(void *elemento, void *buscado)
{
	if (!elemento || !buscado) {
		return false;
	}

	return *(char *)elemento == *(char *)buscado;
}

bool es_elemento_contador(void *elemento, void *contador)
{
	if (!elemento || !contador) {
		return false;
	}

	(*(int *)contador)++;
	return true;
}

void test_crear_lista()
{
	lista_t *lista = lista_crear();

	pa2m_nuevo_grupo("CREANDO");

	pa2m_afirmar(lista != NULL, "Se puede crear una lista");
	pa2m_afirmar(lista_tamanio(lista) == 0,
		     "La cantidad de elementos es 0");
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == NULL,
		     "El primer elemento de una lista vacia es nulo");
	pa2m_afirmar(lista_obtener_elemento(
			     lista, (int)(lista_tamanio(lista) - 1)) == NULL,
		     "El ultimo elemento de una lista vacia es nulo");

	// Crear iterador
	char a = 'a', b = 'b', c = 'c', d = 'd';

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);

	lista_iterador_t *iterador = lista_iterador_crear(lista);
	pa2m_afirmar(iterador != NULL, "Se puede crear un iterador");

	size_t i = 0;
	for (; lista_iterador_quedan_elementos_por_recorrer(iterador);
	     lista_iterador_proxima_iteracion(iterador))
		i++;

	pa2m_afirmar(
		i == lista_tamanio(lista),
		"Se pudo recorrer todos los elementos, con el iterador externo");

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void test_insertar_lista()
{
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
	char *elemento = NULL;

	pa2m_nuevo_grupo("INSERTANDO ELEMENTO");

	lista_t *lista = lista_crear();

	pa2m_afirmar(!lista_insertar(NULL, &d),
		     "No se puede insertar en una lista nula");

	lista_insertar(lista, &a);
	elemento = (char *)lista_obtener_elemento(lista, 0);
	pa2m_afirmar(*(char *)elemento == a,
		     "Se puede agregar el elemento A al final de la lista");
	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "La cantidad de elementos es 1");

	lista_insertar(lista, &b);
	elemento = (char *)lista_obtener_elemento(lista, 1);
	pa2m_afirmar(*elemento == b,
		     "Se puede agregar el elemento B al final de la lista");
	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "La cantidad de elementos es 2");

	lista_insertar(lista, &c);
	elemento = (char *)lista_obtener_elemento(lista, 2);
	pa2m_afirmar(*elemento == c,
		     "Se puede agregar el elemento C al final de la lista");
	pa2m_afirmar(lista_tamanio(lista) == 3,
		     "La cantidad de elementos es 3");

	elemento = (char *)lista_obtener_elemento(lista, 0);
	pa2m_afirmar(*elemento == a, "El primer elemento es A");

	elemento = (char *)lista_obtener_elemento(
		lista, (int)lista_tamanio(lista) - 1);
	pa2m_afirmar(*elemento == c, "El último elemento es C");

	lista_iterador_t *iterador = lista_iterador_crear(lista);

	for (; lista_iterador_quedan_elementos_por_recorrer(iterador);
	     lista_iterador_proxima_iteracion(iterador))
		elemento = lista_iterador_obtener_elemento(iterador);

	pa2m_afirmar(*elemento == c,
		     "Usando el iterador, el elemento en el final es C");

	pa2m_afirmar(lista_insertar(lista, NULL),
		     "Se puede insertar NULL como elemento");
	pa2m_afirmar(lista_tamanio(lista) == 4,
		     "La cantidad de elementos después de insertar NULL es 4");
	pa2m_afirmar(lista_obtener_elemento(lista, 3) == NULL,
		     "Se recupera NULL como cuarto elemento");

	lista_insertar_en_posicion(lista, 2, &e);
	elemento = (char *)lista_obtener_elemento(lista, 2);
	pa2m_afirmar(
		*elemento == e,
		"Se puede agregar el elemento E en la posición 2 de la lista");
	pa2m_afirmar(lista_insertar_en_posicion(
			     lista, (int)lista_tamanio(lista), &e) == true,
		     "Se puede agregar un elemento en la última posición");
	pa2m_afirmar(lista_insertar_en_posicion(lista, 10, &e) == false,
		     "No se pueden agregar elementos en posiciones invalidas");

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void test_sacar_lista()
{
	char a = 'a', b = 'b', c = 'c', d = 'd';
	char *elemento = NULL;

	pa2m_nuevo_grupo("QUITANDO ELEMENTO");

	lista_t *lista = lista_crear();

	pa2m_afirmar(!lista_sacar_de_posicion(NULL, 0),
		     "No se puede quitar elementos de una lista nula");

	pa2m_afirmar(!lista_sacar_de_posicion(lista, 0),
		     "No se puede quitar elementos con lista vacía");

	pa2m_afirmar(
		!lista_sacar_elemento(lista, &c),
		"No se puede sacar un elemento específico de una lista vacía");

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);

	pa2m_afirmar(lista_tamanio(lista) == 3,
		     "La cantidad de elementos es 3");

	elemento = (char *)lista_sacar_de_posicion(
		lista, (int)(lista_tamanio(lista) - 1));
	pa2m_afirmar(*elemento == c,
		     "Se puede quitar el elemento C del final de la lista");
	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "La cantidad de elementos es 2");

	elemento = (char *)lista_obtener_elemento(
		lista, (int)(lista_tamanio(lista) - 1));
	pa2m_afirmar(*elemento == b, "El ultimo elemento es B");

	elemento = (char *)lista_sacar_de_posicion(
		lista, (int)(lista_tamanio(lista) - 1));
	pa2m_afirmar(*elemento == b,
		     "Se puede quitar el elemento B del final de la lista");
	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "La cantidad de elementos es 1");

	elemento = (char *)lista_obtener_elemento(
		lista, (int)(lista_tamanio(lista) - 1));
	pa2m_afirmar(*elemento == a, "El ultimo elemento es A");

	elemento = (char *)lista_obtener_elemento(lista, 0);
	pa2m_afirmar(*elemento == a, "El primer elemento es A");

	lista_insertar(lista, &b);
	lista_insertar(lista, &c);

	pa2m_afirmar(!lista_sacar_elemento(NULL, &c),
		     "No se puede sacar un elemento de una lista nula");

	elemento = lista_sacar_elemento(lista, &c);
	pa2m_afirmar(elemento != NULL && *elemento == c,
		     "Se puede sacar el elemento C de la lista");
	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "La cantidad de elementos es 2 después de sacar C");

	elemento = lista_sacar_elemento(lista, &d);
	pa2m_afirmar(elemento == NULL,
		     "No se puede sacar un elemento inexistente");

	lista_destruir(lista);
}

void test_buscar_lista()
{
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
	char *elemento = NULL;

	pa2m_nuevo_grupo("BUSCANDO ELEMENTO");

	lista_t *lista = lista_crear();

	pa2m_afirmar(!lista_buscar(NULL, es_elemento_buscado, &e),
		     "No se puede buscar un elemento con una lista nula");
	pa2m_afirmar(lista_buscar(lista, es_elemento_buscado, &e) == NULL,
		     "No se encuentra un elemento en una lista vacía");

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);

	elemento = (char *)lista_buscar(lista, es_elemento_buscado, &a);
	pa2m_afirmar(elemento != NULL && *elemento == a,
		     "Se encuentra el elemento A");

	elemento = (char *)lista_buscar(lista, es_elemento_buscado, &c);
	pa2m_afirmar(elemento != NULL && *elemento == c,
		     "Se encuentra el elemento C");

	elemento = (char *)lista_buscar(lista, es_elemento_buscado, &d);
	pa2m_afirmar(elemento != NULL && *elemento == d,
		     "Se encuentra el elemento D");

	elemento = (char *)lista_buscar(lista, es_elemento_buscado, &e);
	pa2m_afirmar(elemento == NULL,
		     "No se encuentra un elemento inexistente");

	pa2m_afirmar(lista_buscar_posicion(NULL, &a) == -1,
		     "No se puede buscar posición en una lista nula");

	pa2m_afirmar(lista_buscar_posicion(lista, &a) == 0,
		     "El elemento A está en la posición 0");

	pa2m_afirmar(lista_buscar_posicion(lista, &c) == 2,
		     "El elemento C está en la posición 2");

	pa2m_afirmar(lista_buscar_posicion(lista, &e) == -1,
		     "Un elemento inexistente devuelve -1");

	lista_sacar_elemento(lista, &c);
	pa2m_afirmar(
		lista_buscar_posicion(lista, &d) == 2,
		"Después de eliminar C, el elemento D está en la posición 2");

	lista_destruir(lista);
}

void test_iterar_lista()
{
	char a = 'a', b = 'b', c = 'c', d = 'd';

	pa2m_nuevo_grupo("ITERANDO ELEMENTOS");

	lista_t *lista = lista_crear();
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);

	int contador = 0;
	pa2m_afirmar(lista_iterar(NULL, es_elemento_buscado, &a) == 0,
		     "No se puede iterar una lista nula");

	int iteraciones = lista_iterar(lista, es_elemento_contador, &contador);
	pa2m_afirmar(iteraciones == 4,
		     "`lista_iterar` recorre todos los elementos de la lista");
	pa2m_afirmar(contador == 4,
		     "El contador se incrementó para cada elemento");

	lista_destruir(lista);
}

void pruebas_listas()
{
	test_crear_lista();
	test_insertar_lista();
	test_sacar_lista();
	test_buscar_lista();
	test_iterar_lista();
}

// ------------------------- PRUEBAS COLA -------------------------

void test_cola_crear()
{
	cola_t *cola = cola_crear();

	pa2m_nuevo_grupo("CREANDO");

	pa2m_afirmar(cola != NULL, "Se puede crear una cola");
	pa2m_afirmar(cola_vacia(cola), "La cola está vacía");
	pa2m_afirmar(cola_tamanio(cola) == 0, "La cantidad de elementos es 0");
	pa2m_afirmar(cola_frente(cola) == NULL,
		     "El primer elemento de una cola vacia es nulo");

	cola_destruir(cola);
}

void test_cola_encolar()
{
	cola_t *cola = cola_crear();

	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
	char *elemento = NULL;

	pa2m_nuevo_grupo("ENCOLANDO");

	pa2m_afirmar(!cola_encolar(NULL, &e),
		     "No se puede encolar con una cola nula");

	cola_encolar(cola, &a);

	elemento = cola_frente(cola);
	pa2m_afirmar(*(char *)elemento == a, "Se puede encolar el elemento A");
	pa2m_afirmar(cola_tamanio(cola) == 1,
		     "La cantidad de elementos en la cola es 1");
	cola_encolar(cola, &b);
	pa2m_afirmar(cola_tamanio(cola) == 2,
		     "La cantidad de elementos en la cola es 2");
	cola_encolar(cola, &c);
	pa2m_afirmar(cola_tamanio(cola) == 3,
		     "La cantidad de elementos en la cola es 3");
	cola_encolar(cola, &d);
	pa2m_afirmar(cola_tamanio(cola) == 4,
		     "La cantidad de elementos en la cola es 4");

	elemento = cola_frente(cola);
	pa2m_afirmar(*(char *)elemento == a, "El frente de la cola es A");

	cola_destruir(cola);
}

void test_cola_desencolar()
{
	cola_t *cola = cola_crear();

	char a = 'a', b = 'b', c = 'c', d = 'd';
	char *elemento = NULL;

	pa2m_nuevo_grupo("DESENCOLANDO");

	pa2m_afirmar(!cola_desencolar(NULL),
		     "No se puede desencolar con una cola nula");

	cola_encolar(cola, &a);
	cola_encolar(cola, &b);
	cola_encolar(cola, &c);
	cola_encolar(cola, &d);

	elemento = cola_desencolar(cola);
	pa2m_afirmar(*(char *)elemento == a,
		     "Se puede desencolar el elemento A");
	pa2m_afirmar(cola_tamanio(cola) == 3,
		     "La cantidad de elementos en la cola es 3");

	elemento = cola_frente(cola);
	pa2m_afirmar(*(char *)elemento == b, "El nuevo frente es B");

	elemento = cola_desencolar(cola);
	pa2m_afirmar(*(char *)elemento == b,
		     "Se puede desencolar el elemento B");
	pa2m_afirmar(cola_tamanio(cola) == 2,
		     "La cantidad de elementos en la cola es 2");

	elemento = cola_frente(cola);
	pa2m_afirmar(*(char *)elemento == c, "El nuevo frente es C");

	elemento = cola_desencolar(cola);
	pa2m_afirmar(*(char *)elemento == c,
		     "Se puede desencolar el elemento C");
	pa2m_afirmar(cola_tamanio(cola) == 1,
		     "La cantidad de elementos en la cola es 1");

	elemento = cola_frente(cola);
	pa2m_afirmar(*(char *)elemento == d, "El nuevo frente es D");

	elemento = cola_desencolar(cola);
	pa2m_afirmar(*(char *)elemento == d,
		     "Se puede desencolar una cola de un elemento");
	pa2m_afirmar(cola_vacia(cola),
		     "La cantidad de elementos en la cola es 0");

	cola_destruir(cola);
}

void pruebas_colas()
{
	test_cola_crear();
	test_cola_encolar();
	test_cola_desencolar();
}

// ------------------------- PRUEBAS PILA -------------------------

void test_pila_crear()
{
	pila_t *pila = pila_crear();

	pa2m_nuevo_grupo("CREANDO");

	pa2m_afirmar(pila != NULL, "Se puede crear una pila");
	pa2m_afirmar(pila_vacia(pila), "La pila está vacía");
	pa2m_afirmar(pila_tamanio(pila) == 0, "La cantidad de elementos es 0");
	pa2m_afirmar(pila_tope(pila) == NULL,
		     "El primer elemento de una pila vacia es nulo");

	pila_destruir(pila);
}

void test_pila_apilar()
{
	pila_t *pila = pila_crear();

	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
	char *elemento = NULL;

	pa2m_nuevo_grupo("APILANDO");

	pa2m_afirmar(!pila_apilar(NULL, &e),
		     "No se puede apilar con una pila nula");

	pila_apilar(pila, &a);
	elemento = pila_tope(pila);
	pa2m_afirmar(*(char *)elemento == a, "El tope de la pila es A");
	pa2m_afirmar(pila_tamanio(pila) == 1, "La cantidad de elementos es 1");

	pila_apilar(pila, &b);
	elemento = pila_tope(pila);
	pa2m_afirmar(*(char *)elemento == b, "El tope de la pila es B");
	pa2m_afirmar(pila_tamanio(pila) == 2, "La cantidad de elementos es 2");

	pila_apilar(pila, &c);
	elemento = pila_tope(pila);
	pa2m_afirmar(*(char *)elemento == c, "El tope de la pila es C");
	pa2m_afirmar(pila_tamanio(pila) == 3, "La cantidad de elementos es 3");

	pila_apilar(pila, &d);
	elemento = pila_tope(pila);
	pa2m_afirmar(*(char *)elemento == d, "El tope de la pila es D");
	pa2m_afirmar(pila_tamanio(pila) == 4, "La cantidad de elementos es 4");

	pila_destruir(pila);
}

void test_pila_desapilar()
{
	pila_t *pila = pila_crear();

	char a = 'a', b = 'b', c = 'c', d = 'd';
	char *elemento = NULL;

	pa2m_nuevo_grupo("DESAPILANDO");

	pa2m_afirmar(!pila_desapilar(NULL),
		     "No se puede desapilar con una pila nula");

	pila_apilar(pila, &a);
	pila_apilar(pila, &b);
	pila_apilar(pila, &c);
	pila_apilar(pila, &d);

	elemento = pila_desapilar(pila);
	pa2m_afirmar(*(char *)elemento == d,
		     "Se puede desapilar el elemento D");
	pa2m_afirmar(pila_tamanio(pila) == 3, "La cantidad de elementos es 3");
	elemento = pila_tope(pila);
	pa2m_afirmar(*(char *)elemento == c, "El nuevo tope es c");

	elemento = pila_desapilar(pila);
	pa2m_afirmar(*(char *)elemento == c,
		     "Se puede desapilar el elemento C");
	pa2m_afirmar(pila_tamanio(pila) == 2, "La cantidad de elementos es 2");
	elemento = pila_tope(pila);
	pa2m_afirmar(*(char *)elemento == b, "El nuevo tope es B");

	elemento = pila_desapilar(pila);
	pa2m_afirmar(*(char *)elemento == b,
		     "Se puede desapilar el elemento b");
	pa2m_afirmar(pila_tamanio(pila) == 1, "La cantidad de elementos es 1");
	elemento = pila_tope(pila);
	pa2m_afirmar(*(char *)elemento == a, "El nuevo tope es a");

	elemento = pila_desapilar(pila);
	pa2m_afirmar(*(char *)elemento == a,
		     "Se puede desapilar el elemento A");
	pa2m_afirmar(pila_vacia(pila), "La cantidad de elementos es 0");
	elemento = pila_tope(pila);
	pa2m_afirmar(!elemento, "No se puede desapilar con una pila vacía");

	pila_destruir(pila);
}

void pruebas_pilas()
{
	test_pila_crear();
	test_pila_apilar();
	test_pila_desapilar();
}

int main()
{
	pa2m_nuevo_grupo(
		"======================== LISTAS ========================");
	pruebas_listas();

	pa2m_nuevo_grupo(
		"======================== COLAS ========================");
	pruebas_colas();

	pa2m_nuevo_grupo(
		"======================== PILAS ========================");
	pruebas_pilas();

	return pa2m_mostrar_reporte();
}
