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
#define EMPATE 2
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
 * Devuelve una coordenada aleatoria.
 */
coordenada_t generar_posicion_aleatoria()
{
	coordenada_t pos;
	pos.fil = rand() % MAX_FILAS;
	pos.col = rand() % MAX_COLUMNAS;
	return pos;
}

/**
 * Devuelve una copia del 'struct pokemon' dado.
 * 
 * En caso de error devuelve NULL.
 */
struct pokemon *copia_pokemon(struct pokemon *pokemon)
{
	struct pokemon *copia = calloc(1, sizeof(struct pokemon));
	if (!copia) {
		return NULL;
	}

	copia->id = pokemon->id;
	copia->tipo = pokemon->tipo;
	copia->fuerza = pokemon->fuerza;
	copia->destreza = pokemon->destreza;
	copia->inteligencia = pokemon->inteligencia;

	copia->nombre = calloc(strlen(pokemon->nombre) + 1, sizeof(char));
	if (!copia->nombre) {
		free(copia);
		return NULL;
	}
	strcpy((char *)copia->nombre, (char *)pokemon->nombre);

	return copia;
}

/**
 * Devuelve una copia del 'pokemon_juego_t' dado.
 * 
 * En caso de error devuelve NULL.
 */
pokemon_juego_t *copia_pokemon_juego(pokemon_juego_t *pokemon)
{
	pokemon_juego_t *copia = calloc(1, sizeof(pokemon_juego_t));
	if (!copia) {
		return NULL;
	}

	struct pokemon *copia_poke = copia_pokemon(pokemon->poke);
	if (!copia_poke) {
		free(copia);
		return NULL;
	}

	copia->poke = copia_poke;
	copia->posicion = pokemon->posicion;

	return copia;
}

/**
 * Carga la pokedex del nombre del archivo dado.
 * 
 * En caso de error devuelve NULL.
 */
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

/**
 * Crea y devuelve un 'pokemon_juego_t' con una posición aleatoria.
 * 
 * En caso de error devuelve NULL.
 */
pokemon_juego_t *crear_pokemon_juego(struct pokemon *pokemon)
{
	if (!pokemon) {
		return NULL;
	}

	pokemon_juego_t *nuevo = calloc(1, sizeof(pokemon_juego_t));
	if (!nuevo) {
		return NULL;
	}

	struct pokemon *copia = copia_pokemon(pokemon);
	if (!copia) {
		free(nuevo);
		return NULL;
	}

	nuevo->posicion = generar_posicion_aleatoria();
	nuevo->poke = copia;

	return nuevo;
}

/**
 * Función auxiliar para recolectar pokemones en una lista hasta llegar al tamaño buscado.
 * 
 * En caso de error devuelve false.
 */
bool recolectar_cant_pokes(struct pokemon *pokemon, void *ctx)
{
	aux_recolectar_pokes_t *aux = (aux_recolectar_pokes_t *)ctx;
	lista_t *pokes = aux->lista_pokes;
	size_t cant = aux->cant_deseada;

	if (cant == lista_tamanio(pokes)) {
		return false;
	}

	pokemon_juego_t *nuevo = crear_pokemon_juego(pokemon);
	if (!nuevo) {
		return false;
	}

	if (!lista_insertar(pokes, nuevo)) {
		free((char *)nuevo->poke->nombre);
		free(nuevo->poke);
		free(nuevo);
		return false;
	}
	return true;
}

/**
 * Devuelve una lista de la cantidad dada de pokemones de la pokedex.
 * 
 * En caso de pasar una cantidad menor a MIN_POKEMONES se adopta esa cantidad.
 * En caso de error devuelve NULL.
 */
