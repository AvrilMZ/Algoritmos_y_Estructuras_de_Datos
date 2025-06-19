#include "pa2m.h"
#include "src/juego.h"
#include "src/menu.h"
#include <string.h>

#define ARCHIVO "datos/pokedex.csv"

// -------------------------------- MENÚ --------------------------------

bool comparar_strings(void *a, void *b)
{
	if (!a || !b) {
		return false;
	}
	return strcmp((char *)a, (char *)b) == 0;
}

bool comparar_enteros(void *a, void *b)
{
	if (!a || !b) {
		return false;
	}
	return *(int *)a == *(int *)b;
}

void prueba_crear_menu()
{
	pa2m_nuevo_grupo("Pruebas de creación de menú");

	menu_t *menu = crear_menu();
	pa2m_afirmar(menu != NULL, "Se puede crear un menú");
	pa2m_afirmar(menu_vacio(menu), "El menú recién creado está vacío");
	pa2m_afirmar(cantidad_opciones_seccion(menu) == 0,
		     "El menú recién creado tiene 0 opciones");

	destruir_menu(menu, NULL);
}

void prueba_insertar_opciones()
{
	pa2m_nuevo_grupo("Pruebas de inserción de opciones");

	menu_t *menu = crear_menu();
	char *opcion1 = "Opción 1";
	char *opcion2 = "Opción 2";
	char *opcion3 = "Opción 3";

	pa2m_afirmar(insertar_opcion_en_seccion(menu, opcion1),
		     "Se puede insertar una opción");
	pa2m_afirmar(!menu_vacio(menu),
		     "El menú ya no está vacío después de insertar");
	pa2m_afirmar(cantidad_opciones_seccion(menu) == 1,
		     "El menú tiene 1 opción");

	pa2m_afirmar(insertar_opcion_en_seccion(menu, opcion2),
		     "Se puede insertar una segunda opción");
	pa2m_afirmar(cantidad_opciones_seccion(menu) == 2,
		     "El menú tiene 2 opciones");

	pa2m_afirmar(insertar_opcion_en_seccion(menu, opcion3),
		     "Se puede insertar una tercera opción");
	pa2m_afirmar(cantidad_opciones_seccion(menu) == 3,
		     "El menú tiene 3 opciones");

	pa2m_afirmar(insertar_opcion_en_seccion(menu, opcion1),
		     "Se pueden insertar elementos repetidos");
	pa2m_afirmar(cantidad_opciones_seccion(menu) == 4,
		     "El menú tiene 4 opciones con repetidos");

	destruir_menu(menu, NULL);
}

void prueba_existe_opcion()
{
	pa2m_nuevo_grupo("Pruebas de existencia de opciones");

	menu_t *menu = crear_menu();
	char *opcion1 = "Opción 1";
	char *opcion2 = "Opción 2";
	char *opcion_inexistente = "No existe";

	insertar_opcion_en_seccion(menu, opcion1);
	insertar_opcion_en_seccion(menu, opcion2);

	pa2m_afirmar(existe_opcion_en_seccion(menu, opcion1, NULL),
		     "Existe la opción 1");
	pa2m_afirmar(existe_opcion_en_seccion(menu, opcion2, NULL),
		     "Existe la opción 2");
	pa2m_afirmar(!existe_opcion_en_seccion(menu, opcion_inexistente, NULL),
		     "No existe una opción no insertada");

	pa2m_afirmar(existe_opcion_en_seccion(menu, opcion2, comparar_strings),
		     "Existe opción con comparador personalizado");

	destruir_menu(menu, NULL);
}

