#include "so_long.h"

int	last_line_analyzer(char *buffer, t_in *fw)
{
	int a;

	a = 0;
	if (ft_strlen(buffer) != (size_t)fw->map->columns)
	{
		perror("Inconsistent map in the last line");
		exit(1);
	}

	while (buffer[a] != '\0')
	{
		if (buffer[a] != '1')
		{
			perror("Error, map not closed in the last line");
			exit(1);
		}
		a++;
	}

	return(0);
}


int	path_finder(t_in *fw)
{
	int i;

	i = 0;
	int **visited = (int **)ft_calloc(fw->map->lines, sizeof(int *));
	while (i < fw->map->lines)
	{
		visited[i] = ft_calloc(fw->map->columns, sizeof(int));
		i++;
	}

	int pathExists = dfs(fw->player->y, fw->player->x, visited, fw);

	if (pathExists)
		printf(GREEN"\nThere is a possible path from "YELLOW"'P'"
		GREEN" to "YELLOW"'E'"GREEN".\n"DEFAULT);
	else
		printf(RED"\nThere is no possible way from "YELLOW"'P'"
		RED" to "YELLOW"'E'"GREEN".\n"DEFAULT);

	i = 0;
	free(visited);
	visited = NULL; // Poner el puntero a NULL

	return(pathExists);
}

int dfs(int row, int col, int **visited, t_in *fw)
{
	// Verificar si estamos fuera de los límites del mapa
	if (row < 0 || row >= fw->map->lines || col < 0 || col >= fw->map->columns)
		return 0;
	// Verificar si el punto actual ya ha sido visitado
	if (visited[row][col])
		return 0;
	// Marcar el punto actual como visitado
	visited[row][col] = 1;
	// Verificar si hemos llegado al punto 'E'
	if (fw->map->mapstruct[row][col] == 'E')
		return(1);
	// Verificar si el punto actual es transitable ('0' o 'P')
	if (fw->map->mapstruct[row][col] == '0'
	|| fw->map->mapstruct[row][col] == 'C'
	|| fw->map->mapstruct[row][col] == 'P')
	{
		// Llamar recursivamente a DFS en los vecinos
		if (dfs(row - 1, col, visited, fw)
		|| dfs(row + 1, col, visited, fw)
		|| dfs(row, col - 1, visited, fw)
		|| dfs(row, col + 1, visited, fw))
		{
			return(1);
		}
	}
	return(0);
}

void	search_entitys(t_in *fw, char	letter, int	e, int	num)
{
		if (letter == 'P')
		{
			fw->player->y = e + 1;
			fw->player->x = num;
		}
}

int	is_entity(t_in *fw, int y, int x, int first_time)
{
	if (fw->map->mapstruct[y][x] == 'P' && first_time == 2)
	{
		mlx_put_image_to_window(fw->map->mlx, fw->map->mlx_win,
		fw->map->floor_ptr, x * BPP, y * BPP);
		draw_image(fw, fw->player->ptr, fw->player->x * BPP, fw->player->y * BPP);
		return 1;
	}
	return 0;
}