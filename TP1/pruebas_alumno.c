#include "pa2m.h"
#include "src/pokedex.h"
#include <string.h>

#define ARCHIVO_PRUEBA "ejemplos/pokedex.csv"
#define ARCHIVO_INEXISTENTE "asdasdasd.csv"
#define ARCHIVO_CON_ERRORES "ejemplos/pokedex_con_errores.csv"

void mostrar_pokemon(const struct pokemon *pokemon)
{
	printf("Id: %d, Nombre: %s, Tipo: %d, Fuerza: %d, Destreza: %d, Inteligencia: %d\n",
	       pokemon->id, pokemon->nombre, pokemon->tipo, pokemon->fuerza,
	       pokemon->destreza, pokemon->inteligencia);
}

bool funcion_generica_para_probar_iterar(struct pokemon *pokemon,
					 void *contexto)
{
	return false;
}

// --------------- PRUEBAS CON ARCHIVO INVÁLIDO ---------------
void pokedex_abrir_devuelve_null_si_el_archivo_no_existe()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_INEXISTENTE);
	pa2m_afirmar(pokedex == NULL,
		     "Abrir un archivo inexistente devuelve NULL");
	pokedex_destruir(pokedex);
}

void pokedex_cantidad_pokemones_devuelve_cero_si_el_archivo_no_existe()
{
	pokedex_t *pokedex = NULL;
	unsigned cantidad = pokedex_cantidad_pokemones(pokedex);
	pa2m_afirmar(cantidad == 0,
		     "La pokedex tiene 0 pokemones (valor obtenido: %d)",
		     cantidad);
}

void pokedex_buscar_pokemon_nombre_devuelve_null_si_el_archivo_no_existe()
{
	pokedex_t *pokedex = NULL;
	const struct pokemon *poke =
		pokedex_buscar_pokemon_nombre(pokedex, "Pikachu");
	pa2m_afirmar(poke == NULL,
		     "Devuelve NULL al buscar un pokemon por nombre");
}

void pokedex_buscar_pokemon_id_devuelve_null_si_el_archivo_no_existe()
{
	pokedex_t *pokedex = NULL;
	const struct pokemon *poke = pokedex_buscar_pokemon_id(pokedex, 4);
	pa2m_afirmar(poke == NULL, "Devuelve NULL al buscar un pokemon por ID");
}

void pokedex_iterar_pokemones_devuelve_cero_si_el_archivo_no_existe()
{
	pokedex_t *pokedex = NULL;
	unsigned contexto_generico = 0;
	pokedex_iterar_pokemones(pokedex, ITERAR_NOMBRE,
				 funcion_generica_para_probar_iterar,
				 &contexto_generico);
	pa2m_afirmar(contexto_generico == 0,
		     "Devuelve cero al querer iterar por los pokemones");
}

// --------------- PRUEBAS CON ARCHIVO VÁLIDO ---------------
void pokedex_abrir_lee_todos_los_pokemon_y_devuelve_la_cantidad_correcta_valido()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	pa2m_afirmar(pokedex != NULL, "La pokedex no es nula");
	unsigned cantidad = pokedex_cantidad_pokemones(pokedex);
	pa2m_afirmar(cantidad == 9,
		     "La pokedex tiene 9 pokemones (valor obtenido: %d)",
		     cantidad);
	pokedex_destruir(pokedex);
}

void pokedex_buscar_pokemon_nombre_devuelve_el_pokemon_cuando_existe()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	const struct pokemon *pikachu =
		pokedex_buscar_pokemon_nombre(pokedex, "Pikachu");
	pa2m_afirmar(strcmp(pikachu->nombre, "Pikachu") == 0,
		     "El pokemon encontrado por nombre es Pikachu");
	pokedex_destruir(pokedex);
}

void pokedex_buscar_pokemon_nombre_que_no_existe()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	const struct pokemon *pokemon_invalido =
		pokedex_buscar_pokemon_nombre(pokedex, "Invalido");
	pa2m_afirmar(pokemon_invalido == NULL,
		     "No se encuentra Pokémon inválido por nombre");
	pokedex_destruir(pokedex);
}

void pokedex_buscar_pokemon_id_devuelve_el_pokemon_cuando_existe()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	const struct pokemon *magcargo =
		pokedex_buscar_pokemon_id(pokedex, 219);
	pa2m_afirmar(magcargo->id == 219,
		     "El pokemon encontrado por ID es Magcargo");
	pokedex_destruir(pokedex);
}