void prueba_eliminar_opcion()
{
	pa2m_nuevo_grupo("Pruebas de eliminación de opciones");

	menu_t *menu = crear_menu();
	char *opcion1 = "Opción 1";
	char *opcion2 = "Opción 2";
	char *opcion3 = "Opción 3";

	insertar_opcion_en_seccion(menu, opcion1);
	insertar_opcion_en_seccion(menu, opcion2);
	insertar_opcion_en_seccion(menu, opcion3);
	insertar_opcion_en_seccion(menu, opcion1); // Repetida

	pa2m_afirmar(cantidad_opciones_seccion(menu) == 4,
		     "El menú tiene 4 opciones inicialmente");

	pa2m_afirmar(eliminar_opcion_en_seccion(menu, opcion1, NULL),
		     "Se puede eliminar una opción existente");
	pa2m_afirmar(cantidad_opciones_seccion(menu) == 3,
		     "El menú tiene 3 opciones después de eliminar");
	pa2m_afirmar(existe_opcion_en_seccion(menu, opcion1, NULL),
		     "La opción repetida aún existe");

	pa2m_afirmar(!eliminar_opcion_en_seccion(menu, "No existe", NULL),
		     "No se puede eliminar una opción inexistente");
	pa2m_afirmar(cantidad_opciones_seccion(menu) == 3,
		     "La cantidad no cambia al intentar eliminar inexistente");

	char *opcion_copia = "Opción 2";
	pa2m_afirmar(eliminar_opcion_en_seccion(menu, opcion_copia,
						comparar_strings),
		     "Se puede eliminar con comparador personalizado");
	pa2m_afirmar(
		cantidad_opciones_seccion(menu) == 2,
		"El menú tiene 2 opciones después de eliminar con comparador");

	destruir_menu(menu, NULL);
}

void prueba_subsecciones()
{
	pa2m_nuevo_grupo("Pruebas de subsecciones");

	menu_t *menu_principal = crear_menu();
	menu_t *submenu1 = crear_menu();
	menu_t *submenu2 = crear_menu();

	char *opcion1 = "Archivo";
	char *opcion2 = "Editar";
	char *subopc1 = "Nuevo";
	char *subopc2 = "Abrir";

	insertar_opcion_en_seccion(menu_principal, opcion1);
	insertar_opcion_en_seccion(menu_principal, opcion2);

	insertar_opcion_en_seccion(submenu1, subopc1);
	insertar_opcion_en_seccion(submenu1, subopc2);

	pa2m_afirmar(agregar_subseccion_a_opcion(menu_principal, opcion1,
						 submenu1, NULL),
		     "Se puede agregar subsección a una opción");

	menu_t *subseccion_obtenida =
		obtener_subseccion_de_opcion(menu_principal, opcion1, NULL);
	pa2m_afirmar(subseccion_obtenida != NULL,
		     "Se puede obtener la subsección de una opción");
	pa2m_afirmar(subseccion_obtenida == submenu1,
		     "La subsección obtenida es la correcta");

	pa2m_afirmar(obtener_subseccion_de_opcion(menu_principal, opcion2,
						  NULL) == NULL,
		     "Opción sin subsección devuelve NULL");

	pa2m_afirmar(agregar_subseccion_a_opcion(menu_principal, opcion1,
						 submenu2, NULL),
		     "Se puede sobreescribir una subsección");
	subseccion_obtenida =
		obtener_subseccion_de_opcion(menu_principal, opcion1, NULL);
	pa2m_afirmar(subseccion_obtenida == submenu2,
		     "La subsección sobreescrita es la correcta");

	destruir_menu(menu_principal, NULL);
}

void prueba_iterador()
{
	pa2m_nuevo_grupo("Pruebas de iterador");

	menu_t *menu = crear_menu();
	iterador_menu_t *it = crear_iterador_menu(menu);

	pa2m_afirmar(it != NULL, "Se puede crear un iterador");
	pa2m_afirmar(!iterador_tiene_siguiente(it),
		     "Iterador de menú vacío no tiene siguiente");

	char *opcion1 = "Opción 1";
	char *opcion2 = "Opción 2";
	char *opcion3 = "Opción 3";

	insertar_opcion_en_seccion(menu, opcion1);
	insertar_opcion_en_seccion(menu, opcion2);
	insertar_opcion_en_seccion(menu, opcion3);

	iterador_reiniciar(it, menu);

	int contador = 0;
	while (iterador_tiene_siguiente(it)) {
		void *dato = iterador_siguiente(it);
		pa2m_afirmar(dato != NULL,
			     "El iterador devuelve un dato válido");
		contador++;
	}
	pa2m_afirmar(contador == 3, "El iterador recorre todas las opciones");

	iterador_reiniciar(it, menu);
	pa2m_afirmar(iterador_tiene_siguiente(it),
		     "Después de reiniciar, el iterador tiene siguiente");

	destruir_iterador_menu(it);
	destruir_menu(menu, NULL);
}

