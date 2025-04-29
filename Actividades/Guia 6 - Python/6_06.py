'''
A diferencia de C, Python es un lenguaje multiparadigma que soporta parcialmente la orientación a objetos. 
Esto quiere decir que se pueden utilizar clases y objetos para programar distintas cosas.

Las clases tienen definidas variables y métodos propios. 
Luego, el usuario puede crear instancias (objetos) de dicha clase que tendrá todos los atributos de la clase original.

Por ejemplo, puedo crear una clase gato con los atributos nombre y tipo, que además tiene definidos los métodos maullar e imprimir nombre:
	class Gato: 
		def __init__(self, n, t):
			self.nombre = n
			self.tipo = t

		def maullar(self):
			pass
		def imprimir_nombre(self):
			print self.nombre

Definir una clase alumno con los atributos y métodos que considere necesarios, y luego en la función guardar los datos recibidos en un alumno nuevo. 
Finalmente, devolver si la edad del alumno es mayor o igual a 19 o no.
'''

class Alumno:
	def __init__(self, nombre, edad, padron):
		self.nombre = nombre
		self.edad = edad
		self.padron = padron

def alumno_nuevo(nombre, edad, padron):
	alumno = Alumno(nombre, edad, padron)
	return alumno.edad >= 19