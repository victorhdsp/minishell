/*#include "./export.h"
#include "../../__test/utils.h"


// Chamada da função sem argumentos
Test(ft_export, functions_with_no_args) {
    //int ft_export(t_env_data env_data, char *word)
    char    *env[] = {"GDMSESSION=ubuntu", "DISPLAY=:0", "SHLVL=1", "OLDPWD=/home/rpassos-", "MAIL=rpassos-@student.42.rio"};
    int ret;
    
    ret = ft_export(env, NULL);

    int expected = 0;

    cr_assert(ret == expected, "valor de retorno diferente");
    
}
/*
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
}*/