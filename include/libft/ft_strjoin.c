/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:58:07 by vide-sou          #+#    #+#             */
/*   Updated: 2024/10/14 15:41:12 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*result;
	char	*first_point;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	first_point = result;
	if (result)
	{
		if (s1 && *s1)
			ft_memmove(result, s1, len_s1);
		result += len_s1;
		if (s2 && *s2)
			ft_memmove(result, s2, len_s2);
	}
	return (first_point);
}
