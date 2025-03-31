/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:59:02 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/31 09:11:40 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/sentences/sentences.h"
#include "../utils.h"

static void ft_assert_redirect(t_redirect *result, t_redirect *expected, int pipe_index) {
    int i = 0;

    if (!result || !expected)
    {
        cr_assert(0, "\"Result\" ou \"Expected\" está vazio.");
        return;
    }

    while (expected[i].word)
    {
        cr_assert(result[i].word != NULL,
                  "Ocorreu um erro ao comparar o %d redirecionamento no %d pipe\nO Valor esperado \"%s\" mas o resultado é NULL",
                  i + 1, pipe_index + 1, expected[i].word);
                  
        cr_assert_str_eq(result[i].word, expected[i].word,
                         "Valor esperado \"%s\" mas obteve \"%s\"",
                         expected[i].word, result[i].word);
        cr_assert(result[i].fn == expected[i].fn,
                  "Valor esperado \"%d\" mas obteve \"%d\"",
                  expected[i].fn, result[i].fn);
        i++;
    }

    cr_assert(result[i].word == NULL,
        "A lista resultante possui redirecionamentos a mais do que o esperado (redirecionamento extra na posição %d)",
    i);
}

static void ft_assert_pipes(t_sentence *result, t_sentence *expected) {
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
        ft_assert_redirect(result[i].infile, expected[i].infile, i);
        ft_assert_redirect(result[i].outfile, expected[i].outfile, i);
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
        { .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = (char *[]){ "comando", "argumento1", "argumento2", NULL } },
        { .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = NULL },
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
        { .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = (char *[]){ "comando", NULL } },
        { .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = (char *[]){ "argumento1", "argumento2", NULL } },
        { .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = NULL },
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
        { .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = (char *[]){ "comando", NULL } },
        { .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = (char *[]){ "argumento1", "argumento2", NULL } },
        { .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = NULL },
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
        { .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = "output.txt", .fn = fn_output }, { .word = NULL }}, .args = (char *[]){ "comando", NULL } },
        { .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = NULL },
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
        { .infile = (t_redirect []){{ .word = "input.txt", .fn = fn_input }, { .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = (char *[]){ "comando", NULL } },
		{ .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = NULL },
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
		{ .infile = (t_redirect []){{ .word = "input.txt", .fn = fn_input }, { .word = NULL }}, .outfile = (t_redirect []){{ .word = "output.txt", .fn = fn_output }, { .word = NULL }}, .args = (char *[]){ "comando", NULL } },
        { .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = NULL },
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
        { .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = (char *[]){ "comando1", NULL } },
		{ .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = "output.txt", .fn = fn_output }, { .word = NULL }}, .args = (char *[]){ "comando2", "=e", NULL } },
        { .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = NULL },
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
        { .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = (char *[]){ "comando1", NULL } },
		{ .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = "output.txt", .fn = fn_append }}, .args = (char *[]){ "comando2", NULL } },
        { .infile = (t_redirect []){{ .word = NULL }}, .outfile = (t_redirect []){{ .word = NULL }}, .args = NULL },
    };
}
