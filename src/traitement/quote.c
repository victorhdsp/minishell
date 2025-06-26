/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:14:22 by vide-sou          #+#    #+#             */
/*   Updated: 2025/06/26 15:59:50 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int	count_quotes(char *str, char type)
// {
// 	int	index;
// 	int	quotes;

// 	index = 0;
// 	quotes = 0;
// 	while (str[index])
// 	{
// 		if (str[index] == type)
// 			quotes++;
// 		index++;
// 	}
// 	return (quotes);
// }

// static void	change_quote(char *get, char **set, char type)
// {
// 	int		index;
// 	int		quotes;
// 	char	*result;
// 	int		index2;

// 	quotes = count_quotes(get, type);
// 	result = ft_calloc(ft_strlen(get) - quotes + 1, sizeof(char));
// 	if (!result)
// 		return;
// 	index = 0;
// 	index2 = 0;
// 	while (get[index])
// 	{
// 		if (get[index] == type)
// 		{
// 			index++;
// 			continue;
// 		}
// 		result[index2++] = get[index++];
// 	}
// 	result[index2] = '\0';
// 	free(*set);
// 	*set = result;
// }

void	quote_traitement(t_lexer_item *args)
{
	int		i;
	char	*src;
	char	*dst;
	char	*new_val;
	char	quote;

	i = 0;
	while (args[i].value)
	{
		src = args[i].value;
		new_val = ft_calloc(ft_strlen(src) + 1, sizeof(char));
		if (!new_val)
			return ;
		dst = new_val;
		while (*src)
		{
			if (*src == '\'' || *src == '\"')
			{
				quote = *src++;
				const char *start = src;
				while (*src && *src != quote)
					*dst++ = *src++;
				if (*src == quote)
					src++;
				else
				{
					dst = new_val;
					*dst++ = quote;
					src = (char *)start;
					while (*src)
						*dst++ = *src++;
					break;
				}
			}
			else
				*dst++ = *src++;
		}
		*dst = '\0';
		free(args[i].value);
		args[i].value = new_val;
		i++;
	}
}

