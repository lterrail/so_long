#include "so_long.h"

static int  ft_is_valid_wall(t_proj *proj)
{
    int i;
    int j;

    i = -1;
    while (proj->map[++i])
    {
        if (i == 0 || i == proj->height_map)
        {
            j = -1;
            while (proj->map[i][++j])
            {
                if (proj->map[i][j] != '1')
                    return (ERROR_WALL);
            }
        }
        else
        {
            if (proj->map[i][0] != '1')
                return (ERROR_WALL);
            if (proj->map[i][proj->width_map-1] != '1')
                return (ERROR_WALL);
        }
    }
    return (SUCCESS);
}

static int ft_is_valid_char_in_line(t_proj *proj, char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == 'C')
            proj->collectable++;
        else if (line[i] == 'E')
            proj->end++;
        else if (line[i] == 'P')
        {
            proj->player++;
            proj->carac_pos_x = proj->height_map;
            proj->carac_pos_y = i;
        }
        else if (!(line[i] == '0') && !(line[i] == '1'))
            return (ERROR);
        i++;
    }
    return (SUCCESS);
}

static int ft_is_valid_line(t_proj *proj, char *line)
{
    int   len_line;

    if ((len_line = ft_strlen(line)) < 0)
        return (ERROR_MAP_SIZE);
    if (len_line != proj->width_map && proj->height_map != 0)
        return (ERROR_MAP_SIZE);
    if (!ft_is_valid_char_in_line(proj, line))
        return (ERROR_INVALID_CHAR);
	proj->width_map = ft_strlen(line);
	proj->height_map++;
    return SUCCESS;
}

static int record_file(t_proj *proj, char *filename)
{
	int		fd;
	char	*line;
    int     err;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (ERROR_OPEN);
	while (get_next_line(fd, &line) > 0)
	{
        if ((err = ft_is_valid_line(proj, line)) < 0)
        {
            close(fd);
		    free(line);
            return (err);
        }
		free(line);
	}
	close(fd);
    if (proj->collectable == 0 || proj->end != 1 || proj->player != 1)
        return (ERROR_INVALID_MAP_PARAMS);
	if (!(proj->map = malloc(sizeof(char *) * (proj->height_map + 1))))
		return (ERROR_MALLOC);
	return (SUCCESS);
}

int	         ft_parse_ber_file(t_proj *proj, char *filename)
{
	int		fd;
	char	*line;
	int		i;
	int		err;

	i = 0;
	if ((err = record_file(proj, filename)) < 0)
		return (err);
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (ERROR_OPEN);
	while (get_next_line(fd, &line) > 0)
	{
		if (!(proj->map[i++] = ft_strdup(line)))
		{
			close(fd);
			free(line);
			return (ERROR_MALLOC);
		}
		free(line);
	}
	close(fd);
	proj->map[i] = NULL;
    if ((err = ft_is_valid_wall(proj)) < 0)
        return (err);
	return (SUCCESS);
}