/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:18:21 by vide-sou          #+#    #+#             */
/*   Updated: 2024/10/09 05:05:49 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index;
	char	*str;
	int		diff;

	index = 0;
	str = (char *)big;
	diff = 0;
	if (!*little)
		return (str);
	while (*str && index < len)
	{
		if (index + ft_strlen(little) > len)
			break ;
		if (ft_memcmp(str, little, ft_strlen(little) + diff) == 0)
			return (str);
		str++;
		index++;
	}
	return (NULL);
}
