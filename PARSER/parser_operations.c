/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:55:34 by uarslan           #+#    #+#             */
/*   Updated: 2024/01/30 16:58:13 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	parser_delone(t_parser *parser, void (*del)(void *))
{
	int	i;

	i = 0;
	if (parser->command)
	{
		while (parser->command[i])
		{
			del(parser->command[i]);
			i++;
		}
		del(parser->command);
	}
	if (parser->file)
	{
		files_clear(&(parser->file), free);
	}
	if (parser->heredoc)
		del(parser->heredoc);
	del(parser);
}

void	parser_clear(t_parser **parser, void (*del)(void *))
{
	t_parser	*tmp;

	if (parser)
	{
		while (*parser)
		{
			tmp = (*parser)->next;
			parser_delone(*parser, del);
			*parser = tmp;
		}
	}
}

static t_parser	*parser_last(t_parser *parser)
{
	if (!parser)
	{
		return (NULL);
	}
	while (parser->next != NULL)
	{
		parser = parser->next;
	}
	return (parser);
}

void	parser_addback(t_parser **parser, t_parser *new)
{
	if (!(*parser))
	{
		*parser = new;
		return ;
	}
	else
	{
		parser_last(*parser)->next = new;
	}
}

t_parser	*parser_new(void)
{
	t_parser	*node;

	node = (t_parser *)malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	node->command = 0;
	node->heredoc = 0;
	node->infile = 0;
	node->outfile = 1;
	node->file = 0;
	node->pid = -1;
	node->next = NULL;
	return (node);
}
