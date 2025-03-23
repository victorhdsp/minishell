/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordbreaker.test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:59:02 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/22 15:04:16 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./tokenizer.h"
#include "../../__test/utils.h"

void ft_assert_lexer_list(t_sentence_item *result, t_sentence_item *expected)
{
    int i = 0;

    while (expected[i].value != NULL)
    {
        cr_assert(result[i].value != NULL,
                  "Token %d: valor esperado \"%s\" mas o resultado é NULL",
                  i, expected[i].value);
                  
        cr_assert_str_eq(result[i].value, expected[i].value,
                  "Token %d: valor esperado \"%s\" mas obteve \"%s\"",
                  i, expected[i].value, result[i].value);
                  
        cr_assert(result[i].type == expected[i].type,
                  "Token %d: tipo esperado %d mas obteve %d",
                  i, expected[i].type, result[i].type);
                  
        cr_assert(result[i].fn == expected[i].fn,
                  "Token %d: fn esperado %d mas obteve %d",
                  i, expected[i].fn, result[i].fn);
        i++;
    }
    
    cr_assert(result[i].value == NULL,
              "A lista resultante possui tokens a mais do que o esperado (token extra na posição %d)",
              i);
}

void ft_free_lexer_list(t_sentence_item *list)
{
    int i = 0;
    if (!list)
        return;
    while (list[i].value != NULL)
    {
        free(list[i].value);
        i++;
    }
    free(list);
}

// Identificação simples com somente palavras:
// Entrada: ["comando", "argumento1", "argumento2"]
// Saída esperada: [{ value: "comando", type: word, fn: null }...]
Test(wordbreaker, identify_by_simple_words)
{
    char *input[] = {"comando", "argumento1", "argumento2", NULL};

    t_sentence_item expected[] = {
        { .value = "comando",    .type = word, .fn = 0 },  // considerando que 'null' é representado por 0
        { .value = "argumento1", .type = word, .fn = 0 },
        { .value = "argumento2", .type = word, .fn = 0 },
        { .value = NULL } // Termina a lista
    };

    t_sentence_item *result = lexer(input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}
