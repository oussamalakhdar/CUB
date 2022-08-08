/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:49:18 by olakhdar          #+#    #+#             */
/*   Updated: 2022/08/08 16:51:59 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

void	drawing(t_data *data)
{
	int	count;

	count = 0;
	initialize_rays(data);
	my3d_painting(data);
	update_image(data, &count);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	clear_collor_buffer(data);
	if (data->map == 1)
		minimapdraw(data);
}
