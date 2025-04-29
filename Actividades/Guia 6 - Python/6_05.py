'''
Se sabe que para iterar sobre un vector o lista se pueden utilizar las estructuras for o while, 
pero en python se puede aprovechar de la comprensión de listas (list comprehension).

A partir de la lista recibida por parámetro, se pide crear una nueva lista con los elementos de la lista original 
elevados al cuadrado, pero solo si el resultado de elevar el elemento al cuadrado es mayor o igual a 36.
'''

def cuadrados_mayores_a_36(lista):
	resultado = [ele*ele for ele in lista if ele*ele >= 36]
	return resultado