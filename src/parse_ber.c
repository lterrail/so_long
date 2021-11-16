#include "so_long.h"


/*
ft_is_valid_wall verifie les walls
*/
static int  ft_is_valid_wall(t_proj *proj)
{
    int i;
    int j;

    i = -1;
    while (proj->map[++i])
    {
        // si premiere ou derniere ligne, que des '1' doivent etre presents
        // sur toute la ligne
        if (i == 0 || i == proj->height_map)
        {
            j = -1;
            while (proj->map[i][++j])
            {
                if (proj->map[i][j] != '1')
                    return (ERROR_WALL);
            }
        }

        // sinon le premier et le dernier char doivent etre des '1'
        else
        {
            // premier
            if (proj->map[i][0] != '1')
                return (ERROR_WALL);
            // dernier
            if (proj->map[i][proj->width_map-1] != '1')
                return (ERROR_WALL);
        }
    }
    return (SUCCESS);
}

/*
ft_is_valid_char_in_line stocke les informations
et verifie chaque char d'une ligne
*/
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

    len_line = ft_strlen(line);

    // verification que chaque ligne soit de la meme taille
    // proj->width_map == la len de la precedente ligne
    // len_line == len de la ligne  actuelle
    if (len_line != proj->width_map && proj->height_map != 0)
        return (ERROR_MAP_SIZE);

    // verification que chaque ligne ait bien que des char autorisés
    if (!ft_is_valid_char_in_line(proj, line))
        return (ERROR_INVALID_CHAR);
    
    // actualisation de la taille d'une ligne
	proj->width_map = len_line;

    // increment la taille de la map (char **) 
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

    // verification du nombre de ressources sur la map
    if (proj->collectable == 0 || proj->end != 1 || proj->player != 1)
        return (ERROR_INVALID_MAP_PARAMS);

    // allocation de la map (char **)
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

    // premier open du fichier pour recuperer sa len
    // pour permettre de faire un malloc (char **)
    // et pour verifier que le fichier est valide
	if ((err = record_file(proj, filename)) < 0)
		return (err);
    
    // deuxieme open, cette fois on stocke les lignes du fichier (char *)
    // dans la proj->map (char **)
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

    // dernier check pour les walls 
    if ((err = ft_is_valid_wall(proj)) < 0)
        return (err);
	return (SUCCESS);
}