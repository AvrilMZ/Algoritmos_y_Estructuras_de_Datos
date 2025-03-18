#include "archivo.h"
#include <stdio.h>
#include <stdlib.h>

#define MODO_LECTURA "r"

const int TAMANO_CONST_BUFFER = 10;

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
	if (nombre == NULL) {
		printf("No se puedo abrir el archivo (null)\n");
		return NULL;
	}

	Archivo *archivo = malloc(sizeof(Archivo));
	if (archivo == NULL) {
		printf("Error reservando memoria\n");
		return NULL;
	}

	archivo->file = fopen(nombre, MODO_LECTURA);
	if (archivo->file == NULL) {
		printf("No se puedo abrir el archivo %s\n", nombre);
		free(archivo);
		return NULL;
	}
	archivo->lineas_leidas = 0;
	archivo->ultima_linea = NULL;

	return archivo;
}

/*
 * Lee una línea del archivo.
 *
 * Devuelve un puntero a la línea leída, o NULL si no hay más líneas.
 */
const char *archivo_leer_linea(Archivo *archivo)
{
	if (archivo == NULL || archivo->file == NULL) {
		return NULL;
	}

	if (archivo->ultima_linea) {
		free(archivo->ultima_linea);
		archivo->ultima_linea = NULL;
	}

	int caracter = fgetc(archivo->file);
	if (caracter == EOF) {
		return NULL;
	}

	char *linea = malloc(sizeof(char) * (size_t)TAMANO_CONST_BUFFER);
	if (linea == NULL) {
		printf("Error reservando memoria\n");
		return NULL;
	}

	int tamano_actual_buffer = TAMANO_CONST_BUFFER;
	int chars_leidos = 0;
	while (caracter != '\n' && caracter != EOF) {
		if (chars_leidos + 1 >= tamano_actual_buffer) {
			tamano_actual_buffer += TAMANO_CONST_BUFFER;
			char *nueva_linea =
			    realloc(linea, (size_t)tamano_actual_buffer);
			if (nueva_linea == NULL) {
				printf("Error reservando memoria\n");
				free(linea);
				if (archivo->ultima_linea) {
					free(archivo->ultima_linea);
					archivo->ultima_linea = NULL;
				}
				return NULL;
			}
			linea = nueva_linea;
		}
		linea[chars_leidos++] = (char)caracter;
		caracter = fgetc(archivo->file);
	}

	if (chars_leidos == 0 && caracter == '\n') {
		linea[chars_leidos++] = '\0';
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
	if (archivo == NULL || archivo->file == NULL) {
		return 0;
	}

	long posicion_actual = ftell(archivo->file);
	if (posicion_actual == -1) {
		printf("Error al obtener la posición del archivo\n");
		return 0;
	}

	int caracter = fgetc(archivo->file);
	if (caracter == EOF) {
		return 0;
	}

	fseek(archivo->file, posicion_actual, SEEK_SET);
	return 1;
}

/*
 * Devuelve la cantidad de líneas leídas hasta el momento.
 *
 * Devuelve 0 si el archivo es NULL.
 */
int archivo_lineas_leidas(Archivo *archivo)
{
	if (archivo == NULL) {
		return 0;
	}
	return archivo->lineas_leidas;
}

/*
 * Cierra el archivo y libera toda la memoria reservada.
 */
void archivo_cerrar(Archivo *archivo)
{
	if (archivo != NULL) {
		if (archivo->file != NULL) {
			fclose(archivo->file);
		}
		if (archivo->ultima_linea) {
			free(archivo->ultima_linea);
		}
		free(archivo);
	}
}