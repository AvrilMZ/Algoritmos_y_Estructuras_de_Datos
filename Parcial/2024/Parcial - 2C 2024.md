# Ejercicio 1
El algoritmo de ordenamiento mergesort es del tipo divide y venceras, este sigue los siguientes pasos:  
1- Si la longitud de la lista es 0 ó 1, entonces ya está ordenada. En caso contrario divide la lista desordenada en dos sublistas.  
2- Ordenar cada sublista recursivamente aplicando el ordenamiento por mezcla.  
3- Mezclar las dos sublistas en una sola lista ordenada.

```txt
V = [1, 7, 2, 9, 21, 3, 11, 15, 4, 0]

Dividimos hasta tener listas unitarias:
         [1, 7, 2, 9, 21]               [3, 11, 15, 4, 0]
    [1, 7, 2]         [9, 21]     [3, 11, 15]        [4, 0]
 [1, 7]    [2]       [9]  [21]   [3, 11]  [15]      [4]  [0]
[1]  [7]                        [3]  [11]

Mergeamos y ordemanos:
[1, 7]    [2]     [9, 21]     [3, 11]    [15]   [0, 4]
   [1, 2, 7]      [9, 21]        [3, 11, 15]    [0, 4]
       [1, 2, 7, 9, 21]              [0, 3, 4, 11, 15]
            [0, 1, 2, 3, 4, 7, 9, 11, 15, 21]

=> V = [0, 1, 2, 3, 4, 7, 9, 11, 15, 21]
```

# Ejercicio 2


# Ejercicio 3
```c
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
        void *elemento;
        char letras[4];
} nodo_t;

void destruir_lista(void **lista) 
{
        for (int i = 0; i < 4; i++) {
                free(lista[i]);
        }
        free(lista);
}

int main() 
{
        void **lista = calloc(4, sizeof(void *));
        if (!lista) {
                return 0;
        }

        void **ele_1 = calloc(1, sizeof(void *));
        if (!ele_1) {
                for (int i = 0; i < 4; i++) {
                        free(lista[i]);
                }
                free(lista);
                return 0;
        }
        lista[0] = ele_1;

        for (int i = 0; i < 4; i++) {
                lista[i] = calloc(1, sizeof(void *));
                if (!lista[i]) {
                        destruir_lista(lista);
                        return 0;
                }
        }

        for (int i = 0; i < 3; i++) {
                *lista[i] = calloc(1, sizeof(nodo_t *));
                if (!*lista[i]) {
                        destruir_lista(lista);
                }
        }

        strcpy(((nodo_t *)*lista[0])->letras, "ABC");
        strcpy(((nodo_t *)*lista[1])->letras, "DEF");
        strcpy(((nodo_t *)*lista[2])->letras, "GHI");

        ((nodo_t *)*lista[0])->elemento = lista[1];
        ((nodo_t *)*lista[1])->elemento = lista[2];
        ((nodo_t *)*lista[2])->elemento = lista[3];

        destruir_lista(lista);

        return 0;
}
```

# Ejercicio 4


# Ejercicio 5 (MAL)
```c
#include <stdbool.h>
#include <stdlib.h>

void copiar_vector(int* original, size_t tope, int* copia, size_t *tope_cpy, size_t vuelta) 
{
        if (!original || tope == 0) {
                return;
        } else if (vuelta == tope) {
                return;
        } else if (vuelta == 0) {
                *tope_cpy = 0;
        }

        copia[vuelta] = original[vuelta];
        (*tope_cpy)++;
        copiar_vector(original, tope, copia, vuelta + 1);
}

bool elemento_en_vector(int** vector, int elemento) 
{
        if (!vector) {
                return false;
        } else if (*vector == elemento) {
                return true;
        }

        return elemento_en_vector(*(vector + 1), elemento);
}

void eliminar_elemento(int* vector, size_t* tope, size_t indice) 
{
        if (!vector || *tope == 0 || indice > *tope) {
                return;
        } else if (indice == tope) {
                tope--;
                return;
        }

        vector[indice] = vector[indice + 1];
        eliminar_elemento(vector, tope, indice + 1);
}

size_t contador_no_repetidos(int* vector, size_t tope, int* no_repetidos, size_t* tope_rep, size_t vuelta) 
{
        if (!vector || tope == 0) {
                return 0;
        } else if (vuelta == 0) {
                *tope_rep = 0;
                copiar_vector(vector, tope, no_repetidos, tope_rep, 0);
        } else if (vuelta == tope) {
                return *tope_rep;
        }

        elemento = vector[vuelta];
        if (elemento_en_vector(&no_repetidos, elemento)) {
                eliminar_elemento(no_repetidos, tope_rep, vuelta);
        }
        return contador_no_repetidos(vector, tope, no_repetidos, tope_rep, vuelta + 1);
}

size_t cantidad_no_repetidos(int* v, size_t n) 
{
        if (!v || n == 0) {
                return 0;
        }

        int* no_repetidos = NULL;
        size_t tope = 0;
        return contador_no_repetidos(v, n, no_repetidos, tope, 0);
}
```

La complejidad de `cantidad_no_repetidos` es $`O(n^2)`$ en tiempo, siendo $`n`$ la cantidad de elementos del arreglo ya que en el peor de los casos cada elemento se compara con todos los del arreglo, y $`O(h)`$ en espacio, siendo $`h`$ la altura de los stackframes generados por las llamadas recursivas. Esto se debe a la implementacion llevada a cabo, ya que se duplico el vector dado y a medida que se iban repitiendo los elementos se eliminaban del mismo, de manera que al final solo queden los valores unicos. Esto implica que ademas de recorrer todos los elementos del vector original cada uno de ellos se comparaba con el auxiliar.