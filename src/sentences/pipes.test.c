/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:59:02 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/26 18:39:25 by vide-sou         ###   ########.fr       */
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
        
        if (result[i].infile || expected[i].infile)
        {
            cr_assert_str_eq(result[i].infile, expected[i].infile,
                    "Sentença %d: infile esperado \"%s\" mas obteve \"%s\"",
                    i, expected[i].infile, result[i].infile);
        }
        if (result[i].outfile || expected[i].outfile)
        {
            cr_assert_str_eq(result[i].outfile, expected[i].outfile,
                    "Sentença %d: outfile esperado \"%s\" mas obteve \"%s\"",
                    i, expected[i].outfile, result[i].outfile);
        }
        
        i++;
    }


    cr_assert(result[i].args == NULL,
              "A lista resultante possui sentenças a mais do que o esperado (sentença extra na posição %d)",
              i);
}

// Divisão de uma sentença solitária
Test(pipes, identify_by_simple_words) {
    t_lexer_item input[] = {
        { .value = "comando",    .type = type_word, .fn = fn_null },
        { .value = "argumento1", .type = type_word, .fn = fn_null },
        { .value = "argumento2", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence expected[] = {
        { .infile = NULL, .outfile = NULL, .args = (char *[]){ "comando", "argumento1", "argumento2", NULL } },
        { .infile = NULL, .outfile = NULL, .args = NULL },
    };

    t_sentence  *result = ft_pipes((t_lexer_item *)input);
    ft_assert_pipes(result, expected);
}

// Divisão de uma sentença com um pipe, finalizando com NULL
Test(pipes, identify_by_pipe) {
    t_lexer_item input[] = {
        { .value = "comando",    .type = type_word, .fn = fn_null },
        { .value = "|",          .type = type_logic, .fn = fn_pipe },
        { .value = "argumento1", .type = type_word, .fn = fn_null },
        { .value = "argumento2", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence expected[] = {
        { .infile = NULL, .outfile = NULL, .args = (char *[]){ "comando", NULL } },
        { .infile = NULL, .outfile = NULL, .args = (char *[]){ "argumento1", "argumento2", NULL } },
        { .infile = NULL, .outfile = NULL, .args = NULL },
    };

    t_sentence  *result = ft_pipes((t_lexer_item *)input);
    ft_assert_pipes(result, expected);
}

// Divisão de uma sentença com um pipe, finalizando com outro divisor lógico
Test(pipes, identify_by_pipe_and_logical_operator) {
    t_lexer_item input[] = {
        { .value = "comando",    .type = type_word, .fn = fn_null },
        { .value = "|",          .type = type_logic, .fn = fn_pipe },
        { .value = "argumento1", .type = type_word, .fn = fn_null },
        { .value = "argumento2", .type = type_word, .fn = fn_null },
        { .value = "&&",         .type = type_logic, .fn = fn_and },
        { .value = "comando2",   .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence expected[] = {
        { .infile = NULL, .outfile = NULL, .args = (char *[]){ "comando", NULL } },
        { .infile = NULL, .outfile = NULL, .args = (char *[]){ "argumento1", "argumento2", NULL } },
        { .infile = NULL, .outfile = NULL, .args = NULL },
    };

    t_sentence  *result = ft_pipes((t_lexer_item *)input);
    ft_assert_pipes(result, expected);
}

// Divisão de uma sentença com output
Test(pipes, identify_by_output) {
    t_lexer_item input[] = {
        { .value = "comando",    .type = type_word, .fn = fn_null },
        { .value = ">",          .type = type_outfile, .fn = fn_output },
        { .value = "output.txt", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence expected[] = {
        { .infile = NULL, .outfile = "output.txt", .args = (char *[]){ "comando", NULL } },
        { .infile = NULL, .outfile = NULL, .args = NULL },
    };

    t_sentence  *result = ft_pipes((t_lexer_item *)input);
    ft_assert_pipes(result, expected);
}

// Divisão de uma sentença com input
Test(pipes, identify_by_input) {
    t_lexer_item input[] = {
        { .value = "comando",    .type = type_word, .fn = fn_null },
        { .value = "<",          .type = type_infile, .fn = fn_input },
        { .value = "input.txt",  .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence expected[] = {
        { .infile = "input.txt", .outfile = NULL, .args = (char *[]){ "comando", NULL } },
        { .infile = NULL, .outfile = NULL, .args = NULL },
    };

    t_sentence  *result = ft_pipes((t_lexer_item *)input);
    ft_assert_pipes(result, expected);
}

// Divisão de uma sentença com input e output
Test(pipes, identify_by_input_and_output) {
    t_lexer_item input[] = {
        { .value = "comando",    .type = type_word, .fn = fn_null },
        { .value = "<",          .type = type_infile, .fn = fn_input },
        { .value = "input.txt",  .type = type_word, .fn = fn_null },
        { .value = ">",          .type = type_outfile, .fn = fn_output },
        { .value = "output.txt", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence expected[] = {
        { .infile = "input.txt", .outfile = "output.txt", .args = (char *[]){ "comando", NULL } },
        { .infile = NULL, .outfile = NULL, .args = NULL },
    };

    t_sentence  *result = ft_pipes((t_lexer_item *)input);
    ft_assert_pipes(result, expected);
}

// Divisão de uma sentença com infile, outfile e pipes
Test(pipes, identify_by_input_output_and_pipes) {
    t_lexer_item input[] = {
        { .value = "comando1",    .type = type_word, .fn = fn_null },
        { .value = "|",           .type = type_logic, .fn = fn_pipe },
        { .value = "comando2",    .type = type_word, .fn = fn_null },
        { .value = ">",           .type = type_outfile, .fn = fn_output },
        { .value = "output.txt",  .type = type_word, .fn = fn_null },
        { .value = "=e",           .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence expected[] = {
        { .infile = NULL, .outfile = NULL, .args = (char *[]){ "comando1", NULL } },
        { .infile = NULL, .outfile = "output.txt", .args = (char *[]){ "comando2", "=e", NULL } },
        { .infile = NULL, .outfile = NULL, .args = NULL },
    };

    t_sentence  *result = ft_pipes((t_lexer_item *)input);
    ft_assert_pipes(result, expected);
}

// Divisão de uma sentença com pipes, append e logical operators
Test(pipes, identify_by_pipes_append_and_logical_operators) {
    t_lexer_item input[] = {
        { .value = "comando1",    .type = type_word, .fn = fn_null },
        { .value = "|",           .type = type_logic, .fn = fn_pipe },
        { .value = "comando2",    .type = type_word, .fn = fn_null },
        { .value = ">",           .type = type_outfile, .fn = fn_output },
        { .value = "output.txt",  .type = type_word, .fn = fn_null },
        { .value = "&&",          .type = type_logic, .fn = fn_and },
        { .value = "comando3",    .type = type_word, .fn = fn_null },
        { .value = ">>",          .type = type_outfile, .fn = fn_append },
        { .value = "output.txt",  .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence expected[] = {
        { .infile = NULL, .outfile = NULL, .args = (char *[]){ "comando1", NULL } },
        { .infile = NULL, .outfile = "output.txt", .args = (char *[]){ "comando2", NULL } },
        { .infile = NULL, .outfile = NULL, .args = NULL },
    };
}