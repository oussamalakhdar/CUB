/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abayar <abayar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 09:33:33 by olakhdar          #+#    #+#             */
/*   Updated: 2022/08/09 11:17:54 by abayar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_num(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if ((s[i] == '-' || s[i] == '+') && i == 0 && s[i + 1] != '\0')
		{
			i++;
			continue ;
		}
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		i++;
	}
	if (s[0] == '\0')
		return (-1);
	return (1);
}

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
	while (str[i])
	{
		if (is_num(str[i]) == -1)
		{
			printf("Error: color\n");
			exit(1);
		}
		i++;
	}
	i = 0;
	color = (int)creatergb(ft_atoi(str[0]), ft_atoi(str[1]), ft_atoi(str[2]));
	free_tab(str);
	if (tabsize(str) != 3)
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
