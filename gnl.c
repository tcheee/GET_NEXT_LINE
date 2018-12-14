/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:43:11 by tcherret          #+#    #+#             */
/*   Updated: 2018/11/30 14:07:47 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoinn(char *s1, char *s2)
{
	size_t		i;
	size_t		j;
	char		*new;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
	{
		new = ft_strdup(s2);
		return (new);
	}
	i = -1;
	j = -1;
	if (!(new = malloc(sizeof(*new) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[++i] != '\0')
		new[i] = s1[i];
	while (s2[++j] != '\0')
		new[i + j] = s2[j];
	new[i + j] = '\0';
	return (new);
}

int		putthatline(char **line, char **tmp, char **str, int i)
{
	*line = ft_strsub(*str, 0, i);
	*tmp = ft_strsub(*str, i + 1, ft_strlen(*str) - i);
	free(*str);
	*str = *tmp;
	return (1);
}

int		gnl_end(char **line, char **tmp, char **str, int i)
{
	while ((*str)[i] != '\0' && (*str)[i] != '\n')
		i++;
	if ((*str)[i] == '\n')
	{
		*line = ft_strsub(*str, 0, i);
		*tmp = ft_strsub(*str, i + 1, ft_strlen(*str) - i);
		free(*str);
		*str = *tmp;
		return (1);
	}
	if ((*str)[i] == '\0')
	{
		*line = ft_strsub(*str, 0, i);
		*tmp = ft_strsub(*str, i, ft_strlen(*str) - i);
		free(*str);
		*str = *tmp;
		return (1);
	}
	return (1);
}

void	init_str(char **tmp, char **str, char *buff, int ret)
{
	buff[ret] = '\0';
	*tmp = ft_strjoinn(*str, buff);
	free(*str);
	*str = *tmp;
}

int		get_next_line(const int fd, char **line)
{
	static char	*str;
	int			ret;
	char		*tmp;
	int			i;
	char		buff[BUFF_SIZE + 1];

	if (!str)
		if (!(str = ft_strnew(1)))
			return (-1);
	if (line == NULL || (ret = read(fd, NULL, 0)) == -1)
		return (-1);
	i = 0;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		init_str(&tmp, &str, buff, ret);
		ft_bzero(buff, BUFF_SIZE);
		while (str[i] != '\0' && str[i] != '\n')
			i++;
		if (str[i] == '\n')
			return (putthatline(line, &tmp, &str, i));
	}
	if ((ret = read(fd, buff, BUFF_SIZE)) == 0 && ft_strlen(str) != 0)
		return (gnl_end(line, &tmp, &str, i));
	*line = NULL;
	return (0);
}
