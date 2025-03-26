/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:42:23 by vide-sou          #+#    #+#             */
/*   Updated: 2024/10/14 15:43:29 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*result;

	index = 0;
	result = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	while (result && s && s[index] && f)
	{
		result[index] = f(index, s[index]);
		index++;
	}
	return (result);
}
