/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:59:33 by abayar            #+#    #+#             */
/*   Updated: 2022/08/07 16:42:00 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_first(char **s)
{
	int	i;

	i = 0;
	while(s[i])
	{
		if (s[i][0] != '1' && s[i][0] != ' ')
		{
			printf("-- %c", s[i][0]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_char(char *s)
{
	int	i;

	i = 0;
	while(s[i])
	{
		if (s[i] != '0' && s[i] != '1' && s[i] != 'N' && s[i] != 'S' && s[i] != 'E' && s[i] != 'W' && s[i] != ' ')
			return (0);
		i++;
	}
	return(1);
}

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
			if (s[x + 1][y] == '0' || col[y + 1] == '0' || s[x + 1][y + 1] == '0')
			{
				printf("4  --[%c]\n", col[y]);
				return (0);
			}
			else if (s[x + 1][y] == '0' || col[y + 1] == '0' || s[x + 1][y + 1] == '0' || s[x - 1][y] == '0' || s[x - 1][y + 1] == '0'|| s[x - 1][y - 1] == '0'|| col[y - 1] == '0' || s[x - 1][y - 1] == '0')
			{
				printf("15  --[[%c][%d][%d][%c]\n", s[x + 1][y], x, y, col[y + 1]);
				return (0);
			}
		}
		else if (col[y] == '1')
		{
			if (s[x + 1][y] == '0' && col[y + 1] == ' ')
			{
				printf("*5  --[%c][%d][%d]\n", s[x + 1][y], x, y);
				return (0);
			}
			else if (col[y + 1] == '0' && col[y + 2] == '\0')
			{
				printf("6  --[%c]\n", s[x + 1][y]);
				return (0);
			}
		}
	}
	// printf("x= %d y =%d\n", x,y);
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
	if(!check_first(s))
		return (0);
	while (s[i])
	{
		if(!check_char(s[i]))
			return (0);
		if (!check_col(s[i], s, i))
			return (0);
		i++;
	}
	return (1);
}