/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:38:57 by vide-sou          #+#    #+#             */
/*   Updated: 2024/10/12 12:35:33 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr(long n, char *result, int index, int size)
{
	if (n > 9)
		ft_putnbr(n / 10, result, index + 1, size);
	result[size - index] = '0' + n % 10;
}

static int	ft_num_count(long n)
{
	int	index;

	index = 0;
	while (n > 9)
	{
		n /= 10;
		index++;
	}
	return (index + 1);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		size;
	long	nbr;

	size = 0;
	nbr = n;
	if (nbr < 0)
	{
		nbr *= -1;
		size++;
	}
	size += ft_num_count(nbr);
	result = (char *)ft_calloc(size + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	if (size <= 0)
		return (NULL);
	if (size > ft_num_count(nbr))
		*result = '-';
	ft_putnbr(nbr, result, 0, size - 1);
	return (result);
}
