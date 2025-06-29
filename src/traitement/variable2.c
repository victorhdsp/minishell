/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:02:19 by rpassos-          #+#    #+#             */
/*   Updated: 2025/06/28 22:14:30 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_single_quotes(char **str)
{
	char	*next;

	next = ft_memchr(*str + 1, '\'', ft_strlen(*str));
	if (next)
		*str = next;
	else
		*str = NULL;
}

static void	handle_dollar(char **str, char **value_ref)
{
	change_variable(*str, value_ref, *str);
	*str = *value_ref;
}

static void	process_value(t_lexer_item *item)
{
	char	*str = item->value;
	char	current_quote = '\0';

	while (str && *str)
	{
		if (current_quote == '\0' && (*str == '\'' || *str == '\"'))
			current_quote = *str;
		if (current_quote != '\"' && *str == '\'')
		{
			skip_single_quotes(&str);
			if (!str)
				break;
		}
		if (*str == '$')
		{
			handle_dollar(&str, &item->value);
			continue;
		}
		if (*str++ == current_quote)
			current_quote = '\0';
	}
}

void	variable_traitement(t_lexer_item *args)
{
	int	index = 0;

	while (args[index].value)
	{
		process_value(&args[index]);
		index++;
	}
}