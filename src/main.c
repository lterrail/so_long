#include "so_long.h"

static t_proj	*ft_init_proj(void)
{
	t_proj	*proj;

	proj = (t_proj *)malloc(sizeof(t_proj));
	if (!proj)
		return (NULL);
    proj->width_win = 0;
    proj->height_win = 0;
    proj->height_map = 0;
    proj->width_map = 0;
    proj->collectable = 0;
    proj->end = 0;
    proj->player = 0;
    proj->img_size = 0;
    proj->carac_pos_x = 0;
    proj->carac_pos_y = 0;
    proj->nb_move = 0;
    proj->map = NULL;
    proj->door_img = NULL;
    proj->player_img = NULL;
    proj->collectable_img = NULL;
    proj->wall_img = NULL;
	proj->mlx = mlx_init();
	return (proj);
}

static int ft_find_extension(char *filename, char *extension)
{
    char *result;
    int i;
    int n;

    n = ft_strlen(filename);
    i = n - 1;
    while ((i >= 0) && (filename[i] != '.') && (filename[i] != '/'))
    {
        i--;
    }
    if ((i > 0) && (filename[i] == '.') && (filename[i - 1] != '/'))
        result = filename + i;
    else
        result = filename + n;
    if (!ft_strcmp(result, extension))
        return (SUCCESS);
    return (ERROR);
}

int main(int ac, char **av)
{
	t_proj		*proj;
    int         error;

    if (ac != 2 || !ft_find_extension(av[1], ".ber"))
        ft_exit(NULL, ERROR_USAGE);
    if (!(proj = ft_init_proj()))
        ft_exit(NULL, ERROR_MALLOC);
    if ((error = ft_parse_ber_file(proj, av[1])) < 0)
        ft_exit(proj, error);
    ft_parse_xpm_file(proj);
    proj->win = mlx_new_window(proj->mlx, proj->width_win,
        proj->height_win, "so_long");
    ft_draw(proj);
    mlx_key_hook(proj->win, ft_event_key, proj);
	mlx_loop(proj->mlx);
    return (SUCCESS);
}