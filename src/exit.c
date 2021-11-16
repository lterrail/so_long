#include "so_long.h"

/*
ft_free_map free proj->map (**char)
*/
static void ft_free_map(char **map, int height_map)
{
    int i;

    i = -1;
	if (map)
		while (map[++i] && i < height_map)
			free(map[i]);
    free(map);
}

/*
ft_print_error parse le type d'erreur et print
le  message correspondant sur la sortie  d'erreur
*/
static void ft_print_error(int err)
{
	if (err == ERROR_MALLOC)
		ft_putstr_fd("error\nMALLOC_FAILED\n", 2);
	else if (err == ERROR_OPEN)
		ft_putstr_fd("error\nOPEN_FAILED\n", 2);
	else if (err == ERROR_INVALID_MAP)
		ft_putstr_fd("error\nINVALID_MAP\n", 2);
	else if (err == ERROR_WALL)
		ft_putstr_fd("error\nINVALID_WALL\n", 2);
	else if (err == ERROR_INVALID_MAP_PARAMS)
		ft_putstr_fd("error\nINVALID_MAP_PARAMS\n", 2);
	else if (err == ERROR_MAP_SIZE)
		ft_putstr_fd("error\nINVALID_MAP_SIZE\n", 2);
	else if (err == ERROR_INVALID_CHAR)
		ft_putstr_fd("error\nINVALID_CHAR\n", 2);
	else if (err == ERROR_USAGE)
		ft_putstr_fd("error\nusage: ./so_long map.ber\n", 2);
	else
		return ;
} 

/*
ft_exit print l'erreur puis 
essaie de free tous les pointeurs de proj
*/
void ft_exit(t_proj *proj, int err)
{
    ft_print_error(err);
	if (proj)
	{
		if (proj->map)
			ft_free_map(proj->map, proj->height_map);
		if (proj->door_img)
			free(proj->door_img);
		if (proj->wall_img)
			free(proj->wall_img);
		if (proj->collectable_img)
			free(proj->collectable_img);
		if (proj->player_img)
			free(proj->player_img);
		free(proj);
	}
	exit(0);
}