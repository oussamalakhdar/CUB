/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:22:54 by abayar            #+#    #+#             */
/*   Updated: 2022/08/06 17:25:16 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include "get_next_line.h"
# include <math.h>
# include <stdint.h>
// # include "textures.h"

# define PI 3.14159265
# define WHITE 0xffffff
# define GREY 0xe4e4e4
# define BLACK 0x000000
# define RED 0xff3d41
# define BLEU 0x9DB6CC
# define BROWN 0xC46200
# define YELL 0xDFFF00
# define GREEN 0x39918C
# define MINIMAP_SIZE 32
# define WIN_HIGH 1080
# define WIN_WIDH 1080

typedef struct s_rays {
	float   xbegin;
	float   ybegin;
	float	xend;
	float	yend;
	float	angle;
	float	wall_high;
	float	text_index;
	float	top_pix;
	float	bot_pix;
	float	of_x;
	float	of_y;
	float	lenth;
	int		dir;
}	t_ray;

typedef struct s_player {
	float   x;
	float   y;
	float	nx;
	float	ny;
	float	angle;
	int		reangle;
	int		move;
	t_ray	*rays;
}	t_player;

typedef struct s_map {
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		F;
	int		C;
}	t_map;

typedef struct s_text {
	void	*img1;
	void	*img2;
	void	*img3;
	void	*img4;
	int		*texture1;
	int		*texture2;
	int		*texture3;
	int		*texture4;
	int		byte1;
	int		endia1;
	int		sizepixel1;
	int		byte2;
	int		endia2;
	int		sizepixel2;
	int		byte3;
	int		endia3;
	int		sizepixel3;
	int		byte4;
	int		endia4;
	int		sizepixel4;
}	t_text;

typedef struct s_data {
	void		*image;
	int			byte;
	int			sizepixel;
	int			endia;
	// void		*img2;
	void		*win;
	void		*mlx;
	int			lmap;
	int			cmap;
	int			fd;
	char		*str;
	char		**s;
	int			*collor_buffer;
	int			xi;
	int			yi;
	char		*wall;
	int			color;
	// int			sizepixell;
	int			map;
	float		index;
	t_map		*mapcontent;
	t_player    *player;
	t_text		*text;
}	t_data;

int		key_hook(int keycode, t_data *vars);
void	pars_map(t_data *data);
int		ft_strncmp(char *s1, char *s2, int n);
char	**ft_split(char const *s, char c);
int 	pars_loop(char **s);
int 	check_col(char *col, char **s, int x);
int 	check_cas(char *col, char **s, int x, int y);

#endif