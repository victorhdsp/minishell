/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:50:09 by vide-sou          #+#    #+#             */
/*   Updated: 2024/10/14 20:37:47 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*cdest;
	char	*csrc;
	char	*fp;
	size_t	index;

	cdest = (char *)dest;
	csrc = (char *)src;
	fp = cdest;
	index = 0;
	if (!csrc && !cdest)
		return (NULL);
	if (cdest <= csrc)
		return (ft_memcpy(dest, src, n));
	cdest += n - 1;
	csrc += n - 1;
	while (index < n)
	{
		*cdest-- = *csrc--;
		index++;
	}
	return (fp);
}
