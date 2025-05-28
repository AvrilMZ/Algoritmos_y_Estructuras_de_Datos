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

bool contar_claves(const char *clave, void *ctx)
{
	int *contador = (int *)ctx;
	(*contador)++;
	return true;
}

bool parar_en_segunda_clave(const char *clave, void *ctx)
{
	int *contador = (int *)ctx;
	(*contador)++;
	return *contador < 2;
}

void destructor_int(void *elemento)
{
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

	hash = hash_crear(0);
	pa2m_afirmar(
		hash != NULL,
		"Se puede crear un HASH con capacidad 0 (se ajusta a mínimo)");
	hash_destruir(hash);

	hash = hash_crear(100);
	pa2m_afirmar(hash != NULL,
		     "Se puede crear un HASH con capacidad grande");
	pa2m_afirmar(hash_tamanio(hash) == 0,
		     "HASH con capacidad grande inicia vacío");
	hash_destruir(hash);

	hash = hash_crear_con_funcion(0, funcion_hash_prueba);
	pa2m_afirmar(hash != NULL, "Se puede crear con función y capacidad 0");
	hash_destruir(hash);

	hash = hash_crear_con_funcion(1, funcion_hash_prueba);
	pa2m_afirmar(hash != NULL, "Se puede crear con función y capacidad 1");
	pa2m_afirmar(hash_tamanio(hash) == 0,
		     "HASH con función personalizada inicia vacío");
	hash_destruir(hash);

	hash = hash_crear(5);
	pa2m_afirmar(hash_buscar(hash, NULL) == NULL,
		     "Buscar con clave nula en hash vacío devuelve NULL");
	pa2m_afirmar(!hash_existe(hash, NULL),
		     "Verificar existencia con clave nula devuelve false");
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

	valor_anterior = NULL;
	hash_insertar(hash, CLAVE_1, &VALOR_3, &valor_anterior);
	pa2m_afirmar(valor_anterior == &VALOR_4,
		     "Reemplazo guarda valor anterior correcto");

	valor_anterior = NULL;
	hash_insertar(hash, CLAVE_1, &VALOR_6, &valor_anterior);
	pa2m_afirmar(valor_anterior == &VALOR_3,
		     "Segundo reemplazo guarda valor anterior correcto");

	elemento_int = (int *)hash_buscar(hash, CLAVE_1);
	pa2m_afirmar(
		*elemento_int == VALOR_6,
		"El valor final después de múltiples reemplazos es correcto");

	hash_insertar(hash, CLAVE_6, &VALOR_3, NULL);
	pa2m_afirmar(hash_tamanio(hash) == 6,
		     "Se pueden insertar múltiples elementos");
	pa2m_afirmar(
		hash_existe(hash, CLAVE_1),
		"La primera clave sigue existiendo después de muchas inserciones");
	pa2m_afirmar(hash_existe(hash, CLAVE_6),
		     "La última clave existe después de muchas inserciones");

	pa2m_afirmar(*(int *)hash_buscar(hash, CLAVE_1) == VALOR_6,
		     "Valor de clave 1 es correcto");
	pa2m_afirmar(*(int *)hash_buscar(hash, CLAVE_2) == VALOR_6,
		     "Valor de clave 2 es correcto");
	pa2m_afirmar(*(int *)hash_buscar(hash, CLAVE_6) == VALOR_3,
		     "Valor de clave 6 es correcto");

	hash_destruir(hash);

	hash = hash_crear_con_funcion(3, funcion_hash_prueba);

	hash_insertar(hash, CLAVE_1, &VALOR_3, NULL);
	hash_insertar(hash, CLAVE_2, &VALOR_4, NULL);
	hash_insertar(hash, CLAVE_3, &VALOR_5, NULL);

	pa2m_afirmar(hash_tamanio(hash) == 3, "Se pueden manejar colisiones");
	pa2m_afirmar(*(int *)hash_buscar(hash, CLAVE_1) == VALOR_3,
		     "Primera clave con colisión es correcta");
	pa2m_afirmar(*(int *)hash_buscar(hash, CLAVE_2) == VALOR_4,
		     "Segunda clave con colisión es correcta");
	pa2m_afirmar(*(int *)hash_buscar(hash, CLAVE_3) == VALOR_5,
		     "Tercera clave con colisión es correcta");

	hash_destruir(hash);
}

