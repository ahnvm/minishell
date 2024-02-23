/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:40:59 by acan              #+#    #+#             */
/*   Updated: 2024/01/30 21:54:00 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	**get_env_cpy(t_minishell *data)
{
	char	**envlist;
	char	*temp_env;
	t_env	*temp_envlist;

	envlist = NULL;
	temp_envlist = data->m_env;
	while (temp_envlist)
	{
		if (temp_envlist->var)
		{
			temp_env = malloc(1);
			temp_env = ft_strjoin(temp_env, temp_envlist->name);
			temp_env = ft_strjoin(temp_env, "=");
			temp_env = ft_strjoin(temp_env, temp_envlist->var);
			envlist = malloc_double(envlist, temp_env);
		}
		temp_envlist = temp_envlist->next;
	}
	return (envlist);
}

static void	is_file(t_parser *parser)
{
	struct stat	st;

	if (stat(parser->command[0], &st))
	{
		executer_error(parser->command[0], ": No such file or directory");
		exit(127);
	}
	if ((st.st_mode & S_IXUSR) == 0)
	{
		executer_error(parser->command[0], ": Permission denied");
		exit(126);
	}
	if (S_ISDIR(st.st_mode))
	{
		executer_error(parser->command[0], ": is a directory");
		exit(126);
	}
}

char	*path_controls(t_parser *parser, char **tmp, char **env)
{
	char		*path;

	path = NULL;
	if (parser->command[0][0] == '/' || parser->command[0][0] == '.')
	{
		is_file(parser);
		execve(parser->command[0], parser->command, env);
	}
	while (*tmp)
	{
		path = ft_strjoin(*tmp, parser->command[0]);
		if (access(path, 0) == 0)
		{
			execve(path, parser->command, env);
			exit(0);
		}
		free(path);
		tmp++;
	}
	path = parser->command[0];
	return (ft_strdup(path));
}

void	run_execve(t_minishell *data, t_parser *parser, int loop, int is_built)
{
	char	**tmp;
	char	**env;
	char	*cmd;

	tmp = data->path;
	env = get_env_cpy(data);
	dup_stdio(data, parser, loop);
	if (is_built > 1 && data->cmd_count > 1)
	{
		builtin_funcs(parser->command, data, parser, is_built);
		exit (0);
	}
	cmd = path_controls(parser, tmp, env);
	execve(cmd, parser->command, env);
	executer_error(cmd, ": command not found");
	exit(127);
}

void	executer(t_minishell *data, int loop)
{
	t_parser	*parser;
	int			is_built;

	is_built = 0;
	open_pipes(data);
	parser = data->m_parser;
	while (parser && ++loop)
	{
		is_built = is_builtin(parser->command);
		if (parser->command)
		{
			if (is_built > 1 && data->cmd_count == 1)
				builtin_funcs(parser->command, data, parser, is_built);
			else
			{
				g_signal = 2;
				parser->pid = fork();
				if (parser->pid == 0)
					run_execve(data, parser, loop - 1, is_built);
			}
		}
		parser = parser->next;
	}
	fd_closer(data);
	wait_all(data, is_built);
}
