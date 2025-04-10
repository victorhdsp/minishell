#include "../../__test/utils.h"
#include "../env/env.h"
#include "cd.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

/*
chamar cd sem argumentos para ir para o home
chamar cd com argumento relativo e mudar de diretório - comparar o pwd da pasta antiga com o da nova || ver se o PWD e o OLDPWD foram alterados
	cd.. - subir um nivel
	cd ../outro_projeto - sobe para /home/usuario e entra em outro_projeto
	cd ./src - entra na pasta src que está dentro do diretório atual.
	cd . - ficar no diretório atual (sem mudar nada).
	cd ../../ - sobe dois níveis
	src/utils - entra nas subpastas src depois utils
	cd ../minishell/src - sobe um nível, depois entra em minishell/src
	cd dados/../minishell/../src - isso funciona
chamar cd com caminho absoluto e mudar de diretório - comparar o pwd da pasta antiga com o da nova || ver se o PWD e o OLDPWD foram alterados
chamar cd com um argumento invalido e retornar mensagem de erro
	multiplos argumentos: cd: too many arguments
	nao é um diretório: cd: arquivo.txt: Not a directory
	diretorio nao existe: cd: pasta_que_nao_existe: No such file or directory

*/

// redirecionador de fd
void	redirect_all_stdout_cd(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

/*// Chamada da função cd sem argumentos - verificar se foi pra home || verificar pwd e oldpwd
Test(ft_cd, cd_with_no_args)
{
	char		*env[] = {
		"HOME=/home/rpassos-",
		"PWD=/home/rpassos-/minishell",
		"OLDPWD=/home/rpassos-",
		NULL
	};
	
	char *args[] ={
		"cd",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(my_env, args);

	cr_assert(0 == ret, "Esperado retorno 0, obtido %d", ret);
	cr_assert_str_eq(my_env->next->value, "/home/rpassos-", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/home/rpassos-/minishell", "OLDPWD não alterado");
}*/

// Chamada da função cd com argumento relativo e mudar de diretório - comparar o pwd da pasta antiga com o da nova || ver se o PWD e o OLDPWD foram alterados
//cd.. - subir um nivel
Test(ft_cd, cd_go_up)
{
	char		*env[] = {
		"HOME=/home/rpassos-",
		"PWD=/home/rpassos-/minishell",
		"OLDPWD=/home/rpassos-",
		NULL
	};
	
	char *args[] ={
		"cd",
		"..",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(my_env, args);

	cr_assert(0 == ret, "Error cd ..");
	cr_assert_str_eq(my_env->next->value, "/home", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/home/rpassos-", "OLDPWD não alterado");
}
/*
//cd ../test - subir um nivel e entrar na pasta test
Test(ft_cd, cd_go_up_and_enter_dir)
{
	char		*env[] = {
		"HOME=/home/rpassos-",
		"PWD=/home/rpassos-/minishell",
		"OLDPWD=/home/rpassos-",
		NULL
	};
	
	char *args[] ={
		"cd",
		"../test",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(my_env, args);

	cr_assert(0 == ret, "Error cd ../test");
	cr_assert_str_eq(my_env->next->value, "/home/rpassos-/test", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/home/rpassos-/minishell", "OLDPWD não alterado");
}

//cd ./src - entra na pasta src que está dentro do diretório atual.
Test(ft_cd, cd_enter_dir_on_present_dir)
{
	char		*env[] = {
		"HOME=/home/rpassos-",
		"PWD=/home/rpassos-/minishell",
		"OLDPWD=/home/rpassos-",
		NULL
	};
	
	char *args[] ={
		"cd",
		"./src",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(my_env, args);

	cr_assert(0 == ret, "Error cd ./src");
	cr_assert_str_eq(my_env->next->value, "/home/rpassos-/minishell/src", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/home/rpassos-/minishell", "OLDPWD não alterado");
}

// cd . - ficar no diretório atual (sem mudar nada)
Test(ft_cd, cd_stay_on_dir)
{
	char		*env[] = {
		"HOME=/home/rpassos-",
		"PWD=/home/rpassos-/minishell",
		"OLDPWD=/home/rpassos-",
		NULL
	};
	
	char *args[] ={
		"cd",
		".",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(my_env, args);

	cr_assert(0 == ret, "Error cd .");
	cr_assert_str_eq(my_env->next->value, "/home/rpassos-/minishell", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/home/rpassos-/minishell", "OLDPWD não alterado");
}

// cd ../../ - sobe dois níveis
Test(ft_cd, cd_go_up_two_dirs)
{
	char		*env[] = {
		"HOME=/home/rpassos-",
		"PWD=/home/rpassos-/minishell",
		"OLDPWD=/home/rpassos-",
		NULL
	};
	
	char *args[] ={
		"cd",
		"../../",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(my_env, args);

	cr_assert(0 == ret, "Error cd ../../");
	cr_assert_str_eq(my_env->next->value, "/home", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/home/rpassos-/minishell", "OLDPWD não alterado");
}


// cd src/utils - entra nas subpastas src depois utils
Test(ft_cd, cd_go_sub_dir_two_times)
{
	char		*env[] = {
		"HOME=/home/rpassos-",
		"PWD=/home/rpassos-/minishell",
		"OLDPWD=/home/rpassos-",
		NULL
	};
	
	char *args[] ={
		"cd",
		"src/echo",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(my_env, args);

	cr_assert(0 == ret, "Error cd src/echo");
	cr_assert_str_eq(my_env->next->value, "/home/rpassos-/minishell/src/echo", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/home/rpassos-/minishell", "OLDPWD não alterado");
}

// cd ../minishell/include/ - sobe um nível, depois entra em minishell/src
Test(ft_cd, cd_go_up_and_down_two_times)
{
	char		*env[] = {
		"HOME=/home/rpassos-",
		"PWD=/home/rpassos-/minishell",
		"OLDPWD=/home/rpassos-",
		NULL
	};
	
	char *args[] ={
		"cd",
		"../minishell/include/",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(my_env, args);

	cr_assert(0 == ret, "Error cd ../minishell/include/");
	cr_assert_str_eq(my_env->next->value, "/home/rpassos-/minishell/src/include", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/home/rpassos-/minishell", "OLDPWD não alterado");
}

// cd learning/../include/../src/env_management - misturado
Test(ft_cd, cd_mixed)
{
	char		*env[] = {
		"HOME=/home/rpassos-",
		"PWD=/home/rpassos-/minishell",
		"OLDPWD=/home/rpassos-",
		NULL
	};
	
	char *args[] ={
		"cd",
		"learning/../include/../src/env_management",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(my_env, args);

	cr_assert(0 == ret, "Error cd learning/../include/../src/env_management");
	cr_assert_str_eq(my_env->next->value, "/home/rpassos-/minishell/src/env_management", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/home/rpassos-/minishell", "OLDPWD não alterado");
}

// Chamada da função cd com path absoluto
Test(ft_cd, cd_with_absolute_path)
{
	char		*env[] = {
		"HOME=/home/rpassos-",
		"PWD=/home/rpassos-/minishell",
		"OLDPWD=/home/rpassos-",
		NULL
	};
	
	char *args[] ={
		"cd",
		"/home/rpassos-/minishell/src/tokenizer",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(my_env, args);

	cr_assert(0 == ret, "Error cd /home/rpassos-/minishell/src/tokenizer");
	cr_assert_str_eq(my_env->next->value, "/home/rpassos-/minishell/src/env_management", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/home/rpassos-/minishell", "OLDPWD não alterado");
}

// Chamada da função cd com argumento inválido
// cd com multiplos argumentos: cd: too many arguments
Test(ft_cd, cd_with_multiple_args, .init = redirect_all_stdout_cd)
{
	char		*env[] = {
		"HOME=/home/rpassos-",
		"PWD=/home/rpassos-/minishell",
		"OLDPWD=/home/rpassos-",
		NULL
	};
	
	char *args[] ={
		"cd",
		"/home/rpassos-/minishell/src/tokenizer",
		"/home/rpassos-/minishell/src/echo",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(my_env, args);

	cr_assert(0 != ret, "Retorno do erro diferente");
	cr_assert_stdout_eq_str("cd: too many arguments\n", "Erro multiple args diferente");
}

// cd nao é um diretório: cd: arquivo.txt: Not a directory
Test(ft_cd, cd_with_no_directory, .init = redirect_all_stdout_cd)
{
	char		*env[] = {
		"HOME=/home/rpassos-",
		"PWD=/home/rpassos-/minishell",
		"OLDPWD=/home/rpassos-",
		NULL
	};
	
	char *args[] ={
		"cd",
		"README.md",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(my_env, args);

	cr_assert(0 != ret, "Retorno do erro diferente");
	cr_assert_stdout_eq_str("cd: README.md: Not a directory\n", "Erro não é um diretório");
}

// cd diretorio nao existe: cd: pasta_que_nao_existe: No such file or directory
Test(ft_cd, cd_with_inexistent_directory, .init = redirect_all_stdout_cd)
{
	char		*env[] = {
		"HOME=/home/rpassos-",
		"PWD=/home/rpassos-/minishell",
		"OLDPWD=/home/rpassos-",
		NULL
	};
	
	char *args[] ={
		"cd",
		"pasta_que_nao_existe",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(my_env, args);

	cr_assert(0 != ret, "Retorno do erro diferente");
	cr_assert_stdout_eq_str("cd: pasta_que_nao_existe: No such file or directory\n", "Erro diretório nao existe");
}

// cd sem premissao: cd: diretório_secreto: Permission denied
Test(ft_cd, cd_with_no_permission, .init = redirect_all_stdout_cd)
{
	char		*env[] = {
		"HOME=/home/rpassos-",
		"PWD=/home/rpassos-/minishell",
		"OLDPWD=/home/rpassos-",
		NULL
	};
	
	char *args[] ={
		"cd",
		"no_permission",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(my_env, args);

	cr_assert(0 != ret, "Retorno do erro diferente");
	cr_assert_stdout_eq_str("cd: no_permission: Permission denied\n", "Erro diretório nao existe");
}
*/