lista_t *conseguir_pokes(pokedex_t *pokedex, size_t cantidad)
{
	if (!pokedex) {
		return NULL;
	} else if (cantidad < MIN_POKEMONES) {
		cantidad = MIN_POKEMONES;
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
 * Devuelve la lista actualizada o en caso de error NULL.
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

/**
 * Agrega el pokemon siguiente de la lista de pokemones compartida entre juegos al juego dado.
 * En caso de que a la lista compartida le queden menos de MIN_POKEMONES elementos se le agregan CANT_CARGA_POKEMONES.
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
			pokemon_juego_t *copia = copia_pokemon_juego(siguiente);
			if (copia) {
				lista_insertar(conexion->juegos[num_juego]
						       ->pokes_en_juego,
					       copia);
			}
			conexion->juegos[num_juego]->indice_aparicion_actual++;
		}
	}
}

/**
 * Inicializa 'jugador_t' dentro del 'juego_t' dado.
 * 
 * En caso de error devuelve false.
 */
bool inicializar_jugador(juego_t *juego)
{
	if (!juego) {
		return false;
	}

	juego->jugador.posicion.col = 0;
	juego->jugador.posicion.fil = 0;
	juego->jugador.puntos = PUNTOS_INICIALES;

	juego->jugador.pokes_capturados = lista_crear();
	juego->pokes_pendientes = pila_crear();
	juego->pokes_en_juego = lista_crear();

	return (juego->jugador.pokes_capturados && juego->pokes_pendientes &&
		juego->pokes_en_juego);
}

/**
 * Inicializa todos los 'juego_t' dentro de 'conexion_juegos_t'.
 * 
 * En caso de error devuelve false.
 */
bool inicializar_juegos(conexion_juegos_t *conexion)
{
	if (!conexion) {
		return false;
	}

	for (int i = 0; i < MAX_JUGADORES; i++) {
		conexion->juegos[i] = calloc(1, sizeof(juego_t));
		if (!conexion->juegos[i]) {
			return false;
		}

		if (!inicializar_jugador(conexion->juegos[i])) {
			return false;
		}

		for (int j = 0; j < MIN_POKEMONES; j++) {
			agregar_pokemon_en_juego(conexion, i);
		}
	}
	return true;
}

/**
 * Inicializa la estructura 'conexion_juegos_t' con los datos de la 'pokedex_t' dada.
 * 
 * En caso de error devuelve NULL.
 */
conexion_juegos_t *inicializar_conexion(pokedex_t *pokedex)
{
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
	conexion->tiempo_inicio = time(NULL);

	return conexion;
}

conexion_juegos_t *inicializar_juego(pokedex_t *pokedex, unsigned int semilla)
{
	if (!pokedex) {
		return NULL;
	}

	srand(semilla);

	conexion_juegos_t *conexion = inicializar_conexion(pokedex);
	if (!conexion) {
		return NULL;
	}

	if (!inicializar_juegos(conexion)) {
		destruir_juego(conexion);
		return NULL;
	}

	return conexion;
}

juego_t *obtener_juego(conexion_juegos_t *conexion, int numero)
{
	if (!conexion || numero < 0 || numero >= MAX_JUGADORES) {
		return NULL;
	}
	return conexion->juegos[numero];
}

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
 * Función destructora para un struct de tipo 'pokemon_juego_t'.
 */
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

/**
 * Obtiene el número del jugador contrario al dado.
 */
int obtener_jugador_contrario(int num_juego)
{
	if (num_juego == 0) {
		return 1;
	}
	return 0;
}

/**
 * Procesa las copias del pokemon capturado:
 * 	- una para la pila de pokemones pendientes del oponente;
 * 	- y otra para su lista de capturados.
 * 
 * Devuelve false si hubo algún error.
 */
bool procesar_pokemon_capturado(conexion_juegos_t *conexion, int num_juego,
				pokemon_juego_t *pokemon_capturado)
{
	int juego_contrario = obtener_jugador_contrario(num_juego);

	pokemon_juego_t *copia_capturados =
		copia_pokemon_juego(pokemon_capturado);
	pokemon_juego_t *copia_pendientes =
		copia_pokemon_juego(pokemon_capturado);

	if (!copia_capturados || !copia_pendientes) {
		if (copia_capturados)
			destruir_pokemon_juego(copia_capturados);
		if (copia_pendientes)
			destruir_pokemon_juego(copia_pendientes);
		return false;
	}

	lista_insertar(conexion->juegos[num_juego]->jugador.pokes_capturados,
		       copia_capturados);
	pila_apilar(conexion->juegos[juego_contrario]->pokes_pendientes,
		    copia_pendientes);

	return true;
}

/**
 * Manjea los puntos luego de una captura:
 * 	- agrega un punto al jugador que captura el pokemon del tope de su lista de pendientes;
 * 	- le resta un punto a su contrincante.
 */
void manejar_puntos_captura(conexion_juegos_t *conexion, int num_juego,
			    pokemon_juego_t *pokemon_capturado)
{
	int juego_contrario = obtener_jugador_contrario(num_juego);

	pokemon_juego_t *tope_pila =
		pila_tope(conexion->juegos[num_juego]->pokes_pendientes);

	if (pila_tamanio(conexion->juegos[num_juego]->pokes_pendientes) > 0 &&
	    pokemon_capturado->poke->tipo == tope_pila->poke->tipo) {
		conexion->juegos[num_juego]->jugador.puntos++;
		conexion->juegos[juego_contrario]->jugador.puntos--;

		pokemon_juego_t *desapilado = pila_desapilar(
			conexion->juegos[num_juego]->pokes_pendientes);
		destruir_pokemon_juego(desapilado);
	}
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

	if (!procesar_pokemon_capturado(conexion, num_juego, poke_capturado)) {
		return eliminado;
	}

	manejar_puntos_captura(conexion, num_juego, poke_capturado);

	return eliminado;
}

/**
 * Captura todos los pokemones que coincidan con la posición del jugador.
 * 
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
 * Mueve la posición del jugador en el juego según la acción pasada y efectua todas 
 * las interacciones necesarias.
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

/**
 * Función auxiliar para buscar pokemon en posición específica.
 * 
 * Devuelve true si la posición del pokemon coincide con la dada, 
 * en caso contrario devuelve false.
 */
bool pokemon_en_posicion(void *pokemon_ptr, void *contexto)
{
	if (!pokemon_ptr || !contexto) {
		return false;
	}

	pokemon_juego_t *pokemon = (pokemon_juego_t *)pokemon_ptr;
	coordenada_t *posicion_buscada = (coordenada_t *)contexto;

	return (pokemon->posicion.fil == posicion_buscada->fil &&
		pokemon->posicion.col == posicion_buscada->col);
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

	struct pokemon *pokemon =
		obtener_pokemon_en_posicion(juego, fila, columna);
	if (pokemon && pokemon->nombre) {
		return pokemon->nombre[0];
	}

	return VACIO;
}

struct pokemon *obtener_pokemon_en_posicion(juego_t *juego, int fila,
					    int columna)
{
	if (!juego) {
		return NULL;
	}

	coordenada_t posicion_buscada = { .fil = fila, .col = columna };

	pokemon_juego_t *pokemon_encontrado = (pokemon_juego_t *)lista_buscar(
		juego->pokes_en_juego, pokemon_en_posicion, &posicion_buscada);

	if (pokemon_encontrado) {
		return pokemon_encontrado->poke;
	}
	return NULL;
}

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
			return EMPATE;
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

struct pokemon *obtener_pokemon_capturado(juego_t *juego, int posicion)
{
	if (!juego || posicion < 0) {
		return NULL;
	}

	pokemon_juego_t *poke_juego = lista_obtener_elemento(
		juego->jugador.pokes_capturados, posicion);
	if (!poke_juego) {
		return NULL;
	}
	return poke_juego->poke;
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

size_t obtener_cantidad_pokes_pendientes(juego_t *juego)
{
	if (!juego) {
		return 0;
	}

	return pila_tamanio(juego->pokes_pendientes);
}

struct pokemon *obtener_pokemon_pendiente_tope(juego_t *juego)
{
	if (!juego || pila_tamanio(juego->pokes_pendientes) == 0) {
		return NULL;
	}

	pokemon_juego_t *poke_juego = pila_tope(juego->pokes_pendientes);
	return poke_juego->poke;
}

int obtener_tiempo_restante(conexion_juegos_t *conexion)
{
	if (!conexion) {
		return 0;
	}

	time_t tiempo_actual = time(NULL);
	int tiempo_transcurrido =
		(int)(tiempo_actual - conexion->tiempo_inicio);
	int tiempo_restante = 60 - (int)tiempo_transcurrido;

	if (tiempo_restante < 0) {
		return 0;
	}
	return tiempo_restante;
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