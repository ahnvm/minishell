/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:11:13 by acan              #+#    #+#             */
/*   Updated: 2024/01/16 19:11:15 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	combine_with_quotes(char *cmd, t_minishell *data)
{
	char	*quotesvar;
	char	*last;
	char	*name;
	char	*var;

	name = ft_substr(cmd, 0, env_equals(cmd));
	var = ft_substr(cmd, env_equals(cmd) + 1, ft_strlen(cmd));
	quotesvar = ft_strjoin("=\"", var);
	quotesvar = my_strjoin(quotesvar, "\"");
	last = ft_strjoin("declare -x ", name);
	free (name);
	free (var);
	last = my_strjoin(last, quotesvar);
	free(quotesvar);
	export_addback(&(data->m_export), export_new(last));
}

void	sort_export(t_export *ex)
{
	t_export	*export1;
	t_export	*export2;
	char		*tmp;

	export1 = ex;
	tmp = 0;
	while (export1)
	{
		export2 = export1->next;
		while (export2)
		{
			if (ft_strcmp(export1->content, export2->content) > 0)
			{
				tmp = export1->content;
				export1->content = export2->content;
				export2->content = tmp;
			}
			export2 = export2->next;
		}
		export1 = export1->next;
	}
}

void	export_set(char *env_node, t_minishell *data)
{
	char	*to_add;

	to_add = ft_strjoin("declare -x ", env_node);
	export_addback(&(data->m_export), export_new((to_add)));
}

size_t	env_equals(char *env_node)
{
	size_t	loop;

	loop = 0;
	while (env_node[loop] && env_node[loop] != '=')
		loop++;
	return (loop);
}

t_env	*env_get(char **env, t_minishell *data)
{
	t_env	*m_env;
	size_t	loop;
	char	*name;
	char	*var;

	loop = 0;
	m_env = NULL;
	while (env[loop])
	{
		name = ft_substr(env[loop], 0, env_equals(env[loop]));
		var = ft_substr(env[loop], env_equals(env[loop]) + 1,
				ft_strlen(env[loop]));
		combine_with_quotes(env[loop], data);
		env_addback(&m_env, env_new(name, var));
		loop++;
	}
	sort_export(data->m_export);
	return (m_env);
}
