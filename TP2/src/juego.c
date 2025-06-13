#include "../extra/engine.h"
#include "juego.h"
#include <string.h>
#include <time.h>

#define MIN_POKEMONES 4
#define TECLA_W 'w'
#define TECLA_S 's'
#define TECLA_D 'd'
#define TECLA_A 'a'
#define GANO_JUGADOR_1 1
#define GANO_JUGADOR_2 -1
#define SIGUEN_JUGANDO 0
#define JUGADOR '@'

const size_t CANT_CARGA_POKEMONES = 10;
const int PUNTOS_INICIALES = 10;
const int PERDIDA_DE_PUNTOS = 1;
const char VACIO = ' ';

typedef struct coordenada {
	int fil;
	int col;
} coordenada_t;

typedef struct pokemon_juego {
	struct pokemon *poke;
	coordenada_t posicion;
} pokemon_juego_t;

typedef struct jugador {
	coordenada_t posicion;
	lista_t *pokes_capturados;
	unsigned puntos;
} jugador_t;

struct juego {
	jugador_t jugador;
	lista_t *pokes_en_juego;
	pila_t *pokes_pendientes;
	unsigned indice_aparicion_actual;
};

struct conexion_juegos {
	pokedex_t *pokedex;
	juego_t *juegos[MAX_JUGADORES];
	lista_t *orden_aparicion_compartido;
	time_t tiempo_inicio;
};

typedef struct aux_recolectar_pokes {
	lista_t *lista_pokes;
	size_t cant_deseada;
} aux_recolectar_pokes_t;

/**
 * Devuelve una posición aleatoria con la semilla dada.
 */
coordenada_t generar_posicion_aleatoria()
{
	coordenada_t pos;
	pos.fil = rand() % MAX_FILAS;
	pos.col = rand() % MAX_COLUMNAS;
	return pos;
}

/**
 * Devuelve una copia del pokemon dado
 */
pokemon_juego_t *copia_pokemon(pokemon_juego_t *pokemon)
{
	pokemon_juego_t *copia_pokemon = calloc(1, sizeof(pokemon_juego_t));
	if (!copia_pokemon) {
		return NULL;
	}

	struct pokemon *copia_poke = calloc(1, sizeof(struct pokemon));
	if (!copia_poke) {
		free(copia_pokemon);
		return NULL;
	}
	*copia_poke = *pokemon->poke;

	copia_poke->nombre =
		calloc(strlen(pokemon->poke->nombre) + 1, sizeof(char));
	if (!copia_poke->nombre) {
		free(copia_poke);
		free(copia_pokemon);
		return NULL;
	}
	strcpy((char *)copia_poke->nombre, (char *)pokemon->poke->nombre);

	copia_pokemon->poke = copia_poke;
	copia_pokemon->posicion = pokemon->posicion;

	return copia_pokemon;
}

void destruir_pokemon_juego(void *pokemon_ptr)
{
	if (!pokemon_ptr) {
		return;
	}

	pokemon_juego_t *pokemon = (pokemon_juego_t *)pokemon_ptr;
	if (pokemon->poke) {
		if (pokemon->poke->nombre) {
			free((char *)pokemon->poke->nombre);
		}
		free(pokemon->poke);
	}
	free(pokemon);
}

// -------------------------------- MANEJO DE POKEDEX --------------------------------

// Carga la pokedex del nombre del archivo dado.
pokedex_t *cargar_pokedex(const char *archivo)
{
	if (!archivo) {
		return NULL;
	}

	pokedex_t *pokedex = pokedex_abrir(archivo);
	if (!pokedex) {
		return NULL;
	}
	return pokedex;
}

// Función auxiliar para recolectar pokemones en una lista hasta llegar al tamaño buscado.
bool recolectar_cant_pokes(struct pokemon *pokemon, void *ctx)
{
	aux_recolectar_pokes_t *aux = (aux_recolectar_pokes_t *)ctx;
	lista_t *pokes = aux->lista_pokes;
	size_t cant = aux->cant_deseada;

	if (cant == lista_tamanio(pokes)) {
		return false;
	}

	pokemon_juego_t *nuevo = calloc(1, sizeof(pokemon_juego_t));
	if (!nuevo) {
		return false;
	}

	struct pokemon *copia = calloc(1, sizeof(struct pokemon));
	if (!copia) {
		free(nuevo);
		return false;
	}
	*copia = *pokemon;

	copia->nombre = calloc(strlen(pokemon->nombre) + 1, sizeof(char));
	if (!copia->nombre) {
		free(copia);
		free(nuevo);
		return false;
	}
	strcpy((char *)copia->nombre, (char *)pokemon->nombre);

	nuevo->posicion = generar_posicion_aleatoria();
	nuevo->poke = copia;

	if (!lista_insertar(pokes, nuevo)) {
		free((char *)copia->nombre);
		free(copia);
		free(nuevo);
		return false;
	}
	return true;
}

