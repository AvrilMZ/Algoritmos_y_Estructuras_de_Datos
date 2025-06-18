#include "pa2m.h"
#include "../src/menu.h"
#include <string.h>

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

	return pa2m_mostrar_reporte();
}
