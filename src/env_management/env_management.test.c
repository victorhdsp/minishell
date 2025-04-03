#include "./env_management.h"
#include "../env/env.h"
#include "../../__test/utils.h"
#include "criterion-2.4.2/include/criterion/assert.h"
#include "criterion-2.4.2/include/criterion/criterion.h"
#include "criterion-2.4.2/include/criterion/redirect.h"

/*
testes:
usar o redirecionador
fazer env - verificar numero correto das envs
fazer export com key=value - incrementar um na env e contar || achar o conteudo inserido com o chr
fazer export somente com key - nao incrementa na env (contador nao muda) || incrementa um no export (contador muda) || achar o conteudo inserido com o chr
fazer somente export - lista as variaveis exportadas com um certo formato de texto
fazer export com variavel com nome invalido - checar retorno 1 || env nao muda
fazer export com varias key=value e ver se entra tudo - checar quantidade que incrementou e buscar o conteudo inserido
fazer export com varias key, key=value e key com valor errado - deve aceitar as certas e dar o erro pra errada
    *se tiver mais de uma errada só da o erro da primeira
fazer unset - decrementa um na env (contador decresce)
*/

//redirecionador de fd
void redirect_all_stdout(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

//Chamada da função ENV - comparação de strs
Test(print_env, show_all_env_and_check_return, .init=redirect_all_stdout)
{
    char    *env[] = {
        "GDMSESSION=ubuntu",
        "DISPLAY=:0",
        "SHLVL=1",
        "OLDPWD=/home/rpassos-",
        "MAIL=rpassos-@student.42.rio",
        NULL};
    int     ret = print_env(env);

    cr_assert_stdout_eq_str("GDMSESSION=ubuntu\nDISPLAY=:0\nSHLVL=1\nOLDPWD=/home/rpassos-\nMAIL=rpassos-@student.42.rio", "Expected to print the env list with line break");
	cr_assert_eq(0, res);
}

//Chamada da função ENV - contagem de variáveis de ambiente
Test(print_env, line_counter, .init=redirect_all_stdout)
{
    char    *env[] = {
        "GDMSESSION=ubuntu",
        "DISPLAY=:0",
        "SHLVL=1",
        "OLDPWD=/home/rpassos-",
        "MAIL=rpassos-@student.42.rio",
        NULL};
    int     ret = print_env(env);

    fflush(stdout);
    char *output = cr_get_redirected_stdout();

    int counter = 0;
    int index = 0;
    while (output[index] != '\0')
    {
        if (output[index] == '\n')
            counter++;
        index++;
    }

    int expected_lines = 5;
    cr_assert_eq(counter, expected_lines, "Esperado %d linhas, mas recebeu %d", expected_lines, counter);
}

//fazer export com key=value - incrementar um na env e contar || achar o conteudo inserido com o chr
//Chamada da função EXPORT com key=value contando linhas
Test(ft_export, add_var_line_counter)
{
    char    *env[] = {
        "GDMSESSION=ubuntu",
        "DISPLAY=:0",
        "SHLVL=1",
        "OLDPWD=/home/rpassos-",
        "MAIL=rpassos-@student.42.rio",
        NULL};
    t_my_env *my_env = get_env(env);

    ft_export(my_env, RENATO=TESTE);

    print_env(env);

    fflush(stdout);
    char *output = cr_get_redirected_stdout();

    int counter = 0;
    int index = 0;
    while (output[index] != '\0')
    {
        if (output[index] == '\n')
            counter++;
        index++;
    }

    int expected_lines = 6;
    cr_assert_eq(counter, expected_lines, "Esperado %d linhas, mas recebeu %d", expected_lines, counter);
}

//Chamada da função EXPORT com key=value buscando o conteúdo inserido
Test(ft_export, add_var_line_counter)
{
    char    *env[] = {
        "GDMSESSION=ubuntu",
        "DISPLAY=:0",
        "SHLVL=1",
        "OLDPWD=/home/rpassos-",
        "MAIL=rpassos-@student.42.rio",
        NULL};
    t_my_env *my_env = get_env(env);
    

    ft_export(my_env, "RENATO=TESTE");

    print_env(env);

    fflush(stdout);
    char *output = cr_get_redirected_stdout();
    char *find = ft_strnstr(output, "RENATO=TEST", ft_strlen(output));

    cr_assert_not_null(ft_strnstr(output, "RENATO=TESTE", ft_strlen(output)), 
        "A variável RENATO=TESTE não foi encontrada na saída do print_env");
}





/*
export
Se a variável for exportada com sucesso, retorna 0.

Se houver um erro (como um nome inválido de variável), retorna 1.

unset
Se a variável for removida com sucesso, retorna 0.

Se a variável não existir, também retorna 0 (Bash não considera isso um erro).
*/
/*
// Chamada da função export sem argumentos
Test(ft_export, functions_with_no_args) {
    //int ft_export(t_env_data env_data, char *word)
    char    *env[] = {"GDMSESSION=ubuntu", "DISPLAY=:0", "SHLVL=1", "OLDPWD=/home/rpassos-", "MAIL=rpassos-@student.42.rio"};
    int ret;
    
    ret = ft_export(env, NULL);

    int expected = 0;

    cr_assert(ret == expected, "valor de retorno diferente");
    
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
}*/