/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uarslan <uarslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:58:20 by acan              #+#    #+#             */
/*   Updated: 2024/01/29 23:13:17 by uarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	remove_quotes(t_minishell *data, char quote)
{
	t_expander	*tmp;
	char		*ret;
	int			loop;

	tmp = data->m_expander;
	while (tmp)
	{
		loop = 0;
		ret = ft_calloc(1, 1);
		while (tmp->command[loop])
		{
			if (quote == 0 && (tmp->command[loop] == S_QUOTE
					|| tmp->command[loop] == D_QUOTE))
				quote = tmp->command[loop];
			else if (quote == tmp->command[loop])
				quote = 0;
			else
				ret = char_to_str(ret, tmp->command[loop]);
			loop++;
		}
		free(tmp->command);
		tmp->command = ft_strdup(ret);
		free(ret);
		tmp = tmp->next;
	}
}
