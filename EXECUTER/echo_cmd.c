/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uarslan <uarslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:26:02 by acan              #+#    #+#             */
/*   Updated: 2024/01/30 18:18:15 by uarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static void	newline_check(char **cmd, int *loop, int *nlflag)
{
	int	inloop;

	while (cmd[*loop])
	{
		inloop = 0;
		if (cmd[*loop][inloop] == '-')
		{
			inloop++;
			if (cmd[*loop][inloop] == ' ' || cmd[*loop][inloop] == '\0')
				return ;
			while (cmd[*loop][inloop] == 'n')
				inloop++;
			if (cmd[*loop][inloop] == ' ' || cmd[*loop][inloop] == '\0')
				*nlflag = 1;
			else
				return ;
		}
		else
			return ;
		(*loop)++;
	}
}

void	echo_cmd(t_minishell *data, t_parser *prs)
{
	int	loop;
	int	nlflag;

	loop = 1;
	nlflag = 0;
	newline_check(prs->command, &loop, &nlflag);
	while (prs->command[loop])
	{
		write(prs->outfile, prs->command[loop], ft_strlen(prs->command[loop]));
		loop++;
		if (prs->command[loop])
			write(prs->outfile, " ", 1);
	}
	if (nlflag == 0)
	{
		write(prs->outfile, "\n", 1);
	}
	data->errorcode = 0;
}
