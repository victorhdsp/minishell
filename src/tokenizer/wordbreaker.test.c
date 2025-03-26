/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordbreaker.test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:59:02 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/24 10:18:10 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./tokenizer.h"
#include "../../__test/utils.h"

// Divisão por espaços simples:
// Entrada: "comando argumento1 argumento2"
// Saída esperada: ["comando", "argumento1", "argumento2"]
Test(wordbreaker, divide_by_simple_spaces) {
    const char *input = "comando argumento1 argumento2";
    char *expected[] = {"comando", "argumento1", "argumento2", NULL};
    char **result = word_breaker(input);
    
    ft_assert_str_list(result, expected);
    ft_free_str_list(result);
}

// Divisão com múltiplos espaços consecutivos:
// Entrada: "comando argumento1 argumento2"
// Saída esperada: ["comando", "argumento1", "argumento2"]
Test(wordbreaker, divide_multiples_consecutive_spaces) {
    const char *input = "comando argumento1      argumento2";
    char *expected[] = {"comando", "argumento1", "argumento2", NULL};
    char **result = word_breaker(input);

    ft_assert_str_list(result, expected);
    ft_free_str_list(result);
}

// Divisão com espaços no início e no fim:
// Entrada: " comando argumento1 argumento2 "
// Saída esperada: ["comando", "argumento1", "argumento2"]
Test(wordbreaker, divide_space_in_start_and_end) {
    const char *input = " comando argumento1 argumento2 ";
    char *expected[] = {"comando", "argumento1", "argumento2", NULL};
    char **result = word_breaker(input);

    ft_assert_str_list(result, expected);
    ft_free_str_list(result);cr_assert(1);
}

// Divisão com espaços dentro de aspas:
// Entrada: "comando \"argumento com espaços\" argumento2"
// Saída esperada: ["comando", "argumento com espaços", "argumento2"]
Test(wordbreaker, divide_space_in_quotes) {
    const char *input = "comando \"argumento com espaços\" argumento2";
    char *expected[] = {"comando", "\"argumento com espaços\"", "argumento2", NULL};
    char **result = word_breaker(input);

    ft_assert_str_list(result, expected);
    ft_free_str_list(result);
}

// Divisão com aspas simples e duplas:
// Entrada: "comando 'argumento com espaços' \"outro argumento\""
// Saída esperada: ["comando", "argumento com espaços", "outro argumento"]
Test(wordbreaker, divide_with_simple_and_double_quotes) {
    const char *input = "comando 'argumento com espaços' \"outro argumento\"";
    char *expected[] = {"comando", "'argumento com espaços'", "\"outro argumento\"", NULL};
    char **result = word_breaker(input);

    ft_assert_str_list(result, expected);
    ft_free_str_list(result);
}

// Divisão com caracteres especiais como separadores:
// Entrada: "comando1|comando2 > output.txt"
// Saída esperada: ["comando1", "|", "comando2", ">", "output.txt"]
Test(wordbreaker, divide_with_special_caracter) {
    const char *input = "comando1|comando2 > output.txt=e";
    char *expected[] = {"comando1", "|", "comando2", ">", "output.txt", "=", "e", NULL};
    char **result = word_breaker(input);

    ft_assert_str_list(result, expected);
    ft_free_str_list(result);cr_assert(1);
}

// Divisão com caracteres especiais dentro de aspas:
// Entrada: "comando \"argumento | com > caracteres\""
// Saída esperada: ["comando", "argumento | com > caracteres"]
Test(wordbreaker, divide_with_special_caracter_in_quotes) {
    const char *input = "comando \"argumento | com > caracteres\"";
    char *expected[] = {"comando", "\"argumento | com > caracteres\"", NULL};
    char **result = word_breaker(input);

    ft_assert_str_list(result, expected);
    ft_free_str_list(result);
}

// Divisão com parênteses:
// Entrada: "(comando1 && comando2) || comando3"
// Saída esperada: ["(", "comando1", "&&", "comando2", ")", "||", "comando3"]
Test(wordbreaker, divide_with_parenthesis) {
    const char *input = "(comando1 && comando2) || comando3";
    char *expected[] = {"(", "comando1", "&&", "comando2", ")", "||", "comando3", NULL};
    char **result = word_breaker(input);

    ft_assert_str_list(result, expected);
    ft_free_str_list(result);
}

