#include "archivo.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Abre un archivo DE TEXTO para su posterior lectura.
 *
 * Devuelve el archivo si se pudo abrir, NULL en caso contrario.
 */
Archivo *archivo_abrir(const char *nombre) {}

/*
 * Lee una línea del archivo.
 *
 * Devuelve un puntero a la línea leída, o NULL si no hay más líneas.
 */
const char *archivo_leer_linea(Archivo *archivo) {}

/*
 * Indica si hay más líneas por leer en el archivo.
 *
 * Devuelve 1 si hay más líneas, 0 en caso contrario.
 */
int archivo_hay_mas_lineas(Archivo *archivo) {}

/*
 * Devuelve la cantidad de líneas leídas hasta el momento.
 *
 * Devuelve 0 si el archivo es NULL.
 */
int archivo_lineas_leidas(Archivo *archivo) {}

/*
 * Cierra el archivo y libera toda la memoria reservada.
 */
void archivo_cerrar(Archivo *archivo) {}