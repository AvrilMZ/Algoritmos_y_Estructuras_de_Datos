# TP1: Archivos, strings y muchos punteros

- **Alumno:** [Avril Victoria Morfeo Zerbi](https://github.com/AvrilMZ) 
- **Legajo:** 112563 
- **Mail:** amorfeo@fi.uba.ar


### Instrucciones para correr el proyecto:

- Para compilar:
```bash
gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/pokedex.c tp1.c -o tp1
```

- Para ejecutar:
```bash
./tp1 <nombre_archivo> <accion_a_realizar>
```

- Para ejecutar con Valgrind:
```bash
valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes -s ./tp1 <nombre_archivo> <accion_a_realizar>
```

<br>

##  Funcionamiento
<div style="text-align: justify">

asd

</div>

<div align="center">
	<img src="img/Diagrama_general.png" alt="Diagrama de flujo general del programa" width="500"/>
</div>

<br>

###  Funciones implementadas en el módulo `pokedex.c`:

#### `pokedex_abrir()`
<div style="text-align: justify">

asd

</div>

<div align="center">
	<img src="img/Diagrama_pokedex_abrir().png" alt="Diagrama de flujo función pokedex_abrir()" width="500"/>
</div>


#### `pokedex_cantidad_pokemones()`
<div style="text-align: justify">

asd

</div>

<div align="center">
	<img src="img/Diagrama_pokedex_cantidad_pokemones().png" alt="Diagrama de flujo función pokedex_cantidad_pokemones()" width="800"/>
</div>


#### `pokedex_buscar_pokemon_nombre()`
<div style="text-align: justify">

asd

</div>

<div align="center">
	<img src="img/Diagrama_pokedex_buscar_pokemon_nombre().png" alt="Diagrama de flujo función pokedex_buscar_pokemon_nombre()" width="500"/>
</div>


#### `pokedex_buscar_pokemon_id()`
<div style="text-align: justify">

asd

</div>

<div align="center">
	<img src="img/Diagrama_pokedex_buscar_pokemon_id().png" alt="Diagrama de flujo función pokedex_buscar_pokemon_id()" width="600"/>
</div>


#### `pokedex_iterar_pokemones()`
<div style="text-align: justify">

asd

</div>

<div align="center">
	<img src="img/Diagrama_pokedex_iterar_pokemones().png" alt="Diagrama de flujo función pokedex_iterar_pokemones()" width="600"/>
</div>


#### `pokedex_destruir()`
<div style="text-align: justify">

asd

</div>

<div align="center">
	<img src="img/Diagrama_pokedex_destruir().png" alt="Diagrama de flujo función pokedex_destruir()" width="600"/>
</div>