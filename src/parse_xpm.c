#include "so_long.h"

void ft_parse_xpm_file(t_proj *proj)
{
    proj->img_size = IMG_SIZE;
    proj->door_img = mlx_xpm_file_to_image(proj->mlx,
		"resources/xpm/door_02.xpm",
		&proj->img_size, &proj->img_size);
    proj->collectable_img = mlx_xpm_file_to_image(proj->mlx,
        "resources/xpm/collectable_01.xpm",
        &proj->img_size, &proj->img_size);
    proj->player_img = mlx_xpm_file_to_image(proj->mlx,
        "resources/xpm/player_01.xpm",
        &proj->img_size, &proj->img_size);
    proj->wall_img = mlx_xpm_file_to_image(proj->mlx,
        "resources/xpm/wall_01.xpm",
        &proj->img_size, &proj->img_size);
    proj->width_win = proj->width_map * proj->img_size;
    proj->height_win = proj->height_map * proj->img_size;
}