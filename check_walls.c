/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abayar <abayar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:59:33 by abayar            #+#    #+#             */
/*   Updated: 2022/08/06 19:54:39 by abayar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int check_cas(char *col, char **s, int x, int y)
{
	if (x == 0)
	{
		if (col[y] == ' ')
		{
			if (s[x + 1][y] == '0' || col[y + 1] == '0')
				return (0);
		}
		else if (col[y] == '1')
		{
			if (ft_strlen(s[x + 1]) > y && s[x + 1][y] == '0' && col[y + 1] != '1')
			{
				printf("3  --[%c]\n", col[y + 1]);
				return (0);
			}
			else if (col[y + 1] == '0')
			{
                printf("2   [%c]\n", col[y + 1]);
				return (0);
			}
		}
		else
			return (0);
	}
	else if (s[x + 1] != NULL)
	{
		if (col[y] == ' ')
		{
			if (s[x + 1][y] == '0' || col[y + 1] == '0' || col[y + 1] == '0')
			{
				printf("4  --[%c]\n", col[y]);
				return (0);
			}
		}
		else if (col[y] == '1')
		{
			if (s[x + 1][y] == '0' && col[y + 1] != '1')
			{
				printf("5  --[%c]\n", col[y]);
				return (0);
			}
			else if (col[y + 1] == '0')
			{
				printf("6  --[%c]\n", col[y]);
				return (0);
			}
		}
		else
			return (0);
	}
	printf("x= %d y =%d\n", x,y);
	return (1);
}

int check_col(char *col, char **s, int x)
{
	int i;

	i = 0;
	if (s[1] == NULL)
		return (0);
	while (col[i])
	{
		if (!check_cas(col, s, x, i))
			return (0);
		i++;
	}
	return (1);
}

int pars_loop(char **s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (!check_col(s[i], s, i))
			return (0);
		i++;
	}
	return (1);
}