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
typedef struct iterador_menu iterador_menu_t;

// -------------------------------- MENÚ --------------------------------
/**
 * Crea un menú vacío.
 * 
 * Devuelve un puntero al menú creado o NULL en caso de error.
 */
menu_t *crear_menu();

/**
 * Devuelve el menu padre.
 * 
 * En caso de error devuelve NULL.
 */
menu_t *obtener_menu_padre(menu_t *menu);

/**
 * Inserta una opción en la sección dada.
 * Permite elementos repetidos.
 * 
 * Devuelve true si se pudo insertar, false en caso contrario.
 */
bool insertar_opcion_en_seccion(menu_t *seccion, void *opcion);

/**
 * Elimina la primera aparición de la opción usando un comparador personalizado.
 * En caso de no pasar ningún comparador se comparan direcciones de memoria.
 * 
 * Devuelve true si eliminarla, en caso contrario false.
 */
bool eliminar_opcion_en_seccion(menu_t *seccion, void *opcion,
				bool (*cmp)(void *a, void *b));

/**
 * Devuelve true si existe la opción dada en la sección usando un comparador personalizado.
 * En caso de no pasar ningún comparador se comparan direcciones de memoria.
 * 
 * Si existe la opción devuelve true, en caso contrario false.
 */
bool existe_opcion_en_seccion(menu_t *seccion, void *opcion,
			      bool (*cmp)(void *a, void *b));

/**
 * Devuelve la subsección asociada a una opción específica.
 * En caso de no pasar ningún comparador se comparan direcciones de memoria.
 * 
 * En caso de error devuelve NULL.
 */
menu_t *obtener_subseccion_de_opcion(menu_t *menu, void *opcion,
				     bool (*cmp)(void *a, void *b));

/**
 * Devuelve la cantidad de opciones en la sección dada.
 */
size_t cantidad_opciones_seccion(menu_t *seccion);

/**
 * Agrega una nueva sub-sección a la opción dada, si ya existia se sobreescribe.
 * En caso de no pasar ningún comparador se comparan direcciones de memoria.
 * 
 * Devuelve true si se pudo agregar, false en caso contrario.
 */
bool agregar_subseccion_a_opcion(menu_t *menu, void *opcion_dato,
				 menu_t *subseccion,
				 bool (*cmp)(void *a, void *b));

/**
 * Devuelve true si el menú no contiene ninguna opción ni sub-sección.
 */
bool menu_vacio(menu_t *menu);

/**
 * Destruye el menú completo, incluyendo todas sus sub-secciones.
 * 
 * Si se pasa una función de destrucción, se aplica a cada opción almacenada.
 */
void destruir_menu(menu_t *menu, void (*destructor)(void *));

// -------------------------------- ITERADOR EXTERNO --------------------------------
/**
 * Crea un iterador externo para el menu dado.
 * 
 * Devuelve el iterador o NULL en caso de error.
 */
iterador_menu_t *crear_iterador_menu(menu_t *menu);

/**
 * Devuelve true el iterador tiene un siguiente, en caso contrario false.
 */
bool iterador_tiene_siguiente(iterador_menu_t *iterador);

/**
 * Avanza el iterador al siguiente.
 * 
 * Devuelve el dato actual o NULL en caso de error.
 */
void *iterador_siguiente(iterador_menu_t *iterador);

/**
 * Devuelve la subseccion actual del iterador.
 * 
 * En caso de error devuelve NULL.
 */
menu_t *iterador_obtener_subseccion_actual(iterador_menu_t *iterador);

/**
 * Devuelve el menú anterior del iterador.
 * 
 * En caso de error devuelve NULL.
 */
menu_t *iterador_obtener_menu_padre(iterador_menu_t *iterador);

/**
 * Reinicia el iterador al principio del menú.
 */
void iterador_reiniciar(iterador_menu_t *iterador, menu_t *menu);

/**
 * Destruye el iterador.
 * 
 * No destruye el menu.
 */
void destruir_iterador_menu(iterador_menu_t *iterador);

#endif // MENU_H