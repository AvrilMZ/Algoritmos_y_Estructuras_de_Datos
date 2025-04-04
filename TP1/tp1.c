#include "src/pokedex.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define ROJO "\x1b[31;1m"
#define AMARILLO "\x1b[33;1m"
#define NORMAL "\x1b[0m"
#define TIPO_INVALIDO -1
const char *EMOJI_AGUA = "\U0001F30A";
const char *EMOJI_FUEGO = "\U0001F525";
const char *EMOJI_PLANTA = "\U0001F33F";
const char *EMOJI_ROCA = "\U0001FAA8";
const char *EMOJI_ELECTRICO = "\U000026A1";
const char *EMOJI_NORMAL = "\U0001F464";
const char *EMOJI_LUCHA = "\U0001F94A";

// Devuelve true si ambos strings son iguales en minúscula, de lo contrario devuelve false.
bool son_iguales_en_lowercase(const char *string1, const char *string2)
{
	bool son_iguales = true;
	while (*string1 && *string2 && son_iguales) {
		int char1 = tolower((unsigned char)*string1);
		int char2 = tolower((unsigned char)*string2);
		if (char1 != char2) {
			son_iguales = false;
		}
		string1++;
		string2++;
	}
	if (*string1 != *string2) {
		son_iguales = false;
	}

	return son_iguales;
}

// Devuelve la equivalencia de un string en formato 'tipo_pokemon', si no hay devuelve 'TIPO_INVALIDO'.
tipo_pokemon obtener_tipo_pokemon(const char *str)
{
	if (!str || !*str) {
		return TIPO_INVALIDO;
	}

	if (son_iguales_en_lowercase(str, "agua") ||
	    son_iguales_en_lowercase(str, "a")) {
		return TIPO_AGUA;
	} else if (son_iguales_en_lowercase(str, "fuego") ||
		   son_iguales_en_lowercase(str, "f")) {
		return TIPO_FUEGO;
	} else if (son_iguales_en_lowercase(str, "planta") ||
		   son_iguales_en_lowercase(str, "p")) {
		return TIPO_PLANTA;
	} else if (son_iguales_en_lowercase(str, "roca") ||
		   son_iguales_en_lowercase(str, "r")) {
		return TIPO_ROCA;
	} else if (son_iguales_en_lowercase(str, "electrico") ||
		   son_iguales_en_lowercase(str, "e")) {
		return TIPO_ELECTRICO;
	} else if (son_iguales_en_lowercase(str, "normal") ||
		   son_iguales_en_lowercase(str, "n")) {
		return TIPO_NORMAL;
	} else if (son_iguales_en_lowercase(str, "lucha") ||
		   son_iguales_en_lowercase(str, "l")) {
		return TIPO_LUCHA;
	}
	return TIPO_INVALIDO;
}

// Devuelve un string con específico según el tipo_pokemon pasado por parámetro.
const char *tipo_a_cadena(tipo_pokemon tipo)
{
	static char resultado[50];

	switch (tipo) {
	case TIPO_AGUA:
		strcpy(resultado, EMOJI_AGUA);
		strcat(resultado, " Agua");
		return resultado;
	case TIPO_FUEGO:
		strcpy(resultado, EMOJI_FUEGO);
		strcat(resultado, " Fuego");
		return resultado;
	case TIPO_PLANTA:
		strcpy(resultado, EMOJI_PLANTA);
		strcat(resultado, " Planta");
		return resultado;
	case TIPO_ROCA:
		strcpy(resultado, EMOJI_ROCA);
		strcat(resultado, " Roca");
		return resultado;
	case TIPO_ELECTRICO:
		strcpy(resultado, EMOJI_ELECTRICO);
		strcat(resultado, " Eléctrico");
		return resultado;
	case TIPO_NORMAL:
		strcpy(resultado, EMOJI_NORMAL);
		strcat(resultado, " Normal");
		return resultado;
	case TIPO_LUCHA:
		strcpy(resultado, EMOJI_LUCHA);
		strcat(resultado, " Lucha");
		return resultado;
	}
	return "";
}

// --------------- FUNCIONES PARA `POKEDEX_ITERAR_POKEMONES` ---------------