/**
 * Devuelve una lista de la cantidad dada de pokemones de la pokedex.
 * 
 * La cantidad mínima que se puede pasar es igual a MIN_POKEMONES.
 */
lista_t *conseguir_pokes(pokedex_t *pokedex, size_t cantidad)
{
	if (!pokedex || cantidad < MIN_POKEMONES) {
		return NULL;
	}

	lista_t *pokes = lista_crear();
	if (!pokes) {
		return NULL;
	}

	aux_recolectar_pokes_t aux;
	aux.lista_pokes = pokes;
	aux.cant_deseada = cantidad;

	pokedex_iterar_pokemones(pokedex, ITERAR_ID, recolectar_cant_pokes,
				 &aux);
	return aux.lista_pokes;
}

/**
 * Agrega a la lista un total de CANT_CARGA_POKEMONES de pokemones de la pokedex.
 * 
 * La lista ya debe estar inicializada.
 * Devuelve la lista actualizada.
 */
lista_t *agregar_pokes(conexion_juegos_t *conexion)
{
	if (!conexion) {
		return NULL;
	}

	aux_recolectar_pokes_t aux;
	aux.lista_pokes = conexion->orden_aparicion_compartido;
	aux.cant_deseada = lista_tamanio(conexion->orden_aparicion_compartido) +
			   CANT_CARGA_POKEMONES;

	pokedex_iterar_pokemones(conexion->pokedex, ITERAR_ID,
				 recolectar_cant_pokes, &aux);
	return aux.lista_pokes;
}

// -------------------------------- BASE JUEGO --------------------------------

/**
 * Agrega el pokemon siguiente de la lista de pokemones compartida entre juegos al juego dado.
 * En caso de que a la lista compartida le queden menos de cuatro elementos se le agregan diez.
 */
void agregar_pokemon_en_juego(conexion_juegos_t *conexion, int num_juego)
{
	if (!conexion || num_juego > MAX_JUGADORES) {
		return;
	}

	if ((conexion->juegos[num_juego]->indice_aparicion_actual +
	     MIN_POKEMONES) >=
	    lista_tamanio(conexion->orden_aparicion_compartido)) {
		agregar_pokes(conexion);
	}

	if (conexion->juegos[num_juego]->indice_aparicion_actual <
	    lista_tamanio(conexion->orden_aparicion_compartido)) {
		pokemon_juego_t *siguiente = lista_obtener_elemento(
			conexion->orden_aparicion_compartido,
			(int)conexion->juegos[num_juego]
				->indice_aparicion_actual);

		if (siguiente) {
			pokemon_juego_t *copia = copia_pokemon(siguiente);
			if (copia) {
				lista_insertar(conexion->juegos[num_juego]
						       ->pokes_en_juego,
					       copia);
			}
			conexion->juegos[num_juego]->indice_aparicion_actual++;
		}
	}
}

