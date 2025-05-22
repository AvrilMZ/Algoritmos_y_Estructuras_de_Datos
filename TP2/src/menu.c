#include "menu.h"

typedef struct opcion {
	void *dato;
	struct opcion *siguiente;
	menu_t *sub_seccion;
} opcion_t;

struct menu {
	opcion_t *primer_opcion;
};

menu_t *crear_menu()
{
}

bool agregar_subseccion(menu_t *menu, menu_t *subseccion)
{
}

bool insertar_opcion_en_seccion(menu_t *seccion, void *opcion)
{
}

bool eliminar_opcion_en_seccion(menu_t *seccion, void *opcion)
{
}

bool existe_opcion(menu_t *menu, void *opcion)
{
}

bool existe_opcion_en_seccion(menu_t *seccion, void *opcion)
{
}

void *buscar_opcion_en_seccion(menu_t *seccion, void *opcion)
{
}

menu_t *buscar_seccion_de_opcion(menu_t *menu, void *opcion)
{
}

bool menu_vacio(menu_t *menu)
{
}

size_t cantidad_opciones_seccion(menu_t *seccion)
{
}

void destruir_menu(menu_t *menu, void (*destructor)(void *))
{
}