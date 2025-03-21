#include "archivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODO_LECTURA "r"
const int CAPACIDAD_INICIAL = 16;

struct Archivo {
	FILE *file;
	int lineas_leidas;
	char *ultima_linea;
};

/*
 * Abre un archivo DE TEXTO para su posterior lectura.
 *
 * Devuelve el archivo si se pudo abrir, NULL en caso contrario.
 */
Archivo *archivo_abrir(const char *nombre)
{
	if (!nombre || !*nombre) {
		printf("No se pudo abrir el archivo\n");
		return NULL;
	}

	Archivo *archivo = malloc(sizeof(Archivo));
	if (!archivo) {
		printf("Error reservando memoria\n");
		return NULL;
	}

	archivo->file = fopen(nombre, MODO_LECTURA);
	if (!archivo->file) {
		free(archivo);
		printf("No se pudo abrir el archivo %s\n", nombre);
		return NULL;
	}

	archivo->lineas_leidas = 0;
	archivo->ultima_linea = NULL;
	return archivo;
}

// Reserva memoria para la línea y la inicializa.
char *reservar_memoria_linea(int capacidad)
{
	char *linea = malloc(sizeof(char) * (size_t)capacidad);
	if (!linea) {
		printf("Error reservando memoria\n");
		return NULL;
	}
	return linea;
}

// Realoca memoria para la línea y los bytes adicionales (si los hay) se inicializan en 0.
char *realocar_memoria_linea(char *linea, int capacidad)
{
	int capacidad_anterior = capacidad / 2;
	char *nueva_linea = realloc(linea, sizeof(char) * (size_t)capacidad);
	if (!nueva_linea) {
		printf("Error realocando memoria\n");
		return NULL;
	}
	memset(nueva_linea + capacidad_anterior, 0,
	       (size_t)(capacidad - capacidad_anterior));

	return nueva_linea;
}

/*
 * Lee una línea del archivo.
 *
 * Devuelve un puntero a la línea leída, o NULL si no hay más líneas.
 */
const char *archivo_leer_linea(Archivo *archivo)
{
	if (!archivo || !archivo->file) {
		return NULL;
	}

	if (archivo->ultima_linea) {
		free(archivo->ultima_linea);
		archivo->ultima_linea = NULL;
	}

	if (feof(archivo->file) != 0) {
		return NULL;
	}

	int capacidad = CAPACIDAD_INICIAL;
	char *linea = reservar_memoria_linea(capacidad);
	if (!linea) {
		return NULL;
	}

	int caracter = fgetc(archivo->file);
	int chars_leidos = 0;
	while (caracter != '\n' && feof(archivo->file) == 0) {
		if (chars_leidos + 1 >= capacidad) {
			capacidad *= 2;
			char *nueva_linea =
				realocar_memoria_linea(linea, capacidad);
			if (!nueva_linea) {
				free(linea);
				linea = NULL;
				return NULL;
			}
			linea = nueva_linea;
		}
		linea[chars_leidos++] = (char)caracter;
		caracter = fgetc(archivo->file);
	}

	linea[chars_leidos] = '\0';
	archivo->lineas_leidas++;
	archivo->ultima_linea = linea;
	return linea;
}

/*
 * Indica si hay más líneas por leer en el archivo.
 *
 * Devuelve 1 si hay más líneas, 0 en caso contrario.
 */
int archivo_hay_mas_lineas(Archivo *archivo)
{
	if (!archivo || !archivo->file) {
		return 0;
	}
	return !feof(archivo->file);
}

/*
 * Devuelve la cantidad de líneas leídas hasta el momento.
 *
 * Devuelve 0 si el archivo es NULL.
 */
int archivo_lineas_leidas(Archivo *archivo)
{
	if (!archivo) {
		return 0;
	}
	return archivo->lineas_leidas;
}

/*
 * Cierra el archivo y libera toda la memoria reservada.
 */
void archivo_cerrar(Archivo *archivo)
{
	if (archivo) {
		if (archivo->file) {
			fclose(archivo->file);
			archivo->file = NULL;
		}
		if (archivo->ultima_linea) {
			free(archivo->ultima_linea);
			archivo->ultima_linea = NULL;
		}
		free(archivo);
		archivo = NULL;
	}
}