#include "../../__test/utils.h"
#include "../env/env.h"
#include "./env_management.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

/*
testes:
usar o redirecionador
fazer env - verificar numero correto das envs
fazer export com key=value - incrementar um na env e contar
	|| achar o conteudo inserido com o chr
fazer export somente com key=- incrementar um na env e contar
	|| achar o conteudo inserido com o chr
fazer export somente com key - nao incrementa na env (contador nao muda)
	|| incrementa um no export (contador muda)
	|| achar o conteudo inserido com o chr
fazer somente export
	- lista as variaveis exportadas com um certo formato de texto
fazer export com variavel com nome invalido - checar retorno 1 || env nao muda
fazer export com varias key=value e ver se entra tudo
	- checar quantidade que incrementou e buscar o conteudo inserido
fazer export com varias key, key=value e key com valor errado
	- deve aceitar as certas e dar o erro pra errada
	*se tiver mais de uma errada só da o erro da primeira
fazer unset - decrementa um na env (contador decresce)
*/

// redirecionador de fd
void	redirect_all_stdout(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

// Chamada da função ENV - comparação de strs
Test(print_env, show_all_env_and_check_return, .init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};

	t_my_env	*my_env = get_env(env);;

	int ret = print_env(my_env);

	fflush(stdout);	
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

	//cr_assert_stdout_eq_str("GDMSESSION=ubuntu\nDISPLAY=:0\nSHLVL=1\nOLDPWD=/home/rpassos-\nMAIL=rpassos-@student.42.rio\n", "Não exibiu as variáveis da env");//PQ NAO FUNCIONA???
	cr_assert(strstr(output, "GDMSESSION=ubuntu"), "GDMSESSION não está presente");
	cr_assert(strstr(output, "DISPLAY=:0"), "DISPLAY não está presente");
	cr_assert(strstr(output, "SHLVL=1"), "SHLVL não está presente");
	cr_assert(strstr(output, "OLDPWD=/home/rpassos-"), "OLDPWD não está presente");
	cr_assert(strstr(output, "MAIL=rpassos-@student.42.rio"), "MAIL não está presente");
	cr_assert_eq(0, ret);
}

// Chamada da função ENV - contagem de variáveis de ambiente
Test(print_env, env_line_counter, .init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL};

	t_my_env	*my_env;
	
	my_env = get_env(env);
	print_env(my_env);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

	int counter = 0;
	int index = 0;
	while (output[index] != '\0')
	{
		if (output[index] == '\n')
			counter++;
		index++;
	}

	int expected_lines = 5;
	cr_assert_eq(counter, expected_lines, "env_line_counter: Esperado %d linhas, mas recebeu %d", expected_lines, counter);
}

// fazer export com key=value - incrementar um na env e contar e achar o conteudo inserido com o chr
// Chamada da função EXPORT com key=value contando linhas
Test(ft_export, add_var_env_line_counter, .init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL};

	char		*param[] = {
		"export", 
		"RENATO=TESTE", 
		NULL};

	t_my_env	*my_env;

	my_env = get_env(env);
	ft_export(&my_env, param);
	print_env(my_env);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

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

// Chamada da função EXPORT com key=value buscando o conteúdo inserido
Test(ft_export, add_var_env_find_var, .init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL};
	char		*param[] = {
		"export",
		"RENATO=TESTE",
		NULL};

	t_my_env	*my_env = get_env(env);
	
	ft_export(&my_env, param);
	print_env(my_env);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

	char *find = ft_strnstr(output, "RENATO=TEST", ft_strlen(output));
	cr_assert_not_null(ft_strnstr(output, "RENATO=TESTE", ft_strlen(output)), "A variável RENATO=TESTE não foi encontrada na saída do print_env");
}

// fazer export somente com key= incrementar um na env e contar e achar o conteudo inserido com o chr
// Chamada da função EXPORT com key= contando linhas
Test(ft_export, add_var_with_equal_and_no_value_env_line_counter,
	.init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};
	char		*param[] = {
		"export",
		"RENATO=",
		NULL};

	t_my_env	*my_env = get_env(env);

	ft_export(&my_env, param);
	print_env(my_env);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

	int counter = 0;
	int index = 0;
	while (output[index] != '\0')
	{
		if (output[index] == '\n')
			counter++;
		index++;
	}

	int expected_lines = 6;

	cr_assert_eq(counter, expected_lines, "Esperado %d linhas, mas recebeu %d",
		expected_lines, counter);
}

// Chamada da função EXPORT com key= buscando o conteúdo inserido
Test(ft_export, add_var_env_with_equal_and_no_value_find_var,
	.init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};
	
	char		*param[] = {
		"export",
		"RENATOAAA=",
		NULL};

	t_my_env	*my_env = get_env(env);

	ft_export(&my_env, param);
	print_env(my_env);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';
	char *find = ft_strnstr(output, "RENATO=TEST", ft_strlen(output));
	cr_assert_not_null(ft_strnstr(output, "RENATOAAA=", ft_strlen(output)), "A variável RENATOAAA= não foi encontrada na saída do print_env");
}

