<p align="end">
   <strong>🌐 Change language:</strong><br>
   <a href="README.es.md">
    <img src="https://github.com/Nachopuerto95/multilang/blob/main/ES.png" alt="Spanish" width="40">
  </a>&nbsp;&nbsp;&nbsp;
  <a href="/README.md">
    <img src="https://github.com/Nachopuerto95/multilang/blob/main/EN.png" alt="English" width="40">
  </a>
</p>

<h1> 🕹️ So_long (Cursus 42)</h1>

<img src="https://github.com/Nachopuerto95/multilang/blob/main/42-Madrid%20-%20Edited.jpg">

## 📜 About the Project

> We will learn how to use the Flood Fill maze-solving algorithm to parse the map and check if it is solvable.  
> So_long is a basic 2D video game project at 42 School. The goal is to create a simple tile-based game  
> where the player can move through a map, collect items, and reach an exit to win.

```html
	🚀 The game uses the MiniLibX graphics library provided by the school. The project evaluates
    	the student’s understanding of algorithms, graphics, input handling, and memory management in C.
```

> [!NOTE]  
> Due to the 42 School coding standard requirements:  
> * Each function may not exceed 25 lines of code.  
> * All variables must be declared and aligned at the beginning of each function.  
> * The project must be done only with allowed functions.  
<br>

## Explanation

The map is passed as an argument with the following format::

```shell
111111111
1000C0011
101011011
1P10010E1
111111111
```

We read it, convert it into a matrix, and render the elements using the library with the functions:

```c
	// to load images and store them in the structure
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "./img/tile_0037.xpm",

	// to draw the images in the window indicating position and size
	mlx_put_image_to_window(game->mlx, game->win, game->img_floor,
		game->player_x * game->img_size, game->player_y * game->img_size);
```

The map must meet certain requirements:

• The map will be composed of 3 components: walls, objects, and open space.  
• It will use only 5 characters:  
  `0` for empty space, `1` for a wall, `C` for a collectible, `E` for the exit, and `P` for the player’s starting position.  
• It must have one exit, at least one collectible, and one player start position.  
• If the map has duplicated characters (exit or start), you must return an error.  
• It must be rectangular.  
• It must be surrounded/closed by walls, or it must return an error.  
• You must verify if there is a valid path in the map.  
• It must support any map as long as it follows these rules.  
• Any configuration error in the file must end the program and return “Error\\n”.

Once parsed and rendered, the map will look like this:

<p align="center">
	<img src="https://github.com/Nachopuerto95/multilang/blob/main/so_long/Captura%20de%20pantalla%202025-05-23%20115208.png" /> 
</p>

# Flood Fill for So_long

This is a maze-solving algorithm that recursively calls the `flood_fill` function, four times, varying "x" and "y" to visit the 4 adjacent tiles.  
Each move performs the same checks:

- Am I out of bounds?  
- Have I already visited the tile?  
- Is it a wall?  
- Is it an enemy?  

If none apply, we mark the tile as visited, record if we found an exit or a coin, and re-call the function in four directions.  
If any of the conditions are met, then on return we check:

- If the exit was visited, and the number of collected coins equals the required number, the map is valid.  
If we cannot move in any direction and did not return success, then the map is not solvable.

```c
static void	flood_fill(char **temp_map, int y, int x, t_game *game)
{
	if (y < 0 || y >= game->col_len || x < 0 || x >= game->row_len || !temp_map[y] // Out of bounds?
		|| temp_map[y][x] == '1' // Wall?
		|| temp_map[y][x] == 'X' // Enemy?
		|| temp_map[y][x] == 'F') // Already visited?
		return ;
	if (temp_map[y][x] == 'C')
		game->coins_found++; // Found a coin
	if (temp_map[y][x] == 'E')
		game->exit_found = 1; // Found the exit
	temp_map[y][x] = 'F';
	flood_fill(temp_map, y + 1, x, game); // Down
	flood_fill(temp_map, y - 1, x, game); // Up
	flood_fill(temp_map, y, x + 1, game); // Right
	flood_fill(temp_map, y, x - 1, game); // Left
}

int	check_path(t_game *game)
{
	char	**temp_map;

	game->coins_found = 0;
	game->exit_found = 0;
	temp_map = copy_map(game);
	flood_fill(temp_map, game->player_y, game->player_x, game);
	free_matrix(temp_map);
	return (game->coins_found == game->coins && game->exit_found); // Return boolean
}
```

## Visual Example

<p align="center">
	<img src="https://github.com/Nachopuerto95/multilang/blob/main/so_long/ezgif.com-animated-gif-maker.gif"/>
</p>

The rest of the logic for parsing, movement, rendering, etc. can be found in the available files in this repository.
