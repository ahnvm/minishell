/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:52:44 by acan              #+#    #+#             */
/*   Updated: 2024/01/14 16:28:49 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	quote_check(char *str)
{
	if (str[0] == '\'' || str[0] == '"')
		return (str[0]);
	return (0);
}

int	metachar_counter(char *cmd)
{
	if (ft_strlen(cmd) == 1)
	{
		if (cmd[0] == IF)
			return (IF_NUM);
		else if (cmd[0] == OF)
			return (OF_NUM);
		else if (cmd[0] == PIPE)
			return (PIPE_NUM);
	}
	else if (ft_strlen(cmd) == 2)
	{
		if (!(ft_strncmp(cmd, DIF, 2)))
			return (HEREDOC);
		else if (!(ft_strncmp(cmd, DOF, 2)))
			return (DOF_NUM);
	}
	return (-1);
}

int	syntax_check(t_minishell *data)
{
	t_lexer	*tmp;
	int		count;

	tmp = data->m_lexer;
	while (tmp)
	{
		if (tmp->type != TEXT_NUM)
			tmp->type = metachar_counter(tmp->command);
		if (tmp->type == -1)
		{
			write (2, "minikshell$: Syntax error near unexpected token '", 50);
			count = ft_strlen(tmp->command) - 1;
			while (count--)
				write (2, &tmp->command[0], 1);
			write (2, "'\n", 2);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	add_lexer(t_list *list, t_minishell *data)
{
	t_list	*tmp;
	char	*str;

	tmp = list;
	while (tmp)
	{
		str = tmp->content;
		if (!(metachar_check(str[0])) || quote_check(tmp->content))
			lexer_addback(&(data->m_lexer), lexer_new(tmp->content, TEXT_NUM));
		else
		{
			lexer_addback(&(data->m_lexer), lexer_new(tmp->content,
					metachar_check(str[0])));
		}
		list = tmp;
		tmp = tmp->next;
		free(list->content);
		free(list);
	}
}