void prueba_casos_borde()
{
	pa2m_nuevo_grupo("Pruebas de casos borde y manejo de errores");

	pa2m_afirmar(!insertar_opcion_en_seccion(NULL, "dato"),
		     "No se puede insertar en menú NULL");
	pa2m_afirmar(!existe_opcion_en_seccion(NULL, "dato", NULL),
		     "No existe opción en menú NULL");
	pa2m_afirmar(cantidad_opciones_seccion(NULL) == 0,
		     "Menú NULL tiene 0 opciones");
	pa2m_afirmar(menu_vacio(NULL), "Menú NULL se considera vacío");

	menu_t *menu = crear_menu();
	pa2m_afirmar(!insertar_opcion_en_seccion(menu, NULL),
		     "No se puede insertar NULL como opción");

	iterador_menu_t *it = crear_iterador_menu(NULL);
	pa2m_afirmar(it == NULL, "No se puede crear iterador de menú NULL");

	destruir_menu(menu, NULL);
	destruir_menu(NULL, NULL); // No debería fallar
	destruir_iterador_menu(NULL); // No debería fallar
}

void prueba_destruccion_con_funcion()
{
	pa2m_nuevo_grupo("Pruebas de destrucción con función destructora");

	menu_t *menu = crear_menu();

	int *dato1 = calloc(1, sizeof(int));
	int *dato2 = calloc(1, sizeof(int));
	int *dato3 = calloc(1, sizeof(int));
	*dato1 = 1;
	*dato2 = 2;
	*dato3 = 3;

	insertar_opcion_en_seccion(menu, dato1);
	insertar_opcion_en_seccion(menu, dato2);
	insertar_opcion_en_seccion(menu, dato3);

	pa2m_afirmar(cantidad_opciones_seccion(menu) == 3,
		     "Se insertaron 3 datos dinámicos");

	destruir_menu(menu, free);
	pa2m_afirmar(true, "La destrucción con función destructora anda");
}

// -------------------------------- JUEGO --------------------------------

void test_inicializar_juego_completo()
{
	pa2m_nuevo_grupo("Pruebas completas de inicialización");

	pokedex_t *pokedex = pokedex_abrir(ARCHIVO);

	conexion_juegos_t *conexion1 = inicializar_juego(pokedex, 1234);
	conexion_juegos_t *conexion2 = inicializar_juego(pokedex, 5678);
	pa2m_afirmar(conexion1 != NULL,
		     "Inicializar juego con semilla 1234 funciona");
	pa2m_afirmar(conexion2 != NULL,
		     "Inicializar juego con semilla 5678 funciona");

	if (conexion1 && conexion2) {
		pa2m_afirmar(
			conexion1 != conexion2,
			"Diferentes inicializaciones crean conexiones distintas");

		destruir_juego(conexion1);
		destruir_juego(conexion2);
	}

	if (pokedex) {
		pokedex_destruir(pokedex);
	}
}

void test_obtener_juego_completo()
{
	pa2m_nuevo_grupo("Pruebas completas de obtener juego");

	pokedex_t *pokedex = pokedex_abrir(ARCHIVO);
	conexion_juegos_t *conexion = inicializar_juego(pokedex, 12345);

	if (conexion) {
		for (int i = 0; i < MAX_JUGADORES; i++) {
			juego_t *juego = obtener_juego(conexion, i);
			pa2m_afirmar(juego != NULL,
				     "Obtener juego %i es válido", i);
		}

		juego_t *juego_neg = obtener_juego(conexion, -1);
		juego_t *juego_max = obtener_juego(conexion, MAX_JUGADORES);
		juego_t *juego_alto = obtener_juego(conexion, 999);

		pa2m_afirmar(juego_neg == NULL,
			     "Obtener juego con índice -1 devuelve NULL");
		pa2m_afirmar(
			juego_max == NULL,
			"Obtener juego con índice MAX_JUGADORES devuelve NULL");
		pa2m_afirmar(juego_alto == NULL,
			     "Obtener juego con índice alto devuelve NULL");

		destruir_juego(conexion);
	}

	juego_t *juego_null = obtener_juego(NULL, 0);
	pa2m_afirmar(juego_null == NULL,
		     "Obtener juego con conexión NULL devuelve NULL");

	if (pokedex) {
		pokedex_destruir(pokedex);
	}
}

