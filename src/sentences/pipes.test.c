/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:59:02 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/26 11:04:55 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./sentences.h"
#include "../../__test/utils.h"

void ft_assert_pipes(t_sentence *result, t_sentence *expected) {
    int i = 0;

    if (!result || !expected)
    {
        cr_assert(0, "\"Result\" ou \"Expected\" está vazio.");
        return;
    }

    while (expected[i].args)
    {
        cr_assert(result[i].args != NULL,
                  "Sentença %d: valor esperado \"%s\" mas o resultado é NULL",
                  i, expected[i].args[0]);
                  
        ft_assert_str_list(result[i].args, expected[i].args);
                  
        cr_assert(result[i].args[1] == NULL,
                  "Sentença %d: valor esperado \"%s\" mas obteve \"%s\"",
                  i, expected[i].args[1], result[i].args[1]);
                  
        i++;
    }

    cr_assert(result[i].args == NULL,
              "A lista resultante possui sentenças a mais do que o esperado (sentença extra na posição %d)",
              i);
}

// Divisão de uma sentença solitária
Test(pipes, identify_by_simple_words) {
    t_sentence_item input[] = {
        { .value = "comando",    .type = type_word, .fn = fn_null },
        { .value = "argumento1", .type = type_word, .fn = fn_null },
        { .value = "argumento2", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence expected[] = {
        { .infile = NULL, .outfile = NULL, .args = { "comando", "argumento1", "argumento2", NULL } },
        { .infile = NULL, .outfile = NULL, .args = NULL },
    };

    t_sentence  result = ft_pipes((t_sentence_item *)input);
}