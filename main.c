/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:12:13 by abayar            #+#    #+#             */
/*   Updated: 2022/08/08 11:15:32 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
	int		w;
	int		h;
	
	text = malloc(sizeof(t_text));
	text->img1 = mlx_xpm_file_to_image(data->mlx, data->mapcontent->NO, &w, &h);
	text->img2 = mlx_xpm_file_to_image(data->mlx, data->mapcontent->SO, &w, &h);
	text->img3 = mlx_xpm_file_to_image(data->mlx, data->mapcontent->WE, &w, &h);
	text->img4 = mlx_xpm_file_to_image(data->mlx, data->mapcontent->EA, &w, &h);
	if (!text->img1 || !text->img3 || !text->img2
		|| !text->img4 || data->mapcontent->F == -1 || data->mapcontent->C == -1)
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