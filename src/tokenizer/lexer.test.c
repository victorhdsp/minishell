/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:59:02 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/24 11:23:26 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./tokenizer.h"
#include "../../__test/utils.h"

void ft_assert_lexer_list(t_sentence_item *result, t_sentence_item *expected)
{
    int i = 0;

    if (!result || !expected)
    {
        cr_assert(0, "\"Result\" ou \"Expected\" está vazio.");
        return;
    }
    while (expected[i].value)
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
    free(list);
}

// Identificação simples com somente palavras
Test(wordbreaker, identify_by_simple_words) {
    char *input[] = {"comando", "argumento1", "argumento2", NULL};

    t_sentence_item expected[] = {
        { .value = "comando",    .type = type_word, .fn = fn_null },
        { .value = "argumento1", .type = type_word, .fn = fn_null },
        { .value = "argumento2", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com caracteres especiais
Test(wordbreaker, identify_with_special_characters) {
    char *input[] = {"comando1", "|", "comando2", ">", "output.txt", "=", "e", NULL};

    t_sentence_item expected[] = {
        { .value = "comando1",  .type = type_word, .fn = fn_null },
        { .value = "|",         .type = type_divider, .fn = fn_pipe },
        { .value = "comando2",  .type = type_word, .fn = fn_null },
        { .value = ">",         .type = type_outfile, .fn = fn_output },
        { .value = "output.txt", .type = type_word, .fn = fn_null },
        { .value = "=", .type = type_equal, .fn = fn_equal },
        { .value = "e", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com aspas
Test(wordbreaker, identify_with_quotes) {
    char *input[] = {"comando", "\"argumento com espaços\"", "argumento2", NULL};

    t_sentence_item expected[] = {
        { .value = "comando", .type = type_word, .fn = fn_null },
        { .value = "\"argumento com espaços\"", .type = type_word, .fn = fn_null },
        { .value = "argumento2", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com caracteres especiais dentro de aspas
Test(wordbreaker, identify_with_special_characters_in_quotes) {
    char *input[] = {"comando", "\"argumento | com > caracteres\"", NULL};

    t_sentence_item expected[] = {
        { .value = "comando", .type = type_word, .fn = fn_null },
        { .value = "\"argumento | com > caracteres\"", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com parênteses
Test(wordbreaker, identify_with_parenthesis) {
    char *input[] = {"(", "comando1", "&&", "comando2", ")", "||", "comando3", NULL};

    t_sentence_item expected[] = {
        { .value = "(", .type = type_parenthesis, .fn = fn_open_parenthesis },
        { .value = "comando1", .type = type_word, .fn = fn_null },
        { .value = "&&", .type = type_divider, .fn = fn_and },
        { .value = "comando2", .type = type_word, .fn = fn_null },
        { .value = ")", .type = type_parenthesis, .fn = fn_close_parenthesis },
        { .value = "||", .type = type_divider, .fn = fn_or },
        { .value = "comando3", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com parênteses dentro de aspas
Test(wordbreaker, identify_with_parenthesis_in_quotes) {
    char *input[] = {"comando", "\"(argumento com parênteses)\"", NULL};

    t_sentence_item expected[] = {
        { .value = "comando", .type = type_word, .fn = fn_null },
        { .value = "\"(argumento com parênteses)\"", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com redirecionamentos
Test(wordbreaker, identify_with_redirects) {
    char *input[] = {"comando", "<", "input.txt", ">", "output.txt", NULL};

    t_sentence_item expected[] = {
        { .value = "comando", .type = type_word, .fn = fn_null },
        { .value = "<", .type = type_infile, .fn = fn_input },
        { .value = "input.txt", .type = type_word, .fn = fn_null },
        { .value = ">", .type = type_outfile, .fn = fn_output },
        { .value = "output.txt", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com redirecionamentos dentro de aspas
Test(wordbreaker, identify_with_redirects_in_quotes) {
    char *input[] = {"comando", "\"< input.txt > output.txt\"", NULL};

    t_sentence_item expected[] = {
        { .value = "comando", .type = type_word, .fn = fn_null },
        { .value = "\"< input.txt > output.txt\"", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com combinações complexas
Test(wordbreaker, identify_with_complex_combination) {
    char *input[] = {"comando1", "|", "comando2", "&&", "comando3", ">", "\"output file.txt\"", NULL};

    t_sentence_item expected[] = {
        { .value = "comando1", .type = type_word, .fn = fn_null },
        { .value = "|", .type = type_divider, .fn = fn_pipe },
        { .value = "comando2", .type = type_word, .fn = fn_null },
        { .value = "&&", .type = type_divider, .fn = fn_and },
        { .value = "comando3", .type = type_word, .fn = fn_null },
        { .value = ">", .type = type_outfile, .fn = fn_output },
        { .value = "\"output file.txt\"", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com escape
Test(wordbreaker, identify_with_escape) {
    char *input[] = {"comando\\", "argumento", NULL};

    t_sentence_item expected[] = {
        { .value = "comando\\", .type = type_word, .fn = fn_null },
        { .value = "argumento", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação apenas com separadores
Test(wordbreaker, identify_only_with_dividers) {
    char *input[] = {"|", ">", "<", "&&", "||", NULL};

    t_sentence_item expected[] = {
        { .value = "|", .type = type_divider, .fn = fn_pipe },
        { .value = ">", .type = type_outfile, .fn = fn_output },
        { .value = "<", .type = type_infile, .fn = fn_input },
        { .value = "&&", .type = type_divider, .fn = fn_and },
        { .value = "||", .type = type_divider, .fn = fn_or },
        { .value = NULL }
    };

    t_sentence_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}