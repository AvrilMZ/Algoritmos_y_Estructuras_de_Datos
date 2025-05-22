/**
 * TDA menu_t
 *
 * Representa un menú jerárquico implementado como un árbol.
 * Cada nodo del árbol es una sección (menu_t), que puede contener opciones (void *) y sub-secciones (otros menu_t).
 */

#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct menu menu_t;

/**
  * Crea un menú vacío.
  * 
  * Devuelve un puntero al menú creado o NULL en caso de error.
  */
menu_t *crear_menu();

/**
  * Agrega una nueva sub-sección al menú dado.
  * 
  * Devuelve true si se pudo agregar, false en caso contrario.
  */
bool agregar_subseccion(menu_t *menu, menu_t *subseccion);

/**
  * Inserta una opción en la sección dada.
  * 
  * Permite elementos repetidos.
  * Devuelve true si se pudo insertar, false en caso contrario.
  */
bool insertar_opcion_en_seccion(menu_t *seccion, void *opcion);

/**
  * Elimina la primera aparición de la opción en la sección dada.
  * 
  * Devuelve true si se pudo eliminar, false en caso contrario.
  */
bool eliminar_opcion_en_seccion(menu_t *seccion, void *opcion);

/**
  * Recorre todo el menú y devuelve true si existe la opción dada, false en caso contrario.
  */
bool existe_opcion(menu_t *menu, void *opcion);

/**
  * Devuelve true si existe la opción dada en la sección, false en caso contrario.
  */
bool existe_opcion_en_seccion(menu_t *seccion, void *opcion);

/**
 * Busca la opción en la sección dada.
 * 
 * Devuelve un puntero a la opción si se encuentra, o NULL si no existe.
 */
void *buscar_opcion_en_seccion(menu_t *seccion, void *opcion);

/**
 * Recorre todo el menú y busca la sección que contiene la opción dada.
 * 
 * Devuelve un puntero a esa sección, o NULL si no se encuentra.
 * 
 * Las opciones se comparan por dirección de memoria.
 */
menu_t *buscar_seccion_de_opcion(menu_t *menu, void *opcion);

/**
  * Devuelve true si el menú no contiene ninguna opción ni sub-sección.
  */
bool menu_vacio(menu_t *menu);

/**
  * Devuelve la cantidad de opciones en la sección dada.
  */
size_t cantidad_opciones_seccion(menu_t *seccion);

/**
  * Destruye el menú completo, incluyendo todas sus sub-secciones.
  * 
  * Si se pasa una función de destrucción, se aplica a cada opción almacenada.
  */
void destruir_menu(menu_t *menu, void (*destructor)(void *));

#endif // MENU_H