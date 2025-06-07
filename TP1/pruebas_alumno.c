#include "pa2m.h"
#include "src/pokedex.h"
#include <string.h>

#define ARCHIVO_PRUEBA "ejemplos/pokedex.csv"
#define ARCHIVO_CON_ERRORES "ejemplos/pokedex_con_errores.csv"
#define ARCHIVO_VACIO "ejemplos/vacio.csv"
#define ARCHIVO_CON_ERRORES_PRIMERO \
	"ejemplos/archivo_con_primer_linea_invalida.csv"

// Contador global para verificar invocaciones de funciones
static int contador_invocaciones = 0;

bool contar_invocaciones_siempre_true(struct pokemon *pokemon, void *contexto)
{
	contador_invocaciones++;
	return true;
}

bool contar_invocaciones_siempre_false(struct pokemon *pokemon, void *contexto)
{
	contador_invocaciones++;
	return false;
}

bool contar_hasta_n(struct pokemon *pokemon, void *contexto)
{
	contador_invocaciones++;
	int *limite = (int *)contexto;
	return contador_invocaciones < *limite;
}

bool verificar_orden_alfabetico(struct pokemon *pokemon, void *contexto)
{
	struct pokemon **ultimo = (struct pokemon **)contexto;
	if (*ultimo && strcmp((*ultimo)->nombre, pokemon->nombre) > 0) {
		return false;
	}
	*ultimo = pokemon;
	return true;
}

bool verificar_orden_numerico_id(struct pokemon *pokemon, void *contexto)
{
	unsigned *ultimo_id = (unsigned *)contexto;
	if (*ultimo_id > pokemon->id) {
		return false;
	}
	*ultimo_id = pokemon->id;
	return true;
}

// PRUEBAS DE ABRIR POKEDEX ADICIONALES
void pokedex_abrir_con_archivo_null_devuelve_null()
{
	pokedex_t *pokedex = pokedex_abrir(NULL);
	pa2m_afirmar(pokedex == NULL, "Abrir un archivo NULL devuelve NULL");
}

void pokedex_cantidad_con_pokedex_null_devuelve_cero()
{
	unsigned cantidad = pokedex_cantidad_pokemones(NULL);
	pa2m_afirmar(cantidad == 0,
		     "Una pokedex NULL tiene 0 pokemones (valor obtenido: %d)",
		     cantidad);
}

// PRUEBAS DE BÚSQUEDA POR NOMBRE ADICIONALES
void buscar_pokemon_con_nombre_null_devuelve_null()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	const struct pokemon *pokemon =
		pokedex_buscar_pokemon_nombre(pokedex, NULL);
	pa2m_afirmar(pokemon == NULL,
		     "Buscar un pokemon con nombre NULL devuelve NULL");
	pokedex_destruir(pokedex);
}

void verificar_atributos_pokemon_encontrado_por_nombre()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	const struct pokemon *pikachu =
		pokedex_buscar_pokemon_nombre(pokedex, "Pikachu");

	if (pikachu) {
		pa2m_afirmar(
			strcmp(pikachu->nombre, "Pikachu") == 0,
			"El pokemon encontrado es Pikachu (encontrado: %s)",
			pikachu->nombre);
		pa2m_afirmar(
			pikachu->id == 25,
			"El pokemon encontrado tiene id 25 (encontrado: %d)",
			pikachu->id);
		pa2m_afirmar(
			pikachu->tipo == 4,
			"El pokemon encontrado es de tipo eléctrico (encontrado: %d)",
			pikachu->tipo);
		pa2m_afirmar(
			pikachu->fuerza == 20,
			"El pokemon encontrado tiene fuerza 20 (encontrado: %d)",
			pikachu->fuerza);
		pa2m_afirmar(
			pikachu->destreza == 15,
			"El pokemon encontrado tiene destreza 15 (encontrado: %d)",
			pikachu->destreza);
		pa2m_afirmar(
			pikachu->inteligencia == 17,
			"El pokemon encontrado tiene inteligencia 17 (encontrado: %d)",
			pikachu->inteligencia);
	}

	pokedex_destruir(pokedex);
}

