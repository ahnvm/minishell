/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uarslan <uarslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:32:52 by acan              #+#    #+#             */
/*   Updated: 2024/01/30 17:15:49 by uarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static void	heredoc_child(t_expander *expander, int fd[2])
{
	char	*input;
	char	*content;

	close(fd[0]);
	signal(SIGINT, interrupt_here_document);
	content = ft_calloc(1, 1);
	while (1)
	{
		input = readline("> ");
		if (!input || !(ft_strcmp(input, expander->next->command)))
		{
			write(fd[1], content, ft_strlen(content));
			if (content)
				free(content);
			content = NULL;
			if (input)
				free(input);
			input = NULL;
			exit(0);
		}
		content = my_strjoin(content, input);
		content = char_to_str(content, '\n');
		free(input);
		input = NULL;
	}
}

static int	heredoc_parent(t_parser *parser, int fd[2], pid_t pid)
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	if (status == 0)
	{
		if (parser->heredoc)
			free(parser->heredoc);
		parser->heredoc = gnl(fd[0]);
		close(fd[0]);
		if (!parser->heredoc)
			exit(EXIT_FAILURE);
	}
	else
	{
		return (1);
	}
	return (0);
}

static int	heredoc_exec(t_expander *expander, t_parser *parser, int fd[2])
{
	pid_t	pid;
	int		ret;

	g_signal = 2;
	ret = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
		heredoc_child(expander, fd);
	else
		ret = heredoc_parent(parser, fd, pid);
	close(fd[1]);
	return (ret);
}

void	heredoc_handle(t_minishell *data)
{
	t_expander	*tmp_exp;
	t_parser	*tmp_pars;
	int			fd[2];

	tmp_exp = data->m_expander;
	tmp_pars = data->m_parser;
	while (tmp_exp)
	{
		while (tmp_exp && tmp_exp->type != PIPE_NUM)
		{
			if (tmp_exp->type == HEREDOC)
			{
				if (heredoc_exec(tmp_exp, tmp_pars, fd))
				{
					parser_clear(&(data->m_parser), free);
					data->m_parser = NULL;
					return ;
				}
			}
			tmp_exp = tmp_exp->next;
		}
		if (tmp_exp)
			tmp_exp = tmp_exp->next;
		tmp_pars = tmp_pars->next;
	}
}
