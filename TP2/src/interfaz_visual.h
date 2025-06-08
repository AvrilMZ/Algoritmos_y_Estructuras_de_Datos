#ifndef INTERFAZ_VISUAL_H
#define INTERFAZ_VISUAL_H

#include "menu.h"
#include "juego.h"

/**
 * Imprime por pantalla todas las opciones del menú dado.
 */
void mostrar_seccion_menu(menu_t *menu);

/**
 * Imprime por pantalla el juego dado.
 */
void mostrar_juego(juego_t *juego);

/**
 * 
 */
void mostrar_info_util(juego_t *juego);

#endif // INTERFAZ_VISUAL_H