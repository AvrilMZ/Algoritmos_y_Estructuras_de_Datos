#include "../extra/ansi.h"
#include "../extra/engine.h"
#include "interfaz_visual.h"
#include <string.h>
#include <ctype.h>

#define TECLA_W 'w'
#define TECLA_S 's'
#define TECLA_D 'd'
#define TECLA_A 'a'
#define JUGADOR '@'
#define GANO_JUGADOR_1 1
#define GANO_JUGADOR_2 -1
#define SIGUEN_JUGANDO 0

const char JUGAR = 'J';
const char JUGAR_CON_SEMILLA = 'S';
const char BUSCAR = 'B';
const char BUSCAR_POR_NOMBRE = 'N';
const char BUSCAR_POR_ID = 'I';
const char MOSTRAR = 'M';
const char MOSTRAR_POR_NOMBRE = 'N';
const char MOSTRAR_POR_ID = 'I';
const char MENU_ANTERIOR = 'A';
const char SALIR_DEL_JUEGO = 'Q';

const char *EMOJI_AGUA = "\U0001F30A";
const char *EMOJI_FUEGO = "\U0001F525";
const char *EMOJI_PLANTA = "\U0001F33F";
const char *EMOJI_ROCA = "\U0001FAA8";
const char *EMOJI_ELECTRICO = "\U000026A1";
const char *EMOJI_NORMAL = "\U0001F464";
const char *EMOJI_LUCHA = "\U0001F94A";

typedef enum {
	ACCION_JUGAR,
	ACCION_JUGAR_SEMILLA,
	ACCION_BUSCAR_NOMBRE,
	ACCION_BUSCAR_ID,
	ACCION_MOSTRAR_NOMBRE,
	ACCION_MOSTRAR_ID,
	ACCION_MENU_ANTERIOR,
	ACCION_SALIR,
	ACCION_SUBSECCION
} tipo_accion_t;

typedef struct opcion_menu {
	char caracter;
	char *texto;
	tipo_accion_t tipo_accion;
} opcion_menu_t;

// -------------------------------- MENÚ PRINCIPAL--------------------------------
/**
 * Devuelve true si el char de entrada es igual al de caracter, en caso contrario false.
 */
bool comparar_opciones_por_caracter(void *opcion, void *caracter)
{
	opcion_menu_t *option = (opcion_menu_t *)opcion;
	char *character = (char *)caracter;

	return tolower(option->caracter) == tolower(*character);
}

/** 
 * Crea y devuelve un puntero a una opcion_menu_t.
 * 
 * En caso de error devuelve NULL.
 */
opcion_menu_t *crear_opcion_menu(char caracter, const char *texto,
				 tipo_accion_t tipo_accion)
{
	opcion_menu_t *opcion = calloc(1, sizeof(opcion_menu_t));
	if (!opcion) {
		return NULL;
	}
	opcion->caracter = caracter;
	opcion->tipo_accion = tipo_accion;

	opcion->texto = calloc(strlen(texto) + 1, sizeof(char));
	if (!opcion->texto) {
		free(opcion);
		return NULL;
	}
	strcpy(opcion->texto, texto);

	return opcion;
}

/**
 * Funcion destructora para un dato opcion_menu_t.
 */
void destruir_opcion_menu(void *opcion)
{
	if (!opcion) {
		return;
	}

	opcion_menu_t *destruir = (opcion_menu_t *)opcion;
	free(destruir->texto);
	free(destruir);
}

/**
 * Crea y devuelve la seccion principal del menu.
 */
menu_t *crear_seccion_principal()
{
	menu_t *seccion_principal = crear_menu();
	if (!seccion_principal) {
		return NULL;
	}

	opcion_menu_t *jugar = crear_opcion_menu(JUGAR, "Jugar", ACCION_JUGAR);
	opcion_menu_t *jugar_semilla = crear_opcion_menu(
		JUGAR_CON_SEMILLA, "Jugar con semilla", ACCION_JUGAR_SEMILLA);
	opcion_menu_t *buscar =
		crear_opcion_menu(BUSCAR, "Buscar", ACCION_SUBSECCION);
	opcion_menu_t *mostrar =
		crear_opcion_menu(MOSTRAR, "Mostrar", ACCION_SUBSECCION);
	opcion_menu_t *salir =
		crear_opcion_menu(SALIR_DEL_JUEGO, "Salir", ACCION_SALIR);

	if (!jugar || !jugar_semilla || !buscar || !mostrar || !salir) {
		destruir_opcion_menu(jugar);
		destruir_opcion_menu(jugar_semilla);
		destruir_opcion_menu(buscar);
		destruir_opcion_menu(mostrar);
		destruir_opcion_menu(salir);
		destruir_menu(seccion_principal, NULL);
		return NULL;
	}

	insertar_opcion_en_seccion(seccion_principal, jugar);
	insertar_opcion_en_seccion(seccion_principal, jugar_semilla);
	insertar_opcion_en_seccion(seccion_principal, buscar);
	insertar_opcion_en_seccion(seccion_principal, mostrar);
	insertar_opcion_en_seccion(seccion_principal, salir);

	return seccion_principal;
}

