/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:28:18 by vide-sou          #+#    #+#             */
/*   Updated: 2024/10/13 14:39:39 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*fp;

	fp = (char *)s;
	s += ft_strlen(s);
	if (!c)
		return ((char *)s);
	while (fp <= s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
	}
	return (NULL);
}
