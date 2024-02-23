/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uarslan <uarslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 20:14:39 by acan              #+#    #+#             */
/*   Updated: 2024/01/30 13:10:35 by uarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	*my_strjoin2(char *s1, char *s2)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (tmp == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		tmp[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		tmp[i++] = s2[j++];
	tmp[i] = '\0';
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (tmp);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	**malloc_double(char **params, char *command)
{
	int		loop;
	char	**ret;
	int		size;

	size = 0;
	while (params && params[size])
		size++;
	ret = (char **)malloc(sizeof(char *) * (size + 2));
	if (!ret)
		return (NULL);
	loop = -1;
	while (++loop < size)
		ret[loop] = ft_strdup(params[loop]);
	ret[loop] = ft_strdup(command);
	ret[++loop] = NULL;
	free_double(params);
	return (ret);
}
