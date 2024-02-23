/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:05:20 by acan              #+#    #+#             */
/*   Updated: 2024/01/16 18:34:46 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	export_delone(t_export *export, void (*del)(void *))
{
	if (export->content)
		del(export->content);
	free(export);
}

void	export_clear(t_export **export, void (*del)(void *))
{
	t_export	*tmp;

	if (export)
	{
		while (*export)
		{
			tmp = (*export)->next;
			export_delone(*export, del);
			*export = tmp;
		}
	}
}

static t_export	*export_last(t_export *export)
{
	if (!export)
	{
		return (NULL);
	}
	while (export->next != 0)
	{
		export = export->next;
	}
	return (export);
}

void	export_addback(t_export **export, t_export *new)
{
	if (!*export)
	{
		*export = new;
		return ;
	}
	else
	{
		export_last(*export)->next = new;
	}
}

t_export	*export_new(char *content)
{
	t_export	*node;

	node = (t_export *)malloc(sizeof(t_export));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
