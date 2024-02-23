/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:16:39 by acan              #+#    #+#             */
/*   Updated: 2024/01/31 15:13:49 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	env_print(t_minishell *data, t_parser *prs)
{
	t_env	*tmp;

	tmp = data->m_env;
	while (tmp)
	{
		write(prs->outfile, tmp->name, ft_strlen(tmp->name));
		write(prs->outfile, "=", 1);
		write(prs->outfile, tmp->var, ft_strlen(tmp->var));
		write(prs->outfile, "\n", 1);
		tmp = tmp->next;
	}
	data->errorcode = 0;
}

void	del_same_node_env(char *cmd, t_env *env)
{
	t_env	*tmp_env;
	t_env	*tmp_node;
	char	*sub;

	tmp_env = env;
	sub = ft_substr(cmd, 0, env_equals(cmd));
	while (tmp_env->next)
	{
		if (!ft_strcmp(tmp_env->next->name, sub))
		{
			tmp_node = tmp_env->next;
			if (tmp_env->next->next != NULL)
				tmp_env->next = tmp_env->next->next;
			else
				tmp_env->next = NULL;
			env_delone(tmp_node, free);
			break ;
		}
		tmp_env = tmp_env->next;
	}
	free(sub);
}

static void	find_same_node_exp(t_export *tmp_exp, char *sub)
{
	t_export	*tmp_node;
	char		*ex_node;

	while (tmp_exp->next)
	{
		ex_node = ft_substr(tmp_exp->next->content, 11,
				env_equals(tmp_exp->next->content + 11));
		if (!ft_strcmp(ex_node, sub))
		{
			tmp_node = tmp_exp->next;
			if (tmp_exp->next->next != NULL)
				tmp_exp->next = tmp_exp->next->next;
			else
				tmp_exp->next = NULL;
			export_delone(tmp_node, free);
			free(ex_node);
			break ;
		}
		free(ex_node);
		tmp_exp = tmp_exp->next;
	}
}

void	del_same_node_exp(char *cmd, t_export **exp)
{
	t_export	**tmp_exp;
	t_export	*tmp_node;
	char		*sub;
	char		*ex_node;

	tmp_exp = exp;
	sub = ft_substr(cmd, 0, env_equals(cmd));
	ex_node = ft_substr((*tmp_exp)->content, 11, env_equals((*tmp_exp)->content
				+ 11));
	if (!ft_strcmp(ex_node, sub))
	{
		tmp_node = (*tmp_exp);
		if ((*tmp_exp)->next != NULL)
		{
			(*tmp_exp) = (*tmp_exp)->next;
		}
		else
			(*tmp_exp) = NULL;
		export_delone(tmp_node, free);
	}
	else
		find_same_node_exp((*tmp_exp), sub);
	free(ex_node);
	free(sub);
}

void	unset_env_export(char **cmd, t_minishell *data, t_export *exp,
		t_env *env)
{
	int	loop;

	loop = 1;
	while (cmd[loop])
	{
		if (!ft_strcmp(cmd[loop], "PATH"))
		{
			if (data->path)
				free_double(data->path);
			data->path = NULL;
		}
		del_same_node_env(cmd[loop], env);
		del_same_node_exp(cmd[loop], &exp);
		loop++;
	}
	data->errorcode = 0;
}
