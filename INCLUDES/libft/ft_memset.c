/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <ahmetabdullahcan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:53:41 by acan              #+#    #+#             */
/*   Updated: 2023/07/09 11:39:50 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t				i;
	unsigned char		*sptr;

	sptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		sptr[i] = (unsigned char)c;
		i++;
	}
	return (sptr);
}
