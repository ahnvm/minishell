/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:07:01 by acan              #+#    #+#             */
/*   Updated: 2024/01/31 14:51:34 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static void	print_export(t_minishell *data, t_export *export, t_parser *prs)
{
	t_export	*tmp;

	tmp = export;
	while (tmp)
	{
		write(prs->outfile, tmp->content, ft_strlen(tmp->content));
		write(prs->outfile, "\n", 1);
		tmp = tmp->next;
	}
	data->errorcode = 0;
}

void	add_env_export(char *cmd, t_minishell *data)
{
	char	*name;
	char	*var;
	char	*nullstr;
	char	*newstr;

	if (!ft_strchr(cmd, '='))
		export_set(cmd, data);
	else
	{
		name = ft_substr(cmd, 0, env_equals(cmd));
		var = ft_substr(cmd, env_equals(cmd) + 1, ft_strlen(cmd));
		env_addback(&(data->m_env), env_new(name, var));
		if (var[0] == '\0')
		{
			nullstr = ft_strjoin(cmd, "\"\"");
			newstr = ft_strjoin("declare -x ", nullstr);
			free(nullstr);
			export_addback(&(data->m_export), export_new(newstr));
		}
		else
			combine_with_quotes(cmd, data);
	}
	sort_export(data->m_export);
	data->errorcode = 0;
}

static int	equals_check(char **cmd, int errorpos, t_minishell *data)
{
	while (cmd[errorpos])
	{
		if (!ft_isalpha(cmd[errorpos][0]))
		{
			write(2, "minikshell$: export: '", 23);
			write(2, cmd[errorpos], ft_strlen(cmd[errorpos]));
			write(2, "': not a valid identifier\n", 27);
			data->errorcode = 1;
			return (1);
		}
		errorpos++;
	}
	return (0);
}

void	export_env(t_minishell *data, t_parser *prs)
{
	t_env	*tmp;
	int		loop;

	loop = 1;
	tmp = data->m_env;
	if (prs->command[1] == NULL)
		print_export(data, (data->m_export), prs);
	else if (equals_check(prs->command, 0, data))
		return ;
	else
	{
		while (prs->command[loop])
		{
			del_same_node_env(prs->command[loop], data->m_env);
			del_same_node_exp(prs->command[loop], &data->m_export);
			add_env_export(prs->command[loop], data);
			if (!ft_strncmp("PATH=", prs->command[loop++], 5))
			{
				if (data->path)
					free_double(data->path);
				data->path = NULL;
				path_get(data->m_env, data);
			}
		}
	}
}
