/*
 * Zangoose y Seviper quieren saber quién es más amenazante a la hora de enfrentar a sus enemigos, pues la rivalidad que existe entre ellos es bastante chispeante. 
 * Por eso, decidieron empezar a llevar la cuenta de cuánto daño puede infligir cada uno y comparar sus resultados.
 * Luego de varias batallas, tienen anotado cuántos golpes dio cada uno en su turno, y cuántos minutos tardaron en dar esos golpes. 
 * Ahora, sólo les queda averiguar quién logró golpear más veces por minuto al otro, para definir de una vez por todas quién es mejor.
 *
 * Es por esto que te piden un programa que, sabiendo la cantidad de golpes que el rival actual dio y la cantidad de minutos que tardó en darlos, devuelva cuánto daño hizo ese rival por minuto.
 * 
 * Ayuda:
 * En otras palabras, lo que se pide es que se calcule de manera recursiva, el ratio de golpes por minuto. 
 * Si la cantidad de golpes es 16 y los minutos son 2, el resultado que se debe devolver es 16/2 = 8 golpes por minuto. 
 * Pero claro… la división debe realizarse de manera recursiva ;)
 */

int calcular_division_sucesiva(int golpes, int minutos)
{
	if (golpes < minutos) {
		return 0;
	}
	return 1 + calcular_division_sucesiva(golpes - minutos, minutos);
}