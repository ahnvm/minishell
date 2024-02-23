/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:02:07 by acan              #+#    #+#             */
/*   Updated: 2024/01/31 14:44:54 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	oldpwd_set(t_minishell *data)
{
	t_env	*tmp;
	char	*olddir;

	tmp = data->m_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PWD"))
		{
			olddir = ft_strjoin("OLDPWD=", tmp->var);
			del_same_node_env("OLDPWD=", data->m_env);
			del_same_node_exp("OLDPWD=", &data->m_export);
			add_env_export(olddir, data);
			data->errorcode = 0;
			free(olddir);
		}
		tmp = tmp->next;
	}
}

static void	upper_dir(t_minishell *data, char *cwd)
{
	t_env	*tmp;
	char	*newdir;
	char	*slash;

	tmp = data->m_env;
	slash = ft_substr(cwd, 0, last_slash(cwd));
	newdir = ft_strjoin("PWD=", slash);
	oldpwd_set(data);
	if (isdir(slash))
		return (cd_errors(data, isdir(slash), slash));
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PWD"))
		{
			del_same_node_env("PWD=", data->m_env);
			del_same_node_exp("PWD=", &data->m_export);
			add_env_export(newdir, data);
			break ;
		}
		tmp = tmp->next;
	}
	free(slash);
	free(newdir);
	data->errorcode = 0;
}

static void	cd_to_dir(t_minishell *data)
{
	t_env	*tmp;
	char	*newdir;
	char	cwd[256];

	tmp = data->m_env;
	oldpwd_set(data);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PWD"))
		{
			oldpwd_set(data);
			newdir = ft_strjoin("PWD=", getcwd(cwd, 256));
			del_same_node_env("PWD=", data->m_env);
			del_same_node_exp("PWD=", &data->m_export);
			add_env_export(newdir, data);
			free(newdir);
			data->errorcode = 0;
			return ;
		}
		tmp = tmp->next;
	}
}

static void	go_homedir(t_minishell *data)
{
	t_env	*tmp;
	char	*homedir;

	tmp = data->m_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "HOME"))
		{
			oldpwd_set(data);
			homedir = ft_strjoin("PWD=", tmp->var);
			if (isdir(tmp->var))
				return (cd_errors(data, isdir(tmp->var), tmp->var));
			del_same_node_env("PWD=", data->m_env);
			del_same_node_exp("PWD=", &data->m_export);
			add_env_export(homedir, data);
			free(homedir);
			data->errorcode = 0;
			return ;
		}
		tmp = tmp->next;
	}
	expander_errors("cd: HOME not set");
	data->errorcode = 1;
}

void	cd_cmd(t_minishell *data, t_parser *prs, char **cmd)
{
	char	cwd[256];

	(void)prs;
	if (!cmd[1])
		go_homedir(data);
	else if (!ft_strcmp(cmd[1], ".."))
		upper_dir(data, getcwd(cwd, 256));
	else if (!isdir(cmd[1]))
		cd_to_dir(data);
	else if (!ft_strcmp(cmd[1], "-"))
		go_oldpwd(data);
	else
		cd_errors(data, isdir(cmd[1]), cmd[1]);
}
