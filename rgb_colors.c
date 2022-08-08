/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 09:33:33 by olakhdar          #+#    #+#             */
/*   Updated: 2022/08/08 15:54:29 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

unsigned long	creatergb(int r, int g, int b)
{
	return ((r * 65536) + (g * 256) + b);
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

int	getcolor(char *s)
{
	char	**str;
	int		color;
	int		i;

	i = 0;
	check_color(s);
	str = ft_split(s, ',');
	color = (int)creatergb(ft_atoi(str[0]), ft_atoi(str[1]), ft_atoi(str[2]));
	while (str[i])
		i++;
	free_tab(str);
	if (i != 3)
	{
		printf("Error: color not suported\n");
		exit(1);
	}
	return (color);
}

char	*hack(char *s)
{
	int		i;
	char	**str;
	char	*ret;

	i = 0;
	str = ft_split(s, ' ');
	while (str[i])
		i++;
	if (i != 1)
	{
		printf("Error: invalid image\n");
		exit(1);
	}
	ret = ft_strdup(str[0]);
	while (ret[i] != '\0')
	{
		if (ret[i] == '\n')
			ret[i] = 0;
		i++;
	}
	free_tab(str);
	return (ret);
}
