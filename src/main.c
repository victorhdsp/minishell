/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:30:53 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/31 12:59:38 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(void)
{
	t_sentence		*result;
	t_lexer_item input[] = {
        { .value = "comando",    .type = type_word, .fn = fn_null },
        { .value = "|",          .type = type_logic, .fn = fn_pipe },
        { .value = "argumento1", .type = type_word, .fn = fn_null },
        { .value = "argumento2", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

	result = ft_pipes((t_lexer_item *)input);
}
