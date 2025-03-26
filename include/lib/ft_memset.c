/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:50:09 by vide-sou          #+#    #+#             */
/*   Updated: 2024/10/14 20:39:47 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			index;
	unsigned char	*s;

	index = 0;
	s = (unsigned char *)str;
	while (index < n)
	{
		s[index] = (unsigned char)c;
		index++;
	}
	return ((void *)s);
}
