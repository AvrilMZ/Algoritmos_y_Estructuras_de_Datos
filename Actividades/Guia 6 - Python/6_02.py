'''
La idea ahora es investigar sobre las primitivas de las listas, aprovechando que muchas ya fueron implementadas.

Dada una lista de elementos y otra de posiciones, se pide quitar de la lista original los elementos de las posiciones recibidas y devolverla.
'''

def sacar_elementos(lista, posiciones):
	if not lista:
		return lista
		
	posiciones_ordenadas = sorted(posiciones, reverse=True)
	resultado = lista.copy()
	
	for pos in posiciones_ordenadas:
		if 0 <= pos < len(resultado):
			resultado.pop(pos)

	return resultado