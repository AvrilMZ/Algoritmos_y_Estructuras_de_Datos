/*
 * Ash y su mejor amigo Pikachu, guardan sus secretos y anécdotas de una manera muy particular e interesante: 
 * dada una palabra se reparten las letras de forma intercalada, una letra para Ash y otra para Pikachu. 
 * Pero esto lleva años de práctica. Ahora, desean recordar todo lo que escribieron. 
 * Te piden que programes una función que, dado el vector donde Ash guarda sus letras y dado el vector donde Pikachu guarda las suyas, se junten y se muestren por pantalla las palabras correctamente de forma intercalada.
 * 
 * Por ejemplo, si el vector de Ash es
 * Cmensprsepe
 * 
 * Y el de Pikachu es
 * apoe o imr!
 * 
 * El vector resultante debe ser
 * Campeones por siempre!
 * 
 * El mensaje final se debe ingresar en el vector correspondiente. Se puede asumir que éste siempre tendrá espacio suficiente. Los tres vectores deben ser tratados como strings.
 */

#include <stdio.h>
#include <string.h>

void letra_pikachu(char *letras_de_ash, char *letras_de_pikachu, size_t pasada,
		   char *mensaje_final);

void letra_ash(char *letras_de_ash, char *letras_de_pikachu, size_t pasada,
	       char *mensaje_final)
{
	if (!letras_de_ash || !letras_de_pikachu) {
		return;
	}

	if (*letras_de_ash != '\0') {
		mensaje_final[pasada] = *letras_de_ash;
		letra_pikachu(letras_de_ash + 1, letras_de_pikachu, pasada + 1,
			      mensaje_final);
	}
}

void letra_pikachu(char *letras_de_ash, char *letras_de_pikachu, size_t pasada,
		   char *mensaje_final)
{
	if (!letras_de_ash || !letras_de_pikachu) {
		return;
	}

	if (*letras_de_pikachu != '\0') {
		mensaje_final[pasada] = *letras_de_pikachu;
		letra_ash(letras_de_ash, letras_de_pikachu + 1, pasada + 1,
			  mensaje_final);
	}
}

void intercalador_de_anecdotas(char *letras_de_ash, char *letras_de_pikachu,
			       char *mensaje_final)
{
	if (!letras_de_ash || !letras_de_pikachu) {
		return;
	}

	letra_ash(letras_de_ash, letras_de_pikachu, 0, mensaje_final);
	mensaje_final[strlen(letras_de_ash) + strlen(letras_de_pikachu)] = '\0';
}