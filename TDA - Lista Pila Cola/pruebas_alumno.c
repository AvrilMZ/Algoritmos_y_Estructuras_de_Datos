#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

void prueba_simple()
{
	int i = 5;
	int j = 16;
	pa2m_afirmar(i == j, "i es igual a j (%d == %d)", i, j);
	pa2m_afirmar(2 * i == 10, "2*i es igual a 2 (%d)", 2 * i);
}

int main()
{
	pa2m_nuevo_grupo("============== ??? ===============");
	prueba_simple();

	return pa2m_mostrar_reporte();
}
