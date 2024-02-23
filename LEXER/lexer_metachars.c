/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_metachars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <ahmetabdullahcan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:28:55 by acan              #+#    #+#             */
/*   Updated: 2024/01/05 20:52:56 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	metachar_check(char c)
{
	if (c == PIPE)
		return (PIPE_NUM);
	else if (c == IF)
		return (IF_NUM);
	else if (c == OF)
		return (OF_NUM);
	else
		return (TEXT_NUM);
}

int	metastr_check(char *str)
{
	int	loop;

	loop = 0;
	while (str[loop])
		if (metachar_check(str[loop++]))
			return (0);
	return (1);
}

static void	sub_not_meta(char *str, int *loop)
{
	char	quote;

	while (str[*loop] && !(metachar_check(str[*loop])))
	{
		if (str[*loop] == '\'' || str[*loop] == '"')
		{
			quote = str[*loop];
			(*loop)++;
			while (str[*loop] && str[*loop] != quote)
				(*loop)++;
		}
		(*loop)++;
	}
}

static void	sub_meta(char *str, t_list **ret)
{
	int	loop;
	int	start;

	loop = 0;
	while (str[loop])
	{
		start = loop;
		if (metachar_check(str[loop]))
			while (str[loop] && str[loop] == str[start])
				loop++;
		else
			sub_not_meta(str, &loop);
		ft_lstadd_back(ret, ft_lstnew(ft_substr(str, start, loop - start)));
	}
	free(str);
}

t_list	*meta_seperate(t_list *lst)
{
	t_list	*ret;
	t_list	*temp;

	ret = NULL;
	temp = lst;
	while (temp)
	{
		if (metastr_check(temp->content))
			ft_lstadd_back(&ret, ft_lstnew(temp->content));
		else
		{
			sub_meta(temp->content, &ret);
		}
		lst = temp;
		temp = temp->next;
		free(lst);
	}
	return (ret);
}
