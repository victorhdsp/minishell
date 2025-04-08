#include "../../__test/utils.h"
#include "../env_management/env_management.h"
#include "echo.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

// redirecionador de fd
void	redirect_all_stdout_echo(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

// Chamada da função ft_echo sem argumentos
Test(ft_echo, functions_with_no_args, .init = redirect_all_stdout_echo)
{
	char	*input[] = {"echo", NULL};

	ft_echo(1, input);
	fflush(stdout);
	cr_assert_stdout_eq_str("\n", "Retorno diferente de \n");
}

// Chamada da função ft_echo sem argumentos com -n
Test(ft_echo, functions_with_no_args_and_flag, .init = redirect_all_stdout_echo)
{
	char	*input[] = {"echo", "-n", NULL};

	ft_echo(2, input);
	fflush(stdout);
	cr_assert_stdout_eq_str("", "Retorno diferente de ''");
}

// Chamada da função ft_echo com argumentos e com flag inexistente
Test(ft_echo, functions_with_wrong_flag_and_args,
	.init = redirect_all_stdout_echo)
{
	char	*input[] = {"echo", "-nx", "renato", NULL};

	ft_echo(3, input);
	fflush(stdout);
	cr_assert_stdout_eq_str("-nx renato\n", "Retorno diferente de -nx renato\\n");
}

// Chamada da função ft_echo com argumentos normais
Test(ft_echo, functions_with_args, .init = redirect_all_stdout_echo)
{
	char	*input[] = {"echo", "renato", "passos", "oi", NULL};

	ft_echo(4, input);
	fflush(stdout);
	cr_assert_stdout_eq_str("renato passos oi\n",
		"Retorno diferente de renato passos oi\\n");
}

// Chamada da função ft_echo com argumentos normais + -n no inicio
Test(ft_echo, functions_with_args_and_flag, .init = redirect_all_stdout_echo)
{
	char	*input[] = {"echo", "-n", "renato", "passos", "oi", NULL};

	ft_echo(sizeof(input) / sizeof(char *) - 1, input);
	fflush(stdout);
	cr_assert_stdout_eq_str("renato passos oi",
		"Retorno diferente de renato passos oi");
}

// Chamada da função ft_echo com argumentos normais + consecutivos -n no inicio
Test(ft_echo, functions_with_args_and_consecutive_flags,
	.init = redirect_all_stdout_echo)
{
	char	*input[] = {"echo", "-n", "-n", "-n", "-n", "-n", "renato",
			"passos", "oi", NULL};

	ft_echo(9, input);
	fflush(stdout);
	cr_assert_stdout_eq_str("renato passos oi",
		"Retorno diferente de renato passos oi");
}

// Chamada da função ft_echo com argumentos normais + -nnnnnnnnnnnnn no inicio
Test(ft_echo, functions_with_args_and_multiple_char_in_flag,
	.init = redirect_all_stdout_echo)
{
	char	*input[] = {"echo", "-nnnnnnnnnnnnn", "renato", "passos", "oi",
			NULL};

	ft_echo(5, input);
	fflush(stdout);
	cr_assert_stdout_eq_str("renato passos oi",
		"Retorno diferente de renato passos oi");
}

// Chamada da função ft_echo com argumentos normais + -n no meio
Test(ft_echo, functions_with_args_and_flag_on_middle,
	.init = redirect_all_stdout_echo)
{
	char	*input[] = {"echo", "renato", "passos", "-n", "oi", NULL};

	ft_echo(5, input);
	fflush(stdout);
	cr_assert_stdout_eq_str("renato passos -n oi\n",
		"Retorno diferente de renato passos -n oi\\n");
}

// Chamada da função ft_echo com argumentos normais + -n no final
Test(ft_echo, functions_with_args_and_flag_on_end,
	.init = redirect_all_stdout_echo)
{
	char	*input[] = {"echo", "renato", "passos", "oi", "-n", NULL};

	ft_echo(5, input);
	fflush(stdout);
	cr_assert_stdout_eq_str("renato passos oi -n\n", "Retorno diferente de renato passos oi -n\\n");
}
