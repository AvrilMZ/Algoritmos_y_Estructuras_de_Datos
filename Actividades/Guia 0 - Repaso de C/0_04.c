/* La estructura de control más conocida es el if-else, que seguramente ya
 * usaste antes. Pero no es la única.
 *
 * La función a programar recibe una letra por parámetro, que representa la
 * inicial de un pokémon. Se pide devolver la cantidad de batallas ganadas por
 * el mismo, utilizando la estructura condicional switch.
 *
 * Se sabe que:
 * 	A es la inicial de Arbok y que ganó 20 batallas en el torneo.
 * 	R es la inicial de Rattata y que ganó 17 batallas en el torneo.
 * 	L es la inicial de Lapras y que ganó 15 batallas en el torneo.
 * 	G es la inicial de Golem y que ganó 30 batallas en el torneo.
 * 	F es la inicial de Flareon y que ganó 8 batallas en el torneo.
 * 	O es la inicial de Onix y que ganó 27 batallas en el torneo.
 * 	T es la inicial de Treecko y que ganó 5 batallas en el torneo.
 * 	C es la inicial de Charizard y que ganó 39 batallas en el torneo.
 * 	B es la inicial de Bulbassaur y que ganó 10 batallas en el torneo.
 * Si se recibe cualquier otra letra, se debe devolver -1, indicando que no se
 * conoce la cantidad de batallas ganadas de ese pokémon. Ya definimos la
 * variable ERROR para mantener las buenas prácticas.
 */

#define ERROR -1

#define INICIAL_ARBOK 'A'
#define INICIAL_RATTATA 'R'
#define INICIAL_LAPRAS 'L'
#define INICIAL_GOLEM 'G'
#define INICIAL_FLAREON 'F'
#define INICIAL_ONIX 'O'
#define INICIAL_TREECKO 'T'
#define INICIAL_CHARIZARD 'C'
#define INICIAL_BULBASSAUR 'B'

const int BATALLAS_ARBOK = 20;
const int BATALLAS_RATTATA = 17;
const int BATALLAS_LAPRAS = 15;
const int BATALLAS_GOLEM = 30;
const int BATALLAS_FLAREON = 8;
const int BATALLAS_ONIX = 27;
const int BATALLAS_TREECKO = 5;
const int BATALLAS_CHARIZARD = 39;
const int BATALLAS_BULBASSAUR = 10;

/*
 * Se recibe una letra. Si ella se corresponde con alguna de las proveídas en el
 * enunciado (A, R, L, G, F, O, T, C, B) se devuelve la cantidad de batallas
 * ganadas por el pokemon respectivo.
 */
int batallas_ganadas(char letra)
{
	switch (letra) {
	case INICIAL_ARBOK:
		return BATALLAS_ARBOK;
	case INICIAL_RATTATA:
		return BATALLAS_RATTATA;
	case INICIAL_LAPRAS:
		return BATALLAS_LAPRAS;
	case INICIAL_GOLEM:
		return BATALLAS_GOLEM;
	case INICIAL_FLAREON:
		return BATALLAS_FLAREON;
	case INICIAL_ONIX:
		return BATALLAS_ONIX;
	case INICIAL_TREECKO:
		return BATALLAS_TREECKO;
	case INICIAL_CHARIZARD:
		return BATALLAS_CHARIZARD;
	case INICIAL_BULBASSAUR:
		return BATALLAS_BULBASSAUR;
	default:
		return ERROR;
	}
}