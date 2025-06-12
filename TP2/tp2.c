#include "src/interfaz_visual.h"
#include "extra/engine.h"
#include <ctype.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Uso: %s <archivo_pokedex.csv>\n", argv[0]);
		return 1;
	}

	pokedex_t *pokedex = pokedex_abrir(argv[1]);
	if (!pokedex) {
		return -1;
	}

	borrar_pantalla();
	mostrar_menu_principal(pokedex);

	return 0;
}
