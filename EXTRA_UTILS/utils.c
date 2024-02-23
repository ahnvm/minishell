/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:59:22 by acan              #+#    #+#             */
/*   Updated: 2024/01/29 18:02:51 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	free_double(char **str)
{
	int	loop;

	loop = 0;
	if (str)
	{
		while (str[loop])
			free(str[loop++]);
		free(str);
	}
}

char	*my_strjoin(char *s1, char *s2)
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
	return (tmp);
}

char	*char_to_str(char *s, char c)
{
	char	*tmp;
	size_t	i;

	if (!s || !c)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (tmp == NULL)
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		tmp[i] = s[i];
	tmp[i] = c;
	tmp[i + 1] = '\0';
	if (s)
		free(s);
	return (tmp);
}
