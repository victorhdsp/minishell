/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:14:22 by vide-sou          #+#    #+#             */
/*   Updated: 2025/06/23 16:23:48 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_quotes(char *str, char type)
{
	int	index;
	int	quotes;

	index = 0;
	quotes = 0;
	while (str[index])
	{
		if (str[index] == type)
			quotes++;
		index++;
	}
	return (quotes);
}

static void	change_quote(char *get, char **set, char type)
{
	int		index;
	int		quotes;
	char	*result;
	int		index2;

	quotes = count_quotes(get, type);
	result = ft_calloc(ft_strlen(get) - quotes + 1, sizeof(char));
	if (!result)
		return;
	index = 0;
	index2 = 0;
	while (get[index])
	{
		if (get[index] == type)
		{
			index++;
			continue;
		}
		result[index2++] = get[index++];
	}
	result[index2] = '\0';
	free(*set);
	*set = result;
}

void	quote_traitement(t_lexer_item *args)
{
	int		index;
	char	*str;

	index = 0;
	while (args[index].value)
	{
		str = args[index].value;
		while (str && *str)
		{
			if (*str == '\'' || *str == '\"')
			{
				change_quote(args[index].value, &args[index].value, *str);
				str = args[index].value;
				continue;
			}
			str++;
		}
		index++;
	}
}
