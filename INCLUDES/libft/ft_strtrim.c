/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <ahmetabdullahcan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:21:41 by acan              #+#    #+#             */
/*   Updated: 2023/07/09 20:34:41 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	setcontrol(char c, char const *set)
{
	size_t	l;

	l = 0;
	while (set[l] != '\0')
	{
		if (c == set[l])
			return (1);
		l++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	char	*temp;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (setcontrol(*s1, set) && *s1 != '\0')
		s1++;
	len = ft_strlen(s1);
	if (len == 0)
		return (ft_strdup(""));
	while (setcontrol(s1[len - 1], set) && len != 0)
		len--;
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, s1, len + 1);
	return (temp);
}
