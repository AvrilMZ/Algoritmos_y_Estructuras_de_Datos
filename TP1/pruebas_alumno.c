#include "pa2m.h"
#include "src/pokedex.h"

#define ARCHIVO_PRUEBA "ejemplos/pokedex.csv"

void pokedex_abrir_lee_todos_los_pokemon_y_devuelve_la_cantidad_correcta()
{
	pokedex_t *pokedex = pokedex_abrir(ARCHIVO_PRUEBA);
	pa2m_afirmar(pokedex != NULL, "La pokedex no es nula");
	unsigned cantidad = pokedex_cantidad_pokemones(pokedex);
	pa2m_afirmar(cantidad == 9,
		     "La pokedex tiene 9 pokemones (valor obtenido: %d)",
		     cantidad);
	pokedex_destruir(pokedex);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas con archivo válido");
	pokedex_abrir_lee_todos_los_pokemon_y_devuelve_la_cantidad_correcta();
	//otras pruebas?????

	return pa2m_mostrar_reporte();
}
