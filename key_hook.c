/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 09:40:54 by olakhdar          #+#    #+#             */
/*   Updated: 2022/08/08 14:38:56 by olakhdar         ###   ########.fr       */
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

int	draw_line(void *mlx, void *win, int beginx, int beginy, int endx, int endy, int color)
{
	float	deltax;
	float	deltay;
	int		pixels;
	float	pixelx;
	float	pixely;

	deltax = endx - beginx;
	deltay = endy - beginy;
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	pixelx = beginx;
	pixely = beginy;
	while (pixels)
	{
		mlx_pixel_put(mlx, win, pixelx, pixely, color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
	return (0);
}

void	clear_collor_buffer(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < WIN_WIDH)
	{
		while (x < (data->cmap * MINIMAP_SIZE))
		{
			data->collor_buffer[(y * data->sizepixel) + x] = BLACK;
			x++;
		}
		y++;
	}
}
