/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abayar <abayar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:12:13 by abayar            #+#    #+#             */
/*   Updated: 2022/08/07 14:20:31 by abayar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

unsigned long createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= (-1);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (res > 9223372036854775807 && sign == 1)
		return (-1);
	if (res > 9223372036854775808U && sign == -1)
		return (0);
	return (res * sign);
}

void	check_color(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
	{
		printf("Error: 3eye9ti\n");
		exit(1);
	}
}

int getcolor(char *s)
{
	char	**str;
	int		color;
	int		i;
	
	i = 0;
	check_color(s);
	str = ft_split(s,',');
	color = (int)createRGB(ft_atoi(str[0]), ft_atoi(str[1]), ft_atoi(str[2]));
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	if (i != 3)
	{
		printf("Error: color not suported\n");
		exit(1);
	}
	return (color);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (!s2 && s1)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	key_hook(int keycode, t_data *vars)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 46)
		vars->map = 1;
	else if (keycode == 126)
		vars->player->move = 1;
	else if (keycode == 125)
		vars->player->move = -1;
	else if (keycode == 123)
		vars->player->reangle = -1;
	else if (keycode == 124)
		vars->player->reangle = 1;
	return (0);
}

int	key_hook2(int keycode, t_data *vars)
{
	if (keycode == 126 || keycode == 125)
		vars->player->move = 0;
	else if (keycode == 123 || keycode == 124)
		vars->player->reangle = 0;
	else if (keycode == 46)
		vars->map = 0;
	return (0);
}

int	destroy(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

char	*hack(char *s)
{
	int	i;

	i = 0;
	while(s[i] != '\0')
	{
		if (s[i] == '\n')
			s[i] = 0;
		i++;
	}
	return (s);
}

void	map_content(t_data *data)
{
	char *s;
	t_map *map;

	map = malloc(sizeof(t_map));
	map->C = -1;
	map->F = -1;
	s = get_next_line(data->fd);
	data->str = ft_strdup("");
	while(s)
	{
		if(ft_strncmp(s, "NO", 2) == 0)
			map->NO = hack(ft_strdup(s + 3));
		else if(ft_strncmp(s, "SO", 2) == 0)
			map->SO = hack(ft_strdup(s + 3));
		else if(ft_strncmp(s, "WE", 2) == 0)
			map->WE = hack(ft_strdup(s + 3));
		else if(ft_strncmp(s, "EA", 2) == 0)
			map->EA = hack(ft_strdup(s + 3));
		else if(ft_strncmp(s, "F", 1) == 0)
		{
			map->F = getcolor(s + 2);
			// while(1);
		}
		else if(ft_strncmp(s, "C", 1) == 0)
		{
			map->C = getcolor(s + 2);

		}
		else if(ft_strncmp(s, "\n", 1) != 0)
			data->str = ft_strjoin(data->str, s);
		free(s);
		s = get_next_line(data->fd);
	}
	free(s);
	data->mapcontent = map;
}

int  count_length(char **s)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while(s[i])
	{
		j = ft_strlen(s[i]);
		if (j > k)
			k = j;
		i++;
	}
	return (k);
}

char	**read_map(t_data *data, char *s)
{
	char	p;
	int		l;

	l = 0;
	data->lmap = 0;
	data->map = 0;
	data->fd = open(s, O_RDWR);
	if (data->fd == -1)
	{
		perror("Error");
		exit(1);
	}
	while (!(read(data->fd, &p, 1) == 0))
	{
		if (p == '\n')
			data->lmap++;
	}
	data->lmap++;
	close(data->fd);
	data->fd = open(s, O_RDWR);
	map_content(data);
	data->s = ft_split(data->str, '\n');
	data->cmap = count_length(data->s);
	return (data->s);
}

void	help_pars(t_data *data, int i, int j)
{
	int	x;
	int	y;

	x = i;
	while (x <= i + MINIMAP_SIZE)
	{	
		y = j;
		while (y <= j + MINIMAP_SIZE)
		{
			mlx_pixel_put(data->mlx, data->win, x, y, data->color);
			y++;
		}
		x++;
	}
}

int	draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
{
	float deltaX = endX - beginX;
	float deltaY = endY - beginY;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	float pixelX = beginX;
	float pixelY = beginY;
	while (pixels)
	{
	    mlx_pixel_put(mlx, win, pixelX, pixelY, color);
	    pixelX += deltaX;
	    pixelY += deltaY;
	    --pixels;
	}
	return (0);
}

void	render_player(t_data *data, int i, int j)
{
	int	x;
	int	y;

	x = i;
	while (x <= i + (MINIMAP_SIZE / 5))
	{	
		y = j;
		while (y <= j + (MINIMAP_SIZE / 5))
		{
			data->player->x = i + 5;
			data->player->y = j + 5;
			mlx_pixel_put(data->mlx, data->win, x, y, RED);
			y++;
		}
		x++;
	}
}

void	mini_player(t_data *data)
{
	int		i;
	t_ray	*ray;

	i = 0;
	ray = data->player->rays;
	render_player(data, data->player->x - 5, data->player->y - 5);
	while (i < data->cmap * MINIMAP_SIZE)
	{
		draw_line(data->mlx, data->win,
			ray[i].xbegin, ray[i].ybegin,
			ray[i].xend, ray[i].yend, BLEU);
		i++;
	}
	draw_line(data->mlx, data->win,
			data->player->x, data->player->y,
			data->player->x + (50 * cos(data->player->angle * PI / 180.0)),
			data->player->y + (sin(data->player->angle * PI / 180.0) * 50), RED);
}

void	init_direction(t_ray *ray, int x, int y)
{
	if (x == 0 || x == 1 || x == 32 || x == 31)
			ray->dir = 'h';
	if (y == 1 || y == 0 || y == 32 || y == 31)
	{
		if (ray->dir == 'h')
			ray->dir = '2';
		else
			ray->dir = 'v';
	}
}

void	find_hit_wall(t_data *data, t_ray *ray)
{
	int		i;
	float	x;
	float	y;

	i = 1;
	while (1)
	{
		x = 0;
		y = 0;
		x = data->player->x + (i * cos(ray->angle * PI / 180.0));
		y = data->player->y + (i * sin(ray->angle * PI / 180.0));
		if (data->s[(int)floor((y / MINIMAP_SIZE))][(int)floor((x / MINIMAP_SIZE))] == '1')
			break;
		i++;
	}
	ray->xend = x;
	ray->yend = y;
	ray->lenth = i;
	init_direction(ray, ((int)round(x)%MINIMAP_SIZE), ((int)round(y)%MINIMAP_SIZE));
}

void	initialize_rays(t_data *data)
{
	int		i;
	float	angindex;
	float	rangle;
	t_ray	*ray;//

	i = 0;
	ray = data->player->rays;
	angindex = 60 / ((float)data->cmap * (float)MINIMAP_SIZE);
	rangle = (data->player->angle - 30);
	data->index = angindex;

	while (i < data->cmap * MINIMAP_SIZE)
	{
		ray[i].xbegin = data->player->x;
		ray[i].ybegin = data->player->y;
		ray[i].angle = rangle;
		ray[i].dir = 'a';
		find_hit_wall(data, &ray[i]);
		rangle += angindex;
		i++;
	}
}

void	my3d_painting(t_data *data)
{
	t_ray	*ray;
	int		i;
	float	adj;
	float	tmp;

	i = 0;
	ray = data->player->rays;
	while (i < data->cmap * MINIMAP_SIZE)
	{
		adj = round(((data->cmap * MINIMAP_SIZE) / 2) / tan((60 * PI / 180.0) / 2));
		tmp = floor(ray[i].lenth * cos(fabs((ray[i].angle * PI / 180.0) - (data->player->angle * PI / 180.0))));
		ray[i].wall_high = (MINIMAP_SIZE / tmp) * adj;
		ray[i].top_pix = (WIN_WIDH / 2) - (ray[i].wall_high / 2);
		ray[i].text_index = 32 / ray[i].wall_high;
		if (ray[i].top_pix < 0.0)
			ray[i].top_pix = 0;
		ray[i].bot_pix = (WIN_WIDH / 2) + (ray[i].wall_high / 2);
		if (ray[i].bot_pix > WIN_WIDH)
			ray[i].bot_pix = WIN_WIDH;
		if (ray[i].dir == 'h')
			ray[i].of_x = fmod(ray[i].yend / 64, 1);
		else
			ray[i].of_x = fmod(ray[i].xend / 64, 1);
		ray[i].of_x *= 64;
		int j=0;
		while (j < WIN_WIDH)
		{
			int	dis = (WIN_WIDH / 2) - (ray[i].wall_high / 2);
			ray[i].of_y = ((j - dis) * 64) / ray[i].wall_high;
			j++;
		}
		i++;
	}
}



void	update_image(t_data *data, int *c)
{
	t_ray	*ray;
	int i, j;

	ray = data->player->rays;
	i = 0;
	for(int y = 0; y < (data->cmap * MINIMAP_SIZE); ++y)
	{
		j = 0;
		(*c)++;
		int	dis = (WIN_WIDH / 2) - (ray[y].wall_high / 2);
		ray[y].of_x = (int)ray[y].of_x % 64; 
		ray[y].of_y = (int)ray[y].of_y % 64;
		for(int x = 0; x < WIN_WIDH; ++x)
		{
			ray[y].of_y = ((x - dis) * 64) / ray[y].wall_high;
			if (x <= ray[y].top_pix)
		    	data->collor_buffer[(x * data->sizepixel) + y] =  data->mapcontent->C;
			else if (x >= ray[y].top_pix && x <= ray[y].bot_pix)
			{
				if (ray[y].dir == 'h')
				{
					if (ray[y].angle > 90 && ray[y].angle < 270)
					{
		    			data->collor_buffer[(x * data->sizepixel) + y] = data->text->texture3[(int)(ray[y].of_y - 1) * data->text->sizepixel3 + (int)(ray[y].of_x * 2)];// * (data->text->byte2 / 32)];
					}
					else
		    			data->collor_buffer[(x * data->sizepixel) + y] = data->text->texture4[(int)(ray[y].of_y - 1) * data->text->sizepixel4 + (int)(ray[y].of_x * 2)];//* (data->text->byte2 / 32)];
				}
				else if (ray[y].dir == '2')
				{
					*c = 0;
		    		data->collor_buffer[(x * data->sizepixel) + y] = BLACK;
				}
				else
				{
					if ((ray[y].angle > 180 && ray[y].angle < 360) || (ray[y].angle < 0 && ray[y].angle > -90))
			    		data->collor_buffer[(x * data->sizepixel) + y] =  data->text->texture1[(int)(ray[y].of_y - 1) * data->text->sizepixel1 + (int)(ray[y].of_x * 2)];// * (data->text->byte1 / 32)];
					else if ((ray[y].angle > 0 && ray[y].angle < 180) || (ray[y].angle > 360 && ray[y].angle < 400))
			    		data->collor_buffer[(x * data->sizepixel) + y] = data->text->texture2[(int)(ray[y].of_y - 1) * data->text->sizepixel2 + (int)(ray[y].of_x * 2)];// * (data->text->byte1 / 32)];
				}
			}
			else
				data->collor_buffer[(x * data->sizepixel) + y] = data->mapcontent->F;
			j++;
			if (j > 64)
				j = 0;
		}
		i++;
		if (i > 64)
			i = 0;
	}
}

void	clear_collor_buffer(t_data *data)
{
	for(int y = 0; y < WIN_WIDH; ++y)
	{
		for(int x = 0; x < (data->cmap * MINIMAP_SIZE); ++x)
		{
		    data->collor_buffer[(y * data->sizepixel) + x] = BLACK;
		}
	}
}

void	init_player_dir(t_data *data, char c)
{
	if (c == 'N')
		data->player->angle = 270;
	else if (c == 'S')
		data->player->angle = 90;
	else if (c == 'E')
		data->player->angle = 0;
	else if (c == 'W')
		data->player->angle = 180;
}

void	find_main(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->s[i])
	{	
		j = 0;
		data->xi = 0;
		while (data->s[i][j])
		{
			if (data->s[i][j] == 'N' || data->s[i][j] == 'S'
				|| data->s[i][j] == 'E' || data->s[i][j] == 'W')
			{
				init_player_dir(data, data->s[i][j]);
				data->player->x = data->xi + (MINIMAP_SIZE / 2);
				data->player->y = data->yi + (MINIMAP_SIZE / 2);
				data->s[i][j] = '0';
				return ;
			}
			j++;
			data->xi += MINIMAP_SIZE;
		}
		data->yi += MINIMAP_SIZE;
		i++;
	}
	write(2, "Error: invalid map\n", 19);
	exit(1);
}

void	minimapdraw(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->yi = 0;
	while (data->s[i])
	{
		j = 0;
		data->xi = 0;
		while (data->s[i][j])
		{
			if (data->s[i][j] == '1')
				data->color = WHITE;
			else if (data->s[i][j] == 'E')
				data->color = BLEU;
			else
				data->color = BLACK;
			if (data->s[i][j] != '\n' && data->s[i][j] != ' ')
				help_pars(data, data->xi, data->yi);
			j++;
			data->xi += MINIMAP_SIZE;
		}
		data->yi += MINIMAP_SIZE;
		i++;
	}
	mini_player(data);
}

void	pars_map(t_data *data)
{
	int count;

	count = 0;
	initialize_rays(data);
	my3d_painting(data);
	update_image(data, &count);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	clear_collor_buffer(data);
	if (data->map == 1)
		minimapdraw(data);
}

void	player_born(t_data *data)
{
	t_player	*player;

	if (!pars_loop(data->s))
	{
		write(2, "Error: Map invalid\n", 19);
		exit(1);
	}
	player = malloc(sizeof(t_player));
	if (!player)
	{
		perror("error: malloc fail");
		return ;
	}
	data->player = player;
	player->angle = 0;
	player->move = 0;
	player->reangle = 0;
	player->rays = malloc(sizeof(t_ray) * (data->cmap * MINIMAP_SIZE));
	if (!player->rays)
	{
		perror((": malloc fail"));
		exit(1);
	}
	find_main(data);
}

void	overlap(t_data *data)
{
	if (data->player->angle < 0)
		data->player->angle = 360 + data->player->angle;
	else if (data->player->angle > 360)
		data->player->angle = data->player->angle - 360;
}

int	loop_game(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	if (data->player->move == -1)
	{
		data->player->nx = round(data->player->x + (3 * cos((data->player->angle + 180) * PI / 180.0)));
		data->player->ny = round(data->player->y + (3 * sin((data->player->angle + 180) * PI / 180.0)));
		if (data->s[(int)data->player->ny / MINIMAP_SIZE][(int)data->player->nx / MINIMAP_SIZE] == '0')
		{
			data->player->x = data->player->nx;
			data->player->y = data->player->ny;
		}
	}
	else if (data->player->move)
	{
		data->player->nx = round(data->player->x + (3 * cos(data->player->angle * PI / 180.0)));
		data->player->ny = round(data->player->y + (3 * sin(data->player->angle * PI / 180.0)));
		if (data->s[(int)data->player->ny / MINIMAP_SIZE][(int)data->player->nx / MINIMAP_SIZE] == '0')
		{
			data->player->x = data->player->nx;
			data->player->y = data->player->ny;
		}
	}
	if (data->player->reangle == -1)
		data->player->angle -= 5; 
	else if (data->player->reangle)
		data->player->angle += 5;
	overlap(data);
	pars_map(data);
	return (0);
}

void	init_texture(t_data *data)
{
	t_text	*text;
	int  w, h;
	
	text = malloc(sizeof(t_text));
	text->img1 = mlx_xpm_file_to_image(data->mlx, data->mapcontent->NO, &w, &h);
	text->img2 = mlx_xpm_file_to_image(data->mlx, data->mapcontent->SO, &w, &h);
	text->img3 = mlx_xpm_file_to_image(data->mlx, data->mapcontent->WE, &w, &h);
	text->img4 = mlx_xpm_file_to_image(data->mlx, data->mapcontent->EA, &w, &h);
	if (!text->img1 || !text->img3 || !text->img2 || !text->img4 || data->mapcontent->F == -1 || data->mapcontent->C == -1)
	{
		write(2, "Error: bad argument\n", 20);
		exit(1);
	}
	text->texture1 = (int *)mlx_get_data_addr(text->img1, &text->byte1, &text->sizepixel1, &text->endia1);
	text->texture2 = (int *)mlx_get_data_addr(text->img2, &text->byte1, &text->sizepixel2, &text->endia2);
	text->texture3 = (int *)mlx_get_data_addr(text->img3, &text->byte1, &text->sizepixel3, &text->endia3);
	text->texture4 = (int *)mlx_get_data_addr(text->img4, &text->byte1, &text->sizepixel4, &text->endia4);
	text->sizepixel1 /= 4;
	text->sizepixel2 /= 4;
	text->sizepixel3 /= 4;
	text->sizepixel4 /= 4;
	data->text = text;
}

int main(int ac, char **av)
{
	t_data	*img;
	char	**s;

	if (ac == 2)
	{
		img = malloc(sizeof(t_data));
		s = read_map(img, av[1]);
		player_born(img);
		img->sizepixel = 0;
		img->mlx = mlx_init();
		img->wall = ft_strdup("./StoneHitler.xpm");
		img->win = mlx_new_window(img->mlx, (img->cmap * MINIMAP_SIZE), WIN_WIDH, "Cub3D");
		img->image = mlx_new_image(img->mlx, (img->cmap * MINIMAP_SIZE), WIN_WIDH);
		img->collor_buffer = (int *)mlx_get_data_addr(img->image, &img->byte, &img->sizepixel, &img->endia);
		img->sizepixel /= 4;
		init_texture(img);
		pars_map(img);
		mlx_hook(img->win, 2, 1L, key_hook, img);
		mlx_hook(img->win, 3, 2L, key_hook2, img);
		mlx_loop_hook(img->mlx, loop_game, img);
		mlx_hook(img->win, 17, 0, destroy, img);
		mlx_loop(img->mlx);
	}
	else
		printf("Error\nerror argment\n");
	return (0);
}