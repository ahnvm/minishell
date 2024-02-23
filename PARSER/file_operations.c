/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:55:34 by uarslan           #+#    #+#             */
/*   Updated: 2024/01/20 20:48:42 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static void	files_delone(t_files *file, void (*del)(void *))
{
	if (file->filename)
		del(file->filename);
	del(file);
}

static t_files	*files_last(t_files *files)
{
	if (!files)
	{
		return (NULL);
	}
	while (files->next != NULL)
	{
		files = files->next;
	}
	return (files);
}

void	files_clear(t_files **files, void (*del)(void *))
{
	t_files	*tmp;

	if (files)
	{
		while (*files)
		{
			tmp = (*files)->next;
			files_delone(*files, del);
			*files = tmp;
		}
	}
}

void	files_addback(t_files **files, t_files *new)
{
	if (!(*files))
	{
		*files = new;
		return ;
	}
	else
	{
		files_last(*files)->next = new;
	}
}

t_files	*files_new(char *filename, int re_type, int fd)
{
	t_files	*node;

	node = (t_files *)malloc(sizeof(t_files));
	if (!node)
		return (NULL);
	node->filename = filename;
	node->re_type = re_type;
	node->fd = fd;
	node->next = NULL;
	return (node);
}
