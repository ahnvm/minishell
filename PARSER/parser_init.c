/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uarslan <uarslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:29:19 by acan              #+#    #+#             */
/*   Updated: 2024/01/30 17:55:15 by uarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static int	infile_fd(t_expander *ex, t_parser *prs, t_minishell *data)
{
	struct stat	st;
	char		*fn;
	int			*fd;

	fd = &(prs->infile);
	if (ex->type == IF_NUM)
	{
		fn = ex->next->command;
		if (ex->prev_cmd)
			fn = ex->prev_cmd;
		else if (*(ex->next->command) == '\\')
			fn = ex->next->command + 1;
		if (stat(ex->next->command, &st) != 0)
			file_errors(fn, "No such file or directory", fd, data);
		else
			*fd = open(fn, O_RDONLY, 0777);
	}
	if (ex->type == HEREDOC)
		*fd = -2;
	return (*fd);
}

int	file_controls(t_expander **ex, t_parser *prs, t_minishell *data,
		int *fd)
{
	if (*fd == 2)
		return (0);
	else if ((*ex)->next->is_first == -1 && (*ex)->type != HEREDOC)
		file_errors((*ex)->next->prev_cmd, "ambigious redirect", fd, data);
	else if ((*ex)->type == IF_NUM || (*ex)->type == HEREDOC)
		*fd = infile_fd(*ex, prs, data);
	else if ((*ex)->type == OF_NUM || (*ex)->type == DOF_NUM)
		*fd = outfile_fd(*ex, prs, data);
	files_addback(&(prs->file), files_new(ft_strdup((*ex)->next->command),
			(*ex)->type, *fd));
	(*ex) = (*ex)->next;
	return (*fd);
}
