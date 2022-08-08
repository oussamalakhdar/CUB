/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:19:07 by olakhdar          #+#    #+#             */
/*   Updated: 2022/08/08 14:20:55 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_first(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i][0] != '1' && s[i][0] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_char(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '0' && s[i] != '1' && s[i] != 'N' && s[i] != 'S'
			&& s[i] != 'E' && s[i] != 'W' && s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