/**
 * Crea y enlaza la subseccion de buscar al menu principal.
 * 
 * Devuelve true si se pudo agregar la subseccion, en caso contrario false.
 */
bool agregar_subseccion_buscar(menu_t *menu_principal)
{
	menu_t *subseccion = crear_menu();
	if (!subseccion) {
		return false;
	}

	opcion_menu_t *b_nombre = crear_opcion_menu(
		BUSCAR_POR_NOMBRE, "Buscar por nombre", ACCION_BUSCAR_NOMBRE);
	opcion_menu_t *b_id = crear_opcion_menu(BUSCAR_POR_ID, "Buscar por ID",
						ACCION_BUSCAR_ID);
	opcion_menu_t *menu_anterior = crear_opcion_menu(
		MENU_ANTERIOR, "Menu anterior", ACCION_MENU_ANTERIOR);

	if (!b_nombre || !b_id || !menu_anterior) {
		destruir_opcion_menu(b_nombre);
		destruir_opcion_menu(b_id);
		destruir_opcion_menu(menu_anterior);
		destruir_menu(subseccion, NULL);
		return false;
	}

	insertar_opcion_en_seccion(subseccion, b_nombre);
	insertar_opcion_en_seccion(subseccion, b_id);
	insertar_opcion_en_seccion(subseccion, menu_anterior);

	return agregar_subseccion_a_opcion(menu_principal, (void *)&BUSCAR,
					   subseccion,
					   comparar_opciones_por_caracter);
}

/**
 * Crea y enlaza la subseccion de mostrar al menu principal.
 * 
 * Devuelve true si se pudo agregar la subseccion, en caso contrario false.
 */
bool agregar_subseccion_mostrar(menu_t *menu_principal)
{
	menu_t *subseccion = crear_menu();
	if (!subseccion) {
		return false;
	}

	opcion_menu_t *m_nombre = crear_opcion_menu(MOSTRAR_POR_NOMBRE,
						    "Mostrar por nombre",
						    ACCION_MOSTRAR_NOMBRE);
	opcion_menu_t *m_id = crear_opcion_menu(
		MOSTRAR_POR_ID, "Mostrar por ID", ACCION_MOSTRAR_ID);
	opcion_menu_t *menu_anterior = crear_opcion_menu(
		MENU_ANTERIOR, "Menu anterior", ACCION_MENU_ANTERIOR);

	if (!m_nombre || !m_id || !menu_anterior) {
		destruir_opcion_menu(m_nombre);
		destruir_opcion_menu(m_id);
		destruir_opcion_menu(menu_anterior);
		destruir_menu(subseccion, NULL);
		return false;
	}

	insertar_opcion_en_seccion(subseccion, m_nombre);
	insertar_opcion_en_seccion(subseccion, m_id);
	insertar_opcion_en_seccion(subseccion, menu_anterior);

	return agregar_subseccion_a_opcion(menu_principal, (void *)&MOSTRAR,
					   subseccion,
					   comparar_opciones_por_caracter);
}

/**
 * Devulve y crea el menu con todas las subsecciones agregadas.
 */
menu_t *crear_menu_completo()
{
	menu_t *menu = crear_seccion_principal();
	if (!menu) {
		return NULL;
	}

	if (!agregar_subseccion_buscar(menu)) {
		destruir_menu(menu, destruir_opcion_menu);
		return NULL;
	}

	if (!agregar_subseccion_mostrar(menu)) {
		destruir_menu(menu, destruir_opcion_menu);
		return NULL;
	}

	return menu;
}

// -------------------------------- POKEDEX --------------------------------

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
	mostrar_pokemon(pokemon);
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

/**
 * Maneja la acción 'buscar' deseada.
 */
