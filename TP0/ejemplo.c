#include "src/archivo.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if (argc < 2) {
		printf("Error de invocacion, debe incluir un archivo\n");
		return -1;
	}

	const char *nombre = argv[1];
	Archivo *archivo = archivo_abrir(nombre);
	if (archivo == NULL) {
		printf("Error al abrir el archivo\n");
		return -1;
	}

	for (int i = 0; archivo_hay_mas_lineas(archivo); i++) {
		const char *linea = archivo_leer_linea(archivo);
		printf("Linea %d: %s\n", i, linea);
	}

	printf("Total de líneas leidas: %d\n", archivo_lineas_leidas(archivo));

	archivo_cerrar(archivo);

	return 0;
}
