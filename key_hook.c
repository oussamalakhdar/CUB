/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 09:40:54 by olakhdar          #+#    #+#             */
/*   Updated: 2022/08/08 09:58:26 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

int	draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
{
	float	deltaX;
	float	deltaY;
	int		pixels;
	float	pixelX;
	float	pixelY;

	deltaX = endX - beginX;
	deltaY = endY - beginY;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = beginX;
	pixelY = beginY;    
	while (pixels)
	{
		mlx_pixel_put(mlx, win, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return (0);
}

void	clear_collor_buffer(t_data *data)
{
	for (int y = 0; y < WIN_WIDH; ++y)
	{
		for(int x = 0; x < (data->cmap * MINIMAP_SIZE); ++x)
		{
			data->collor_buffer[(y * data->sizepixel) + x] = BLACK;
		}
	}
}
