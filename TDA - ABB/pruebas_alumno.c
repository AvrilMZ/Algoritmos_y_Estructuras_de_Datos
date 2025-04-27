#include "pa2m.h"
#include "src/abb.h"

int comparador(const void *elemento1, const void *elemento2)
{
	return (*(int *)elemento1 - *(int *)elemento2);
}

bool contar_elementos(void *elemento, void *contador)
{
	(*(int *)contador)++;
	return true;
}

bool verificar_valor(void *elemento, void *valor_buscado)
{
	return (*(int *)elemento != *(int *)valor_buscado);
}

void tests_abb_crear()
{
	pa2m_nuevo_grupo("CREANDO");
	abb_t *abb = abb_crear(comparador);

	pa2m_afirmar(abb != NULL, "Se puede crear un ABB");
	pa2m_afirmar(abb_tamanio(abb) == 0, "La cantidad de elementos es 0");
	pa2m_afirmar(abb_vacio(abb), "El ABB esta vacio");
	pa2m_afirmar(abb_buscar(abb, 0) == NULL,
		     "No se pueden buscar elementos cuando el ABB esta vacio");
	pa2m_afirmar(
		!abb_existe(abb, 0),
		"No se pueden saber si existen elementos cuando el ABB esta vacio");

	abb_destruir(abb);
}

void test_abb_insertar()
{
	pa2m_nuevo_grupo("INSERTANDO ELEMENTO");
	abb_t *abb = abb_crear(comparador);

	int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, diez = 10;

	pa2m_afirmar(!abb_insertar(NULL, &tres),
		     "No se puede insertar en un ABB nulo");

	int *elemento = NULL;
	abb_insertar(abb, &tres);
	elemento = (int *)abb_buscar(abb, &tres);
	pa2m_afirmar(*elemento == tres, "Se puede insertar el 3");
	pa2m_afirmar(abb_existe(abb, &tres), "Existe el 3");
	pa2m_afirmar(abb_tamanio(abb) == 1, "La cantidad de elementos es 1");

	abb_insertar(abb, &cinco);
	elemento = (int *)abb_buscar(abb, &cinco);
	pa2m_afirmar(*elemento == cinco, "Se puede insertar el 5");
	pa2m_afirmar(abb_existe(abb, &cinco), "Existe el 5");
	pa2m_afirmar(abb_tamanio(abb) == 2, "La cantidad de elementos es 2");

	abb_insertar(abb, &uno);
	elemento = (int *)abb_buscar(abb, &uno);
	pa2m_afirmar(*elemento == uno, "Se puede insertar el 1");
	pa2m_afirmar(abb_existe(abb, &uno), "Existe el 1");
	pa2m_afirmar(abb_tamanio(abb) == 3, "La cantidad de elementos es 3");

	abb_insertar(abb, &cuatro);
	elemento = (int *)abb_buscar(abb, &cuatro);
	pa2m_afirmar(*elemento == cuatro, "Se puede insertar el 4");
	pa2m_afirmar(abb_existe(abb, &cuatro), "Existe el 4");
	pa2m_afirmar(abb_tamanio(abb) == 4, "La cantidad de elementos es 4");

	abb_insertar(abb, &dos);
	elemento = (int *)abb_buscar(abb, &dos);
	pa2m_afirmar(*elemento == dos, "Se puede insertar el 2");
	pa2m_afirmar(abb_existe(abb, &dos), "Existe el 2");
	pa2m_afirmar(abb_tamanio(abb) == 5, "La cantidad de elementos es 5");

	pa2m_afirmar(!abb_existe(abb, &diez), "No existe el 10");

	abb_destruir(abb);
}

