#include "extra/ansi.h"
#include "extra/engine.h"
#include "src/menu.h"
#include "src/juego.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TECLA_W 'W'
#define TECLA_S 'S'
#define TECLA_D 'D'
#define TECLA_A 'A'
#define JUGADOR '@'
#define GANO_JUGADOR_1 1
#define GANO_JUGADOR_2 -1
#define EMPATE 2
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
const char *STR_VACIO = "";
const char *MENSAJE_GANA_JUGADOR_1 = "WINS PLAYER 1";
const char *MENSAJE_GANA_JUGADOR_2 = "WINS PLAYER 2";
const char *MENSAJE_EMPATE = "EMPATE";

const char *EMOJI_AGUA = "\U0001F30A";
const char *EMOJI_FUEGO = "\U0001F525";
const char *EMOJI_PLANTA = "\U0001F33F";
const char *EMOJI_ROCA = "\U0001FAA8";
const char *EMOJI_ELECTRICO = "\U000026A1";
const char *EMOJI_NORMAL = "\U0001F464";
const char *EMOJI_LUCHA = "\U0001F94A";
const char *EMOJI_ESTRELLA = "\U00002B50";
const char *EMOJI_TARGET = "\U0001F3AF";
const char *EMOJI_BRUJULA = "\U0001F9ED";

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

void dibujo_logo_pokemon()
{
	printf("\n");
	printf(ANSI_COLOR_YELLOW "\t                                  ,'\\\n");
	printf("\t    _.----.        ____         ,'  _\\   ___    ___     ____\n");
	printf("\t_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.\n");
	printf("\t\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |\n");
	printf("\t \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |\n");
	printf("\t   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |\n");
	printf("\t    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |\n");
	printf("\t     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |\n");
	printf("\t      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |\n");
	printf("\t       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |\n");
	printf("\t        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |\n");
	printf("\t                                `'                            '-._|\n" ANSI_COLOR_RESET);
}

void dibujo_charizard(char *texto)
{
	printf("\n");
	printf(ANSI_COLOR_RED "\t                 .\"-,.__\n");
	printf("\t                 `.     `.  ,\n");
	printf("\t              .--'  .._,'\"-' `.\n");
	printf("\t             .    .'         `' \n");
	printf("\t             `.   %s%s%s\n", ANSI_COLOR_BOLD, texto,
	       ANSI_COLOR_RED);
	printf("\t               `  '--.   ,-\"'\n");
	printf("\t                `\"`   |  \\\n");
	printf("\t                   -. \\, |\n");
	printf("\t                    `--Y.'      ___.\n");
	printf("\t                         \\     L._, \\\n");
	printf("\t               _.,        `.   <  <\\                _\n");
	printf("\t             ,' '           `, `.   | \\            ( `\n");
	printf("\t          ../, `.            `  |    .\\`.           \\ \\_\n");
	printf("\t         ,' ,..  .           _.,'    ||\\l            )  '\".\n");
	printf("\t        , ,'   \\           ,'.-.`-._,'  |           .  _._`.\n");
	printf("\t      ,' /      \\ \\        `' ' `--/   | \\          / /   ..\\\n");
	printf("\t    .'  /        \\ .         |\\__ - _ ,'` `        / /     `.`.\n");
	printf("\t    |  '          ..         `-...-\"  |  `-'      / /        . `.\n");
	printf("\t    | /           |L__           |    |          / /          `. `.\n");
	printf("\t   , /            .   .          |    |         / /             ` `\n");
	printf("\t  / /          ,. ,`._ `-_       |    |  _   ,-' /               ` \\\n");
	printf("\t / .           \\\"`_/. `-_ \\_,.  ,'    +-' `-'  _,        ..,-.    `.\\\n");
	printf("\t.  '         .-f    ,'   `    '.       \\__.---'     _   .'   '     \\ \\\n");
	printf("\t' /          `.'    l     .' /          \\..      ,_|/   `.  ,'`     L`\n");
	printf("\t|'      _.-\"\"` `.    \\ _,'  `            \\ `.___`.'\"`-.  , |   |    | \\\n");
	printf("\t||    ,'      `. `.   '       _,...._        `  |    `/ '  |   '     .|\n");
	printf("\t||  ,'          `. ;.,.---' ,'       `.   `.. `-'  .-' /_ .'    ;_   ||\n");
	printf("\t|| '              V      / /           `   | `   ,'   ,' '.    !  `. ||\n");
	printf("\t||/            _,-------7 '              . |  `-'    l         /    `||\n");
	printf("\t. |          ,' .-   ,' ||               | .-.        `.      .'     ||\n");
	printf("\t `'        ,'    `\".'    |               |    `.        '. -.'       `'\n");
	printf("\t          /      ,'      |               |,'    \\-.._,.'/'\n");
	printf("\t          .     /        .               .       \\    .''\n");
	printf("\t        .`.    |         `.             /         :_,' .'\n");
	printf("\t          \\ `...\\   _     ,'-.        .'         /_.-'\n");
	printf("\t           `-.__ `,  `'   .  _.>----''.  _  __  /\n");
	printf("\t                .'        /\"'          |  \"'   '_\n");
	printf("\t               /_|.-'\\ ,\".             '.'`__'-( \\\n");
	printf("\t                 / ,\"'\"\\,'               `/  `-.|\"\n" ANSI_COLOR_RESET);
}

