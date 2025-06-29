/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:14:22 by vide-sou          #+#    #+#             */
/*   Updated: 2025/06/28 21:55:05 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_quoted_segment(const char **src, char **dst, char quote)
{
	const char	*start = *src;

	while (**src && **src != quote)
		*(*dst)++ = *(*src)++;
	if (**src == quote)
		(*src)++;
	else
	{
		*dst = *dst - (start - *src);
		*(*dst)++ = quote;
		*src = start;
		while (**src)
			*(*dst)++ = *(*src)++;
	}
}

static void	process_quotes(t_lexer_item *item)
{
	const char	*src;
	char		*new_val;
	char		*dst;

	src = item->value;
	new_val = ft_calloc(ft_strlen(src) + 1, sizeof(char));
	dst = new_val;
	if (!new_val)
		return ;
	while (*src)
	{
		if (*src == '\'' || *src == '\"')
			handle_quoted_segment(&src, &dst, *src++);
		else
			*dst++ = *src++;
	}
	*dst = '\0';
	free(item->value);
	item->value = new_val;
}

void	quote_traitement(t_lexer_item *args)
{
	int	i = 0;

	while (args[i].value)
	{
		process_quotes(&args[i]);
		i++;
	}
}
