/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abayar <abayar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 09:34:42 by olakhdar          #+#    #+#             */
/*   Updated: 2022/08/09 10:56:20 by abayar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_texture2(t_text *text, t_data *data)
{
	int		w;
	int		h;

	text->img1 = mlx_xpm_file_to_image(data->mlx, data->mapcontent->no, &w, &h);
	text->img2 = mlx_xpm_file_to_image(data->mlx, data->mapcontent->so, &w, &h);
	text->img3 = mlx_xpm_file_to_image(data->mlx, data->mapcontent->we, &w, &h);
	text->img4 = mlx_xpm_file_to_image(data->mlx, data->mapcontent->ea, &w, &h);
	if (!text->img1 || !text->img3 || !text->img2
		|| !text->img4 || data->mapcontent->f == -1 || \
		data->mapcontent->c == -1)
	{
		write(2, "Error: bad argument\n", 20);
		exit(1);
	}
}

void	if_v(t_data *data, t_ray *ray, int x, int y)
{
	if ((ray[y].angle > 180 && ray[y].angle < 360) || \
		(ray[y].angle < 0 && ray[y].angle > -90))
		data->collor_buffer[(x * data->sizepixel) + y] = \
		data->text->texture1[(int)(ray[y].of_y - 1) *\
		data->text->sizepixel1 + (int)(ray[y].of_x * 2)];
	else if ((ray[y].angle > 0 && ray[y].angle < 180) || \
			(ray[y].angle > 360 && ray[y].angle < 400))
		data->collor_buffer[(x * data->sizepixel) + y] = \
		data->text->texture2[(int)(ray[y].of_y - 1) *\
		data->text->sizepixel2 + (int)(ray[y].of_x * 2)];
}

void	if_h(t_data *data, t_ray *ray, int x, int y)
{
	if (ray[y].angle > 90 && ray[y].angle < 270)
		data->collor_buffer[(x * data->sizepixel) + y] = \
		data->text->texture3[((int)(ray[y].of_y - 1) *\
		data->text->sizepixel3) + (int)(ray[y].of_x * 2)];
	else
		data->collor_buffer[(x * data->sizepixel) + y] = \
		data->text->texture4[((int)(ray[y].of_y - 1) *\
		data->text->sizepixel4) + (int)(ray[y].of_x * 2)];
}

void	update_image2(t_data *data, t_ray *ray, int x, int y)
{
	if (x <= ray[y].top_pix)
		data->collor_buffer[(x * data->sizepixel) + y] = \
		data->mapcontent->c;
	else if (x >= ray[y].top_pix && x <= ray[y].bot_pix)
	{
		if (ray[y].dir == 'h')
			if_h(data, ray, x, y);
		else if (ray[y].dir == '2')
		{
			// *c = 0;
			data->collor_buffer[(x * data->sizepixel) + y] = BLACK;
		}
		else
			if_v(data, ray, x, y);
	}
	else
		data->collor_buffer[(x * data->sizepixel) + y] = \
		data->mapcontent->f;
}
	
void	update_image(t_data *data)
{
	t_ray	*ray;
	int		x;
	int		y;
	int		dis;

	y = 0;
	ray = data->player->rays;
	while (y < (data->cmap * MINIMAP_SIZE))
	{
		x = 0;
		// (*c)++;
		dis = (WIN_WIDH / 2) - (ray[y].wall_high / 2);
		ray[y].of_x = (int)ray[y].of_x % 64;
		ray[y].of_y = (int)ray[y].of_y % 64;
		while (x < WIN_WIDH)
		{
			ray[y].of_y = ((x - dis) * 64) / ray[y].wall_high;
			update_image2(data, ray, x, y);
			x++;
		}
		y++;
	}
}
