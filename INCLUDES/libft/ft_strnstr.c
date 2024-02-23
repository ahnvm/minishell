/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <ahmetabdullahcan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:12:08 by acan              #+#    #+#             */
/*   Updated: 2023/07/12 16:30:11 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	smallen;
	size_t	i;
	size_t	j;
	char	*hay;

	smallen = ft_strlen(needle);
	hay = (char *)haystack;
	if (smallen == 0 || needle == haystack)
		return (hay);
	i = 0;
	while (hay[i] != '\0' && i < len)
	{
		j = 0;
		while (hay[i + j] != '\0' && needle[j] != '\0'
			&& hay[i + j] == needle[j] && i + j < len)
			j++;
		if (j == smallen)
			return (hay + i);
		i++;
	}
	return (NULL);
}
