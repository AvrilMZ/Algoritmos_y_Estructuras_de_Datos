# TP0 - Lectura de archivos de texto

- **Alumno:** [Avril Victoria Morfeo Zerbi](https://github.com/AvrilMZ) 
- **Legajo:** 112563 
- **Mail:** amorfeo@fi.uba.ar


### Instrucciones para correr el proyecto:

- Para compilar:
```bash
gcc src/archivo.c ejemplo.c -o tp0
```

- Para ejecutar:
```bash
./tp0 <nombre_archivo>
```

- Para ejecutar con Valgrind:
```bash
valgrind ./tp0 <nombre_archivo>
```
 
<br>

##  Funcionamiento
<div style="text-align: justify">

El programa comienza verificando los argumentos proporcionados en la línea de comandos. Se comprueba si se ha pasado el nombre de un archivo como argumento. En caso de que no se proporcione, se muestra un mensaje de error y el programa finaliza inmediatamente.

A continuación, se intenta abrir el archivo llamando a la función `archivo_abrir()`. Si el archivo no se puede abrir, se imprime un mensaje de error y el programa termina sin continuar con el resto de las operaciones. Si la apertura es exitosa, el programa procede con la lectura del contenido del archivo.

El siguiente paso es la lectura de líneas del archivo. Se inicia un bucle for que se ejecuta mientras `archivo_hay_mas_lineas()` devuelva 1, lo que indica que aún quedan líneas por leer. En cada iteración del bucle, se llama a `archivo_leer_linea()` para obtener la siguiente línea disponible. La línea obtenida se imprime en la salida estándar junto con su número de línea, lo que permite visualizar el contenido del archivo procesado de manera ordenada.

Después de finalizar la lectura, el programa imprime la cantidad total de líneas leídas. Para esto, se invoca la función `archivo_lineas_leidas()`, la cual devuelve el número de líneas que han sido procesadas hasta el momento. Esta información se muestra en la salida estándar antes de proceder al cierre del archivo.

Finalmente, se llama a la función `archivo_cerrar()`, la cual libera toda la memoria reservada y cierra correctamente el archivo abierto. Una vez que se ha completado esta operación, el programa retorna 0, indicando que se ha ejecutado correctamente y ha finalizado sin errores.

</div>

<div align="center">
	<img src="img/Diagrama_general.png" alt="Diagrama de flujo general del programa" width="500"/>
</div>


<br>


###  Funciones implementadas en el módulo `archivo.c`:

#### `archivo_abrir()`
<div style="text-align: justify">

Es responsable de abrir un archivo de texto en modo lectura y devolver un puntero a una estructura `Archivo`. Para lograr esto, primero se reserva memoria para la estructura `Archivo`. Luego, se intenta abrir el archivo utilizando `fopen()`. Si esta operación falla, se libera la memoria previamente reservada y se retorna `NULL` como indicación de error. En caso de éxito, se inicializan los valores de la estructura, estableciendo `lineas_leidas` en `0` y `ultima_linea` en `NULL`, y finalmente se devuelve el puntero a la estructura `Archivo`.

</div>

<div align="center">
	<img src="img/Diagrama_archivo_abrir().png" alt="Diagrama de flujo función archivo_abrir()" width="500"/>
</div>


#### `archivo_leer_linea()`
<div style="text-align: justify">

Lee una línea del archivo y la devuelve como una cadena de caracteres. Antes de iniciar la lectura, libera la memoria de la última línea almacenada, si existe. Luego, reserva una cantidad inicial de memoria para la nueva línea. Utiliza `fgetc()` para leer caracteres del archivo hasta encontrar un salto de línea (`\n`) o el final del archivo (`EOF`). Si la cantidad de caracteres leídos supera la capacidad reservada, la memoria se expande dinámicamente duplicando su tamaño. Al finalizar la lectura, la línea obtenida se almacena en ultima_linea, se incrementa el contador de líneas leídas y se retorna un puntero a la línea. Si el archivo ya no tiene más contenido, la función devuelve `NULL`.

</div>

<div align="center">
	<img src="img/Diagrama_archivo_leer_linea().png" alt="Diagrama de flujo función archivo_leer_linea()" width="800"/>
</div>


#### `archivo_hay_mas_lineas()`
<div style="text-align: justify">

Determina si quedan líneas por leer en el archivo. Verifica la validez del puntero y usa `feof()` para comprobar si se alcanzó el final, retornando `1` si hay más líneas y `0` en caso contrario.

</div>

<div align="center">
	<img src="img/Diagrama_archivo_hay_mas_lineas().png" alt="Diagrama de flujo función archivo_hay_mas_lineas()" width="500"/>
</div>


#### `archivo_lineas_leidas()`
<div style="text-align: justify">

Proporciona la cantidad de líneas que han sido leídas hasta el momento. Si el archivo recibido como parámetro es `NULL`, la función retorna `0`. De lo contrario, se devuelve el valor almacenado en `lineas_leidas` dentro de la estructura `Archivo`, lo que permite obtener un seguimiento de la cantidad de líneas procesadas.

</div>

<div align="center">
	<img src="img/Diagrama_archivo_lineas_leidas().png" alt="Diagrama de flujo función archivo_lineas_leidas()" width="600"/>
</div>


#### `archivo_cerrar()`
<div style="text-align: justify">

Se encarga de cerrar el archivo y liberar toda la memoria reservada. Si el puntero archivo no es `NULL`, se procede a cerrar el archivo utilizando `fclose()` en caso de que estuviera abierto. También se libera la memoria de la última línea almacenada, si existía, y finalmente se libera la estructura `Archivo`.

</div>

<div align="center">
	<img src="img/Diagrama_archivo_cerrar().png" alt="Diagrama de flujo función archivo_cerrar()" width="600"/>
</div>
