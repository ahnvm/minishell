/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_inits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uarslan <uarslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:47:20 by acan              #+#    #+#             */
/*   Updated: 2024/01/20 15:08:12 by uarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static void	dir_check(char *fn, t_parser *prs, t_minishell *data)
{
	struct stat	st;
	char		*path;
	int			loop;
	int			*fd;

	fd = &(prs->outfile);
	if (!stat(fn, &st) && S_ISDIR(st.st_mode))
		file_errors(fn, "is a directory", fd, data);
	else if (stat(fn, &st) != 0)
	{
		loop = ft_strlen(fn);
		while (--loop >= 0 && fn[loop] && fn[loop] != '/')
			;
		path = ft_substr(fn, 0, loop + 1);
		if (stat(path, &st) != 0 && ft_strchr(path, '/'))
			file_errors(fn, "No such file or directory", fd, data);
		else if (stat(path, &st) == 0)
			if (S_ISDIR(st.st_mode))
				if (!(ft_strcmp(path, "/")) || !(ft_strcmp(path, "/Users/")))
					file_errors(fn, "Permisson denied", fd, data);
		free(path);
	}
}

int	outfile_fd(t_expander *ex, t_parser *prs, t_minishell *data)
{
	char		*fn;
	int			*fd;

	fd = &(prs->outfile);
	fn = ex->next->command;
	if (*ex->next->command == '\\')
		fn = ex->next->command + 1;
	dir_check(fn, prs, data);
	if (*fd != 2)
	{
		if (ex->type == OF_NUM)
			*fd = open(fn, O_CREAT | O_RDWR | O_TRUNC, 0777);
		else if (ex->type == DOF_NUM)
			*fd = open(fn, O_CREAT | O_RDWR | O_APPEND, 0777);
	}
	return (*fd);
}
