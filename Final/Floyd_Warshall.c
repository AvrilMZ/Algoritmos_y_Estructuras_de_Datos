// Floyd-Washall
#define CANT_VERTICES 5
#define INF 9999

void preparar_matriz_distancia(int copia_grafo[CANT_VERTICES][CANT_VERTICES])
{
	for (int i = 0; i < CANT_VERTICES; i++) {
		for (int j = 0; j < CANT_VERTICES; j++) {
			if (copia_grafo[i][j] == 0 && i != j) {
				copia_grafo[i][j] = INF;
			}
		}
	}
}

void floyd_washall(int matriz_distancia[CANT_VERTICES][CANT_VERTICES])
{
	for (int v2 = 0; v2 < CANT_VERTICES; v2++) {
		for (int v0 = 0; v0 < CANT_VERTICES; v0++) {
			for (int v1 = 0; v1 < CANT_VERTICES; v1++) {
				if (matriz_distancia[v0][v2] < INF &&
				    matriz_distancia[v2][v1] < INF) {
					if (matriz_distancia[v0][v2] +
						    matriz_distancia[v2][v1] <
					    matriz_distancia[v0][v1]) {
						matriz_distancia[v0][v1] =
							matriz_distancia[v0][v2] +
							matriz_distancia[v2][v1];
					}
				}
			}
		}
	}
}
