/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:42:59 by acan              #+#    #+#             */
/*   Updated: 2024/01/29 18:52:13 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	pwd_cmd(t_minishell *data, t_parser *prs)
{
	char	pwd[256];

	write(prs->outfile, getcwd(pwd, 256), ft_strlen(pwd));
	write(prs->outfile, "\n", 1);
	data->errorcode = 0;
}