// -------------------------------- MENÚ PRINCIPAL--------------------------------
/**
 * Devuelve true si el char de entrada es igual al de caracter, en caso contrario false.
 */
bool comparar_opciones_por_caracter(void *opcion, void *caracter)
{
	opcion_menu_t *option = (opcion_menu_t *)opcion;
	char *character = (char *)caracter;

	return toupper(option->caracter) == toupper(*character);
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
 * Función destructora para el tipo de dato 'opcion_menu_t'.
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
 * 
 * En caso de error devuelve NULL.
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
 * 
 * En caso de erorr devuelve NULL.
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

/**
 * Devuelve true si ambos strings son iguales en minúscula, de lo contrario devuelve false.
 */
bool son_iguales_en_lowercase(const char *string1, const char *string2)
{
	bool son_iguales = true;
	while (*string1 && *string2 && son_iguales) {
		int char1 = toupper((unsigned char)*string1);
		int char2 = toupper((unsigned char)*string2);
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

/**
 * Devuelve un string específico según el 'tipo_pokemon' dado.
 */
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
	return STR_VACIO;
}

/**
 * Imprime los datos del pokémon pasado por parámetro.
 */
void mostrar_pokemon_con_formato(const struct pokemon *pokemon)
{
	const int espacios_centrado = 15;

	for (int i = 0; i < espacios_centrado; i++) {
		printf(" ");
	}
	printf("%s[%3d]%s %-15s F%-3d D%-3d I%-3d %s\n", ANSI_COLOR_BOLD,
	       pokemon->id, ANSI_COLOR_RESET, pokemon->nombre, pokemon->fuerza,
	       pokemon->destreza, pokemon->inteligencia,
	       tipo_a_cadena(pokemon->tipo));
}

/**
 * Muestra una línea de encabezado.
 */
void mostrar_encabezado_resultado(const char *titulo)
{
	const int espacios_centrado = 25;

	printf("\n");
	for (int i = 0; i < espacios_centrado; i++) {
		printf(" ");
	}
	printf("%s%s%s\n", ANSI_COLOR_YELLOW ANSI_COLOR_BOLD, titulo,
	       ANSI_COLOR_RESET);

	for (int i = 0; i < espacios_centrado; i++) {
		printf(" ");
	}
	printf("%s", ANSI_COLOR_BOLD);
	for (int i = 0; i < (int)strlen(titulo); i++) {
		printf("=");
	}
	printf("%s\n", ANSI_COLOR_RESET);
}

/**
 * Imprime los datos del pokémon dado.
 * 
 * Devuelve true siempre.
 */
bool imprimir_pokemon_con_formato(struct pokemon *pokemon, void *ctx)
{
	mostrar_pokemon_con_formato(pokemon);
	return true;
}

/**
 * Devuelve true si el pokémon no coincide con el ID, de lo contrario lo imprime con formato y devuelve false.
 */
bool mostrar_pokemon_con_id_formato(struct pokemon *pokemon, void *ctx)
{
	int *id = ctx;
	if (pokemon->id == *id) {
		mostrar_pokemon_con_formato(pokemon);
		return false;
	}
	return true;
}

/**
 * Devuelve true si el pokémon no coincide con el nombre, de lo contrario lo imprime con formato y devuelve false.
 */
bool mostrar_pokemon_con_nombre_formato(struct pokemon *pokemon, void *ctx)
{
	char *nombre = ctx;
	if (son_iguales_en_lowercase(pokemon->nombre, nombre)) {
		mostrar_pokemon_con_formato(pokemon);
		return false;
	}
	return true;
}

/**
 * Muestra una indicación con el mensaje dado.
 */
void mostrar_indicacion(const char *mensaje)
{
	const int espacios_centrado = 25;

	printf("\n");
	for (int i = 0; i < espacios_centrado; i++) {
		printf(" ");
	}
	printf("     %s%-25s%s\n", ANSI_COLOR_RED, mensaje, ANSI_COLOR_RESET);

	for (int i = 0; i < espacios_centrado; i++) {
		printf(" ");
	}
	printf("%s> %s", ANSI_COLOR_RED, ANSI_COLOR_RESET);
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
		dibujo_logo_pokemon();
		mostrar_indicacion("Ingrese el nombre");
		if (scanf("%99s", nombre) != 1) {
			return;
		}

		borrar_pantalla();
		dibujo_logo_pokemon();
		mostrar_encabezado_resultado(
			"RESULTADO DE BÚSQUEDA POR NOMBRE");

		pokedex_iterar_pokemones(pokedex, ITERAR_NOMBRE,
					 mostrar_pokemon_con_nombre_formato,
					 nombre);
	} else if (opcion == BUSCAR_POR_ID) {
		int id;
		dibujo_logo_pokemon();
		mostrar_indicacion("Ingrese el ID:");
		if (scanf("%d", &id) != 1) {
			return;
		}

		borrar_pantalla();
		dibujo_logo_pokemon();
		mostrar_encabezado_resultado("RESULTADO DE BÚSQUEDA POR ID");

		pokedex_iterar_pokemones(pokedex, ITERAR_ID,
					 mostrar_pokemon_con_id_formato, &id);
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

	borrar_pantalla();
	dibujo_logo_pokemon();

	if (opcion == MOSTRAR_POR_NOMBRE) {
		mostrar_encabezado_resultado("POKÉMONES ORDENADOS POR NOMBRE");
		pokedex_iterar_pokemones(pokedex, ITERAR_NOMBRE,
					 imprimir_pokemon_con_formato, NULL);
	} else if (opcion == MOSTRAR_POR_ID) {
		mostrar_encabezado_resultado("POKÉMONES ORDENADOS POR ID");
		pokedex_iterar_pokemones(pokedex, ITERAR_ID,
					 imprimir_pokemon_con_formato, NULL);
	}
}

/**
 * Le pide una semilla al usuario.
 * 
 * En caso de ser pasada devuelve la misma, en caso contrario cero.
 */
unsigned int preguntar_semilla()
{
	unsigned int semilla = 0;
	dibujo_logo_pokemon();
	mostrar_indicacion("Ingrese la semilla");
	if (scanf("%u", &semilla) != 1) {
		return 0;
	}
	return semilla;
}

/**
 * Devuelve el color ANSI correspondiente según el tipo de pokémon.
 */
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
		return ANSI_COLOR_WHITE;
	case TIPO_LUCHA:
		return ANSI_COLOR_MAGENTA;
	default:
		return ANSI_COLOR_RESET;
	}
}

