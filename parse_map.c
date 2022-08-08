/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:04:19 by olakhdar          #+#    #+#             */
/*   Updated: 2022/08/08 10:17:11 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	map_content(t_data *data)
{
	char	*s;
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->C = -1;
	map->F = -1;
	s = get_next_line(data->fd);
	data->str = ft_strdup("");
	while (s)
	{
		if(ft_strncmp(s, "NO", 2) == 0)
			map->NO = hack(s + 3);
		else if(ft_strncmp(s, "SO", 2) == 0)
			map->SO = hack(s + 3);
		else if(ft_strncmp(s, "WE", 2) == 0)
			map->WE = hack(s + 3);
		else if(ft_strncmp(s, "EA", 2) == 0)
			map->EA = hack(s + 3);
		else if(ft_strncmp(s, "F", 1) == 0)
			map->F = getcolor(s + 2);
		else if(ft_strncmp(s, "C", 1) == 0)
			map->C = getcolor(s + 2);
		else if(ft_strncmp(s, "\n", 1) != 0)
			data->str = ft_strjoin(data->str, s);
		free(s);
		s = get_next_line(data->fd);
	}
	free(s);
	data->mapcontent = map;
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
