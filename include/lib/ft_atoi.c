/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:54:49 by vide-sou          #+#    #+#             */
/*   Updated: 2024/10/12 12:38:15 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	char	*nb;
	long	result;
	int		minus;

	nb = (char *)nptr;
	result = 0;
	minus = 0;
	while (*nb == 32 || (*nb >= 9 && *nb <= 13))
		nb++;
	if ((*nb == '+') || (*nb == '-'))
	{
		if (*nb == '-')
			minus = 1;
		nb++;
	}
	while (ft_isdigit(*nb))
		result = (result * 10) + (*nb++ - 48);
	if (minus)
		result *= -1;
	return ((int)result);
}
