#include "menu.h"

typedef struct opcion {
	menu_t *sub_seccion;
	struct opcion *siguiente;
	void *dato;
} opcion_t;

struct menu {
	menu_t *menu_padre;
	opcion_t *primer_opcion;
	size_t cantidad_opciones;
};

struct iterador_menu {
	menu_t *menu;
	opcion_t *actual;
	opcion_t *anterior;
};

// -------------------------------- MENÚ --------------------------------
menu_t *crear_menu()
{
	menu_t *menu = calloc(1, sizeof(menu_t));
	if (!menu) {
		return NULL;
	}
	return menu;
}

menu_t *obtener_menu_padre(menu_t *menu)
{
	if (!menu) {
		return NULL;
	}
	return menu->menu_padre;
}

bool insertar_opcion_en_seccion(menu_t *seccion, void *opcion)
{
	if (!seccion || !opcion) {
		return false;
	}

	opcion_t *nueva_opcion = calloc(1, sizeof(opcion_t));
	if (!nueva_opcion) {
		return false;
	}

	nueva_opcion->dato = opcion;
	nueva_opcion->siguiente = NULL;
	nueva_opcion->sub_seccion = NULL;

	if (!seccion->primer_opcion) {
		seccion->primer_opcion = nueva_opcion;
	} else {
		opcion_t *actual = seccion->primer_opcion;
		while (actual->siguiente) {
			actual = actual->siguiente;
		}
		actual->siguiente = nueva_opcion;
	}
	seccion->cantidad_opciones++;

	return true;
}

bool eliminar_opcion_en_seccion(menu_t *seccion, void *opcion,
				bool (*cmp)(void *a, void *b))
{
	if (menu_vacio(seccion) || !opcion) {
		return false;
	}

	opcion_t *actual = seccion->primer_opcion;
	opcion_t *anterior = NULL;
	bool eliminado = false;
	while (!eliminado && actual) {
		bool iguales = false;
		if (cmp) {
			iguales = cmp(actual->dato, opcion);
		} else {
			iguales = (actual->dato == opcion);
		}

		if (iguales) {
			if (anterior) {
				anterior->siguiente = actual->siguiente;
			} else {
				seccion->primer_opcion = actual->siguiente;
			}

			if (actual->sub_seccion) {
				destruir_menu(actual->sub_seccion, NULL);
			}
			free(actual);
			seccion->cantidad_opciones--;
			eliminado = true;
		} else {
			anterior = actual;
			actual = actual->siguiente;
		}
	}
	return eliminado;
}

bool existe_opcion_en_seccion(menu_t *seccion, void *opcion,
			      bool (*cmp)(void *a, void *b))
{
	if (menu_vacio(seccion) || !opcion) {
		return false;
	}

	opcion_t *actual = seccion->primer_opcion;
	bool encontrado = false;
	while (!encontrado && actual) {
		if (cmp) {
			encontrado = cmp(actual->dato, opcion);
		} else {
			encontrado = (actual->dato == opcion);
		}
		actual = actual->siguiente;
	}
	return encontrado;
}

menu_t *obtener_subseccion_de_opcion(menu_t *menu, void *opcion,
				     bool (*cmp)(void *a, void *b))
{
	if (!menu || !opcion) {
		return NULL;
	}

	menu_t *subseccion = NULL;
	opcion_t *actual = menu->primer_opcion;
	bool encontrado = false;
	while (!encontrado && actual) {
		bool iguales = false;
		if (cmp) {
			iguales = cmp(actual->dato, opcion);
		} else {
			iguales = (actual->dato == opcion);
		}

		if (iguales) {
			subseccion = actual->sub_seccion;
			encontrado = true;
		}

		actual = actual->siguiente;
	}
	return subseccion;
}

size_t cantidad_opciones_seccion(menu_t *seccion)
{
	if (!seccion) {
		return 0;
	}

	return seccion->cantidad_opciones;
}

bool agregar_subseccion_a_opcion(menu_t *menu, void *opcion_dato,
				 menu_t *subseccion,
				 bool (*cmp)(void *a, void *b))
{
	if (!menu || !opcion_dato || !subseccion) {
		return false;
	}

	if (menu == subseccion) {
		return false;
	}

	opcion_t *actual = menu->primer_opcion;
	bool agregado = false;
	while (!agregado && actual) {
		bool iguales = false;
		if (cmp) {
			iguales = cmp(actual->dato, opcion_dato);
		} else {
			iguales = (actual->dato == opcion_dato);
		}

		if (iguales) {
			if (actual->sub_seccion) {
				destruir_menu(actual->sub_seccion, NULL);
			}
			actual->sub_seccion = subseccion;
			subseccion->menu_padre = menu;
			agregado = true;
		}

		actual = actual->siguiente;
	}
	return agregado;
}

bool menu_vacio(menu_t *menu)
{
	return !menu || !menu->primer_opcion;
}

void destruir_menu(menu_t *menu, void (*destructor)(void *))
{
	if (!menu) {
		return;
	}

	opcion_t *actual = menu->primer_opcion;
	while (actual) {
		opcion_t *siguiente = actual->siguiente;

		if (actual->sub_seccion) {
			destruir_menu(actual->sub_seccion, destructor);
		}

		if (destructor && actual->dato) {
			destructor(actual->dato);
		}

		free(actual);
		actual = siguiente;
	}

	free(menu);
}

// -------------------------------- ITERADOR EXTERNO --------------------------------
iterador_menu_t *crear_iterador_menu(menu_t *menu)
{
	if (!menu) {
		return NULL;
	}

	iterador_menu_t *iterador = calloc(1, sizeof(iterador_menu_t));
	if (!iterador) {
		return NULL;
	}

	iterador->menu = menu;
	iterador->actual = menu->primer_opcion;
	return iterador;
}

bool iterador_tiene_siguiente(iterador_menu_t *iterador)
{
	return iterador && iterador->actual;
}

void *iterador_siguiente(iterador_menu_t *iterador)
{
	if (!iterador || !iterador->actual) {
		return NULL;
	}

	void *dato = iterador->actual->dato;
	if (dato) {
		iterador->anterior = iterador->actual;
		iterador->actual = iterador->actual->siguiente;
	}
	return dato;
}

menu_t *iterador_obtener_subseccion_actual(iterador_menu_t *iterador)
{
	if (!iterador || !iterador->anterior) {
		return NULL;
	}
	return iterador->anterior->sub_seccion;
}

menu_t *iterador_obtener_menu_padre(iterador_menu_t *iterador)
{
	if (!iterador || !iterador->anterior) {
		return NULL;
	}
	return iterador->menu->menu_padre;
}

void iterador_reiniciar(iterador_menu_t *iterador, menu_t *menu)
{
	if (!iterador || menu_vacio(menu)) {
		return;
	}
	iterador->menu = menu;
	iterador->actual = menu->primer_opcion;
	iterador->anterior = NULL;
}

void destruir_iterador_menu(iterador_menu_t *iterador)
{
	free(iterador);
}