/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:18:07 by acan              #+#    #+#             */
/*   Updated: 2024/01/30 16:54:31 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static size_t	my_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (len);
	else
		while (str[len])
			len++;
	return (len);
}

static char	*my_strjoin3(char *s1, char *s2)
{
	char	*tmp;
	int		i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2) + 1));
	if (tmp == NULL)
		return (NULL);
	i = -1;
	while (s1 && s1[++i] != '\0')
		tmp[i] = s1[i];
	j = 0;
	if (i == -1)
		i = 0;
	while (s2 && s2[j])
	{
		tmp[i++] = s2[j++];
	}
	tmp[i] = '\0';
	if (s1)
		free(s1);
	return (tmp);
}

static char	*find_line(char *line, int fd)
{
	int		rdcount;
	char	*buf;

	rdcount = 1;
	buf = malloc(sizeof(char) * 2);
	while (rdcount > 0)
	{
		rdcount = read(fd, buf, 1);
		if (rdcount == -1)
		{
			if (line)
				free(line);
			line = NULL;
			if (buf)
				free(buf);
			buf = NULL;
			return (0);
		}
		buf[rdcount] = 0;
		line = my_strjoin3(line, buf);
	}
	free(buf);
	return (line);
}

char	*gnl(int fd)
{
	char	*line;

	line = NULL;
	if (fd < 0)
		return (0);
	line = find_line(line, fd);
	if (!line)
		return (0);
	return (line);
}
