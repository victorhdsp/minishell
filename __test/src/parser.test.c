/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:59:02 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/31 09:11:21 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/tokenizer/tokenizer.h"
#include "../utils.h"

Test(parser, only_one_cmd_and_no_errors) {
    char *cmd[] = {"comando", "argumento1", "argumento2", NULL};
    t_lexer_item *input = lexer((char **)cmd);

    int             expected = 0;
    int             result = ft_parser((t_lexer_item **)&input);

    cr_assert(expected == result);
    cr_assert(input[0].fn == fn_cmd);
}

Test(parser, two_cmds_and_no_errors) {
    char *cmd[] = {"comando1", "|", "comando2", ">", "output.txt=e", NULL};
    t_lexer_item *input = lexer((char **)cmd);

    int             expected = 0;
    int             result = ft_parser((t_lexer_item **)&input);

    cr_assert(expected == result);
    cr_assert(input[0].fn == fn_cmd);
    cr_assert(input[2].fn == fn_cmd);
}

Test(parser, error_in_pipe) {
    char *cmd[] = {"|", "comando2", ">", "output.txt=e", NULL};
    t_lexer_item *input = lexer((char **)cmd);

    int             expected = 2;
    int             result = ft_parser((t_lexer_item **)&input);

    cr_assert(expected == result);
}

Test(parser, error_in_redirect) {
    char *cmd[] = {"comando1", "|", "comando2", ">", "|", "=e", NULL};
    t_lexer_item *input = lexer((char **)cmd);

    int             expected = 2;
    int             result = ft_parser((t_lexer_item **)&input);

    cr_assert(expected == result);
    cr_assert(input[0].fn == fn_cmd);
    cr_assert(input[2].fn == fn_cmd);
}

Test(parser, open_an_close_parenthesis_no_errors) {
    char *cmd[] = {"(", "comando1", "&&", "comando2", ")", "||", "comando3", NULL};
    t_lexer_item *input = lexer((char **)cmd);

    int             expected = 0;
    int             result = ft_parser((t_lexer_item **)&input);

    cr_assert(expected == result);
    cr_assert(input[1].fn == fn_cmd);
    cr_assert(input[3].fn == fn_cmd);
}

Test(parser, open_parenthesis_and_not_close_has_error) {
    char *cmd[] = {"(", "comando1", "&&", "comando2", "||", "comando3", NULL};
    t_lexer_item *input = lexer((char **)cmd);

    int             expected = 2;
    int             result = ft_parser((t_lexer_item **)&input);

    cr_assert(expected == result);
    cr_assert(input[1].fn == fn_cmd);
    cr_assert(input[3].fn == fn_cmd);
}

Test(parser, close_parenthesis_and_not_open_has_error) {
    char *cmd[] = {"comando1", "&&", "comando2", ")", "||", "comando3", NULL};
    t_lexer_item *input = lexer((char **)cmd);

    int             expected = 2;
    int             result = ft_parser((t_lexer_item **)&input);

    cr_assert(expected == result);
    cr_assert(input[0].fn == fn_cmd);
    cr_assert(input[2].fn == fn_cmd);
}

Test(parser, simple_quote) {
    char *cmd[] = {"tr", "''", "','", "|", "cat", "-e", "|", "ls", NULL};
    t_lexer_item *input = lexer((char **)cmd);

    int             expected = 0;
    int             result = ft_parser((t_lexer_item **)&input);

    cr_assert(expected == result);
    cr_assert(input[0].fn == fn_cmd);
    cr_assert(input[4].fn == fn_cmd);
    cr_assert(input[7].fn == fn_cmd);
}
