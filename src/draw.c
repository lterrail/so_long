#include "so_long.h"


static void ft_draw_block(t_proj *proj, int y, int x)
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


// itere sur toute la map (.ber file)
// pour chaque lettre de la map, ajoute dans l'image le block entier xpm
void ft_draw(t_proj *proj)
{
    int y;
    int x;

	mlx_clear_window(proj->mlx, proj->win);

    y = 0;
    while (proj->map[y])
    {
        x = 0;
        while (proj->map[y][x])
        {
            ft_draw_block(proj, y, x);
            x++;
        }
        y++;
    }
}