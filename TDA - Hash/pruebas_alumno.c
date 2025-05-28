#include "pa2m.h"
#include "src/hash.h"

#include <string.h>

const char *CLAVE_1 = "AABBCC";
const char *CLAVE_2 = "DDEEFF";
const char *CLAVE_3 = "GGHHII";
const char *CLAVE_4 = "JJKKLL";
const char *CLAVE_5 = "MMNNOO";
const char *CLAVE_6 = "PPQQRR";

size_t funcion_hash_prueba(const char *clave)
{
	return 0;
}

void tests_hash_crear()
{
	pa2m_nuevo_grupo("CREANDO");
	hash_t *hash = hash_crear(1);
	pa2m_afirmar(
		hash != NULL,
		"Se puede crear un HASH pasandole una capacidad menor a 3");
	pa2m_afirmar(hash_tamanio(hash) == 0, "La cantidad de elementos es 0");
	pa2m_afirmar(hash_buscar(hash, "hola") == NULL,
		     "No se pueden buscar elementos cuando el HASH esta vacio");
	pa2m_afirmar(
		!hash_existe(hash, "hola"),
		"No se pueden saber si existen elementos cuando el HASH esta vacio");
	hash_destruir(hash);

	hash = hash_crear(5);
	pa2m_afirmar(
		hash != NULL,
		"Se puede crear un HASH pasandole una capacidad mayor a 3");
	pa2m_afirmar(hash_tamanio(hash) == 0, "La cantidad de elementos es 0");
	pa2m_afirmar(hash_buscar(hash, "hola") == NULL,
		     "No se pueden buscar elementos cuando el HASH esta vacio");
	pa2m_afirmar(
		!hash_existe(hash, "hola"),
		"No se pueden saber si existen elementos cuando el HASH esta vacio");
	hash_destruir(hash);

	hash = hash_crear_con_funcion(5, NULL);
	pa2m_afirmar(hash == NULL,
		     "No se puede crear un HASH con una funcion de hash nula");

	hash = hash_crear_con_funcion(5, funcion_hash_prueba);
	pa2m_afirmar(hash != NULL,
		     "Se puede crear un HASH con una funcion de hash dada");
	hash_destruir(hash);
}

void test_hash_insertar()
{
	pa2m_nuevo_grupo("INSERTANDO ELEMENTO");
	hash_t *hash = hash_crear(3);

	int VALOR_NEGATIVO = -1;
	int VALOR_3 = 3;
	int VALOR_4 = 4;
	int VALOR_5 = 5;
	int VALOR_6 = 6;

	pa2m_afirmar(!hash_insertar(NULL, CLAVE_1, &VALOR_3, NULL),
		     "No se puede insertar en un HASH nulo");
	pa2m_afirmar(!hash_insertar(hash, NULL, &VALOR_3, NULL),
		     "No se puede insertar una clave nula");
	pa2m_afirmar(hash_insertar(hash, CLAVE_1, NULL, NULL),
		     "Puedo insertar una clave con valor nulo");
	pa2m_afirmar(
		hash_insertar(hash, CLAVE_1, &VALOR_4, NULL),
		"Puedo insertar la misma clave otra vez sin pasarle un 'anterior'");
	void *valor_anterior = NULL;
	pa2m_afirmar(hash_insertar(hash, CLAVE_2, &VALOR_5, &valor_anterior),
		     "Puedo insertar una clave");
	pa2m_afirmar(hash_insertar(hash, CLAVE_2, &VALOR_6, &valor_anterior),
		     "Puedo insertar la misma clave otra vez");
	pa2m_afirmar(valor_anterior == &VALOR_5,
		     "El valor anterior es el correcto");

	char *elemento_char = NULL;
	hash_insertar(hash, CLAVE_3, "hola", NULL);
	elemento_char = (char *)hash_buscar(hash, CLAVE_3);
	pa2m_afirmar(strcmp("hola", elemento_char) == 0,
		     "Se pudo insertar la clave 3");
	pa2m_afirmar(hash_existe(hash, CLAVE_3), "Existe la clave 3");
	pa2m_afirmar(hash_tamanio(hash) == 3, "La cantidad de elementos es 3");

	int *elemento_int = NULL;
	hash_insertar(hash, CLAVE_4, &VALOR_5, NULL);
	elemento_int = (int *)hash_buscar(hash, CLAVE_4);
	pa2m_afirmar(*elemento_int == VALOR_5, "Se pudo insertar la clave 4");
	pa2m_afirmar(hash_existe(hash, CLAVE_4), "Existe la clave 4");
	pa2m_afirmar(hash_tamanio(hash) == 4, "La cantidad de elementos es 4");

	hash_insertar(hash, CLAVE_5, &VALOR_NEGATIVO, NULL);
	elemento_int = (int *)hash_buscar(hash, CLAVE_5);
	pa2m_afirmar(*elemento_int == VALOR_NEGATIVO,
		     "Se pudo insertar la clave 5");
	pa2m_afirmar(hash_existe(hash, CLAVE_5), "Existe la clave 5");
	pa2m_afirmar(hash_tamanio(hash) == 5, "La cantidad de elementos es 5");

	pa2m_afirmar(!hash_existe(hash, CLAVE_6), "No existe la clave 6");

	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo(
		"======================== HASH ========================");
	tests_hash_crear();
	test_hash_insertar();
	// test_hash_sacar();
	// test_has_iterar();
	// test_hash_destruir_todo();

	return pa2m_mostrar_reporte();
}
