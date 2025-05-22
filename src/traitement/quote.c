/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:14:22 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/22 17:40:43 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_quotes(char *str, char type)
{
	int		index;
	int		quotes;

	index = 0;
	quotes = 0;
	while (str[index])
	{
		if (str[index] == type)
			quotes++;
		index++;
	}
	return quotes;
}

static void	change_quote(char *get, char **set, char type)
{
	int		index;
	int		quotes;
	char	*result;

	index = 0;
	quotes = count_quotes(get, type);
	result = ft_calloc(ft_strlen(get) - quotes, sizeof(char));
	quotes = 0;
	while (get[index])
	{
		while (get[index] == type)
		{
			quotes++;
			index++;
		}
		result[index - quotes] = get[index];
		index++;
	}
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
				change_quote(str, &args[index].value, *str);
			str++;
		}
		index++;
	}
}
