/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:47:31 by vide-sou          #+#    #+#             */
/*   Updated: 2024/10/14 20:09:49 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char const *s, char c)
{
	size_t	index;
	int		in_word;
	int		count;

	index = 0;
	in_word = 0;
	count = 0;
	while (s && s[index])
	{
		if (s[index] == c)
			in_word = 0;
		if (s[index] != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		index++;
	}
	return (count);
}

static char	**ft_clean(char **result)
{
	int	index;

	index = 0;
	while (result && result[index])
	{
		free(result[index]);
		index++;
	}
	free(result);
	result = NULL;
	return (ft_calloc(1, sizeof(char *)));
}

static int	ft_create_text(char const *s, char const *s2, char **result,
		size_t index)
{
	char	*tmp_text;

	tmp_text = ft_substr(s, 0, s2 - s);
	if (tmp_text && *tmp_text)
		result[index] = tmp_text;
	else
		free(tmp_text);
	if (tmp_text == NULL)
		return (0);
	else
		return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**result;
	size_t		index;
	char const	*s2;
	int			has_created_text;
	size_t		len;

	index = 0;
	if (!s)
		return (NULL);
	len = ft_count_word(s, c);
	result = ft_calloc(len + 1, sizeof(char *));
	while (*s && index < len && result != NULL)
	{
		s2 = ft_strchr(s, (int)c);
		if (!s2)
			s2 = s + ft_strlen(s);
		has_created_text = ft_create_text(s, s2, result, index);
		if (!has_created_text)
			return (ft_clean(result));
		if (result[index])
			index++;
		if (*s2)
			s = s2 + 1;
	}
	return (result);
}
