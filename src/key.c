#include "so_long.h"


static void ft_key_move(t_proj *proj, int x, int y)
{
	proj->nb_move++;
	if (proj->player == 0 || (proj->map[x][y] == 'E' && proj->collectable != 0))
		return ;
	if (proj->map[x][y] == 'E' && proj->collectable == 0)
	{
		proj->map[proj->carac_pos_x][proj->carac_pos_y] = '0';
		proj->player = 0;
	}
	else if (proj->map[x][y] == 'C')
	{
		proj->collectable--;
		proj->map[x][y] = '0';
	}
	else if (proj->map[x][y] != '1')
	{
		proj->map[proj->carac_pos_x][proj->carac_pos_y] = '0';
		proj->map[x][y] = 'P';
		proj->carac_pos_x = x;
		proj->carac_pos_y = y;
	}
	ft_draw(proj);
	return ;
}

int			ft_event_key(int keycode, t_proj *proj)
{
	char *nb_move;

	if (keycode == ESC)
		ft_exit(proj, EXIT_ERROR);
	else if (keycode == KEY_A)
		ft_key_move(proj, proj->carac_pos_x, proj->carac_pos_y - 1);
	else if (keycode == KEY_D)
		ft_key_move(proj, proj->carac_pos_x, proj->carac_pos_y + 1);
	else if (keycode == KEY_W)
		ft_key_move(proj, proj->carac_pos_x - 1, proj->carac_pos_y);
	else if (keycode == KEY_S)
		ft_key_move(proj, proj->carac_pos_x + 1, proj->carac_pos_y);
	if (!(nb_move = ft_itoa(proj->nb_move)))
		return (ERROR);
	mlx_string_put(proj->mlx, proj->win, 160, 40, 0xFFFFFF, nb_move);
	return (SUCCESS);
}