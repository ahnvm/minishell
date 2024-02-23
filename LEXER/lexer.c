/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uarslan <uarslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:25:00 by acan              #+#    #+#             */
/*   Updated: 2024/01/29 18:08:56 by uarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static t_list	*seperate_spaces(t_minishell *data, int loop, int start,
		int quotes)
{
	t_list	*lst;

	lst = NULL;
	while (data->line && data->line[loop])
	{
		start = loop;
		if (is_whitespace(data->line[loop]))
			while (data->line[loop] && is_whitespace(data->line[loop]))
				loop++;
		else
		{
			while (data->line[loop] && !(is_whitespace(data->line[loop])))
			{
				quotes = data->line[loop];
				if (data->line[loop] == '"' || data->line[loop] == '\'')
					while (data->line[++loop] && data->line[loop] != quotes)
						;
				loop++;
			}
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(data->line, start, loop
						- start)));
		}
	}
	return (lst);
}

static int	is_quotes_closed(char *line, int *pos, char c)
{
	(*pos)++;
	if (line[*pos] == 0)
		return (1);
	while (line[*pos])
	{
		if (line[*pos] == c)
			return (0);
		(*pos)++;
	}
	return (1);
}

static int	quote_control(t_minishell *data)
{
	int		loop;
	char	quote;

	loop = 0;
	while (data->line && data->line[loop])
	{
		if (data->line[loop] == '"' || data->line[loop] == '\'')
		{
			quote = data->line[loop];
			if (is_quotes_closed(data->line, &loop, quote))
			{
				data->errorcode = 524;
				write(2, "minikshell$: Incorrect usage of quotes\n", 39);
				return (1);
			}
			else
				while (data->line[loop] && is_whitespace(data->line[loop]))
					loop++;
		}
		loop++;
	}
	return (0);
}

void	lexer(t_minishell *data)
{
	t_list	*space_seperated;
	t_list	*meta_seperated;

	if (quote_control(data))
		return ;
	space_seperated = seperate_spaces(data, 0, 0, 0);
	meta_seperated = meta_seperate(space_seperated);
	add_lexer(meta_seperated, data);
	if (syntax_check(data))
		return ;
	expander(data);
}
