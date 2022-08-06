/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:19:02 by abayar            #+#    #+#             */
/*   Updated: 2022/07/30 13:01:30 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_final_res(char **s)
{
	char	*temp;

	if (*s && **s != '\0')
	{
		temp = *s;
		*s = NULL;
		return (temp);
	}
	else
	{
		free(*s);
		*s = NULL;
		return (NULL);
	}
}

char	*get_result(char **s)
{
	char	*line;
	int		i;
	char	*temp;

	i = ft_strchr(*s, '\n');
	line = ft_substr(*s, 0, i + 1);
	temp = *s;
	*s = ft_substr(*s, i + 1, (ft_strlen(*s) - i));
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		buffer[BUFFER_SIZE + 1];
	int			ret;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (str == NULL)
		str = ft_strdup("");
	while (ft_strchr(str, '\n') == -1)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 0)
		{
			free(str);
			str = NULL;
			return (NULL);
		}
		if (ret == 0)
			break ;
		buffer[ret] = '\0';
		str = ft_strjoin(str, buffer);
	}
	if (ft_strchr(str, '\n') == -1)
		return (get_final_res(&str));
	return (get_result(&str));
}
