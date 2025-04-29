'''
Luego de haber programado todos los TDA en C, llega la noticia de que en python ya fueron implementados y se pueden usar libremente!

Para conocer un poco mejor las primitivas, la idea es dado un diccionario o hash con materias y sus respectivas notas devolver una 
lista de todas las materias que comienzan con la letra 'A' y además tuvieron una nota mayor o igual a 4.

TIP: el diccionario es de la siguiente forma:
	{'materia': nota, 'otra materia': nota, ...}. 
'''

def materias_aprobadas_con_a(materias):
	resultado = []
	for mat in materias:
		if materias[mat] >= 4 and mat[0] == 'A':
			resultado.append(mat)
	return resultado