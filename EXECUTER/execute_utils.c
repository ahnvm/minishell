/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:29:15 by uarslan           #+#    #+#             */
/*   Updated: 2024/01/30 21:49:54 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	wait_all(t_minishell *data, int builtin)
{
	t_parser	*parser;
	int			status;

	(void) builtin;
	parser = data->m_parser;
	while (parser)
	{
		waitpid(parser->pid, &status, 0);
		data->errorcode = status / 256;
		if (parser->outfile == 2 || parser->infile == 2)
			data->errorcode = 1;
		parser = parser->next;
	}
	if (data->cmd_count > 1)
		free_double_int(data->fd);
}

void	fd_closer(t_minishell *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count - 1)
	{
		if (data->fd[i][1])
			close(data->fd[i][1]);
		if (data->fd[i][0])
			close(data->fd[i][0]);
	}
}

static void	tempfd_init(t_minishell *data, t_parser *parser, int i)
{
	if (data->m_parser == parser)
		dup2(data->fd[i][1], STDOUT_FILENO);
	else if (!parser->next)
		dup2(data->fd[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(data->fd[i - 1][0], STDIN_FILENO);
		dup2(data->fd[i][1], STDOUT_FILENO);
	}
	fd_closer(data);
}

void	dup_stdio(t_minishell *data, t_parser *parser, int i)
{
	int	fd[2];

	signal(SIGINT, interrupt_here_document);
	if (data->cmd_count > 1 && ft_strcmp(parser->command[0], "exit"))
	{
		tempfd_init(data, parser, i);
	}
	if (parser->infile == -2)
	{
		pipe(fd);
		write(fd[1], parser->heredoc, ft_strlen(parser->heredoc));
		close (fd[1]);
		if (parser->next || ft_strcmp(parser->command[0], "echo"))
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (parser->outfile >= 2)
		dup2(parser->outfile, STDOUT_FILENO);
	if (parser->infile >= 2)
		dup2(parser->infile, STDIN_FILENO);
}

void	open_pipes(t_minishell *data)
{
	int	**fd;
	int	i;

	if (data->cmd_count > 1)
	{
		fd = (int **)malloc(sizeof(int *) * (data->cmd_count));
		fd[data->cmd_count - 1] = NULL;
		i = -1;
		while (++i < data->cmd_count - 1)
			fd[i] = malloc(sizeof(int) * 2);
		data->fd = fd;
		i = -1;
		while (++i < data->cmd_count - 1)
			pipe(data->fd[i]);
	}
}