conexion_juegos_t *inicializar_juego(pokedex_t *pokedex, unsigned int semilla)
{
	if (!pokedex) {
		return NULL;
	}

	srand(semilla);

	conexion_juegos_t *conexion = calloc(1, sizeof(conexion_juegos_t));
	if (!conexion) {
		return NULL;
	}
	conexion->pokedex = pokedex;

	lista_t *pokes_iniciales =
		conseguir_pokes(conexion->pokedex, CANT_CARGA_POKEMONES);
	if (!pokes_iniciales) {
		free(conexion);
		return NULL;
	}
	conexion->orden_aparicion_compartido = pokes_iniciales;

	for (int i = 0; i < MAX_JUGADORES; i++) {
		conexion->juegos[i] = calloc(1, sizeof(juego_t));
		if (!conexion->juegos[i]) {
			for (int j = 0; j < i; j++) {
				if (conexion->juegos[j]) {
					if (conexion->juegos[j]
						    ->jugador.pokes_capturados) {
						lista_destruir_todo(
							conexion->juegos[j]
								->jugador
								.pokes_capturados,
							destruir_pokemon_juego);
					}
					if (conexion->juegos[j]
						    ->pokes_pendientes) {
						pila_destruir_todo(
							conexion->juegos[j]
								->pokes_pendientes,
							destruir_pokemon_juego);
					}
					if (conexion->juegos[j]->pokes_en_juego) {
						lista_destruir_todo(
							conexion->juegos[j]
								->pokes_en_juego,
							destruir_pokemon_juego);
					}
					free(conexion->juegos[j]);
				}
			}
			lista_destruir_todo(
				conexion->orden_aparicion_compartido,
				destruir_pokemon_juego);
			free(conexion);
			return NULL;
		}

		conexion->juegos[i]->jugador.posicion.col = 0;
		conexion->juegos[i]->jugador.posicion.fil = 0;
		conexion->juegos[i]->jugador.puntos = PUNTOS_INICIALES;

		conexion->juegos[i]->jugador.pokes_capturados = lista_crear();
		conexion->juegos[i]->pokes_pendientes = pila_crear();
		conexion->juegos[i]->pokes_en_juego = lista_crear();

		if (!conexion->juegos[i]->jugador.pokes_capturados ||
		    !conexion->juegos[i]->pokes_pendientes ||
		    !conexion->juegos[i]->pokes_en_juego) {
			destruir_juego(conexion);
			return NULL;
		}

		for (int j = 0; j < MIN_POKEMONES; j++) {
			agregar_pokemon_en_juego(conexion, i);
		}
	}
	conexion->tiempo_inicio = time(NULL);
	return conexion;
}

juego_t *obtener_juego(conexion_juegos_t *conexion, int numero)
{
	if (!conexion || numero > MAX_JUGADORES) {
		return NULL;
	}
	return conexion->juegos[numero];
}

// -------------------------------- POSICIONES EN JUEGO --------------------------------

/**
 * Devuelve true si la posición del jugador es la misma que la del pokemon, en caso contrario false.
 */
bool misma_posicion_que_poke(void *pokemon, void *jugador)
{
	if (!jugador || !pokemon) {
		return false;
	}

	pokemon_juego_t *poke = (pokemon_juego_t *)pokemon;
	jugador_t *player = (jugador_t *)jugador;

	bool misma_fil = (player->posicion.fil == poke->posicion.fil);
	bool misma_col = (player->posicion.col == poke->posicion.col);

	return (misma_fil && misma_col);
}

/**
 * En caso de que la posición del jugador coincida con la de algún pokemon en el juego, este se elimina y se devuelve.
 * 
 * De no coincidir de devuelve NULL.
 */
pokemon_juego_t *jugador_capturar_pokemon(conexion_juegos_t *conexion,
					  int num_juego)
{
	if (!conexion || num_juego > MAX_JUGADORES ||
	    !lista_tamanio(conexion->juegos[num_juego]->pokes_en_juego)) {
		return NULL;
	}

	pokemon_juego_t *poke_capturado = (pokemon_juego_t *)lista_buscar(
		conexion->juegos[num_juego]->pokes_en_juego,
		misma_posicion_que_poke, &conexion->juegos[num_juego]->jugador);
	if (!poke_capturado) {
		return NULL;
	}

	pokemon_juego_t *eliminado = lista_sacar_elemento(
		conexion->juegos[num_juego]->pokes_en_juego, poke_capturado);

	int juego_contrario;
	if (num_juego == 0) {
		juego_contrario = 1;
	} else {
		juego_contrario = 0;
	}

	pokemon_juego_t *copia_capturados = copia_pokemon(poke_capturado);
	pokemon_juego_t *copia_pendientes = copia_pokemon(poke_capturado);

	if (!copia_capturados || !copia_pendientes) {
		if (copia_capturados)
			destruir_pokemon_juego(copia_capturados);
		if (copia_pendientes)
			destruir_pokemon_juego(copia_pendientes);
		return eliminado;
	}

	lista_insertar(conexion->juegos[num_juego]->jugador.pokes_capturados,
		       copia_capturados);
	pila_apilar(conexion->juegos[juego_contrario]->pokes_pendientes,
		    copia_pendientes);

	pokemon_juego_t *tope_pila =
		pila_tope(conexion->juegos[num_juego]->pokes_pendientes);
	if (pila_tamanio(conexion->juegos[num_juego]->pokes_pendientes) > 0 &&
	    eliminado->poke->tipo == tope_pila->poke->tipo) {
		conexion->juegos[num_juego]->jugador.puntos++;
		conexion->juegos[juego_contrario]->jugador.puntos--;
		pokemon_juego_t *desapilado = pila_desapilar(
			conexion->juegos[num_juego]->pokes_pendientes);
		destruir_pokemon_juego(desapilado);
	}

	return eliminado;
}

