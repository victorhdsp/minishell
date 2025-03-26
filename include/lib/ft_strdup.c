/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:01:00 by vide-sou          #+#    #+#             */
/*   Updated: 2024/10/14 15:38:14 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		index;
	int		length;
	char	*result;

	index = 0;
	length = ft_strlen(s);
	result = (char *)ft_calloc(length + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	while (s && s[index])
	{
		result[index] = s[index];
		index++;
	}
	return (result);
}
