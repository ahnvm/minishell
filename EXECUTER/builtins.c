/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uarslan <uarslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:54:56 by acan              #+#    #+#             */
/*   Updated: 2024/01/30 19:33:53 by uarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static void	exit_cmd(t_parser *prs)
{
	int	exitcode;
	int	loop;

	loop = 0;
	if (!prs->command[1])
		exit (0);
	else
	{
		while (prs->command[1][loop])
		{
			if (!ft_isdigit(prs->command[1][loop]))
			{
				write (prs->outfile, "minikshell: exit: ", 19);
				write (prs->outfile, prs->command[1],
					ft_strlen(prs->command[1]));
				write (prs->outfile, ": numeric argument required\n", 29);
				exit (255);
			}
			loop++;
		}
		exitcode = ft_atoi(prs->command[1]);
		exit (exitcode);
	}
}

void	builtin_funcs(char **command, t_minishell *data, t_parser *prs,
		int builtincode)
{
	if (builtincode == 60)
		exit_cmd(prs);
	else if (builtincode == 61)
		env_print(data, prs);
	else if (builtincode == 62)
		export_env(data, prs);
	else if (builtincode == 63)
		echo_cmd(data, prs);
	else if (builtincode == 64)
		unset_env_export(command, data, data->m_export, data->m_env);
	else if (builtincode == 65)
		cd_cmd(data, prs, command);
	else if (builtincode == 66)
		pwd_cmd(data, prs);
}

int	is_builtin(char **command)
{
	if (!command)
		return (69);
	if (!ft_strcmp(command[0], "exit"))
		return (60);
	else if (!ft_strcmp(command[0], "env") || !ft_strcmp(command[0], "ENV"))
		return (61);
	else if (!ft_strcmp(command[0], "export"))
		return (62);
	else if (!ft_strcmp(command[0], "echo"))
		return (63);
	else if (!ft_strcmp(command[0], "unset"))
		return (64);
	else if (!ft_strcmp(command[0], "cd"))
		return (65);
	else if (!ft_strcmp(command[0], "pwd"))
		return (66);
	return (0);
}
