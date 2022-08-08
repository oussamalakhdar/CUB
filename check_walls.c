/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:59:33 by abayar            #+#    #+#             */
/*   Updated: 2022/08/08 14:20:48 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check2(char *col, char **s, int x, int y)
{
	if (col[y] == ' ')
	{
		if (s[x + 1][y] == '0' || col[y + 1] == '0')
			return (0);
	}
	else if (col[y] == '1')
	{
		if (ft_strlen(s[x + 1]) > y && s[x + 1][y] == '0'
			&& col[y + 1] != '1')
			return (0);
		else if (col[y + 1] == '0')
			return (0);
	}
	else
		return (0);
	return (1);
}

int	check3(char *col, char **s, int x, int y)
{
	if (col[y] == ' ')
	{
		if (s[x + 1][y] == '0' || col[y + 1] == '0'
			|| s[x + 1][y + 1] == '0')
			return (0);
		else if (s[x + 1][y] == '0' || col[y + 1] == '0'
				|| s[x + 1][y + 1] == '0' || s[x - 1][y] == '0'
				|| s[x - 1][y + 1] == '0' || s[x - 1][y - 1] == '0'
				|| col[y - 1] == '0' || s[x - 1][y - 1] == '0')
			return (0);
	}
	else if (col[y] == '1')
	{
		if (s[x + 1][y] == '0' && col[y + 1] == ' ')
			return (0);
		else if (col[y + 1] == '0' && col[y + 2] == '\0')
			return (0);
	}
	return (1);
}

int	check_cas(char *col, char **s, int x, int y)
{
	if (x == 0)
	{
		if (!check2(col, s, x, y))
			return (0);
	}
	else if (s[x + 1] != NULL)
	{
		if (!check3(col, s, x, y))
			return (0);
	}
	if (x == tabsize(s) - 1)
	{
		if (col[y] == ' ')
		{
			if (col[y + 1] == '0')
				return (0);
		}
		else if (col[y] == '1')
		{
			if (col[y + 1] == '0')
				return (0);
		}
	}
	return (1);
}

int	check_col(char *col, char **s, int x)
{
	int	i;

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

int	pars_loop(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (!check_first(s))
		return (0);
	while (s[i])
	{
		if (!check_char(s[i]))
			return (0);
		if (!check_col(s[i], s, i))
			return (0);
		i++;
	}
	return (1);
}