// Imprime los datos del pokemon pasado por parámetro.
void mostrar_pokemon(const struct pokemon *pokemon)
{
	printf("%-12s (%3d) \t F%-3d D%-3d I%-3d \t %s\n", pokemon->nombre,
	       pokemon->id, pokemon->fuerza, pokemon->destreza,
	       pokemon->inteligencia, tipo_a_cadena(pokemon->tipo));
}

// Imprime los datos del pokemon pasado por parámetro.
bool imprimir_pokemon(struct pokemon *pokemon, void *ctx)
{
	printf("%-12s (%3d) \t F%-3d D%-3d I%-3d \t %s\n", pokemon->nombre,
	       pokemon->id, pokemon->fuerza, pokemon->destreza,
	       pokemon->inteligencia, tipo_a_cadena(pokemon->tipo));
	return true;
}

// Devuelve true si el pokemon pasado por parámetro no coincide con el ID buscado, de lo contrario lo imprime y devuelve false.
bool mostrar_pokemon_con_id(struct pokemon *pokemon, void *ctx)
{
	int *id = ctx;
	if (pokemon->id == *id) {
		mostrar_pokemon(pokemon);
		return false;
	}
	return true;
}

// Devuelve true si el pokemon pasado por parámetro no coincide con el nombre buscado, de lo contrario lo imprime y devuelve false.
bool mostrar_pokemon_con_nombre(struct pokemon *pokemon, void *ctx)
{
	char *nombre = ctx;
	if (son_iguales_en_lowercase(pokemon->nombre, nombre)) {
		mostrar_pokemon(pokemon);
		return false;
	}
	return true;
}

// Imprime el pokemon si su campo 'tipo' coincide con el buscado.
bool mostrar_pokemon_tipo(struct pokemon *pokemon, void *ctx)
{
	tipo_pokemon tipo = *((tipo_pokemon *)ctx);
	if (pokemon->tipo == tipo) {
		mostrar_pokemon(pokemon);
	}
	return true;
}

int main(int argc, char const *argv[])
{
	if (argc < 2) {
		printf("Uso: %s <archivo_pokedex.csv>\n", argv[0]);
		return 1;
	}

	pokedex_t *pokedex = pokedex_abrir(argv[1]);
	if (!pokedex) {
		printf("Error al abrir el archivo %s\n", argv[1]);
		return 1;
	}

	if (argc > 2) {
		if (son_iguales_en_lowercase(argv[2], "buscar")) {
			if (son_iguales_en_lowercase(argv[3], "id")) {
				int id = atoi(argv[4]);
				printf("%sPokemon buscado:%s\n", AMARILLO,
				       NORMAL);
				pokedex_iterar_pokemones(pokedex, ITERAR_ID,
							 mostrar_pokemon_con_id,
							 &id);
			} else if (son_iguales_en_lowercase(argv[3],
							    "nombre")) {
				char *nombre = (char *)argv[4];
				printf("%sPokemon buscado:%s\n", AMARILLO,
				       NORMAL);
				pokedex_iterar_pokemones(
					pokedex, ITERAR_NOMBRE,
					mostrar_pokemon_con_nombre, nombre);
			} else if (son_iguales_en_lowercase(argv[3], "tipo")) {
				tipo_pokemon tipo =
					obtener_tipo_pokemon(argv[4]);
				if (tipo == TIPO_INVALIDO) {
					printf("%sEl tipo '%s' es inválido%s\n",
					       ROJO, argv[4], NORMAL);
				} else {
					printf("%sPokemones de tipo %s:%s\n",
					       AMARILLO, argv[4], NORMAL);
					pokedex_iterar_pokemones(
						pokedex, ITERAR_ID,
						mostrar_pokemon_tipo, &tipo);
				}
			}
		} else if (son_iguales_en_lowercase(argv[2], "mostrar")) {
			if (son_iguales_en_lowercase(argv[3], "nombre")) {
				printf("%sPokemones ordenados por nombre:%s\n",
				       AMARILLO, NORMAL);
				pokedex_iterar_pokemones(pokedex, ITERAR_NOMBRE,
							 imprimir_pokemon,
							 NULL);
			} else if (son_iguales_en_lowercase(argv[3], "id")) {
				printf("%sPokemones ordenados por ID:%s\n",
				       AMARILLO, NORMAL);
				pokedex_iterar_pokemones(pokedex, ITERAR_ID,
							 imprimir_pokemon,
							 NULL);
			}
		}
	}

	pokedex_destruir(pokedex);

	return 0;
}