void test_realizar_jugadas_completo()
{
	pa2m_nuevo_grupo("Pruebas completas de realizar jugadas");

	pokedex_t *pokedex = pokedex_abrir(ARCHIVO);
	conexion_juegos_t *conexion = inicializar_juego(pokedex, 12345);

	if (conexion) {
		realizar_jugada(conexion, 'W');
		realizar_jugada(conexion, 'A');
		realizar_jugada(conexion, 'S');
		realizar_jugada(conexion, 'D');
		pa2m_afirmar(1, "Movimientos WASD del jugador 1 no rompen");

		realizar_jugada(conexion, 'x');
		realizar_jugada(conexion, '1');
		realizar_jugada(conexion, ' ');
		pa2m_afirmar(1, "Teclas inválidas no rompen");

		for (int i = 0; i < MAX_FILAS + 5; i++) {
			realizar_jugada(conexion, 'W');
		}
		for (int i = 0; i < MAX_COLUMNAS + 5; i++) {
			realizar_jugada(conexion, 'A');
		}
		pa2m_afirmar(1, "Movimiento fuera de límites no rompe");

		for (int i = 0; i < MAX_FILAS + 5; i++) {
			realizar_jugada(conexion, 'S');
		}
		for (int i = 0; i < MAX_COLUMNAS + 5; i++) {
			realizar_jugada(conexion, 'D');
		}
		pa2m_afirmar(1, "Movimiento hacia límites opuestos no rompe");

		destruir_juego(conexion);
	}

	if (pokedex) {
		pokedex_destruir(pokedex);
	}
}

void test_contenido_y_pokemon_en_posicion()
{
	pa2m_nuevo_grupo("Pruebas de contenido y pokemon en posición");

	pokedex_t *pokedex = pokedex_abrir(ARCHIVO);
	conexion_juegos_t *conexion = inicializar_juego(pokedex, 12345);

	if (conexion) {
		juego_t *juego = obtener_juego(conexion, 0);

		if (juego) {
			struct pokemon *poke_null =
				obtener_pokemon_en_posicion(NULL, 0, 0);
			pa2m_afirmar(
				poke_null == NULL,
				"Obtener pokemon con juego NULL devuelve NULL");

			char contenido_neg =
				obtener_contenido_posicion(juego, -1, -1);
			char contenido_alto = obtener_contenido_posicion(
				juego, MAX_FILAS, MAX_COLUMNAS);
			pa2m_afirmar(
				contenido_neg == ' ',
				"Posición negativa devuelve espacio vacío");
			pa2m_afirmar(
				contenido_alto == ' ',
				"Posición fuera de rango devuelve espacio vacío");

			struct pokemon *poke_neg =
				obtener_pokemon_en_posicion(juego, -1, -1);
			struct pokemon *poke_alto = obtener_pokemon_en_posicion(
				juego, MAX_FILAS, MAX_COLUMNAS);
			pa2m_afirmar(
				poke_neg == NULL,
				"Pokemon en posición negativa devuelve NULL");
			pa2m_afirmar(
				poke_alto == NULL,
				"Pokemon en posición fuera de rango devuelve NULL");

			int posiciones_jugador = 0;
			int posiciones_pokemon = 0;
			int posiciones_vacias = 0;
			for (int i = 0; i < MAX_FILAS; i++) {
				for (int j = 0; j < MAX_COLUMNAS; j++) {
					char contenido =
						obtener_contenido_posicion(
							juego, i, j);
					if (contenido == '@') {
						posiciones_jugador++;
					} else if (contenido == ' ') {
						posiciones_vacias++;
					} else {
						posiciones_pokemon++;
					}
				}
			}
			pa2m_afirmar(
				posiciones_jugador == 1,
				"Hay exactamente un jugador en el tablero");
			pa2m_afirmar(
				posiciones_vacias + posiciones_pokemon +
						posiciones_jugador ==
					MAX_FILAS * MAX_COLUMNAS,
				"Todas las posiciones están contabilizadas");
		}

		destruir_juego(conexion);
	}

	if (pokedex) {
		pokedex_destruir(pokedex);
	}
}

void test_estado_juego_completo()
{
	pa2m_nuevo_grupo("Pruebas completas de estado del juego");

	pokedex_t *pokedex = pokedex_abrir(ARCHIVO);
	conexion_juegos_t *conexion = inicializar_juego(pokedex, 12345);

	if (conexion) {
		for (int i = 0; i < 5; i++) {
			int estado = estado_juego(conexion);
			pa2m_afirmar(
				estado == 0,
				"Estado del juego es correcto (intento %i)",
				i + 1);
		}

		realizar_jugada(conexion, 'W');
		realizar_jugada(conexion, 'S');
		realizar_jugada(conexion, 'D');
		realizar_jugada(conexion, 'A');

		int estado_post_movimiento = estado_juego(conexion);
		pa2m_afirmar(estado_post_movimiento == 0,
			     "Estado se mantiene después de movimientos");

		destruir_juego(conexion);
	}

	if (pokedex) {
		pokedex_destruir(pokedex);
	}
}