void manejar_busqueda(pokedex_t *pokedex, char opcion)
{
	if (!pokedex) {
		return;
	}

	if (opcion == BUSCAR_POR_NOMBRE) {
		char nombre[100];
		printf("Ingrese el nombre del pokémon: ");
		if (scanf("%99s", nombre) != 1) {
			return;
		}
		printf("%sPokemon buscado:%s\n", ANSI_COLOR_YELLOW,
		       ANSI_COLOR_RESET);
		unsigned encontrados = pokedex_iterar_pokemones(
			pokedex, ITERAR_NOMBRE, mostrar_pokemon_con_nombre,
			nombre);
		if (encontrados == 0) {
			printf("No se encontró ningún pokémon con el nombre '%s'\n",
			       nombre);
		}
	} else if (opcion == BUSCAR_POR_ID) {
		int id;
		printf("Ingrese el ID del pokémon: ");
		if (scanf("%d", &id) != 1) {
			return;
		}
		printf("%sPokemon buscado:%s\n", ANSI_COLOR_YELLOW,
		       ANSI_COLOR_RESET);
		unsigned encontrados = pokedex_iterar_pokemones(
			pokedex, ITERAR_ID, mostrar_pokemon_con_id, &id);
		if (encontrados == 0) {
			printf("No se encontró ningún pokémon con el ID %d\n",
			       id);
		}
	}
}

/**
 * Maneja la acción 'mostrar' deseada.
 */
