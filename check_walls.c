/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:59:33 by abayar            #+#    #+#             */
/*   Updated: 2022/08/02 20:57:43 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int check_cas(char *col, char **s, int x, int y)
{
    if (x == 0)
    {
        if (col[y] == ' ')
        {
            if (s[x + 1][y] == '0')
                return (0);
        }
        else if (col[y] == '1')
        {
            if (s[x + 1][y] == '0' && col[y + 1] != '1')
                return (0);
        }
    }
    return 0;
}

int check_col(char *col, char **s, int x)
{
    int i;

    i = 0;
    if (s[1] == NULL)
        return (0);
    while (col[i])
    {
        if (!check_cas(s[i], s, x, i))
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