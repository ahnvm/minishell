/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uarslan <uarslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 23:08:20 by uarslan           #+#    #+#             */
/*   Updated: 2024/01/30 13:21:00 by uarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	executer_error(char *cmd, char *msg)
{
	write(2, "minikshell$: ", 14);
	write(2, cmd, ft_strlen(cmd));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	file_errors(char *prev_cmd, char *error, int *fd, t_minishell *data)
{
	write(2, "minikshell$: ", 14);
	write(2, prev_cmd, ft_strlen(prev_cmd));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	*fd = 2;
	data->errorcode = 1;
}

void	expander_errors(char *error)
{
	write(2, "minikshell$: ", 14);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

void	cd_errors(t_minishell *data, int errorcode, char *file)
{
	char	*errormsg;

	errormsg = ft_strjoin("cd: ", file);
	if (errorcode == 1)
		errormsg = my_strjoin(errormsg, ": Permisson denied");
	else if (errorcode == 2)
		errormsg = my_strjoin(errormsg, ": Not a directory");
	else if (errorcode == 3)
		errormsg = my_strjoin(errormsg, ": No such file or directory");
	expander_errors(errormsg);
	free(errormsg);
	data->errorcode = 1;
}
