/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:55:34 by uarslan           #+#    #+#             */
/*   Updated: 2024/01/13 17:31:00 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	expander_delone(t_expander *expander, void (*del)(void *))
{
	if (expander->command)
		del(expander->command);
	if (expander->prev_cmd)
		del(expander->prev_cmd);
	free(expander);
}

void	expander_clear(t_expander **expander, void (*del)(void *))
{
	t_expander	*tmp;

	if (expander)
	{
		while (*expander)
		{
			tmp = (*expander)->next;
			expander_delone(*expander, del);
			*expander = tmp;
		}
	}
}

static t_expander	*expander_last(t_expander *expander)
{
	if (!expander)
	{
		return (NULL);
	}
	while (expander->next != NULL)
	{
		expander = expander->next;
	}
	return (expander);
}

void	expander_addback(t_expander **expander, t_expander *new)
{
	if (!(*expander))
	{
		*expander = new;
		return ;
	}
	else
	{
		expander_last(*expander)->next = new;
	}
}

t_expander	*expander_new(t_lexer *lexer, char *command, int is_first)
{
	t_expander	*node;

	node = (t_expander *)malloc(sizeof(t_expander));
	if (!node)
		return (NULL);
	node->command = command;
	node->type = lexer->type;
	node->is_first = is_first;
	node->prev_cmd = NULL;
	if (is_first == -1)
		node->prev_cmd = ft_strdup(lexer->command);
	node->next = NULL;
	return (node);
}
