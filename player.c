/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abayar <abayar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:38:01 by olakhdar          #+#    #+#             */
/*   Updated: 2022/08/09 10:35:30 by abayar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
		draw_line(data, ray[i].xend, ray[i].yend, BLEU);
		i++;
	}
	draw_line(data, \
		data->player->x + (50 * cos(data->player->angle * PI / 180.0)),
		data->player->y + (sin(data->player->angle * PI / 180.0) * 50), RED);
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
		if (data->s[(int)floor((y / MINIMAP_SIZE))]
			[(int)floor((x / MINIMAP_SIZE))] == '1')
			break ;
		i++;
	}
	ray->xend = x;
	ray->yend = y;
	ray->lenth = i;
	init_direction(ray, ((int)round(x) % MINIMAP_SIZE),
		((int)round(y) % MINIMAP_SIZE));
}

int	find_main2(t_data *data, int i, int j)
{
	if (data->s[i][j] == 'N' || data->s[i][j] == 'S'
		|| data->s[i][j] == 'E' || data->s[i][j] == 'W')
	{
		init_player_dir(data, data->s[i][j]);
		data->player->x = data->xi + (MINIMAP_SIZE / 2);
		data->player->y = data->yi + (MINIMAP_SIZE / 2);
		data->s[i][j] = '0';
		return (1);
	}
	return (0);
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
			if (find_main2(data, i, j))
				return ;
			j++;
			data->xi += MINIMAP_SIZE;
		}
		data->yi += MINIMAP_SIZE;
		i++;
	}
	write(2, "Error: invalid map\n", 19);
	exit(1);
}
