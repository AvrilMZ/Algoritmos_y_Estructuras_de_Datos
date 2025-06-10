#ifndef INTERFAZ_VISUAL_H
#define INTERFAZ_VISUAL_H

#include <stdio.h>

#include "menu.h"
#include "juego.h"

// -------------------------------- MENÚ --------------------------------
/**
 * Imprime por pantalla el menú principal.
 */
void mostrar_menu_principal();

// -------------------------------- JUEGO --------------------------------
/**
 * Imprime por pantalla el juego dado.
 */
void mostrar_juego(juego_t *juego);

/**
 * Imprime por pantalla la información relevante del juego.
 */
void mostrar_info_util(juego_t *juego);

#endif // INTERFAZ_VISUAL_H