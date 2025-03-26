/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:28:18 by vide-sou          #+#    #+#             */
/*   Updated: 2024/10/13 14:41:45 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	len;

	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (!c)
		return ((char *)s);
	return (NULL);
}
