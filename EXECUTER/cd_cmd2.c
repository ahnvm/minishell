/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:50:07 by acan              #+#    #+#             */
/*   Updated: 2024/01/31 14:40:26 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	go_oldpwd(t_minishell *data)
{
	t_env	*tmp;
	char	*homedir;

	tmp = data->m_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "OLDPWD"))
		{
			homedir = ft_strjoin("PWD=", tmp->var);
			if (isdir(tmp->var))
				return (cd_errors(data, isdir(tmp->var), tmp->var));
			oldpwd_set(data);
			del_same_node_env("PWD=", data->m_env);
			del_same_node_exp("PWD=", &data->m_export);
			add_env_export(homedir, data);
			free(homedir);
			data->errorcode = 0;
			return ;
		}
		tmp = tmp->next;
	}
	expander_errors("cd: OLDPWD not set");
	data->errorcode = 1;
}

int	isdir(const char *filename)
{
	struct stat	file;
	int			is_folder;

	if (filename)
	{
		stat(filename, &file);
		if (!access(filename, F_OK))
		{
			is_folder = S_ISREG(file.st_mode);
			if (is_folder == 0)
			{
				is_folder = chdir(filename);
				if (is_folder == 0)
					return (0);
				else
					return (1);
			}
			else
				return (2);
		}
		else
			return (3);
	}
	return (4);
}

size_t	last_slash(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	while (len > -1)
	{
		if (filename[len] == '/')
		{
			if (len != 0)
				return (len);
			else
				return (len + 1);
		}
		len--;
	}
	return (len);
}
