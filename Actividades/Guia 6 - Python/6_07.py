'''
Una empresa está haciendo recolección de datos y necesita saber cuánta gente de cada rango etario participó en su encuesta.

La división de grupos es la siguiente:
	18 a 30 años
	31 a 50 años
	51 a 70 años

A partir de una lista de tuplas que contiene la edad y qué voto el participante se pide crear una lista nueva que contenga cuántos votos 'si' hubo de cada rango.

TIP: una lista de tuplas se ve de la siguiente forma:
	lista = [(18, 'si'), (34, 'no'), (55, 'si')]

Una tupla es similar a una lista, con la diferencia de que es inmutable.
'''

def conteo_votos_afirmativos(respuestas):
	salida = []
	contador_grupo1 = 0
	contador_grupo2 = 0
	contador_grupo3 = 0
	for persona in respuestas:
		if persona[0] in range(18, 31) and persona[1] == 'si':
			contador_grupo1 += 1
		elif persona[0] in range(31, 51) and persona[1] == 'si':
			contador_grupo2 += 1
		elif persona[0] in range(51, 71) and persona[1] == 'si':
			contador_grupo3 += 1
	salida = [contador_grupo1, contador_grupo2, contador_grupo3]
	return salida