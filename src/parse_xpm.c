#include "so_long.h"

/*
ft_parse_xpm_file load les fichiers xpm dans des pointeurs
*/
int ft_parse_xpm_file(t_proj *proj)
{
    proj->img_size = IMG_SIZE;
    if (!(proj->door_img = mlx_xpm_file_to_image(proj->mlx,
		"resources/xpm/door_01.xpm",
		&proj->img_size, &proj->img_size)))
        ft_exit(proj, ERROR_MALLOC);
    if (!(proj->collectable_img = mlx_xpm_file_to_image(proj->mlx,
        "resources/xpm/collectable_01.xpm",
        &proj->img_size, &proj->img_size)))
        ft_exit(proj, ERROR_MALLOC);
    if (!(proj->player_img = mlx_xpm_file_to_image(proj->mlx,
        "resources/xpm/player_01.xpm",
        &proj->img_size, &proj->img_size)))
        ft_exit(proj, ERROR_MALLOC);
    if (!(proj->wall_img = mlx_xpm_file_to_image(proj->mlx,
        "resources/xpm/wall_01.xpm",
        &proj->img_size, &proj->img_size)))
        ft_exit(proj, ERROR_MALLOC);
    proj->width_win = proj->width_map * proj->img_size;
    proj->height_win = proj->height_map * proj->img_size;
    return (SUCCESS);
}