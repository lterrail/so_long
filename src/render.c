#include "so_long.h"

/*
ft_render_block rajoute  chaque block d'image dans la window
*/
static void ft_render_block(t_proj *proj, int y, int x)
{
    int x_win;
    int y_win;

    y_win = y*proj->img_size;
    x_win = x*proj->img_size;
    if (proj->map[y][x] == '1')
        mlx_put_image_to_window(proj->mlx, proj->win,
			proj->wall_img, x_win, y_win);
    else if (proj->map[y][x] == 'P')
        mlx_put_image_to_window(proj->mlx, proj->win,
			proj->player_img, x_win, y_win);
    else if (proj->map[y][x] == 'C')
        mlx_put_image_to_window(proj->mlx, proj->win,
			proj->collectable_img, x_win, y_win);
    else if (proj->map[y][x] == 'E')
        mlx_put_image_to_window(proj->mlx, proj->win,
			proj->door_img, x_win, y_win);
}

/*
ft_draw nettoie la précédente window puis parcourt chaque index
de la map pour y rajouter les blocks d'image
*/
void        ft_render(t_proj *proj)
{
    int y;
    int x;

    y = 0;
	mlx_clear_window(proj->mlx, proj->win);
    while (proj->map[y])
    {
        x = 0;
        while (proj->map[y][x])
        {
            ft_render_block(proj, y, x);
            x++;
        }
        y++;
    }
}