void pokedex_buscar_pokemon_id_que_no_existe()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	const struct pokemon *pokemon_invalido =
		pokedex_buscar_pokemon_id(pokedex, 9999);
	pa2m_afirmar(pokemon_invalido == NULL,
		     "No se encuentra Pokémon inválido por ID");
	pokedex_destruir(pokedex);
}

// --------------- PRUEBAS CON ARCHIVO PARCIALMENTE VÁLIDO ---------------
void pokedex_abrir_lee_todos_los_pokemon_y_devuelve_la_cantidad_correcta_semivalido()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_CON_ERRORES);
	pa2m_afirmar(pokedex != NULL, "La pokedex no es nula");
	unsigned cantidad = pokedex_cantidad_pokemones(pokedex);
	pa2m_afirmar(cantidad == 5,
		     "La pokedex tiene 5 pokemones (valor obtenido: %d)",
		     cantidad);
	pokedex_destruir(pokedex);
}

void pokedex_buscar_pokemon_nombre_linea_invalida()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_CON_ERRORES);
	const struct pokemon *togepi =
		pokedex_buscar_pokemon_nombre(pokedex, "Togepi");
	pa2m_afirmar(
		togepi == NULL,
		"No se encontro, buscando por nombre, el pokemon Togepi, ya que es la linea inválida");
	pokedex_destruir(pokedex);
}

void pokedex_buscar_pokemon_id_linea_invalida()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_CON_ERRORES);
	const struct pokemon *togepi = pokedex_buscar_pokemon_id(pokedex, 175);
	pa2m_afirmar(
		togepi == NULL,
		"No se encontro, buscando por ID, el pokemon Togepi, ya que es la linea inválida");
	pokedex_destruir(pokedex);
}

void pokedex_buscar_pokemon_nombre_por_fuera_del_rango_valido()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_CON_ERRORES);
	const struct pokemon *dedenne =
		pokedex_buscar_pokemon_nombre(pokedex, "Dedenne");
	pa2m_afirmar(
		dedenne == NULL,
		"No se encontro, buscando por nombre, el pokemon Dedenne, ya que se encuentra luego de la linea inválida");
	pokedex_destruir(pokedex);
}

void pokedex_buscar_pokemon_id_por_fuera_del_rango_valido()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_CON_ERRORES);
	const struct pokemon *dedenne = pokedex_buscar_pokemon_id(pokedex, 702);
	pa2m_afirmar(
		dedenne == NULL,
		"No se encontro, buscando por ID, el pokemon Dedenne, ya que se encuentra luego de la linea inválida");
	pokedex_destruir(pokedex);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas con archivo inválido");
	pokedex_abrir_devuelve_null_si_el_archivo_no_existe();
	pokedex_cantidad_pokemones_devuelve_cero_si_el_archivo_no_existe();
	pokedex_buscar_pokemon_nombre_devuelve_null_si_el_archivo_no_existe();
	pokedex_buscar_pokemon_id_devuelve_null_si_el_archivo_no_existe();
	pokedex_iterar_pokemones_devuelve_cero_si_el_archivo_no_existe();

	pa2m_nuevo_grupo("Pruebas con archivo válido");
	pokedex_abrir_lee_todos_los_pokemon_y_devuelve_la_cantidad_correcta_valido();
	pokedex_buscar_pokemon_nombre_devuelve_el_pokemon_cuando_existe();
	pokedex_buscar_pokemon_nombre_que_no_existe();
	pokedex_buscar_pokemon_id_devuelve_el_pokemon_cuando_existe();
	pokedex_buscar_pokemon_id_que_no_existe();

	pa2m_nuevo_grupo("Pruebas con archivo parcialmente válido");
	pokedex_abrir_lee_todos_los_pokemon_y_devuelve_la_cantidad_correcta_semivalido();
	pokedex_buscar_pokemon_nombre_linea_invalida();
	pokedex_buscar_pokemon_id_linea_invalida();
	pokedex_buscar_pokemon_nombre_por_fuera_del_rango_valido();
	pokedex_buscar_pokemon_id_por_fuera_del_rango_valido();

	return pa2m_mostrar_reporte();
}
