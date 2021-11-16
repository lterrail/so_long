/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 05:21:59 by lterrail          #+#    #+#             */
/*   Updated: 2019/05/19 15:12:18 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include <mlx.h>
# include <math.h>
# include "libft.h"


# define IMG_SIZE                   64

# define END_OF_GAME                 2
# define SUCCESS		             1
# define ERROR			             0
# define ERROR_MALLOC               -2
# define ERROR_OPEN                 -3
# define ERROR_INVALID_MAP          -4
# define ERROR_WALL                 -5
# define ERROR_INVALID_MAP_PARAMS   -6
# define ERROR_MAP_SIZE             -7
# define ERROR_INVALID_CHAR         -8
# define ERROR_USAGE                -9

# define KEY_W                      13
# define KEY_S                       1
# define KEY_A                       0
# define KEY_D                       2
# define ESC                        53


typedef struct		s_img
{
	void			*img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_img;

typedef struct		s_proj
{
    int             width_win;
    int             height_win;
    int             height_map;
    int             width_map;
    int             collectable;
    int             end;
    int             player;
    int             img_size;
    int             carac_pos_x;
    int             carac_pos_y;
    int             nb_move;
    void			*win;
	void			*mlx;
    char            **map;
    void            *door_img;
    void            *collectable_img;
    void            *player_img;
    void            *wall_img;
}					t_proj;

void                ft_render(t_proj *proj);

void                ft_exit(t_proj *proj, int error);

int                 ft_event_key(int keycode, t_proj *proj);

int			        ft_event_key(int keycode, t_proj *proj);

int                 ft_parse_ber_file(t_proj *proj, char *filename);

int                 ft_parse_xpm_file(t_proj *proj);


#endif