// fazer export somente com key - nao incrementa na env (contador nao muda) || incrementa um no export (contador muda)	|| achar o conteudo inserido com o chr
// Chamada da função export somente com key verificando se a env foi ou não incrementada
Test(ft_export, add_var_not_add_in_env, .init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};
	char		*param[] = {
		"export",
		"RENATO",
		NULL};

	t_my_env	*my_env = get_env(env);
		
	ft_export(&my_env, param);
	print_env(my_env);
	
	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

	int counter = 0;
	int index = 0;
	while (output[index] != '\0')
	{
		if (output[index] == '\n')
			counter++;
		index++;
	}

	int expected_lines = 5;
	cr_assert_neq(counter, expected_lines, "add_var_not_add_in_env: Esperado %d linhas, mas recebeu %d", expected_lines, counter);
}

// Chamada da função export somente com key verificando se a export foi ou não incrementada
Test(ft_export, add_var_export_line_counter, .init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};
	char		*param[] = {
		"export",
		"RENATO",
		NULL
	};

	char		*param2[] = {
		"export",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	
	ft_export(&my_env, param);
	ft_export(&my_env, param2);
	
	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

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

// Chamada da função EXPORT somente com key buscando o conteúdo inserido
Test(ft_export, add_var_export_find_var, .init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};
	char		*param[] = {
		"export",
		"RENATO",
		NULL
	};

	char		*param2[] = {
		"export",
		NULL
	};

	t_my_env	*my_env = get_env(env);

	ft_export(&my_env, param);
	ft_export(&my_env, param2);
	
	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

	cr_assert_not_null(ft_strnstr(output, "RENATO", ft_strlen(output)), "A variável RENATO não foi encontrada na saída do export ordenado");
}

// fazer somente export - lista as variaveis exportadas com um certo formato de texto
// Chamada da função export sozinha para ver se a lista está ordenada
Test(ft_export, check_ordered_list, .init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};
	
	char		*param[] = {
		"export",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	
	ft_export(&my_env, param);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

	cr_assert_str_eq(output, "declare -x DISPLAY=\":0\"\ndeclare -x GDMSESSION=\"ubuntu\"\ndeclare -x MAIL=\"rpassos-@student.42.rio\"\ndeclare -x OLDPWD=\"/home/rpassos-\"\ndeclare -x SHLVL=\"1\"\n", "A lista não está em ordem");
}

// fazer export com variavel com nome invalido - checar retorno 1 e msg de erro
// Chamada da função export com key invalida para verificar o retorno e a msg de erro
Test(ft_export, invalid_key_check_error_and_return, .init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};
	
	char		*param[] = {
		"export",
		"#RENATO", 
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int			ret;

	ret = ft_export(&my_env, param);
	fflush(stdout);

	cr_assert_eq(ret, 1, "Retorno de erro errado");
	cr_assert_stdout_eq_str("export: `#RENATO': not a valid identifier\n", "Mensagem de erro não funcionando");
}

// Chamada da função export com key invalida para verificar se a lista foi incrementada
Test(ft_export, invalid_key_check_list_size, .init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};
	
	char		*param[] = {
		"export",
		"#RENATO", 
		NULL
	};

	char		*param2[] = {
		"export", 
		NULL
	};

	t_my_env	*my_env = get_env(env);
	
	ft_export(&my_env, param);
	cr_redirect_stdout();
	ft_export(&my_env, param2);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

	int counter = 0;
	int index = 0;
	while (output[index] != '\0')
	{
		if (output[index] == '\n')
			counter++;
		index++;
	}

	int expected_lines = 5;

	cr_assert_eq(counter, expected_lines, "invalid_key_check_list_size: Esperado %d linhas, mas recebeu %d", expected_lines, counter);
}

// fazer export com varias key=value e ver se entra tudo - checar quantidade que incrementou e buscar o conteudo inserido
// Chamada da funçao export com varias key=value para verificar se todas foram incrementadas na lista
Test(ft_export, add_multiple_vars_line_counter, .init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};
	char		*param[] = {
		"export",
		"RENATO=123",
		"VICTOR=123",
		"MINISHELL=123",
		NULL
	};

	t_my_env	*my_env = get_env(env);

	ft_export(&my_env, param);
	print_env(my_env);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

	int counter = 0;
	int index = 0;
	while (output[index] != '\0')
	{
		if (output[index] == '\n')
			counter++;
		index++;
	}

	int expected_lines = 8;
	cr_assert_eq(counter, expected_lines, "Esperado %d linhas, mas recebeu %d", expected_lines, counter);
}

// Chamada da funçao export com varias key=value buscando elas no output
Test(ft_export, add_multiple_vars_find_vars, .init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};
	char		*param[] = {
		"export",
		"RENATO=123",
		"VICTOR=123",
		"MINISHELL=123",
		NULL};

	t_my_env	*my_env = get_env(env);

	ft_export(&my_env, param);
	print_env(my_env);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

	cr_assert_not_null(ft_strnstr(output, "RENATO=123", ft_strlen(output)), "A variável RENATO=123 não foi encontrada na saída do export ordenado");
	cr_assert_not_null(ft_strnstr(output, "VICTOR=123", ft_strlen(output)), "A variável VICTOR=123 não foi encontrada na saída do export ordenado");
	cr_assert_not_null(ft_strnstr(output, "MINISHELL=123", ft_strlen(output)), "A variável MINISHELL=123 não foi encontrada na saída do export ordenado");
}

