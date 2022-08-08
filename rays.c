/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:59:36 by olakhdar          #+#    #+#             */
/*   Updated: 2022/08/08 11:13:02 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	initialize_rays(t_data *data)
{
	int		i;
	float	angindex;
	float	rangle;
	t_ray	*ray;

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
