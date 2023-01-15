/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abayar <abayar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:22:54 by abayar            #+#    #+#             */
/*   Updated: 2022/08/17 19:05:46 by abayar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "mlx.h"
# include "get_next_line.h"
# include <math.h>
# include <stdint.h>

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
	float	xbegin;
	float	ybegin;
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
	float	x;
	float	y;
	float	nx;
	float	ny;
	float	angle;
	int		reangle;
	int		move;
	t_ray	*rays;
}	t_player;

typedef struct s_map {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
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
	int			map;
	float		index;
	t_map		*mapcontent;
	t_player	*player;
	t_text		*text;
}	t_data;

int				key_hook(int keycode, t_data *vars);
void			drawing(t_data *data);
int				ft_strncmp(char *s1, char *s2, int n);
char			**ft_split(char const *s, char c);
int				pars_loop(char **s);
int				check_col(char *col, char **s, int x);
int				check_cas(char *col, char **s, int x, int y);
int				ft_atoi(const char *str);
int				ft_strncmp(char *s1, char *s2, int n);
void			free_tab(char **str);
int				count_length(char **s);
int				tabsize(char **s);
unsigned long	creatergb(int r, int g, int b);
void			check_color(char *s);
int				getcolor(char *s);
char			*hack(char *s);
int				key_hook(int keycode, t_data *vars);
int				key_hook2(int keycode, t_data *vars);
int				destroy(t_data *data);
int				draw_line(t_data *data, int endX, int endY, int color);
void			clear_collor_buffer(t_data *data);
void			map_content(t_data *data);
void			read_map(t_data *data, char *s);
void			help_pars(t_data *data, int i, int j);
void			init_player_dir(t_data *data, char c);
void			render_player(t_data *data, int i, int j);
void			mini_player(t_data *data);
void			find_hit_wall(t_data *data, t_ray *ray);
void			find_main(t_data *data);
void			init_direction(t_ray *ray, int x, int y);
void			initialize_rays(t_data *data);
void			my3d_painting(t_data *data);
int				check_first(char **s);
int				check_char(char *s);
void			player_born(t_data *data);
void			overlap(t_data *data);
void			drawing(t_data *data);
void			update_image(t_data *data);
void			minimapdraw(t_data *data);
void			minimap_utils(t_data *data, int i, int j);
void			minimapdraw(t_data *data);
void			init_texture2(t_text *text, t_data *data);

#endif