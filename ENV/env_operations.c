/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:05:20 by acan              #+#    #+#             */
/*   Updated: 2024/01/17 20:06:18 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	env_delone(t_env *env, void (*del)(void *))
{
	if (env->name)
		del(env->name);
	if (env->var)
		del(env->var);
	free(env);
}

void	env_clear(t_env **env, void (*del)(void *))
{
	t_env	*tmp;

	if (env)
	{
		while (*env)
		{
			tmp = (*env)->next;
			env_delone(*env, del);
			*env = tmp;
		}
	}
}

static t_env	*env_last(t_env *env)
{
	if (!env)
	{
		return (NULL);
	}
	while (env->next != 0)
	{
		env = env->next;
	}
	return (env);
}

void	env_addback(t_env **env, t_env *new)
{
	if (!*env)
	{
		*env = new;
		return ;
	}
	else
	{
		env_last(*env)->next = new;
	}
}

t_env	*env_new(char *name, char *var)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = name;
	node->var = var;
	node->next = NULL;
	return (node);
}