// Divisão com parênteses dentro de aspas:
// Entrada: "comando \"(argumento com parênteses)\""
// Saída esperada: ["comando", "(argumento com parênteses)"]
Test(wordbreaker, divide_with_parenthesis_in_quotes) {
    const char *input = "comando \"(argumento com parênteses)\"";
    char *expected[] = {"comando", "\"(argumento com parênteses)\"", NULL};
    char **result = word_breaker(input);

    ft_assert_str_list(result, expected);
    ft_free_str_list(result);
}

// Divisão com redirecionamentos:
// Entrada: "comando < input.txt > output.txt"
// Saída esperada: ["comando", "<", "input.txt", ">", "output.txt"]
Test(wordbreaker, divide_with_redirects) {
    const char *input = "comando < input.txt > output.txt";
    char *expected[] = {"comando", "<", "input.txt", ">", "output.txt", NULL};
    char **result = word_breaker(input);

    ft_assert_str_list(result, expected);
    ft_free_str_list(result);
}

// Divisão com redirecionamentos dentro de aspas:
// Entrada: "comando \"< input.txt > output.txt\""
// Saída esperada: ["comando", "< input.txt > output.txt"]
Test(wordbreaker, divide_with_redirects_in_quotes) {
    const char *input = "comando \"< input.txt > output.txt\"";
    char *expected[] = {"comando", "\"< input.txt > output.txt\"", NULL};
    char **result = word_breaker(input);

    ft_assert_str_list(result, expected);
    ft_free_str_list(result);
}

// Divisão com combinações complexas:
// Entrada: "comando1 | comando2 && comando3 > \"output file.txt\""
// Saída esperada: ["comando1", "|", "comando2", "&&", "comando3", ">", "output file.txt"]
Test(wordbreaker, divide_with_complex_combination) {
    const char *input = "comando1 | comando2 && comando3 > \"output file.txt\"";
    char *expected[] = {"comando1", "|", "comando2", "&&", "comando3", ">", "\"output file.txt\"", NULL};
    char **result = word_breaker(input);

    ft_assert_str_list(result, expected);
    ft_free_str_list(result);
}

// Divisão com caracteres de escape:
// Entrada: "comando\\ argumento"
// Saída esperada: ["comando\\", "argumento"]
Test(wordbreaker, divide_with_escape) {
    const char *input = "comando\\ argumento";
    char *expected[] = {"comando\\", "argumento", NULL};
    char **result = word_breaker(input);

    ft_assert_str_list(result, expected);
    ft_free_str_list(result);
}

// Divisão com aspas não fechadas:
// Entrada: "comando \"argumento não fechado"
// Saída esperada: NULL
Test(wordbreaker, divide_with_quotes_not_complete) {
    const char *input = "comando \"argumento não fechado";
    char *expected[] = {"comando", "argumento não fechado", NULL};
    char **result = word_breaker(input);

    cr_assert(result == 0);
}

// Divisão com apenas separadores:
// Entrada: "| > < && ||"
// Saída esperada: ["|", ">", "<", "&&", "||"]
Test(wordbreaker, divide_only_with_dividers) {
    const char *input = "| > < && ||";
    char *expected[] = {"|", ">", "<", "&&", "||", NULL};
    char **result = word_breaker(input);

    ft_assert_str_list(result, expected);
    ft_free_str_list(result);
}

// Divisão com multiplos separadores em sequencia:
// Entrada: "|>>|>|<||"
// Saída esperada: ["|", ">>", "|", ">", "<", "||"]
Test(wordbreaker, divide_with_multiple_dividers) {
    const char *input = "|>>|>|<||";
    char *expected[] = {"|", ">>", "|", ">", "|", "<", "||", NULL};
    char **result = word_breaker(input);

    ft_assert_str_list(result, expected);
    ft_free_str_list(result);
}

// Divisão com strings vazias:
// Entrada: ""
// Saída esperada: NULL
Test(wordbreaker, empty_divide) {
    const char *input = "";
    char *expected[] = {NULL};
    char **result = word_breaker(input);

    cr_assert(result == 0);
}

// Divisão com apenas espaços:
// Entrada: " "
// Saída esperada: NULL
Test(wordbreaker, divide_with_only_space) {
    const char *input = " ";
    char *expected[] = {NULL};
    char **result = word_breaker(input);

    cr_assert(result == 0);
}