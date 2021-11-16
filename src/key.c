#include "so_long.h"

/*
ft_key_move verifie si la nouvelle position est valide
puis lance un nouveau render dans la window
*/
static void ft_key_move(t_proj *proj, int x, int y)
{
	proj->nb_move++;

	// le player est sorti par la porte en ayant recupérés
	// au préalable tous les collectables
	if (proj->player == 0 || (proj->map[x][y] == 'E' && proj->collectable != 0))
		return ;

	// le player a récupéré tous les collectables et est sur la porte de sortie
	// le player est delete de la map
	if (proj->map[x][y] == 'E' && proj->collectable == 0)
	{
		proj->map[proj->carac_pos_x][proj->carac_pos_y] = '0';
		proj->player = 0;
	}

	// le player arrive sur un collectable
	// le collectable disparait et le joueur ne bouge  pas
	else if (proj->map[x][y] == 'C')
	{
		proj->collectable--;
		proj->map[x][y] = '0';
	}

	// le player se deplace
	// changement de position du player sur la map
	else if (proj->map[x][y] != '1')
	{
		proj->map[proj->carac_pos_x][proj->carac_pos_y] = '0';
		proj->map[x][y] = 'P';
		proj->carac_pos_x = x;
		proj->carac_pos_y = y;
	}

	// render de la window
	ft_render(proj);
	return ;
}

/*
ft_event_key recoit les events du clavier
appelle ft_key_move avec la nouvelle position du player
*/
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

	// transformation de nb_move de int a char*
	if (!(nb_move = ft_itoa(proj->nb_move)))
		return (ERROR);
	
	// pour pouvoir l'afficher dans la window
	mlx_string_put(proj->mlx, proj->win, 160, 100, 0xFFFFFF, nb_move);
	return (SUCCESS);
}