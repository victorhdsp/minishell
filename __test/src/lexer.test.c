/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:59:02 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/23 14:46:26 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/tokenizer/tokenizer.h"
#include "../utils.h"

void ft_assert_lexer_list(t_lexer_item *result, t_lexer_item *expected)
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

void ft_free_lexer_list(t_lexer_item *list)
{
    int i = 0;
    if (!list)
        return;
    free(list);
}

// Identificação simples com somente palavras
Test(lexer, identify_by_simple_words) {
    char *input[] = {"comando", "argumento1", "argumento2", NULL};

    t_lexer_item expected[] = {
        { .value = "comando",    .type = type_word, .fn = fn_null },
        { .value = "argumento1", .type = type_word, .fn = fn_null },
        { .value = "argumento2", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_lexer_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com caracteres especiais
Test(lexer, identify_with_special_characters) {
    char *input[] = {"comando1", "|", "comando2", ">", "output.txt=e", NULL};

    t_lexer_item expected[] = {
        { .value = "comando1",  .type = type_word, .fn = fn_null },
        { .value = "|",         .type = type_logic, .fn = fn_pipe },
        { .value = "comando2",  .type = type_word, .fn = fn_null },
        { .value = ">",         .type = type_outfile, .fn = fn_output },
        { .value = "output.txt=e", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_lexer_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com aspas
Test(lexer, identify_with_quotes) {
    char *input[] = {"comando", "\"argumento com espaços\"", "argumento2", NULL};

    t_lexer_item expected[] = {
        { .value = "comando", .type = type_word, .fn = fn_null },
        { .value = "\"argumento com espaços\"", .type = type_word, .fn = fn_null },
        { .value = "argumento2", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_lexer_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com caracteres especiais dentro de aspas
Test(lexer, identify_with_special_characters_in_quotes) {
    char *input[] = {"comando", "\"argumento | com > caracteres\"", NULL};

    t_lexer_item expected[] = {
        { .value = "comando", .type = type_word, .fn = fn_null },
        { .value = "\"argumento | com > caracteres\"", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_lexer_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com parênteses
Test(lexer, identify_with_parenthesis) {
    char *input[] = {"(", "comando1", "&&", "comando2", ")", "||", "comando3", NULL};

    t_lexer_item expected[] = {
        { .value = "(", .type = type_parenthesis, .fn = fn_open_parenthesis },
        { .value = "comando1", .type = type_word, .fn = fn_null },
        { .value = "&&", .type = type_logic, .fn = fn_and },
        { .value = "comando2", .type = type_word, .fn = fn_null },
        { .value = ")", .type = type_parenthesis, .fn = fn_close_parenthesis },
        { .value = "||", .type = type_logic, .fn = fn_or },
        { .value = "comando3", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_lexer_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com parênteses dentro de aspas
Test(lexer, identify_with_parenthesis_in_quotes) {
    char *input[] = {"comando", "\"(argumento com parênteses)\"", NULL};

    t_lexer_item expected[] = {
        { .value = "comando", .type = type_word, .fn = fn_null },
        { .value = "\"(argumento com parênteses)\"", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_lexer_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com redirecionamentos
Test(lexer, identify_with_redirects) {
    char *input[] = {"comando", "<", "input.txt", ">", "output.txt", NULL};

    t_lexer_item expected[] = {
        { .value = "comando", .type = type_word, .fn = fn_null },
        { .value = "<", .type = type_infile, .fn = fn_input },
        { .value = "input.txt", .type = type_word, .fn = fn_null },
        { .value = ">", .type = type_outfile, .fn = fn_output },
        { .value = "output.txt", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_lexer_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com redirecionamentos dentro de aspas
Test(lexer, identify_with_redirects_in_quotes) {
    char *input[] = {"comando", "\"< input.txt > output.txt\"", NULL};

    t_lexer_item expected[] = {
        { .value = "comando", .type = type_word, .fn = fn_null },
        { .value = "\"< input.txt > output.txt\"", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_lexer_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com combinações complexas
Test(lexer, identify_with_complex_combination) {
    char *input[] = {"comando1", "|", "comando2", "&&", "comando3", ">", "\"output file.txt\"", NULL};

    t_lexer_item expected[] = {
        { .value = "comando1", .type = type_word, .fn = fn_null },
        { .value = "|", .type = type_logic, .fn = fn_pipe },
        { .value = "comando2", .type = type_word, .fn = fn_null },
        { .value = "&&", .type = type_logic, .fn = fn_and },
        { .value = "comando3", .type = type_word, .fn = fn_null },
        { .value = ">", .type = type_outfile, .fn = fn_output },
        { .value = "\"output file.txt\"", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_lexer_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com escape
Test(lexer, identify_with_escape) {
    char *input[] = {"comando\\", "argumento", NULL};

    t_lexer_item expected[] = {
        { .value = "comando\\", .type = type_word, .fn = fn_null },
        { .value = "argumento", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_lexer_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação apenas com separadores
Test(lexer, identify_only_with_dividers) {
    char *input[] = {"|", ">", "<", "&&", "||", NULL};

    t_lexer_item expected[] = {
        { .value = "|", .type = type_logic, .fn = fn_pipe },
        { .value = ">", .type = type_outfile, .fn = fn_output },
        { .value = "<", .type = type_infile, .fn = fn_input },
        { .value = "&&", .type = type_logic, .fn = fn_and },
        { .value = "||", .type = type_logic, .fn = fn_or },
        { .value = NULL }
    };

    t_lexer_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}

// Identificação com aspas simples
Test(lexer, divide_with_simple_quotes) {
    char *input[] = {"tr", "''", "','", "|", "cat", "-e", "|", "ls", NULL};

    t_lexer_item expected[] = {
        { .value = "tr", .type = type_word, .fn = fn_null },
        { .value = "''", .type = type_word, .fn = fn_null },
        { .value = "','", .type = type_word, .fn = fn_null },
        { .value = "|", .type = type_logic, .fn = fn_pipe },
        { .value = "cat", .type = type_word, .fn = fn_null },
        { .value = "-e", .type = type_word, .fn = fn_null },
        { .value = "|", .type = type_logic, .fn = fn_pipe },
        { .value = "ls", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };
    
    t_lexer_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}


// ["cat", "echo", ">", "ls", "grep", ">", "find", "k"]
Test(lexer, divide_with_special_caracter_no_quotes) {
    char *input[] = {"cat", "echo", ">", "ls", "grep", ">", "find", "k", NULL};

    t_lexer_item expected[] = {
        { .value = "cat", .type = type_word, .fn = fn_null },
        { .value = "echo", .type = type_word, .fn = fn_null },
        { .value = ">", .type = type_outfile, .fn = fn_output },
        { .value = "ls", .type = type_word, .fn = fn_null },
        { .value = "grep", .type = type_word, .fn = fn_null },
        { .value = ">", .type = type_outfile, .fn = fn_output },
        { .value = "find", .type = type_word, .fn = fn_null },
        { .value = "k", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };
    
    t_lexer_item *result = lexer((char **)input);

    ft_assert_lexer_list(result, expected);
    ft_free_lexer_list(result);
}