/**
 * Devuelve el color ANSI correspondiente al tipo de pokémon de la posición.
 * 
 * En caso de ser el jugador tambien.
 */
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

/**
 * Muestra el encabezado del juego con el tiempo restante.
 */
void mostrar_encabezado_juego(conexion_juegos_t *conexion)
{
	int tiempo_restante = obtener_tiempo_restante(conexion);
	printf("\t\t\t\t\t\t   %sTiempo restante: %d segundos%s\n\n",
	       ANSI_COLOR_YELLOW, tiempo_restante, ANSI_COLOR_RESET);
}

/**
 * Muestra el terreno de juego con el jugador y pokémones.
 */
void mostrar_terreno(conexion_juegos_t *conexion)
{
	if (!conexion) {
		return;
	}

	for (int i = 0; i < MAX_FILAS; i++) {
		printf("\t");
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
 * Muestra los títulos de los jugadores.
 */
void mostrar_titulos_jugadores()
{
	printf("\t%s%-50s%s\t\t%s%-50s%s\n", ANSI_COLOR_BOLD,
	       "Jugador 1:", ANSI_COLOR_RESET, ANSI_COLOR_BOLD,
	       "Jugador 2:", ANSI_COLOR_RESET);
}

/**
 * Obtiene información de los últimos pokémones capturados por un jugador.
 */
void obtener_info_capturados(juego_t *juego, char *info_capturados,
			     size_t max_len)
{
	size_t total_capturados = obtener_cantidad_pokes_capturados(juego);

	if (total_capturados == 0) {
		strcpy(info_capturados, "Ninguno");
		return;
	}

	int inicio = (int)total_capturados - 3;
	if (inicio < 0) {
		inicio = 0;
	}

	info_capturados[0] = '\0';
	bool salir = false;
	for (int i = inicio; i < (int)total_capturados && !salir; i++) {
		struct pokemon *pokemon = obtener_pokemon_capturado(juego, i);
		if (pokemon) {
			size_t len_actual = strlen(info_capturados);

			if (len_actual > 0) {
				if (len_actual + 2 < max_len) {
					strcat(info_capturados, ", ");
				} else {
					salir = true;
				}
			}

			size_t len_nombre = strlen(pokemon->nombre);
			size_t len_nueva = strlen(info_capturados);

			if (len_nueva + len_nombre < max_len) {
				strcat(info_capturados, pokemon->nombre);
			} else {
				salir = true;
			}
		}
	}
}

/**
 * Muestra la sección de los últimos pokémones capturados.
 */
void mostrar_seccion_capturados(conexion_juegos_t *conexion)
{
	printf("\t%s %-50s\t\t%s %-50s\n", EMOJI_TARGET,
	       "Últimos capturados:", EMOJI_TARGET, "Últimos capturados:");

	for (int jugador = 0; jugador < MAX_JUGADORES; jugador++) {
		juego_t *juego = obtener_juego(conexion, jugador);
		char info_capturados[100];

		obtener_info_capturados(juego, info_capturados,
					sizeof(info_capturados));

		if (jugador == 0) {
			printf("\t   %-50s\t\t", info_capturados);
		} else {
			printf("   %-50s\n", info_capturados);
		}
	}
}

/**
 * Muestra la sección del próximo pokémon a capturar.
 */
void mostrar_seccion_proximos(conexion_juegos_t *conexion)
{
	printf("\t%s %-50s\t\t%s %-50s\n", EMOJI_BRUJULA,
	       "Próximo a capturar:", EMOJI_BRUJULA, "Próximo a capturar:");

	printf("\t");
	for (int jugador = 0; jugador < MAX_JUGADORES; jugador++) {
		juego_t *juego = obtener_juego(conexion, jugador);

		printf("   ");

		if (obtener_cantidad_pokes_pendientes(juego) == 0) {
			printf("%-50s", "Ninguno");
		} else {
			struct pokemon *proximo =
				obtener_pokemon_pendiente_tope(juego);
			if (proximo) {
				const char *color =
					obtener_color_por_tipo(proximo->tipo);
				printf("%s%-50s%s", color,
				       tipo_a_cadena(proximo->tipo),
				       ANSI_COLOR_RESET);
			}
		}

		if (jugador == 0) {
			printf("\t\t");
		} else {
			printf("\n");
		}
	}
}

/**
 * Muestra la sección de puntos.
 */
void mostrar_seccion_puntos(conexion_juegos_t *conexion)
{
	printf("\t%s %-50s\t\t%s %-50s\n", EMOJI_ESTRELLA,
	       "Puntos:", EMOJI_ESTRELLA, "Puntos:");

	for (int jugador = 0; jugador < MAX_JUGADORES; jugador++) {
		juego_t *juego = obtener_juego(conexion, jugador);
		unsigned puntos = obtener_puntos_jugador(juego);

		if (jugador == 0) {
			printf("\t   %-50u\t\t", puntos);
		} else {
			printf("   %-50u\n", puntos);
		}
	}
}

/**
 * Muestra las estadísticas de ambos jugadores.
 */
void mostrar_estadisticas_jugadores(conexion_juegos_t *conexion)
{
	mostrar_titulos_jugadores();
	mostrar_seccion_capturados(conexion);
	mostrar_seccion_proximos(conexion);
	mostrar_seccion_puntos(conexion);
}

/**
 * Muestra ambos juegos con sus estadisticas por pantalla.
 */
void mostrar_juegos(conexion_juegos_t *conexion)
{
	if (!conexion) {
		return;
	}

	borrar_pantalla();
	printf("\n");

	mostrar_encabezado_juego(conexion);
	printf("\n");

	mostrar_terreno(conexion);
	printf("\n");

	mostrar_estadisticas_jugadores(conexion);
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
	char texto[20] = "";
	if (estado == GANO_JUGADOR_1) {
		strcpy(texto, MENSAJE_GANA_JUGADOR_1);
	} else if (estado == GANO_JUGADOR_2) {
		strcpy(texto, MENSAJE_GANA_JUGADOR_2);
	} else if (estado == EMPATE) {
		strcpy(texto, MENSAJE_EMPATE);
	}
	dibujo_charizard(texto);
}

/**
 * Función callback para 'game_loop'.
 */
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

	dibujo_logo_pokemon();

	const int espacios_centrado = 25;

	printf("\n");
	for (int i = 0; i < espacios_centrado; i++) {
		printf(" ");
	}
	printf("%s----------------------------%s\n", ANSI_COLOR_BOLD,
	       ANSI_COLOR_RESET);

	while (iterador_tiene_siguiente(iterador)) {
		opcion_menu_t *opcion =
			(opcion_menu_t *)iterador_siguiente(iterador);
		if (opcion) {
			for (int i = 0; i < espacios_centrado; i++) {
				printf(" ");
			}
			printf("%s|%s [%s%c%s] %-20s %s|%s\n", ANSI_COLOR_BOLD,
			       ANSI_COLOR_RESET, ANSI_COLOR_BOLD,
			       opcion->caracter, ANSI_COLOR_RESET,
			       opcion->texto, ANSI_COLOR_BOLD,
			       ANSI_COLOR_RESET);
		}
	}

	for (int i = 0; i < espacios_centrado; i++) {
		printf(" ");
	}
	printf("%s----------------------------%s\n", ANSI_COLOR_BOLD,
	       ANSI_COLOR_RESET);

	destruir_iterador_menu(iterador);
}

/**
 * Devuelve true si el carácter dado está en la sección del menú, en caso contrario false.
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
	mostrar_indicacion("Ingrese una opción");
	if (scanf(" %c", &opcion) != 1) {
		return SALIR_DEL_JUEGO;
	}

	while (!es_opcion_valida(menu, opcion)) {
		borrar_pantalla();
		mostrar_menu(menu);
		printf("\n\t\t\t      %sOpción inválida%s", ANSI_COLOR_RED,
		       ANSI_COLOR_RESET);
		mostrar_indicacion("Ingrese una opción");
		if (scanf(" %c", &opcion) != 1) {
			return SALIR_DEL_JUEGO;
		}
	}

	return opcion;
}

/**
 * Obtiene la opción del menú basándose en el carácter seleccionado.
 * 
 * En caso de no existir o error devuelve NULL.
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
		if (opcion && comparar_opciones_por_caracter(&opcion->caracter,
							     &caracter)) {
			opcion_encontrada = opcion;
			encontrado = true;
		}
	}

	destruir_iterador_menu(iterador);
	return opcion_encontrada;
}

/**
 * Procesa la opción seleccionada por el usuario.
 * 
 * En caso de que la opción no tenga una subseccion devuelve NULL.
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
			return menu_padre;
		}
		break;
	}
	case ACCION_JUGAR:
		manejar_juego(pokedex, JUGAR);
		return NULL;
	case ACCION_JUGAR_SEMILLA:
		manejar_juego(pokedex, JUGAR_CON_SEMILLA);
		return NULL;
	case ACCION_BUSCAR_NOMBRE:
		manejar_busqueda(pokedex, BUSCAR_POR_NOMBRE);
		return NULL;
	case ACCION_BUSCAR_ID:
		manejar_busqueda(pokedex, BUSCAR_POR_ID);
		return NULL;
	case ACCION_MOSTRAR_NOMBRE:
		manejar_mostrar(pokedex, MOSTRAR_POR_NOMBRE);
		return NULL;
	case ACCION_MOSTRAR_ID:
		manejar_mostrar(pokedex, MOSTRAR_POR_ID);
		return NULL;
	case ACCION_SUBSECCION: {
		menu_t *subseccion = obtener_subseccion_de_opcion(
			menu_actual, &opcion, comparar_opciones_por_caracter);
		if (subseccion) {
			return subseccion;
		}
		break;
	}
	case ACCION_SALIR:
		break;
	}

	return menu_actual;
}

/**
 * Imprime por pantalla el menú principal.
 */
void mostrar_menu_principal(pokedex_t *pokedex)
{
	menu_t *menu_raiz = crear_menu_completo();
	if (!menu_raiz) {
		return;
	}

	menu_t *menu_actual = menu_raiz;
	char opcion = menu_obtener_opcion_usuario(menu_actual);
	bool salir = false;
	while (!salir && menu_actual && opcion != SALIR_DEL_JUEGO) {
		menu_t *nuevo_menu =
			procesar_opcion(menu_actual, opcion, pokedex);
		if (nuevo_menu == NULL) {
			salir = true;
		} else {
			menu_actual = nuevo_menu;
			if (menu_actual) {
				opcion = menu_obtener_opcion_usuario(
					menu_actual);
			}
		}
	}

	destruir_menu(menu_raiz, destruir_opcion_menu);
}

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
	pokedex_destruir(pokedex);

	return 0;
}