void test_puntos_y_captura_avanzado()
{
	pa2m_nuevo_grupo("Pruebas avanzadas de puntos y captura");

	pokedex_t *pokedex = pokedex_abrir(ARCHIVO);
	conexion_juegos_t *conexion = inicializar_juego(pokedex, 12345);

	if (conexion) {
		juego_t *juego1 = obtener_juego(conexion, 0);
		juego_t *juego2 = obtener_juego(conexion, 1);

		if (juego1 && juego2) {
			unsigned puntos_iniciales_j1 =
				obtener_puntos_jugador(juego1);
			unsigned puntos_iniciales_j2 =
				obtener_puntos_jugador(juego2);

			pa2m_afirmar(
				puntos_iniciales_j1 == puntos_iniciales_j2,
				"Ambos jugadores inician con los mismos puntos");

			// Índices válidos
			for (int i = 0; i < 5; i++) {
				struct pokemon *poke1 =
					obtener_pokemon_capturado(juego1, i);
				struct pokemon *poke2 =
					obtener_pokemon_capturado(juego2, i);
				pa2m_afirmar(
					poke1 == NULL,
					"Pokemon capturado en índice %i es NULL para jugador 1",
					i);
				pa2m_afirmar(
					poke2 == NULL,
					"Pokemon capturado en índice %i es NULL para jugador 2",
					i);
			}

			// Índices inválidos (negativos y muy altos)
			struct pokemon *poke_neg1 =
				obtener_pokemon_capturado(juego1, -1);
			struct pokemon *poke_neg2 =
				obtener_pokemon_capturado(juego2, -1);
			struct pokemon *poke_alto1 =
				obtener_pokemon_capturado(juego1, 999);
			struct pokemon *poke_alto2 =
				obtener_pokemon_capturado(juego2, 999);
			pa2m_afirmar(
				poke_neg1 == NULL,
				"Pokemon capturado en índice -1 es NULL para jugador 1");
			pa2m_afirmar(
				poke_neg2 == NULL,
				"Pokemon capturado en índice -1 es NULL para jugador 2");
			pa2m_afirmar(
				poke_alto1 == NULL,
				"Pokemon capturado en índice alto es NULL para jugador 1");
			pa2m_afirmar(
				poke_alto2 == NULL,
				"Pokemon capturado en índice alto es NULL para jugador 2");

			for (int i = 0; i < 3; i++) {
				size_t cant_cap_j1 =
					obtener_cantidad_pokes_capturados(
						juego1);
				size_t cant_cap_j2 =
					obtener_cantidad_pokes_capturados(
						juego2);

				pa2m_afirmar(
					cant_cap_j1 == 0,
					"Cantidad capturados J1 es 0 (llamada %i)",
					i + 1);
				pa2m_afirmar(
					cant_cap_j2 == 0,
					"Cantidad capturados J2 es 0 (llamada %i)",
					i + 1);
			}
		}

		destruir_juego(conexion);
	}

	if (pokedex) {
		pokedex_destruir(pokedex);
	}
}

void test_casos_extremos_pokemon_capturado()
{
	pa2m_nuevo_grupo("Pruebas de casos extremos para pokemon capturado");

	pokedex_t *pokedex = pokedex_abrir(ARCHIVO);
	conexion_juegos_t *conexion = inicializar_juego(pokedex, 12345);

	if (conexion) {
		juego_t *juego = obtener_juego(conexion, 0);

		if (juego) {
			struct pokemon *poke_null =
				obtener_pokemon_capturado(NULL, 0);
			pa2m_afirmar(
				poke_null == NULL,
				"Pokemon capturado con juego NULL devuelve NULL");

			struct pokemon *poke_muy_neg =
				obtener_pokemon_capturado(juego, -999);
			struct pokemon *poke_muy_alto =
				obtener_pokemon_capturado(juego, 999999);

			pa2m_afirmar(
				poke_muy_neg == NULL,
				"Pokemon capturado con índice muy negativo devuelve NULL");
			pa2m_afirmar(
				poke_muy_alto == NULL,
				"Pokemon capturado con índice muy alto devuelve NULL");
		}

		destruir_juego(conexion);
	}

	if (pokedex) {
		pokedex_destruir(pokedex);
	}
}

