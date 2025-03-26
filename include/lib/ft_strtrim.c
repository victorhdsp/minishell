/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:47:31 by vide-sou          #+#    #+#             */
/*   Updated: 2024/10/14 19:33:59 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_search(char const *s1, char const *set, int pos, int dir)
{
	size_t	index;
	int		in_word;

	index = 0;
	in_word = 0;
	while (s1 && s1[pos])
	{
		while (set[index])
		{
			if (s1[pos] == set[index])
				in_word++;
			index++;
		}
		if (in_word)
		{
			in_word = 0;
			index = 0;
			pos += dir;
		}
		else
			break ;
	}
	return (pos);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		start;
	int		end;

	if (!s1)
		return (NULL);
	start = ft_search(s1, set, 0, 1);
	end = ft_search(s1, set, ft_strlen(s1) - 1, -1) + 1;
	if (end - start + 1 < 0)
		return (ft_calloc(1, sizeof(char)));
	result = ft_calloc(end - start + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	if (!*set)
		ft_memmove(result, s1, ft_strlen(s1));
	else
		ft_memmove(result, s1 + start, end - start);
	return (result);
}