/**
 * Captura todos los pokemones que coincidan con la posición del jugador.
 * Devuelve la cantidad de pokemones capturados.
 */
int jugador_capturar_todos_pokemon(conexion_juegos_t *conexion, int num_juego)
{
	if (!conexion || num_juego > MAX_JUGADORES ||
	    !lista_tamanio(conexion->juegos[num_juego]->pokes_en_juego)) {
		return 0;
	}

	int pokemon_capturados = 0;
	pokemon_juego_t *capturado = NULL;
	do {
		capturado = jugador_capturar_pokemon(conexion, num_juego);
		if (capturado) {
			pokemon_capturados++;
			destruir_pokemon_juego(capturado);
		}
	} while (capturado);

	while (lista_tamanio(conexion->juegos[num_juego]->pokes_en_juego) <
	       MIN_POKEMONES) {
		agregar_pokemon_en_juego(conexion, num_juego);
	}

	return pokemon_capturados;
}

/**
 * Mueve la posición del jugador en el juego segun la accion pasada.
 */
void realizar_movimiento(conexion_juegos_t *conexion, int accion, int num_juego)
{
	if (!conexion || num_juego > MAX_JUGADORES) {
		return;
	}

	juego_t *juego = conexion->juegos[num_juego];
	if (accion == TECLA_W || accion == TECLA_ARRIBA) {
		if (juego->jugador.posicion.fil - 1 >= 0) {
			juego->jugador.posicion.fil--;
		}
	} else if (accion == TECLA_S || accion == TECLA_ABAJO) {
		if (juego->jugador.posicion.fil + 1 < MAX_FILAS) {
			juego->jugador.posicion.fil++;
		}
	} else if (accion == TECLA_D || accion == TECLA_DERECHA) {
		if (juego->jugador.posicion.col + 1 < MAX_COLUMNAS) {
			juego->jugador.posicion.col++;
		}
	} else if (accion == TECLA_A || accion == TECLA_IZQUIERDA) {
		if (juego->jugador.posicion.col - 1 >= 0) {
			juego->jugador.posicion.col--;
		}
	}

	jugador_capturar_todos_pokemon(conexion, num_juego);
}

char obtener_contenido_posicion(juego_t *juego, int fila, int columna)
{
	if (!juego) {
		return VACIO;
	}

	if (juego->jugador.posicion.fil == fila &&
	    juego->jugador.posicion.col == columna) {
		return JUGADOR;
	}

	char poke = VACIO;
	for (size_t i = 0; i < lista_tamanio(juego->pokes_en_juego); i++) {
		pokemon_juego_t *pokemon =
			lista_obtener_elemento(juego->pokes_en_juego, (int)i);
		if (pokemon && pokemon->posicion.fil == fila &&
		    pokemon->posicion.col == columna) {
			if (pokemon->poke->nombre) {
				poke = pokemon->poke->nombre[0];
			}
		}
	}

	return poke;
}

struct pokemon *obtener_pokemon_en_posicion(juego_t *juego, int fila,
					    int columna)
{
	if (!juego) {
		return NULL;
	}

	pokemon_juego_t *pokemon = NULL;
	bool encontrado = false;
	for (size_t i = 0;
	     i < lista_tamanio(juego->pokes_en_juego) && !encontrado; i++) {
		pokemon = lista_obtener_elemento(juego->pokes_en_juego, (int)i);
		if (pokemon && pokemon->posicion.fil == fila &&
		    pokemon->posicion.col == columna) {
			encontrado = true;
		}
	}

	if (encontrado) {
		return pokemon->poke;
	}
	return NULL;
}

void realizar_jugada(conexion_juegos_t *conexion, int accion)
{
	if (!conexion) {
		return;
	}

	int jugador = 0;
	if (accion == TECLA_ARRIBA || accion == TECLA_ABAJO ||
	    accion == TECLA_IZQUIERDA || accion == TECLA_DERECHA) {
		jugador = 1;
	}
	realizar_movimiento(conexion, accion, jugador);
}

// -------------------------------- ESTADO --------------------------------