// PRUEBAS DE BÚSQUEDA POR ID ADICIONALES
void verificar_atributos_pokemon_encontrado_por_id()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	const struct pokemon *togepi = pokedex_buscar_pokemon_id(pokedex, 175);

	if (togepi) {
		pa2m_afirmar(strcmp(togepi->nombre, "Togepi") == 0,
			     "El pokemon encontrado es Togepi (encontrado: %s)",
			     togepi->nombre);
		pa2m_afirmar(
			togepi->id == 175,
			"El pokemon encontrado tiene id 175 (encontrado: %d)",
			togepi->id);
		pa2m_afirmar(
			togepi->tipo == 5,
			"El pokemon encontrado es de tipo eléctrico (encontrado: %d)",
			togepi->tipo);
		pa2m_afirmar(
			togepi->fuerza == 8,
			"El pokemon encontrado tiene fuerza 8 (encontrado: %d)",
			togepi->fuerza);
		pa2m_afirmar(
			togepi->destreza == 8,
			"El pokemon encontrado tiene destreza 8 (encontrado: %d)",
			togepi->destreza);
		pa2m_afirmar(
			togepi->inteligencia == 2,
			"El pokemon encontrado tiene inteligencia 2 (encontrado: %d)",
			togepi->inteligencia);
	}

	pokedex_destruir(pokedex);
}

// PRUEBAS DE ITERACIÓN POR NOMBRE ADICIONALES
void iterar_por_nombre_cuenta_invocaciones()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	contador_invocaciones = 0;

	unsigned resultado = pokedex_iterar_pokemones(
		pokedex, ITERAR_NOMBRE, contar_invocaciones_siempre_true, NULL);
	pa2m_afirmar(resultado > 0, "Iterar por nombre devuelve mayor a 0");
	pa2m_afirmar(
		resultado == contador_invocaciones,
		"Iterar por nombre devuelve %d pokemones (valor obtenido: %d)",
		contador_invocaciones, resultado);

	struct pokemon *ultimo = NULL;
	bool ordenado = pokedex_iterar_pokemones(
		pokedex, ITERAR_NOMBRE, verificar_orden_alfabetico, &ultimo);
	pa2m_afirmar(ordenado, "Los pokemones se iteran en orden alfabético");

	pa2m_afirmar(
		contador_invocaciones == resultado,
		"La función de iteración se invocó exactamente %d veces (valor obtenido: %d)",
		resultado, contador_invocaciones);

	pokedex_destruir(pokedex);
}

void iterar_por_nombre_con_limite()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	contador_invocaciones = 0;
	int limite = 8;

	unsigned resultado = pokedex_iterar_pokemones(pokedex, ITERAR_NOMBRE,
						      contar_hasta_n, &limite);
	pa2m_afirmar(resultado > 0, "Iterar por nombre devuelve mayor a 0");
	pa2m_afirmar(resultado == limite,
		     "Iterar por nombre devuelve %d (valor obtenido: %d)",
		     limite, resultado);
	pa2m_afirmar(
		contador_invocaciones == limite,
		"La función de iteración se invocó exactamente %d veces (valor obtenido: %d)",
		limite, contador_invocaciones);

	pokedex_destruir(pokedex);
}

void iterar_por_nombre_funcion_false()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	contador_invocaciones = 0;

	unsigned resultado = pokedex_iterar_pokemones(
		pokedex, ITERAR_NOMBRE, contar_invocaciones_siempre_false,
		NULL);
	pa2m_afirmar(resultado > 0, "Iterar por nombre devuelve mayor a 0");
	pa2m_afirmar(
		resultado == 1,
		"Iterar por nombre devuelve 1 para una funcion que siempre devuelve false (valor obtenido: %d)",
		resultado);
	pa2m_afirmar(
		contador_invocaciones == 1,
		"La función de iteración se invocó exactamente 1 vez (valor obtenido: %d)",
		contador_invocaciones);

	pokedex_destruir(pokedex);
}

void iterar_por_nombre_pokedex_null()
{
	contador_invocaciones = 0;
	unsigned resultado = pokedex_iterar_pokemones(
		NULL, ITERAR_NOMBRE, contar_invocaciones_siempre_true, NULL);
	pa2m_afirmar(resultado == 0,
		     "Iterar por nombre en una pokedex NULL devuelve 0");
	pa2m_afirmar(
		contador_invocaciones == 0,
		"La función de iteración no se invocó (valor obtenido: %d)",
		contador_invocaciones);
}

void iterar_por_nombre_funcion_null()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	unsigned resultado =
		pokedex_iterar_pokemones(pokedex, ITERAR_NOMBRE, NULL, NULL);
	pa2m_afirmar(resultado == 0,
		     "Iterar por nombre con una función NULL devuelve 0");
	pokedex_destruir(pokedex);
}

