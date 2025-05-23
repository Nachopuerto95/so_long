
<p align="end">
   <strong>🌐 Cambiar idioma:</strong><br>
   <a href="README.es.md">
    <img src="https://github.com/Nachopuerto95/multilang/blob/main/ES.png" alt="Español" width="40">
  </a>&nbsp;&nbsp;&nbsp;
  <a href="/README.md">
    <img src="https://github.com/Nachopuerto95/multilang/blob/main/EN.png" alt="English" width="40">
  </a>
</p>

<h1> 🕹️ So_long (Cursus 42)</h1>

<img src="https://github.com/Nachopuerto95/multilang/blob/main/42-Madrid%20-%20Edited.jpg">

## 📜 Sobre el Proyecto

> Aprenderemos a utilizar el algoritmo de resolución de laberintos Flood Fill para parsear el mapa y ver si es resoluble
> So_long es un proyecto básico de videojuego 2D en la Escuela 42. El objetivo es crear un juego sencillo
> basado en casillas, donde el jugador puede moverse por un mapa, recoger objetos y llegar a una salida para ganar.

```html
	🚀 El juego utiliza la biblioteca gráfica MiniLibX proporcionada por la escuela. El proyecto evalúa
    	la comprensión del estudiante sobre algoritmos, gráficos, manejo de entradas y gestión de memoria en C.
```

> [!NOTE]  
> Debido a los requisitos de la norma de la Escuela 42:
> * Cada función no puede tener más de 25 líneas de código.
> * Todas las variables deben declararse y alinearse al inicio de cada función.
> * El proyecto debe realizarse solo con las funciones permitidas.
<br>

## Explicación

Como argumento nos entra un mapa con el siguiente formato::

```shell
111111111
1000C0011
101011011
1P10010E1
111111111
```
Lo vamos a leer, convertirlo en una matriz y renderizar los elementos mediante la librería con las funciones

```c
	// para cargar imagenes y guardarlas en la estructura
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "./img/tile_0037.xpm",

	// para pintar las imágenes en la ventana indicando posición y tamaño
	mlx_put_image_to_window(game->mlx, game->win, game->img_floor,
		game->player_x * game->img_size, game->player_y * game->img_size);
```

El mapa debe debe cumplir ciertos requisitos:

• El mapa estará construido de 3 componentes: paredes, objetos y espacio abierto.

• El mapa estará compuesto de solo 5 caracteres: 0 para un espacio vacío, 1 para un
muro, C para un coleccionable, E para salir del mapa y P para la posición inicial
del jugador.

• El mapa debe tener una salida, al menos un objeto y una posición inicial.
Si el mapa contiene caractéres duplicados (salida o posición
inicial), deberás mostrar un mensaje de error.

• El mapa debe ser rectangular.

• El mapa deberá estar cerrado/rodeado de muros, en caso contrario el programa
deberá devolver un error.

• Tienes que comprobar si hay un camino válido en el mapa.

• Debes poder procesar cualquier tipo de mapa, siempre y cuando respete las anteriores normas.

• En caso de fallos de configuración de cualquier tipo encontrados en el archivo, el
programa debe terminar correctamente y devolver “Error\n”.

Una vez parseado y pintado el mapa quedará así:

<p align="center">
	<img src="https://github.com/Nachopuerto95/multilang/blob/main/so_long/Captura%20de%20pantalla%202025-05-23%20115208.png" /> 
</p>

## Flood Fill

este es un algoritmo de resolución de laberintos que consiste en llamar de forma recursiva a la funcion flood_fill, la llamaremos 4 veces variando "x" e "y" para "visitar las 4 casillas colindantes.
una vez nos movamos, cada una hará las mismas comprobaciones.

- ¿Estoy fuera del mapa?
- ¿Ya he visitado la casilla?
- ¿Es una pared?
- ¿Es un Enemigo?

si ninguno de estos se cumple, marcaremos la casilla como visitada, guardaremos si hemos visitado una salida o una moneda y lanzaremos de nuevo las 4 funciones, una en cada dirección.
en el caso de que alguno se cumpla, haremos la siguiente comprobación en el return,

- Si he visitado la salida, y el numero de monedas que he recolectado es igual al numero de monedas que hay, el mapa es correcto. Si ya no podemos movernos a ninguna dirección y no hemos conseguido un retorno positivo, el mapa no puede realizarse

```c
static void	flood_fill(char **temp_map, int y, int x, t_game *game)
{
	if (y < 0 || y >= game->col_len || x < 0 || x >= game->row_len || !temp_map[y] // ¿Estoy fuera del mapa?
		|| temp_map[y][x] == '1' // ¿Es una pared?
		|| temp_map[y][x] == 'X' // ¿Es un Enemigo?
		|| temp_map[y][x] == 'F') // ¿Ya he visitado la casilla?
		return ;
	if (temp_map[y][x] == 'C')
		game->coins_found++; // si es una C "Recogemos moneda"
	if (temp_map[y][x] == 'E')
		game->exit_found = 1; si es una 1 "Recogemos Salida"
	temp_map[y][x] = 'F';
	flood_fill(temp_map, y + 1, x, game); // Lanzamos la funcion de nuevo con las nuevas direcciones
	flood_fill(temp_map, y - 1, x, game);
	flood_fill(temp_map, y, x + 1, game);
	flood_fill(temp_map, y, x - 1, game);
}

int	check_path(t_game *game)
{
	char	**temp_map;

	game->coins_found = 0;
	game->exit_found = 0;
	temp_map = copy_map(game);
	flood_fill(temp_map, game->player_y, game->player_x, game);
	free_matrix(temp_map);
	return (game->coins_found == game->coins && game->exit_found); // Retornamos un boolean
}
```
## Ejemplo visual

<p align="center">
	<img src="https://github.com/Nachopuerto95/multilang/blob/main/so_long/ezgif.com-animated-gif-maker.gif"/>
</p>

El resto de la lógica de parseo, movimiento, renderizado etc puedes consultarla en los archivos disponibles de este repositorio
