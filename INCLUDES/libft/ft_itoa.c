/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <ahmetabdullahcan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:26:32 by acan              #+#    #+#             */
/*   Updated: 2023/07/10 16:30:31 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_count(long int i)
{
	int	count;

	count = 0;
	if (i == 0)
	{
		return (1);
	}
	if (i < 0)
	{
		i *= -1;
		count++;
	}
	while (i > 0)
	{
		i /= 10;
		count++;
	}
	return (count);
}

static void	getnbr(long n, char *str, int *i)
{
	if (n > 9)
	{
		getnbr(n / 10, str, i);
		getnbr(n % 10, str, i);
	}
	else
		str[(*i)++] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nbr;

	nbr = n;
	str = malloc(sizeof(char) * (digit_count(nbr) + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (nbr == 0)
	{
		str[i] = '0';
		str[i + 1] = '\0';
		return (str);
	}
	if (nbr < 0)
	{
		str[i++] = '-';
		nbr *= -1;
	}
	getnbr(nbr, str, &i);
	str[i] = '\0';
	return (str);
}