void manejar_mostrar(pokedex_t *pokedex, char opcion)
{
	if (!pokedex) {
		return;
	}

	if (opcion == MOSTRAR_POR_NOMBRE) {
		printf("%sPokemones ordenados por nombre:%s\n",
		       ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
		pokedex_iterar_pokemones(pokedex, ITERAR_NOMBRE,
					 imprimir_pokemon, NULL);
	} else if (opcion == MOSTRAR_POR_ID) {
		printf("%sPokemones ordenados por ID:%s\n", ANSI_COLOR_YELLOW,
		       ANSI_COLOR_RESET);
		pokedex_iterar_pokemones(pokedex, ITERAR_ID, imprimir_pokemon,
					 NULL);
	}
}

// -------------------------------- JUEGO --------------------------------
/**
 * 
 */
unsigned int preguntar_semilla()
{
	unsigned int semilla = (unsigned int)rand();
	printf("Ingrese la semilla: ");
	if (scanf("%u", &semilla) != 1) {
		return 0;
	}
	return semilla;
}

// Función auxiliar para obtener color por tipo de pokémon
const char *obtener_color_por_tipo(tipo_pokemon tipo)
{
	switch (tipo) {
	case TIPO_AGUA:
		return ANSI_COLOR_BLUE;
	case TIPO_FUEGO:
		return ANSI_COLOR_RED;
	case TIPO_PLANTA:
		return ANSI_COLOR_GREEN;
	case TIPO_ROCA:
		return ANSI_COLOR_CYAN;
	case TIPO_ELECTRICO:
		return ANSI_COLOR_YELLOW;
	case TIPO_NORMAL:
		return ANSI_COLOR_BLACK;
	case TIPO_LUCHA:
		return ANSI_COLOR_MAGENTA;
	default:
		return ANSI_COLOR_RESET;
	}
}

/**
 * Muestra información detallada de un jugador específico
 */
void mostrar_info_detallada_jugador(juego_t *juego, int num_jugador)
{
	if (!juego) {
		return;
	}

	printf("\nJugador %i:\n", num_jugador);

	printf("Últimos capturados: ");
	size_t total_capturados = obtener_cantidad_pokes_capturados(juego);
	if (total_capturados == 0) {
		printf("Ninguno");
	} else {
		int inicio = (int)total_capturados - 3;
		if (inicio < 0) {
			inicio = 0;
		}

		for (int i = inicio; i < (int)total_capturados; i++) {
			struct pokemon *pokemon =
				obtener_pokemon_capturado(juego, i);
			if (pokemon) {
				printf("%s", pokemon->nombre);
				if (i < (int)total_capturados - 1) {
					printf(", ");
				}
			}
		}
	}
	printf("\n");

	printf("Próximo a capturar: ");
	if (obtener_cantidad_pokes_pendientes(juego) > 0) {
		struct pokemon *proximo = obtener_pokemon_pendiente_tope(juego);
		if (proximo) {
			const char *color =
				obtener_color_por_tipo(proximo->tipo);
			printf("%s%s%s", color, tipo_a_cadena(proximo->tipo),
			       ANSI_COLOR_RESET);
		} else {
			printf("Desconocido");
		}
	} else {
		printf("Ninguno");
	}
	printf("\n");

	printf("Puntos: %u\n", obtener_puntos_jugador(juego));
	printf("\n");
}

const char *obtener_color_tipo_pokemon(char contenido, juego_t *juego, int fila,
				       int columna)
{
	struct pokemon *pokemon =
		obtener_pokemon_en_posicion(juego, fila, columna);
	if (!pokemon) {
		return ANSI_COLOR_RESET;
	}

	return obtener_color_por_tipo(pokemon->tipo);
}

void mostrar_juegos(conexion_juegos_t *conexion)
{
	if (!conexion) {
		return;
	}

	borrar_pantalla();

	int tiempo_restante = obtener_tiempo_restante(conexion);
	printf("%sTiempo restante: %d segundos%s\n\n", ANSI_COLOR_YELLOW,
	       tiempo_restante, ANSI_COLOR_RESET);

	mostrar_info_detallada_jugador(obtener_juego(conexion, 0), 0);
	mostrar_info_detallada_jugador(obtener_juego(conexion, 1), 1);

	for (int i = 0; i < MAX_FILAS; i++) {
		for (int k = 0; k < MAX_JUGADORES; k++) {
			juego_t *juego = obtener_juego(conexion, k);

			for (int j = 0; j < MAX_COLUMNAS; j++) {
				char contenido =
					obtener_contenido_posicion(juego, i, j);
				const char *color = ANSI_COLOR_RESET;
				if (contenido != JUGADOR && contenido != ' ') {
					color = obtener_color_tipo_pokemon(
						contenido, juego, i, j);
				}
				printf("| %s%c%s ", color, contenido,
				       ANSI_COLOR_RESET);
			}
			printf("|");

			if (k < MAX_JUGADORES - 1) {
				printf("\t\t");
			}
		}
		printf("\n");
	}
}

/**
 * Devuelve true si la acción dada es válida, de lo contrario false.
 */
bool es_movimiento_valido(int accion)
{
	return (accion == TECLA_W || accion == TECLA_S || accion == TECLA_D ||
		accion == TECLA_A || accion == TECLA_ARRIBA ||
		accion == TECLA_ABAJO || accion == TECLA_IZQUIERDA ||
		accion == TECLA_DERECHA);
}

/**
 * Imprime un mensaje de cierre informando el ganador del juego según el estado dado.
 */
void cierre_juego(int estado)
{
	borrar_pantalla();
	if (estado == GANO_JUGADOR_1) {
		printf("GANA JUGADOR 1\n");
	} else if (estado == GANO_JUGADOR_2) {
		printf("GANA JUGADOR 2\n");
	}
	printf("¡Se acabó el tiempo!\n");
}

// Función callback para el game_loop
int callback_juego(int tecla, void *datos)
{
	conexion_juegos_t *conexion = (conexion_juegos_t *)datos;
	if (!conexion) {
		return 1;
	}

	if (es_movimiento_valido(tecla)) {
		realizar_jugada(conexion, tecla);
	}

	mostrar_juegos(conexion);

	if (estado_juego(conexion) != SIGUEN_JUGANDO) {
		return 1;
	}
	return 0;
}

/**
 * Maneja la lógica el juego.
 */
void manejar_juego(pokedex_t *pokedex, char opcion)
{
	if (!pokedex) {
		return;
	}

	unsigned int semilla = 0;
	if (opcion == JUGAR_CON_SEMILLA) {
		semilla = preguntar_semilla();
	}

	conexion_juegos_t *conexion = inicializar_juego(pokedex, semilla);
	if (!conexion) {
		return;
	}

	esconder_cursor();
	mostrar_juegos(conexion);
	game_loop(callback_juego, conexion);

	mostrar_cursor();
	cierre_juego(estado_juego(conexion));
	destruir_juego(conexion);
}

// -------------------------------- VISUALIZACION E INTERACCION --------------------------------

/**
 * Imprime por pantalla las opciones del menú dado.
 */
void mostrar_menu(menu_t *menu)
{
	if (!menu) {
		return;
	}

	iterador_menu_t *iterador = crear_iterador_menu(menu);
	if (!iterador) {
		return;
	}

	while (iterador_tiene_siguiente(iterador)) {
		opcion_menu_t *opcion =
			(opcion_menu_t *)iterador_siguiente(iterador);
		if (opcion) {
			printf("[%c] %s\n", opcion->caracter, opcion->texto);
		}
	}
	destruir_iterador_menu(iterador);
}

/**
 * Devuelve true si el carácter dado esta en la sección del menú, en caso contrario false.
 */
bool es_opcion_valida(menu_t *menu, char caracter)
{
	if (!menu) {
		return false;
	}
	return existe_opcion_en_seccion(menu, &caracter,
					comparar_opciones_por_caracter);
}

/**
 * Pide al usuario una opción del menú hasta que la ingresada sea válida.
 * 
 * Devulve el carácter ingresado.
 */
char menu_obtener_opcion_usuario(menu_t *menu)
{
	char opcion;
	mostrar_menu(menu);
	printf("\nSeleccione una opción: ");
	if (scanf(" %c", &opcion) != 1) {
		return SALIR_DEL_JUEGO;
	}

	while (!es_opcion_valida(menu, opcion)) {
		borrar_pantalla();
		mostrar_menu(menu);
		printf("Opción inválida. Intente nuevamente.\n\n");
		if (scanf(" %c", &opcion) != 1) {
			return SALIR_DEL_JUEGO;
		}
	}

	return opcion;
}

/**
 * Obtiene la opción del menú basándose en el carácter seleccionado
 */
opcion_menu_t *obtener_opcion_por_caracter(menu_t *menu, char caracter)
{
	if (!menu) {
		return NULL;
	}

	iterador_menu_t *iterador = crear_iterador_menu(menu);
	if (!iterador) {
		return NULL;
	}

	opcion_menu_t *opcion_encontrada = NULL;
	bool encontrado = false;
	while (!encontrado && iterador_tiene_siguiente(iterador)) {
		opcion_menu_t *opcion =
			(opcion_menu_t *)iterador_siguiente(iterador);
		if (opcion &&
		    (tolower(opcion->caracter) == tolower(caracter))) {
			opcion_encontrada = opcion;
			encontrado = true;
		}
	}

	destruir_iterador_menu(iterador);
	return opcion_encontrada;
}

/**
 * Procesa la opción seleccionada por el usuario.
 */
menu_t *procesar_opcion(menu_t *menu_actual, char opcion, pokedex_t *pokedex)
{
	borrar_pantalla();

	opcion_menu_t *opcion_seleccionada =
		obtener_opcion_por_caracter(menu_actual, opcion);
	if (!opcion_seleccionada) {
		return menu_actual;
	}

	switch (opcion_seleccionada->tipo_accion) {
	case ACCION_MENU_ANTERIOR: {
		menu_t *menu_padre = obtener_menu_padre(menu_actual);
		if (menu_padre) {
			printf("\n====== MENÚ ======\n");
			return menu_padre;
		}
		break;
	}
	case ACCION_JUGAR:
		manejar_juego(pokedex, JUGAR);
		break;
	case ACCION_JUGAR_SEMILLA:
		manejar_juego(pokedex, JUGAR_CON_SEMILLA);
		break;
	case ACCION_BUSCAR_NOMBRE:
		manejar_busqueda(pokedex, BUSCAR_POR_NOMBRE);
		break;
	case ACCION_BUSCAR_ID:
		manejar_busqueda(pokedex, BUSCAR_POR_ID);
		break;
	case ACCION_MOSTRAR_NOMBRE:
		manejar_mostrar(pokedex, MOSTRAR_POR_NOMBRE);
		break;
	case ACCION_MOSTRAR_ID:
		manejar_mostrar(pokedex, MOSTRAR_POR_ID);
		break;
	case ACCION_SUBSECCION: {
		menu_t *subseccion = obtener_subseccion_de_opcion(
			menu_actual, &opcion, comparar_opciones_por_caracter);
		if (subseccion) {
			printf("\n====== MENÚ ======\n");
			return subseccion;
		}
		break;
	}
	case ACCION_SALIR:
		break;
	}

	return menu_actual;
}

void mostrar_menu_principal(pokedex_t *pokedex)
{
	printf("\n====== MENÚ ======\n");
	menu_t *menu_actual = crear_menu_completo();
	if (!menu_actual) {
		return;
	}

	char opcion = menu_obtener_opcion_usuario(menu_actual);
	while (opcion != SALIR_DEL_JUEGO) {
		menu_actual = procesar_opcion(menu_actual, opcion, pokedex);
		opcion = menu_obtener_opcion_usuario(menu_actual);
	}

	destruir_menu(menu_actual, destruir_opcion_menu);
}