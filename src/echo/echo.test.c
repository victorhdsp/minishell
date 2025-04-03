#include "echo.h"
#include "../env/env.h"
#include "../../__test/utils.h"


// Chamada da função ft_echo sem argumentos
Test(ft_echo, functions_with_no_args) {
    char *input[] = {"echo", NULL};
    char *ret;
    char *expected = "\n";    

    ret = ft_echo(1, input);

    
    cr_assert_str_eq(ret , expected, "expected: %s \nretorno echo: %s", expected, ret);
}

// Chamada da função ft_echo sem argumentos com -n
Test(ft_echo, functions_with_no_args_and_flag) {
    char *input[] = {"echo", "-n", NULL};
    char *ret;
    char *expected = "";    

    ret = ft_echo(2, input);

    cr_assert_str_eq(ret , expected, "expected: %s \nretorno echo: %s", expected, ret);
}

// Chamada da função ft_echo com argumentos e com flag inexistente
Test(ft_echo, functions_with_wrong_flag_and_args) {
    char *input[] = {"echo", "-nx", "renato", NULL};
    char *ret;
    char *expected = "-nx renato\n";    

    ret = ft_echo(3, input);

    cr_assert_str_eq(ret , expected, "expected: %s \nretorno echo: %s", expected, ret);
}

// Chamada da função ft_echo com argumentos normais
Test(ft_echo, functions_with_args) {
    char    *input[] = {"echo", "renato", "passos", "oi", NULL};
    char *expected = "renato passos oi\n";    
    
    char *ret = ft_echo(4, input);
    
    cr_assert_str_eq(ret , expected, "expected: %s \nretorno echo: %s", expected, ret);
}

// Chamada da função ft_echo com argumentos normais + -n no inicio
Test(ft_echo, functions_with_args_and_flag) {
    char    *input[] = {"echo", "-n", "renato", "passos", "oi", NULL};
    char *expected = "renato passos oi";    
    
    char *ret = ft_echo(5, input);
    
    cr_assert_str_eq(ret , expected, "expected: %s \nretorno echo: %s", expected, ret);
}

// Chamada da função ft_echo com argumentos normais + consecutivos -n no inicio
Test(ft_echo, functions_with_args_and_consecutive_flags) {
    char    *input[] = {"echo", "-n", "-n", "-n", "-n", "-n", "renato", "passos", "oi", NULL};
    char *expected = "renato passos oi";    
    
    char *ret = ft_echo(9, input);
    
    cr_assert_str_eq(ret , expected, "expected: %s \nretorno echo: %s", expected, ret);
}

// Chamada da função ft_echo com argumentos normais + -nnnnnnnnnnnnn no inicio
Test(ft_echo, functions_with_args_and_multiple_char_in_flag) {
    char    *input[] = {"echo", "-nnnnnnnnnnnnn", "renato", "passos", "oi", NULL};
    char *expected = "renato passos oi";    
    
    char *ret = ft_echo(5, input);
    
    cr_assert_str_eq(ret , expected, "expected: %s \nretorno echo: %s", expected, ret);
}

// Chamada da função ft_echo com argumentos normais + -n no meio
Test(ft_echo, functions_with_args_and_flag_on_middle) {
    char    *input[] = {"echo", "renato", "passos", "-n", "oi", NULL};
    char *expected = "renato passos -n oi\n";    
    
    char *ret = ft_echo(5, input);
    
    cr_assert_str_eq(ret , expected, "expected: %s \nretorno echo: %s", expected, ret);
}

// Chamada da função ft_echo com argumentos normais + -n no final
Test(ft_echo, functions_with_args_and_flag_on_end) {
    char    *input[] = {"echo", "renato", "passos", "-n", "oi", NULL};
    char *expected = "renato passos -n oi\n";    
    
    char *ret = ft_echo(5, input);
    
    cr_assert_str_eq(ret , expected, "expected: %s \nretorno echo: %s", expected, ret);
}