int estado_juego(conexion_juegos_t *conexion)
{
	if (obtener_tiempo_restante(conexion) <= 0) {
		juego_t *juego1 = conexion->juegos[0];
		juego_t *juego2 = conexion->juegos[1];

		if (juego1->jugador.puntos > juego2->jugador.puntos) {
			return GANO_JUGADOR_1;
		} else if (juego2->jugador.puntos > juego1->jugador.puntos) {
			return GANO_JUGADOR_2;
		} else {
			return GANO_JUGADOR_1;
		}
	}

	juego_t *juego1 = conexion->juegos[0];
	juego_t *juego2 = conexion->juegos[1];
	if (juego1->jugador.puntos == 0) {
		return GANO_JUGADOR_2;
	} else if (juego2->jugador.puntos == 0) {
		return GANO_JUGADOR_1;
	}
	return SIGUEN_JUGANDO;
}

void destruir_juego(conexion_juegos_t *conexion)
{
	if (!conexion) {
		return;
	}

	for (int i = 0; i < MAX_JUGADORES; i++) {
		if (conexion->juegos[i]) {
			if (conexion->juegos[i]->jugador.pokes_capturados) {
				lista_destruir_todo(
					conexion->juegos[i]
						->jugador.pokes_capturados,
					destruir_pokemon_juego);
			}

			if (conexion->juegos[i]->pokes_pendientes) {
				pila_destruir_todo(
					conexion->juegos[i]->pokes_pendientes,
					destruir_pokemon_juego);
			}

			if (conexion->juegos[i]->pokes_en_juego) {
				lista_destruir_todo(
					conexion->juegos[i]->pokes_en_juego,
					destruir_pokemon_juego);
			}

			free(conexion->juegos[i]);
		}
	}

	if (conexion->orden_aparicion_compartido) {
		lista_destruir_todo(conexion->orden_aparicion_compartido,
				    destruir_pokemon_juego);
	}

	free(conexion);
}

unsigned obtener_puntos_jugador(juego_t *juego)
{
	if (!juego) {
		return 0;
	}
	return juego->jugador.puntos;
}

size_t obtener_cantidad_pokes_capturados(juego_t *juego)
{
	if (!juego) {
		return 0;
	}
	return lista_tamanio(juego->jugador.pokes_capturados);
}

unsigned recorrer_pokemones_capturados(juego_t *juego,
				       bool (*criterio)(void *, void *),
				       void *ctx)
{
	if (!juego || !criterio) {
		return 0;
	}

	unsigned contador = 0;
	size_t tamanio = lista_tamanio(juego->jugador.pokes_capturados);

	for (size_t i = 0; i < tamanio; i++) {
		pokemon_juego_t *pokemon = lista_obtener_elemento(
			juego->jugador.pokes_capturados, (int)i);
		if (pokemon && criterio(pokemon, ctx)) {
			contador++;
		}
	}

	return contador;
}

/**
 * Obtiene el pokémon en la posición específica de la lista de pokémones capturados
 */
struct pokemon *obtener_pokemon_capturado(juego_t *juego, int posicion)
{
	if (!juego || posicion < 0) {
		return NULL;
	}

	pokemon_juego_t *poke_juego = lista_obtener_elemento(
		juego->jugador.pokes_capturados, posicion);
	return poke_juego->poke;
}

/**
 * Obtiene el pokémon en el tope de la pila de pokémones pendientes
 */
struct pokemon *obtener_pokemon_pendiente_tope(juego_t *juego)
{
	if (!juego || pila_tamanio(juego->pokes_pendientes) == 0) {
		return NULL;
	}

	pokemon_juego_t *poke_juego = pila_tope(juego->pokes_pendientes);
	return poke_juego->poke;
}

/**
 * Obtiene el tamaño de la pila de pokémones pendientes
 */
size_t obtener_cantidad_pokes_pendientes(juego_t *juego)
{
	if (!juego) {
		return 0;
	}

	return pila_tamanio(juego->pokes_pendientes);
}

int obtener_tiempo_restante(conexion_juegos_t *conexion)
{
	if (!conexion) {
		return 0;
	}

	time_t tiempo_actual = time(NULL);
	double tiempo_transcurrido =
		difftime(tiempo_actual, conexion->tiempo_inicio);
	int tiempo_restante =
		60 - (int)tiempo_transcurrido; // 60 segundos = 1 minuto

	return (tiempo_restante < 0) ? 0 : tiempo_restante;
}