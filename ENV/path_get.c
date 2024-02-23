/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:02:49 by acan              #+#    #+#             */
/*   Updated: 2024/01/17 20:05:09 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static void	split_path(char *path, t_minishell *data)
{
	char	**splitted_path;
	char	*tmp;
	int		loop;

	loop = 0;
	splitted_path = ft_split(path, ':');
	while (splitted_path[loop])
		loop++;
	data->path = malloc(sizeof(char *) * (loop + 1));
	data->path[loop] = NULL;
	loop = 0;
	while (splitted_path[loop])
	{
		tmp = ft_strjoin(splitted_path[loop], "/");
		free(splitted_path[loop]);
		data->path[loop] = tmp;
		loop++;
	}
	free(splitted_path);
}

void	path_get(t_env *m_env, t_minishell *data)
{
	t_env	*tmp;

	tmp = (m_env);
	while (tmp)
	{
		if (!(ft_strncmp(tmp->name, "PATH", ft_strlen(tmp->name))))
		{
			split_path(tmp->var, data);
			break ;
		}
		tmp = tmp->next;
	}
}