void test_hash_sacar()
{
	pa2m_nuevo_grupo("QUITANDO ELEMENTO");

	hash_t *hash = hash_crear(3);

	int VALOR_3 = 3;
	int VALOR_4 = 4;

	pa2m_afirmar(hash_sacar(NULL, CLAVE_1) == NULL,
		     "No se puede sacar de un HASH nulo");
	pa2m_afirmar(hash_sacar(hash, NULL) == NULL,
		     "No se puede sacar con una clave nula");
	pa2m_afirmar(hash_sacar(hash, CLAVE_1) == NULL,
		     "No se puede sacar una clave que no existe");

	hash_insertar(hash, CLAVE_1, &VALOR_3, NULL);
	hash_insertar(hash, CLAVE_2, &VALOR_4, NULL);
	hash_insertar(hash, CLAVE_3, "hola", NULL);
	pa2m_afirmar(hash_tamanio(hash) == 3, "Se insertaron 3 elementos");

	int *elemento_sacado = (int *)hash_sacar(hash, CLAVE_1);
	pa2m_afirmar(elemento_sacado == &VALOR_3,
		     "Se pudo sacar la clave 1 y devuelve el valor correcto");
	pa2m_afirmar(!hash_existe(hash, CLAVE_1), "Ya no existe la clave 1");
	pa2m_afirmar(hash_tamanio(hash) == 2, "La cantidad de elementos es 2");

	char *elemento_string = (char *)hash_sacar(hash, CLAVE_3);
	pa2m_afirmar(strcmp("hola", elemento_string) == 0,
		     "Se pudo sacar la clave 3 y devuelve el valor correcto");
	pa2m_afirmar(!hash_existe(hash, CLAVE_3), "Ya no existe la clave 3");
	pa2m_afirmar(hash_tamanio(hash) == 1, "La cantidad de elementos es 1");

	pa2m_afirmar(hash_sacar(hash, CLAVE_1) == NULL,
		     "No se puede sacar una clave ya sacada");

	hash_destruir(hash);
}

void test_hash_iterar()
{
	pa2m_nuevo_grupo("ITERANDO");

	hash_t *hash = hash_crear(5);

	int VALOR_1 = 1;
	int VALOR_2 = 2;
	int VALOR_3 = 3;

	int contador = 0;
	pa2m_afirmar(hash_iterar_claves(NULL, contar_claves, &contador) == 0,
		     "No se puede iterar un HASH nulo");
	pa2m_afirmar(hash_iterar_claves(hash, NULL, &contador) == 0,
		     "No se puede iterar con función nula");

	contador = 0;
	pa2m_afirmar(hash_iterar_claves(hash, contar_claves, &contador) == 0,
		     "Iterar un HASH vacío devuelve 0");
	pa2m_afirmar(contador == 0, "El contador sigue en 0");

	hash_insertar(hash, CLAVE_1, &VALOR_1, NULL);
	hash_insertar(hash, CLAVE_2, &VALOR_2, NULL);
	hash_insertar(hash, CLAVE_3, &VALOR_3, NULL);

	contador = 0;
	size_t iteraciones = hash_iterar_claves(hash, contar_claves, &contador);
	pa2m_afirmar(iteraciones == 3, "Se iteraron 3 elementos");
	pa2m_afirmar(contador == 3, "El contador llegó a 3");

	contador = 0;
	iteraciones =
		hash_iterar_claves(hash, parar_en_segunda_clave, &contador);
	pa2m_afirmar(iteraciones == 2,
		     "Se iteraron 2 elementos antes de parar");
	pa2m_afirmar(contador == 2, "El contador llegó a 2");

	hash_destruir(hash);
}

void test_hash_destruir_todo()
{
	pa2m_nuevo_grupo("DESTRUCCIÓN CON DESTRUCTOR");

	hash_t *hash = hash_crear(3);

	hash_destruir_todo(NULL, destructor_int);
	pa2m_afirmar(
		true,
		"Se puede llamar destruir_todo con HASH nulo sin problemas");

	hash_destruir_todo(hash, destructor_int);
	pa2m_afirmar(true, "Se puede destruir un HASH vacío con destructor");

	hash = hash_crear(3);

	int *valor1 = calloc(1, sizeof(int));
	int *valor2 = calloc(1, sizeof(int));
	int *valor3 = calloc(1, sizeof(int));
	*valor1 = 10;
	*valor2 = 20;
	*valor3 = 30;

	hash_insertar(hash, CLAVE_1, valor1, NULL);
	hash_insertar(hash, CLAVE_2, valor2, NULL);
	hash_insertar(hash, CLAVE_3, valor3, NULL);

	pa2m_afirmar(hash_tamanio(hash) == 3, "El HASH tiene 3 elementos");

	hash_destruir_todo(hash, free);
	pa2m_afirmar(true, "Se pudo destruir el HASH con destructor");

	hash = hash_crear(2);
	int valor_local = 42;
	hash_insertar(hash, CLAVE_1, &valor_local, NULL);

	hash_destruir_todo(hash, NULL);
	pa2m_afirmar(true, "Se puede destruir con destructor nulo");
}

int main()
{
	pa2m_nuevo_grupo(
		"======================== HASH ========================");
	tests_hash_crear();
	test_hash_insertar();
	test_hash_sacar();
	test_hash_iterar();
	test_hash_destruir_todo();

	return pa2m_mostrar_reporte();
}
