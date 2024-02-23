/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uarslan <uarslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:50:53 by uarslan           #+#    #+#             */
/*   Updated: 2024/01/20 20:21:31 by uarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static char	*get_env(char *to_find, t_minishell *data)
{
	t_env	*tmp;
	char	pwd[256];

	tmp = (data->m_env);
	if (!ft_strcmp(to_find, "PWD"))
		return (ft_strdup(getcwd(pwd, 256)));
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, to_find)))
		{
			return (ft_strdup(tmp->var));
		}
		tmp = tmp->next;
	}
	if (*to_find == 0)
		return (ft_strdup("$"));
	else
		return (ft_strdup(""));
}

static char	*after_dollar(char *cmd, int *loop, t_minishell *data)
{
	if (should_be_done_but_null(cmd[*loop]))
		return (ft_strdup(""));
	else if (printable_special_character(cmd[*loop]))
		return (char_to_str(ft_strdup("$"), cmd[*loop]));
	else if (should_be_done_but_error(cmd[*loop]))
	{
		expander_errors("syntax error");
		return (char_to_str(ft_strdup("$"), cmd[*loop]));
	}
	else if (special_chars(cmd[*loop]))
	{
		if (cmd[*loop] == '?')
			return (ft_itoa(data->errorcode));
		else if (cmd[*loop] == '0')
			return (ft_strdup("minikshell"));
		else if (cmd[*loop] == '_')
			return (ft_strdup("/minishell"));
		else
			return (ft_strdup("$$"));
	}
	return (0);
}

static char	*expand_dollar(char *cmd, int *loop, t_minishell *data)
{
	char	*str;
	char	*ret;

	str = ft_calloc(1, 1);
	if (all_after_dollar(cmd[++(*loop)]))
	{
		free(str);
		return (after_dollar(cmd, loop, data));
	}
	while (cmd[*loop])
	{
		if (ft_isalnum(cmd[*loop]) || cmd[*loop] == '_')
			str = char_to_str(str, cmd[(*loop)]);
		else
			break ;
		(*loop)++;
	}
	(*loop)--;
	if (*str != '\0')
		ret = get_env(str, data);
	else
		ret = ft_strdup("$");
	free(str);
	return (ret);
}

static char	*search_dollar(t_minishell *data, t_lexer *tmp, char quote,
		int *is_first)
{
	int		loop;
	char	*ret;

	ret = ft_calloc(1, 1);
	loop = 0;
	while (tmp->command[loop])
	{
		if (quote_check(&(tmp->command[loop])))
		{
			if (quote == quote_check(&(tmp->command[loop])))
				quote = 0;
			else if (quote == 0)
				quote = quote_check(&(tmp->command[loop]));
		}
		if (tmp->command[loop] == '$' && (quote == '"' || quote == 0))
			ret = my_strjoin2(ret, expand_dollar(tmp->command, &loop, data));
		else
			ret = char_to_str(ret, tmp->command[loop]);
		if (tmp->command[loop])
			loop++;
	}
	if (ret && !*ret)
		*is_first = -1;
	return (ret);
}

void	expander(t_minishell *data)
{
	t_lexer	*tmp;
	int		is_first;

	if (!data->m_lexer)
		return ;
	tmp = (data->m_lexer);
	while (tmp)
	{
		is_first = 0;
		if (!ft_strncmp(tmp->command, "~", ft_strlen(tmp->command)))
			expander_addback(&data->m_expander, expander_new(tmp,
					ft_strdup(get_env("HOME", data)), is_first));
		else if (ft_strchr(tmp->command, '$'))
			expander_addback(&data->m_expander, expander_new(tmp,
					search_dollar(data, tmp, '\0', &is_first), is_first));
		else
			expander_addback(&data->m_expander, expander_new(tmp,
					ft_strdup(tmp->command), 0));
		tmp = tmp->next;
	}
	remove_quotes(data, '\0');
	parser(data);
}