void iterar_por_nombre_contexto_null()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	contador_invocaciones = 0;

	unsigned resultado = pokedex_iterar_pokemones(
		pokedex, ITERAR_NOMBRE, contar_invocaciones_siempre_true, NULL);
	pa2m_afirmar(resultado > 0,
		     "Iterar por nombre con contexto NULL devuelve mayor a 0");
	pa2m_afirmar(contador_invocaciones == resultado,
		     "La función de iteración devolvio %d (valor obtenido: %d)",
		     resultado, contador_invocaciones);

	pokedex_destruir(pokedex);
}

// PRUEBAS DE ITERACIÓN POR ID ADICIONALES
void iterar_por_id_cuenta_invocaciones()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	contador_invocaciones = 0;

	unsigned resultado = pokedex_iterar_pokemones(
		pokedex, ITERAR_ID, contar_invocaciones_siempre_true, NULL);
	pa2m_afirmar(resultado > 0, "Iterar por nombre devuelve mayor a 0");
	pa2m_afirmar(
		resultado == contador_invocaciones,
		"Iterar por nombre devuelve %d pokemones (valor obtenido: %d)",
		contador_invocaciones, resultado);

	unsigned ultimo_id = 0;
	bool ordenado = pokedex_iterar_pokemones(
		pokedex, ITERAR_ID, verificar_orden_numerico_id, &ultimo_id);
	pa2m_afirmar(ordenado,
		     "Los pokemones se iteran en orden numerico por id");

	pa2m_afirmar(
		contador_invocaciones == resultado,
		"La función de iteración se invocó exactamente %d veces (valor obtenido: %d)",
		resultado, contador_invocaciones);

	pokedex_destruir(pokedex);
}

void iterar_por_id_funcion_false()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	contador_invocaciones = 0;

	unsigned resultado = pokedex_iterar_pokemones(
		pokedex, ITERAR_ID, contar_invocaciones_siempre_false, NULL);
	pa2m_afirmar(resultado > 0, "Iterar por id devuelve mayor a 0");
	pa2m_afirmar(
		resultado == 1,
		"Iterar por id devuelve 1 para una funcion que siempre devuelve false (valor obtenido: %d)",
		resultado);
	pa2m_afirmar(
		contador_invocaciones == 1,
		"La función de iteración se invocó exactamente 1 vez (valor obtenido: %d)",
		contador_invocaciones);

	pokedex_destruir(pokedex);
}

void iterar_por_id_pokedex_null()
{
	contador_invocaciones = 0;
	unsigned resultado = pokedex_iterar_pokemones(
		NULL, ITERAR_ID, contar_invocaciones_siempre_true, NULL);
	pa2m_afirmar(resultado == 0,
		     "Iterar por id en una pokedex NULL devuelve 0");
	pa2m_afirmar(
		contador_invocaciones == 0,
		"La función de iteración no se invocó (valor obtenido: %d)",
		contador_invocaciones);
}

void iterar_por_id_funcion_null()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	unsigned resultado =
		pokedex_iterar_pokemones(pokedex, ITERAR_ID, NULL, NULL);
	pa2m_afirmar(resultado == 0,
		     "Iterar por id con una función NULL devuelve 0");
	pokedex_destruir(pokedex);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de abrir podekex");
	pokedex_abrir_con_archivo_null_devuelve_null();
	pokedex_cantidad_con_pokedex_null_devuelve_cero();

	pa2m_nuevo_grupo("Pruebas de búsqueda por nombre");
	buscar_pokemon_con_nombre_null_devuelve_null();
	verificar_atributos_pokemon_encontrado_por_nombre();

	pa2m_nuevo_grupo("Pruebas de búsqueda por id");
	verificar_atributos_pokemon_encontrado_por_id();

	pa2m_nuevo_grupo("Pruebas de iteracion por nombre");
	iterar_por_nombre_cuenta_invocaciones();
	iterar_por_nombre_con_limite();
	iterar_por_nombre_funcion_false();
	iterar_por_nombre_pokedex_null();
	iterar_por_nombre_funcion_null();
	iterar_por_nombre_contexto_null();

	pa2m_nuevo_grupo("Pruebas de iteracion por id");
	iterar_por_id_cuenta_invocaciones();
	iterar_por_id_funcion_false();
	iterar_por_id_pokedex_null();
	iterar_por_id_funcion_null();

	return pa2m_mostrar_reporte();
}