void test_tiempo_restante_completo()
{
	pa2m_nuevo_grupo("Pruebas completas de tiempo restante");

	pokedex_t *pokedex = pokedex_abrir(ARCHIVO);
	conexion_juegos_t *conexion = inicializar_juego(pokedex, 12345);

	if (conexion) {
		int tiempo_inicial = obtener_tiempo_restante(conexion);
		pa2m_afirmar(tiempo_inicial > 0, "Tiempo inicial es positivo");

		for (int i = 0; i < 10; i++) {
			realizar_jugada(conexion, 'W');
			realizar_jugada(conexion, 'S');
		}

		int tiempo_despues = obtener_tiempo_restante(conexion);
		pa2m_afirmar(tiempo_despues >= 0,
			     "Tiempo después de operaciones no es negativo");
		pa2m_afirmar(tiempo_despues <= tiempo_inicial,
			     "Tiempo no aumenta");

		destruir_juego(conexion);
	}

	if (pokedex) {
		pokedex_destruir(pokedex);
	}
}

void test_recorrer_pokemones_capturados()
{
	pa2m_nuevo_grupo("Pruebas de recorrer pokemones capturados");

	pokedex_t *pokedex = pokedex_abrir(ARCHIVO);
	conexion_juegos_t *conexion = inicializar_juego(pokedex, 12345);

	if (conexion) {
		juego_t *juego = obtener_juego(conexion, 0);

		if (juego) {
			unsigned resultado = recorrer_pokemones_capturados(
				juego, NULL, NULL);
			pa2m_afirmar(resultado == 0,
				     "Recorrer con función NULL devuelve 0");

			resultado =
				recorrer_pokemones_capturados(NULL, NULL, NULL);
			pa2m_afirmar(resultado == 0,
				     "Recorrer con juego NULL devuelve 0");
		}

		destruir_juego(conexion);
	}

	if (pokedex) {
		pokedex_destruir(pokedex);
	}
}

void test_multiples_conexiones()
{
	pa2m_nuevo_grupo("Pruebas con múltiples conexiones");

	pokedex_t *pokedex = pokedex_abrir(ARCHIVO);

	conexion_juegos_t *conexiones[5];
	for (int i = 0; i < 5; i++) {
		conexiones[i] =
			inicializar_juego(pokedex, (unsigned int)(1000 + i));
		pa2m_afirmar(conexiones[i] != NULL,
			     "Conexión %i creada exitosamente", i);
	}

	for (int i = 0; i < 5; i++) {
		if (conexiones[i]) {
			int estado = estado_juego(conexiones[i]);
			pa2m_afirmar(estado == 0,
				     "Estado inicial correcto para conexión %i",
				     i);

			juego_t *juego1 = obtener_juego(conexiones[i], 0);
			juego_t *juego2 = obtener_juego(conexiones[i], 1);
			pa2m_afirmar(juego1 != NULL && juego2 != NULL,
				     "Ambos juegos válidos en conexión %i", i);
		}
	}

	for (int i = 0; i < 5; i++) {
		if (conexiones[i]) {
			destruir_juego(conexiones[i]);
		}
	}

	if (pokedex) {
		pokedex_destruir(pokedex);
	}
}

int main()
{
	pa2m_nuevo_grupo(
		"======================== MENÚ ========================");
	prueba_crear_menu();
	prueba_insertar_opciones();
	prueba_existe_opcion();
	prueba_eliminar_opcion();
	prueba_subsecciones();
	prueba_iterador();
	prueba_casos_borde();
	prueba_destruccion_con_funcion();

	pa2m_nuevo_grupo(
		"======================== JUEGO ========================");
	test_inicializar_juego_completo();
	test_obtener_juego_completo();
	test_realizar_jugadas_completo();
	test_contenido_y_pokemon_en_posicion();
	test_estado_juego_completo();
	test_puntos_y_captura_avanzado();
	test_casos_extremos_pokemon_capturado();
	test_tiempo_restante_completo();
	test_recorrer_pokemones_capturados();
	test_multiples_conexiones();

	return pa2m_mostrar_reporte();
}