/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:23:23 by acan              #+#    #+#             */
/*   Updated: 2024/01/14 18:13:52 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	lexer_delone(t_lexer *lexer, void (*del)(void *))
{
	if (lexer->command)
		del(lexer->command);
	free(lexer);
}

void	lexer_clear(t_lexer **lexer, void (*del)(void *))
{
	t_lexer	*tmp;

	if (lexer)
	{
		while (*lexer)
		{
			tmp = (*lexer)->next;
			lexer_delone(*lexer, del);
			*lexer = tmp;
		}
	}
}

static t_lexer	*lexer_last(t_lexer *lexer)
{
	if (!lexer)
	{
		return (NULL);
	}
	while (lexer->next != 0)
	{
		lexer = lexer->next;
	}
	return (lexer);
}

void	lexer_addback(t_lexer **lexer, t_lexer *new)
{
	if (!(*lexer))
	{
		*lexer = new;
		return ;
	}
	else
	{
		lexer_last(*lexer)->next = new;
	}
}

t_lexer	*lexer_new(char *command, int type)
{
	t_lexer	*node;

	node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->command = ft_strdup(command);
	node->type = type;
	node->next = NULL;
	return (node);
}
