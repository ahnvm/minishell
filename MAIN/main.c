/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:48:31 by acan              #+#    #+#             */
/*   Updated: 2024/01/31 14:51:24 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static void	routine(t_minishell *data)
{
	while (1)
	{
		data->m_lexer = NULL;
		data->m_expander = NULL;
		data->m_parser = NULL;
		data->line = NULL;
		data->line = readline("minikshell$ ");
		if (data->line && *data->line)
			add_history(data->line);
		if (data->line == NULL)
		{
			printf("minikshell$ exit\n");
			exit(data->errorcode);
		}
		lexer(data);
		lexer_clear(&(data->m_lexer), free);
		expander_clear(&(data->m_expander), free);
		parser_clear(&(data->m_parser), free);
		free(data->line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_minishell	*data;

	(void)ac;
	(void)av;
	data = (t_minishell *)malloc(sizeof(t_minishell));
	data->m_export = NULL;
	data->m_env = env_get(env, data);
	data->errorcode = 0;
	g_signal = 0;
	path_get(data->m_env, data);
	signal_init();
	routine(data);
}
