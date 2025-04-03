/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:30:53 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/03 12:07:12 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(void)
{
	t_sentence		*result;
	t_lexer_item	input[] = {
		{.value = ">", .type = type_outfile, .fn = fn_output},
		{.value = "local/tmp", .type = type_word, .fn = fn_null},
		{.value = "cat", .type = type_word, .fn = fn_cmd},
		{.value = "Makefile", .type = type_word, .fn = fn_null},
		{.value = NULL}
	};
	result = ft_pipes((t_lexer_item *)input);
	ft_prepare_exec(result);
}
