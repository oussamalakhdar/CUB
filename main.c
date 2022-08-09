/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abayar <abayar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:12:13 by abayar            #+#    #+#             */
/*   Updated: 2022/08/09 11:20:53 by abayar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_motherfucker(t_data *data)
{
	data->player->nx = data->player->x;
	data->player->ny = data->player->y;
	if (data->player->move == -1)
	{
		data->player->nx = round(data->player->x + \
		(3 * cos((data->player->angle + 180) * PI / 180.0)));
		data->player->ny = round(data->player->y + \
		(3 * sin((data->player->angle + 180) * PI / 180.0)));
	}
	else if (data->player->move)
	{
		data->player->nx = round(data->player->x + \
		(3 * cos(data->player->angle * PI / 180.0)));
		data->player->ny = round(data->player->y + \
		(3 * sin(data->player->angle * PI / 180.0)));
	}
	if (data->s[(int)data->player->ny / MINIMAP_SIZE] \
			[(int)data->player->nx / MINIMAP_SIZE] == '0')
	{
		data->player->x = data->player->nx;
		data->player->y = data->player->ny;
	}
}

int	loop_game(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	move_motherfucker(data);
	if (data->player->reangle == -1)
		data->player->angle -= 5;
	else if (data->player->reangle)
		data->player->angle += 5;
	overlap(data);
	drawing(data);
	return (0);
}

void	init_texture(t_data *data)
{
	t_text	*text;

	text = malloc(sizeof(t_text));
	init_texture2(text, data);
	text->texture1 = (int *)mlx_get_data_addr(text->img1, \
	&text->byte1, &text->sizepixel1, &text->endia1);
	text->texture2 = (int *)mlx_get_data_addr(text->img2, \
	&text->byte1, &text->sizepixel2, &text->endia2);
	text->texture3 = (int *)mlx_get_data_addr(text->img3, \
	&text->byte1, &text->sizepixel3, &text->endia3);
	text->texture4 = (int *)mlx_get_data_addr(text->img4, \
	&text->byte1, &text->sizepixel4, &text->endia4);
	text->sizepixel1 /= 4;
	text->sizepixel2 /= 4;
	text->sizepixel3 /= 4;
	text->sizepixel4 /= 4;
	data->text = text;
}

void	cub3d(t_data *img)
{
	mlx_hook(img->win, 2, 1L, key_hook, img);
	mlx_hook(img->win, 3, 2L, key_hook2, img);
	mlx_loop_hook(img->mlx, loop_game, img);
	mlx_hook(img->win, 17, 0, destroy, img);
}

int	main(int ac, char **av)
{
	t_data	*img;

	if (ac == 2)
	{
		img = malloc(sizeof(t_data));
		read_map(img, av[1]);
		player_born(img);
		img->sizepixel = 0;
		img->mlx = mlx_init();
		img->wall = ft_strdup("./StoneHitler.xpm");
		img->win = mlx_new_window(img->mlx, \
		(img->cmap * MINIMAP_SIZE), WIN_WIDH, "Cub3D");
		img->image = mlx_new_image(img->mlx, \
		(img->cmap * MINIMAP_SIZE), WIN_WIDH);
		img->collor_buffer = (int *)mlx_get_data_addr(img->image, \
		&img->byte, &img->sizepixel, &img->endia);
		img->sizepixel /= 4;
		init_texture(img);
		drawing(img);
		cub3d(img);
		mlx_loop(img->mlx);
	}
	else
		printf("Error\nerror argment\n");
}