void test_abb_sacar()
{
	pa2m_nuevo_grupo("QUITANDO ELEMENTO");
	abb_t *abb = abb_crear(comparador);

	int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6,
	    siete = 7, ocho = 8, diez = 10;

	pa2m_afirmar(!abb_sacar(NULL, &uno),
		     "No se puede quitar elementos de un ABB nulo");
	pa2m_afirmar(!abb_sacar(abb, &uno),
		     "No se puede quitar elementos de un ABB vacío");

	abb_insertar(abb, &cuatro);
	abb_insertar(abb, &seis);
	abb_insertar(abb, &siete);
	abb_insertar(abb, &cinco);
	abb_insertar(abb, &ocho);
	abb_insertar(abb, &dos);
	abb_insertar(abb, &uno);
	abb_insertar(abb, &tres);

	pa2m_afirmar(abb_tamanio(abb) == 8, "La cantidad de elementos es 8");

	int *elemento = NULL;
	elemento = (int *)abb_sacar(abb, &diez);
	pa2m_afirmar(elemento == NULL,
		     "No se puede sacar un elemento inexistente");
	pa2m_afirmar(abb_tamanio(abb) == 8, "La cantidad de elementos es 8");

	elemento = (int *)abb_sacar(abb, &uno);
	pa2m_afirmar(*elemento == uno, "Se puede quitar un elemento hoja");
	pa2m_afirmar(abb_tamanio(abb) == 7, "La cantidad de elementos es 7");

	elemento = (int *)abb_sacar(abb, &dos);
	pa2m_afirmar(*elemento == dos,
		     "Se puede quitar un elemento con un hijo");
	pa2m_afirmar(abb_tamanio(abb) == 6, "La cantidad de elementos es 6");

	elemento = (int *)abb_sacar(abb, &seis);
	pa2m_afirmar(*elemento == seis,
		     "Se puede quitar un elemento con un sub-árbol");
	pa2m_afirmar(abb_tamanio(abb) == 5, "La cantidad de elementos es 5");

	elemento = (int *)abb_sacar(abb, &cuatro);
	pa2m_afirmar(*elemento == cuatro, "Se puede quitar la raiz");
	pa2m_afirmar(abb_tamanio(abb) == 4, "La cantidad de elementos es 4");

	abb_destruir(abb);
}

