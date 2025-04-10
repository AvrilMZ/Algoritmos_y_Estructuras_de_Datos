#include <stdlib.h>
#include <stdio.h>
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

#define AMARILLO "\x1b[33;1m"
#define NORMAL "\x1b[0m"

bool mostrar_int(void *elemento, void *contexto)
{
	int *posicion = contexto;

	int *n = (int *)elemento;
	printf("\tPosición %i: %i\n", *posicion, *n);
	(*posicion)++;
	return true;
}

int main(int argc, char *argv[])
{
	printf("\n%s---------------- LISTA ----------------%s\n", AMARILLO,
	       NORMAL);
	int uno = 1;
	int dos = 2;
	int tres = 3;

	lista_t *l = lista_crear();

	lista_insertar(l, &uno);
	lista_insertar_en_posicion(l, 1, &dos);
	lista_insertar(l, &tres);

	printf("\nMuestro los elementos usando el iterador interno:\n");
	int posicion = 0;
	lista_iterar(l, mostrar_int, &posicion);

	printf("\nMuestro los elementos usando lista_obtener_elemento:\n");
	for (int i = 0; i < lista_tamanio(l); i++) {
		int *n = lista_obtener_elemento(l, i);
		printf("\tPosición %i: %i\n", i, *n);
	}

	printf("\nMuestro los elementos usando el iterador externo:\n");
	posicion = 0;
	lista_iterador_t *li;
	for (li = lista_iterador_crear(l);
	     lista_iterador_quedan_elementos_por_recorrer(li);
	     lista_iterador_proxima_iteracion(li)) {
		int *n = lista_iterador_obtener_elemento(li);
		printf("\tPosición %i: %i\n", posicion, *n);
		posicion++;
	}
	lista_iterador_destruir(li);
	lista_destruir(l);

	printf("\n%s---------------- COLA ----------------%s\n", AMARILLO,
	       NORMAL);
	int cuatro = 4;
	int cinco = 5;
	int seis = 6;

	cola_t *c = cola_crear();

	printf("\nEncolo elementos: 4, 5, 6\n");
	cola_encolar(c, &cuatro);
	cola_encolar(c, &cinco);
	cola_encolar(c, &seis);

	printf("\nMuestro y desencolo los elementos:\n");
	int posicion_cola = 0;
	while (!cola_vacia(c)) {
		int *elemento = cola_frente(c);
		printf("\tPosición %i: %i\n", posicion_cola, *elemento);
		cola_desencolar(c);
		posicion_cola++;
	}
	cola_destruir(c);

	printf("\n%s---------------- PILA ----------------%s\n", AMARILLO,
	       NORMAL);
	int siete = 7;
	int ocho = 8;
	int nueve = 9;

	pila_t *p = pila_crear();

	printf("\nApilo elementos: 7, 8, 9\n");
	pila_apilar(p, &siete);
	pila_apilar(p, &ocho);
	pila_apilar(p, &nueve);

	printf("\nMuestro y desapilo los elementos:\n");
	int posicion_pila = 0;
	while (!pila_vacia(p)) {
		int *elemento = pila_tope(p);
		printf("\tPosición %i: %i\n", posicion_pila, *elemento);
		pila_desapilar(p);
		posicion_pila++;
	}
	pila_destruir(p);

	return 0;
}
