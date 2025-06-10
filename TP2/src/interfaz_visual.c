#include "interfaz_visual.h"
#include <string.h>

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

typedef struct opcion_menu {
	char caracter;
	char *texto;
} opcion_menu_t;

// -------------------------------- MENÚ --------------------------------
/**
 * Devuelve true si el char de entrada es igual al de caracter, en caso contrario false.
 */
bool comparar_opciones_por_caracter(void *opcion, void *caracter)
{
	opcion_menu_t *option = (opcion_menu_t *)opcion;
	char *character = (char *)caracter;

	return option->caracter == *character;
}

/** 
 * Crea y devuelve un puntero a una opcion_menu_t.
 * 
 * En caso de error devuelve NULL.
 */
opcion_menu_t *crear_opcion_menu(char caracter, const char *texto)
{
	opcion_menu_t *opcion = calloc(1, sizeof(opcion_menu_t));
	if (!opcion) {
		return NULL;
	}
	opcion->caracter = caracter;

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

	opcion_menu_t *jugar = crear_opcion_menu(JUGAR, "Jugar");
	opcion_menu_t *jugar_semilla =
		crear_opcion_menu(JUGAR_CON_SEMILLA, "Jugar con semilla");
	opcion_menu_t *buscar = crear_opcion_menu(BUSCAR, "Buscar");
	opcion_menu_t *mostrar = crear_opcion_menu(MOSTRAR, "Mostrar");
	opcion_menu_t *salir = crear_opcion_menu(SALIR_DEL_JUEGO, "Salir");

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

	opcion_menu_t *b_nombre =
		crear_opcion_menu(BUSCAR_POR_NOMBRE, "Buscar por nombre");
	opcion_menu_t *b_id = crear_opcion_menu(BUSCAR_POR_ID, "Buscar por ID");
	opcion_menu_t *menu_anterior =
		crear_opcion_menu(MENU_ANTERIOR, "Menu anterior");

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

	opcion_menu_t *m_nombre =
		crear_opcion_menu(BUSCAR_POR_NOMBRE, "Mostrar por nombre");
	opcion_menu_t *m_id =
		crear_opcion_menu(BUSCAR_POR_ID, "Mostrar por ID");
	opcion_menu_t *menu_anterior =
		crear_opcion_menu(MENU_ANTERIOR, "Menu anterior");

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
char obtener_opcion_usuario(menu_t *menu)
{
	char opcion;
	do {
		mostrar_menu(menu);
		printf("\nSeleccione una opción: ");
		if (scanf(" %c", &opcion) != 1) {
			printf("Error al leer la opción. Intente nuevamente.\n\n");
		}

		if (!es_opcion_valida(menu, opcion)) {
			printf("Opción inválida. Intente nuevamente.\n\n");
		}
	} while (!es_opcion_valida(menu, opcion));
	return opcion;
}

void mostrar_menu_principal()
{
	printf("\n=== MENÚ PRINCIPAL ===\n");
	menu_t *menu_actual = crear_menu_completo();
	if (!menu_actual) {
		return;
	}

	char opcion;
	do {
		opcion = obtener_opcion_usuario(menu_actual);

		if (opcion == MENU_ANTERIOR) {
			menu_t *menu_padre = obtener_menu_padre(menu_actual);
			if (menu_padre) {
				menu_actual = menu_padre;
				printf("\n=== MENÚ PRINCIPAL ===\n");
			}
		} else {
			menu_t *subseccion = obtener_subseccion_de_opcion(
				menu_actual, &opcion,
				comparar_opciones_por_caracter);

			if (subseccion) {
				printf("\n=== SUBMENÚ ===\n");
				menu_actual = subseccion;
			}
		}
	} while (opcion != SALIR_DEL_JUEGO);

	destruir_menu(menu_actual, destruir_opcion_menu);
	printf("========================\n");
}

// -------------------------------- JUEGO --------------------------------
void mostrar_juego(juego_t *juego)
{
	if (!juego) {
		return;
	}
}

void mostrar_info_util(juego_t *juego)
{
	if (!juego) {
		return;
	}
}