void test_abb_recorrer()
{
	pa2m_nuevo_grupo("RECORRIENDO");
	abb_t *abb = abb_crear(comparador);

	int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5;

	abb_insertar(abb, &tres);
	abb_insertar(abb, &cinco);
	abb_insertar(abb, &uno);
	abb_insertar(abb, &cuatro);
	abb_insertar(abb, &dos);

	pa2m_afirmar(abb_tamanio(abb) == 5, "La cantidad de elementos es 5");

	size_t tope = 5;
	void *vector[5];
	int vector_preorden[5] = { 3, 1, 2, 5, 4 };
	int vector_inorden[5] = { 1, 2, 3, 4, 5 };
	int vector_postorden[5] = { 2, 1, 4, 5, 3 };

	size_t cantidad;
	cantidad = abb_vectorizar(NULL, ABB_INORDEN, vector, tope);
	pa2m_afirmar(cantidad == 0, "No se puede vectorizar un ABB NULL");

	cantidad = abb_vectorizar(abb, ABB_INORDEN, NULL, tope);
	pa2m_afirmar(cantidad == 0, "No se puede vectorizar en un vector NULL");

	cantidad = abb_vectorizar(abb, ABB_INORDEN, vector, 0);
	pa2m_afirmar(cantidad == 0, "No se puede vectorizar con capacidad 0");

	cantidad = abb_vectorizar(abb, ABB_PREORDEN, (void **)vector, tope);
	pa2m_afirmar(cantidad == tope,
		     "Se vectorizaron la cantidad de elementos pedidos");
	for (size_t i = 0; i < tope; i++) {
		pa2m_afirmar(
			vector_preorden[i] == *(int *)vector[i],
			"El elemento %zu del vector preorden es el esperado (encontro: %i, esperado: %i)",
			i, *(int *)vector[i], vector_preorden[i]);
	}

	cantidad = abb_vectorizar(abb, ABB_INORDEN, (void **)vector, tope);
	pa2m_afirmar(cantidad == tope,
		     "Se vectorizaron la cantidad de elementos pedidos");
	for (size_t i = 0; i < tope; i++) {
		pa2m_afirmar(
			vector_inorden[i] == *(int *)vector[i],
			"El elemento %zu del vector inorden es el esperado (encontro: %i, esperado: %i)",
			i, *(int *)vector[i], vector_inorden[i]);
	}

	cantidad = abb_vectorizar(abb, ABB_POSTORDEN, (void **)vector, tope);
	pa2m_afirmar(cantidad == tope,
		     "Se vectorizaron la cantidad de elementos pedidos");
	for (size_t i = 0; i < tope; i++) {
		pa2m_afirmar(
			vector_postorden[i] == *(int *)vector[i],
			"El elemento %zu del vector postorden es el esperado (encontro: %i, esperado: %i)",
			i, *(int *)vector[i], vector_postorden[i]);
	}

	cantidad = abb_vectorizar(abb, ABB_INORDEN, vector, 3);
	pa2m_afirmar(cantidad == 3,
		     "Se vectoriza con éxito hasta el maximo dado");

	int contador = 0;
	cantidad = abb_recorrer(NULL, ABB_INORDEN, contar_elementos, &contador);
	pa2m_afirmar(cantidad == 0, "No se puede recorrer un ABB NULL");

	cantidad = abb_recorrer(abb, ABB_INORDEN, NULL, &contador);
	pa2m_afirmar(cantidad == 0,
		     "No se puede recorrer con una función NULL");

	cantidad = abb_recorrer(abb, ABB_INORDEN, contar_elementos, &contador);
	pa2m_afirmar(cantidad == 5,
		     "Se recorrieron todos los elementos con la función");
	pa2m_afirmar(contador == 5,
		     "La función de recorrido se aplicó a todos los elementos");

	contador = 3;
	cantidad = abb_recorrer(abb, ABB_INORDEN, verificar_valor, &contador);
	pa2m_afirmar(cantidad < 5,
		     "El recorrido se detiene al encontrar el valor 3");

	abb_destruir(abb);
}

void test_abb_destruir_todo()
{
	pa2m_nuevo_grupo("DESTRUCCIÓN CON DESTRUCTOR");
	abb_t *abb = abb_crear(comparador);

	int uno = 1, tres = 3, cinco = 5;

	abb_insertar(abb, &tres);
	abb_insertar(abb, &cinco);
	abb_insertar(abb, &uno);

	pa2m_afirmar(abb_tamanio(abb) == 3, "La cantidad de elementos es 3");

	abb_destruir_todo(abb, NULL);
	pa2m_afirmar(true, "Se puede destruir un ABB con destructor NULL");

	abb = abb_crear(comparador);
	int *elemento1 = calloc(1, sizeof(int));
	if (!elemento1) {
		abb_destruir(abb);
		return;
	}
	int *elemento2 = calloc(1, sizeof(int));
	if (!elemento2) {
		free(elemento1);
		abb_destruir(abb);
		return;
	}
	int *elemento3 = calloc(1, sizeof(int));
	if (!elemento3) {
		free(elemento1);
		free(elemento2);
		abb_destruir(abb);
		return;
	}

	*elemento1 = tres;
	*elemento2 = cinco;
	*elemento3 = uno;

	abb_insertar(abb, elemento1);
	abb_insertar(abb, elemento2);
	abb_insertar(abb, elemento3);

	pa2m_afirmar(abb_tamanio(abb) == 3, "La cantidad de elementos es 3");
	abb_destruir_todo(abb, free);
	pa2m_afirmar(true, "Se destruyó el ABB con elementos dinámicos");
}

int main()
{
	pa2m_nuevo_grupo(
		"======================== ABB ========================");
	tests_abb_crear();
	test_abb_insertar();
	test_abb_sacar();
	test_abb_recorrer();
	test_abb_destruir_todo();

	return pa2m_mostrar_reporte();
}