// fazer export com varias key, key=value e key com valor errado - deve aceitar as certas e dar o erro pra errada
//*se tiver mais de uma errada ele dá o erro em todas
// Chamada da funçao export com varias key=value, algumas com erro, checando retorno e msg de erro
Test(ft_export,	add_multiple_invalid_and_valid_vars_check_return_and_error_message,	.init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};
	char		*param[] = {
		"export",
		"RENATO=123",
		"+REN=123",
		"VICTOR=123",
		"+VIC=123",
		"MINISHELL=123",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int			ret;
	
	ret = ft_export(&my_env, param);

	fflush(stdout);

	cr_assert_stdout_eq_str("export: `+REN=123': not a valid identifier\nexport: `+VIC=123': not a valid identifier\n", "Não printou as mensagens de erro");
	cr_assert_eq(ret, 1, "Valor de retorno errado");
}
// Chamada da funçao export com varias key=value, algumas com erro, verificando se as validas foram inseridas
Test(ft_export, add_multiple_invalid_and_valid_vars_find_valids,
	.init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};
	char		*param[] = {
		"export",
		"RENATO=123",
		"+REN=123",
		"VICTOR=123",
		"+VIC=123",
		"MINISHELL=123", NULL};

	t_my_env	*my_env = get_env(env);

	
	ft_export(&my_env, param);
	print_env(my_env);

	fflush(stdout);

	cr_assert_stdout_eq_str("export: `+REN=123': not a valid identifier\nexport: `+VIC=123': not a valid identifier\nGDMSESSION=ubuntu\nDISPLAY=:0\nSHLVL=1\nOLDPWD=/home/rpassos-\nMAIL=rpassos-@student.42.rio\nRENATO=123\nVICTOR=123\nMINISHELL=123\n", "Os elementos válidos não foram inseridos");
}

// fazer unset - decrementa um na env (contador decresce)
// Chamada da função unset buscando se a variavel "SHLVL=1" foi excluida
Test(ft_unset, remove_var_try_to_find_var, .init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};

	char		*param[] = {
		"unset",
		"SHLVL",
		NULL
	};
	t_my_env	*my_env = get_env(env);
	

	
	ft_unset(&my_env, param);
	print_env(my_env);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

	cr_assert_null(ft_strnstr(output, "SHLVL=1", ft_strlen(output)), "A variável SHLVL não foi removida da lista");
}

// Chamada da função unset contando linha para ver se decrementou
Test(ft_unset, remove_var_line_counter, .init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};

	char		*param[] = {"unset", "SHLVL", NULL};
	t_my_env	*my_env = get_env(env);

	ft_unset(&my_env, param);
	print_env(my_env);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

	int counter = 0;
	int index = 0;
	while (output[index] != '\0')
	{
		if (output[index] == '\n')
			counter++;
		index++;
	}

	int expected_lines =  4;
	cr_assert_eq(counter, expected_lines, "remove_var_line_counter: Esperado %d linhas, mas recebeu %d", expected_lines, counter);
}

// Chamada da função unset com varios argumentos contando linha para ver se decrementou e tentando buscar as variáveis
Test(ft_unset, remove_multiples_var_line_counter_and_try_to_find, .init = redirect_all_stdout)
{
	char		*env[] = {
		"GDMSESSION=ubuntu",
		"DISPLAY=:0", "SHLVL=1",
		"OLDPWD=/home/rpassos-",
		"MAIL=rpassos-@student.42.rio",
		NULL
	};

	char		*param[] = {
		"unset",
		"SHLVL",
		"DISPLAY",
		"OLDPWD",
		NULL
	};

	t_my_env	*my_env = get_env(env);

	ft_unset(&my_env, param);
	print_env(my_env);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';;

	int counter = 0;
	int index = 0;
	while (output[index] != '\0')
	{
		if (output[index] == '\n')
			counter++;
		index++;
	}

	int expected_lines =  2;
	cr_assert_eq(counter, expected_lines, "remove_multiples_var_line_counter_and_try_to_find: Esperado %d linhas, mas recebeu %d", expected_lines, counter);
	cr_assert(strstr(output, "GDMSESSION=ubuntu"), "GDMSESSION não está presente na saída");
	cr_assert(strstr(output, "MAIL=rpassos-@student.42.rio"), "MAIL não está presente na saída");
	cr_assert(!strstr(output, "SHLVL"), "SHLVL ainda está presente");
	cr_assert(!strstr(output, "DISPLAY"), "DISPLAY ainda está presente");
	cr_assert(!strstr(output, "OLDPWD"), "OLDPWD ainda está presente");
}

/*
export
Se a variável for exportada com sucesso, retorna 0.

Se houver um erro (como um nome inválido de variável), retorna 1.

unset
Se a variável for removida com sucesso, retorna 0.

Se a variável não existir, também retorna 0 (Bash não considera isso um erro).
*/