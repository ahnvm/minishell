/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uarslan <uarslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:15:13 by uarslan           #+#    #+#             */
/*   Updated: 2024/01/30 18:52:44 by uarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static void	pipe_error(t_minishell *data)
{
	expander_errors("syntax error");
	data->errorcode = 524;
}

static int	pipe_counter(t_minishell *data)
{
	t_expander	*temp;
	int			pipe_count;

	temp = data->m_expander;
	pipe_count = 1;
	if (temp->type == PIPE_NUM)
		return (-1);
	while (temp)
	{
		if (temp->type == PIPE_NUM)
			pipe_count++;
		if (temp->type != TEXT_NUM && !temp->next)
			return (-1);
		temp = temp->next;
	}
	data->cmd_count = pipe_count;
	return (pipe_count);
}

static char	**prsjoin(char *newcmd, char **prscmd)
{
	int		loop;
	int		size;
	char	**newprscmd;

	loop = 0;
	size = 0;
	while (prscmd && prscmd[size])
		size++;
	newprscmd = malloc(sizeof(char *) * (size + 2));
	newprscmd[size + 1] = 0;
	while (prscmd && prscmd[loop])
	{
		newprscmd[loop] = prscmd[loop];
		loop++;
	}
	newprscmd[loop] = newcmd;
	free(prscmd);
	return (newprscmd);
}

static void	init_parser(t_minishell *data, t_expander **expander,
		t_parser **parser, int *fd)
{
	while ((*expander) && (*expander)->type != PIPE_NUM)
	{
		if ((*expander)->type == TEXT_NUM)
			(*parser)->command = prsjoin(ft_strdup((*expander)->command),
					(*parser)->command);
		else if ((*expander)->type != TEXT_NUM && (*expander)->next
			&& file_controls(expander, *parser, data, fd) == 2)
		{
			if ((*expander) && (*expander)->type != PIPE_NUM)
				(*expander) = (*expander)->next;
			if ((*expander) && (*expander)->type != PIPE_NUM)
				(*expander) = (*expander)->next;
		}
		if ((*expander) && (*expander)->type != PIPE_NUM)
			(*expander) = (*expander)->next;
	}
}

void	parser(t_minishell *data)
{
	t_expander	*ex;
	t_parser	*pars;
	int			pipe_count;
	int			fd;

	fd = 0;
	pipe_count = pipe_counter(data);
	if (pipe_count == -1)
		return (pipe_error(data));
	while (pipe_count--)
		parser_addback(&data->m_parser, parser_new());
	heredoc_handle(data);
	ex = data->m_expander;
	pars = data->m_parser;
	if (!data->m_parser)
		return ;
	while (ex)
	{
		init_parser(data, &ex, &pars, &fd);
		if (pars)
			pars = pars->next;
		if (ex)
			ex = ex->next;
	}
	executer(data, 0);
}
