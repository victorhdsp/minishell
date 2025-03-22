/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordbreaker.test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:59:02 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/21 19:51:07 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include "../../__test/utils.h"
#include "./tokenizer.h"

// Divisão por espaços simples:
// Entrada: "comando argumento1 argumento2"
// Saída esperada: ["comando", "argumento1", "argumento2"]
Test(wordbreaker, divide_by_simple_spaces) {
    char *input = "comando argumento1 argumento2";
    const result = word_breaker(input);
    ft_assert_str_list(result, (char *[]){"comando", "argumento1", "argumento2", NULL});
}

// Divisão com múltiplos espaços consecutivos:
// Entrada: "comando argumento1 argumento2"
// Saída esperada: ["comando", "argumento1", "argumento2"]
Test(wordbreaker, divide_multiples_consecutive_spaces) {
    char *input = "comando argumento1      argumento2";
    cr_assert(0);
}

// Divisão com espaços no início e no fim:
// Entrada: " comando argumento1 argumento2 "
// Saída esperada: ["comando", "argumento1", "argumento2"]
Test(wordbreaker, divide_space_in_start_and_end) {
    char *input = " comando argumento1 argumento2 ";
    cr_assert(0);
}

// Divisão com espaços dentro de aspas:
// Entrada: "comando \"argumento com espaços\" argumento2"
// Saída esperada: ["comando", "argumento com espaços", "argumento2"]
Test(wordbreaker, divide_space_in_quotes) {
    char *input = "comando \"argumento com espaços\" argumento2";
    cr_assert(0);
}

// Divisão com aspas simples e duplas:
// Entrada: "comando 'argumento com espaços' \"outro argumento\""
// Saída esperada: ["comando", "argumento com espaços", "outro argumento"]
Test(wordbreaker, divide_with_simple_and_double_quotes) {
    char *input = "comando 'argumento com espaços' \"outro argumento\"";
    cr_assert(0);
}

// Divisão com caracteres especiais como separadores:
// Entrada: "comando1|comando2 > output.txt"
// Saída esperada: ["comando1", "|", "comando2", ">", "output.txt"]
Test(wordbreaker, divide_with_special_caracter) {
    char *input = "comando1|comando2 > output.txt=e";
    cr_assert(0);
}

// Divisão com caracteres especiais dentro de aspas:
// Entrada: "comando \"argumento | com > caracteres\""
// Saída esperada: ["comando", "argumento | com > caracteres"]
Test(wordbreaker, divide_with_special_caracter_in_quotes) {
    char *input = "comando \"argumento | com > caracteres\"";
    cr_assert(0);
}

// Divisão com parênteses:
// Entrada: "(comando1 && comando2) || comando3"
// Saída esperada: ["(", "comando1", "&&", "comando2", ")", "||", "comando3"]
Test(wordbreaker, divide_with_parenthesis) {
    char *input = "(comando1 && comando2) || comando3";
    cr_assert(0);
}

// Divisão com parênteses dentro de aspas:
// Entrada: "comando \"(argumento com parênteses)\""
// Saída esperada: ["comando", "(argumento com parênteses)"]
Test(wordbreaker, divide_with_parenthesis_in_quotes) {
    char *input = "comando \"(argumento com parênteses)\"";
    cr_assert(0);
}

// Divisão com redirecionamentos:
// Entrada: "comando < input.txt > output.txt"
// Saída esperada: ["comando", "<", "input.txt", ">", "output.txt"]
Test(wordbreaker, divide_with_redirects) {
    char *input = "comando < input.txt > output.txt";
    cr_assert(0);
}

// Divisão com redirecionamentos dentro de aspas:
// Entrada: "comando \"< input.txt > output.txt\""
// Saída esperada: ["comando", "< input.txt > output.txt"]
Test(wordbreaker, divide_with_redirects_in_quotes) {
    char *input = "comando \"< input.txt > output.txt\"";
    cr_assert(0);
}

// Divisão com combinações complexas:
// Entrada: "comando1 | comando2 && comando3 > \"output file.txt\""
// Saída esperada: ["comando1", "|", "comando2", "&&", "comando3", ">", "output file.txt"]
Test(wordbreaker, divide_with_complex_combination) {
    char *input = "comando1 | comando2 && comando3 > \"output file.txt\"";
    cr_assert(0);
}

// Divisão com caracteres de escape:
// Entrada: "comando\\ argumento"
// Saída esperada: ["comando\\", "argumento"]
Test(wordbreaker, divide_with_escape) {
    char *input = "comando\\ argumento";
    cr_assert(0);
}

// Divisão com aspas não fechadas:
// Entrada: "comando \"argumento não fechado"
// Saída esperada: ["comando", "argumento não fechado"] ou um erro, dependendo da implementação.
Test(wordbreaker, divide_with_quotes_not_complete) {
    char *input = "comando \"argumento não fechado";
    cr_assert(0);
}

// Divisão com apenas separadores:
// Entrada: "| > < && ||"
// Saída esperada: ["|", ">", "<", "&&", "||"]
Test(wordbreaker, divide_only_with_dividers) {
    char *input = "| > < && ||";
    cr_assert(0);
}

// Divisão com strings vazias:
// Entrada: ""
// Saída esperada: []
Test(wordbreaker, empty_divide) {
    char *input = "";
    cr_assert(0);
}

// Divisão com apenas espaços:
// Entrada: " "
// Saída esperada: []
Test(wordbreaker, divide_with_only_space) {
    char *input = " ";
    cr_assert(0);
}