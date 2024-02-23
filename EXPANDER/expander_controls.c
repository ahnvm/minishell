/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:35:48 by acan              #+#    #+#             */
/*   Updated: 2024/01/10 19:28:19 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	should_be_done_but_null(char c)
{
	return ((c >= '1' && c <= '9') || c == '*' || c == '@' || c == '!');
}

int	printable_special_character(char c)
{
	return (c == '%' || c == '+' || c == ',' || c == '.' || c == '/' || c == ':'
		|| c == '=' || c == ']' || c == '^' || c == '}' || c == '~'
		|| c == ' ');
}

int	should_be_done_but_error(char c)
{
	return (c == '(' || c == '[' || c == 92 || c == '{' || c == ')' || c == ';'
		|| c == '#' || c == '-');
}

int	special_chars(char c)
{
	return (c == '0' || c == '?' || c == '$' || c == '_');
}

int	all_after_dollar(char c)
{
	return (special_chars(c) || should_be_done_but_error(c)
		|| printable_special_character(c) || should_be_done_but_null(c));
}
