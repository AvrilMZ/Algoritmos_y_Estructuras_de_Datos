#include <stdlib.h>
#include <stdio.h>
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

bool mostrar_int(void *elemento, void *contexto)
{
	int *posicion = contexto;

	int *n = (int *)elemento;
	printf("Elemento en posicion %i: %i\n", *posicion, *n);
	(*posicion)++;
	return true;
}

int main(int argc, char *argv[])
{
	//Este es el ejemplo que armamos en clase
	//Notar que no incluye ejemplos de cola y pila
	//Si la implementación es correcta, se deberían mostrar correctamente 3 veces
	//todos los elementos de la lista en el orden en que fueron insertados

	int uno = 1;
	int dos = 2;
	int tres = 3;

	lista_t *l = lista_crear();

	lista_insertar(l, &uno);
	lista_insertar(l, &dos);
	lista_insertar(l, &tres);

	printf("Muestro los elementos usando el iterador interno:\n");
	int posicion = 0;
	lista_iterar(l, mostrar_int, &posicion);

	printf("\nMuestro los elementos usando lista_obtener_elemento:\n");
	for (int i = 0; i < lista_tamanio(l); i++) {
		int *n = lista_obtener_elemento(l, i);
		printf("Elemento en posicion %i: %i\n", i, *n);
	}

	printf("\nMuestro los elementos usando el iterador externo:\n");
	posicion = 0;
	lista_iterador_t *li;
	for (li = lista_iterador_crear(l);
	     lista_iterador_quedan_elementos_por_recorrer(li);
	     lista_iterador_proxima_iteracion(li)) {
		int *n = lista_iterador_obtener_elemento(li);
		printf("Elemento en posicion %i: %i\n", posicion, *n);
		posicion++;
	}
	lista_iterador_destruir(li);

	lista_destruir(l);
	return 0;
}
