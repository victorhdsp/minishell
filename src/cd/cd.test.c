#include "../../__test/utils.h"
#include "../env/env.h"
#include "./cd.h"
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

// Chamada da função cd sem argumentos - verificar se foi pra home || verificar pwd e oldpwd
Test(ft_cd, cd_with_no_args, .init = redirect_all_stdout_cd)
{
	char		*env[] = {
		"HOME=/home/renato",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};
	
	char *args[] ={
		"cd",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(&my_env, args);



	cr_assert(0 == ret, "Esperado retorno 0, obtido %d", ret);

	printf("%s", my_env->next->value);
	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';
	cr_assert_str_eq(output, "/root", "PWD: imprimiu: %s", output);

	printf("%s", my_env->next->next->value);
	fflush(stdout);
	FILE *fp2 = cr_get_redirected_stdout(); 
	char output2[4096];
	size_t bytes2 = fread(output2, 1, sizeof(output2) - 1, fp2);
	output2[bytes2] = '\0';
	cr_assert_str_eq(output2, "/usr/src/app/__test", "OLDPWD: imprimiu: %s", output2);



/*	cr_assert_str_eq(my_env->next->value, "/root", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/usr/src/app/__test", "OLDPWD não alterado");
*/

}

// Chamada da função cd com argumento relativo e mudar de diretório - comparar o pwd da pasta antiga com o da nova || ver se o PWD e o OLDPWD foram alterados
//cd.. - subir um nivel
Test(ft_cd, cd_go_up)
{
	char		*env[] = {
		"HOME=/home/renato",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};
	
	char *args[] ={
		"cd",
		"..",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(&my_env, args);


	cr_assert(0 == ret, "Error cd ..");
	cr_assert_str_eq(my_env->next->value, "/usr/src/app", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/usr/src/app/__test", "OLDPWD não alterado");

	
}

//cd ../test - subir um nivel e entrar na pasta test
Test(ft_cd, cd_go_up_and_enter_dir)
{
	char		*env[] = {
		"HOME=/home/renato",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};
	
	char *args[] ={
		"cd",
		"../learning",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(&my_env, args);

	cr_assert(0 == ret, "Error cd ../learning");
	cr_assert_str_eq(my_env->next->value, "/usr/src/app/learning", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/usr/src/app/__test", "OLDPWD não alterado");
}

//cd ./src - entra na pasta src que está dentro do diretório atual.
Test(ft_cd, cd_enter_dir_on_present_dir)
{
	char		*env[] = {
		"HOME=/home/renato",
		"PWD=/usr/src/app/__test/",
		"OLDPWD=/home/renato",
		NULL
	};
	
	char *args[] ={
		"cd",
		"./testando",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(&my_env, args);

	cr_assert(0 == ret, "Error cd ./testando");
	cr_assert_str_eq(my_env->next->value, "/usr/src/app/__test/testando", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/usr/src/app/__test", "OLDPWD não alterado");
}

// cd . - ficar no diretório atual (sem mudar nada)
Test(ft_cd, cd_stay_on_dir)
{
	char		*env[] = {
		"HOME=/home/renato",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};
	
	char *args[] ={
		"cd",
		".",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(&my_env, args);

	cr_assert(0 == ret, "Error cd .");
	cr_assert_str_eq(my_env->next->value, "/usr/src/app/__test", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/usr/src/app/__test", "OLDPWD não alterado");
}

// cd ../../ - sobe dois níveis
Test(ft_cd, cd_go_up_two_dirs)
{
	char		*env[] = {
		"HOME=/home/renato",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};
	
	char *args[] ={
		"cd",
		"../../",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(&my_env, args);

	cr_assert(0 == ret, "Error cd ../../");
	cr_assert_str_eq(my_env->next->value, "/usr/src", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/usr/src/app/__test", "OLDPWD não alterado");
}


/*// cd src/utils - entra nas subpastas src depois utils
Test(ft_cd, cd_go_sub_dir_two_times)
{
	char		*env[] = {
		"HOME=/home/renato",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};
	
	char *args[] ={
		"cd",
		"src/echo",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(&my_env, args);

	cr_assert(0 == ret, "Error cd src/echo");
	cr_assert_str_eq(my_env->next->value, "/home/renato/minishell/src/echo", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/home/renato/minishell", "OLDPWD não alterado");
}*/

// cd ../minishell/include/ - sobe um nível, depois entra em minishell/src
Test(ft_cd, cd_go_uo_and_go_sub_dir_two_times)
{
	char		*env[] = {
		"HOME=/home/renato",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};
	
	char *args[] ={
		"cd",
		"../src/echo",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(&my_env, args);

	cr_assert(0 == ret, "Error cd src/echo");
	cr_assert_str_eq(my_env->next->value, "/usr/src/app/src/echo", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/usr/src/app/__test", "OLDPWD não alterado");
}

// cd learning/../include/../src/env_management - misturado
Test(ft_cd, cd_mixed)
{
	char		*env[] = {
		"HOME=/home/renato",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};
	
	char *args[] ={
		"cd",
		"../learning/../src/sentences/../env",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(&my_env, args);

	cr_assert(0 == ret, "Error cd /../learning/../src/sentences/../env");
	cr_assert_str_eq(my_env->next->value, "/usr/src/app/src/env", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/usr/src/app/__test", "OLDPWD não alterado");
}

// Chamada da função cd com path absoluto
Test(ft_cd, cd_with_absolute_path)
{
	char		*env[] = {
		"HOME=/home/renato",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};
	
	char *args[] ={
		"cd",
		"/usr/src/app/src/tokenizer",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(&my_env, args);

	cr_assert(0 == ret, "Error cd /usr/src/app/src/tokenizer");
	cr_assert_str_eq(my_env->next->value, "/usr/src/app/src/tokenizer", "PWD não alterado");
	cr_assert_str_eq(my_env->next->next->value, "/usr/src/app/__test", "OLDPWD não alterado");
}

// Chamada da função cd com argumento inválido
// cd com multiplos argumentos: cd: too many arguments
Test(ft_cd, cd_with_multiple_args, .init = redirect_all_stdout_cd)
{
	char		*env[] = {
		"HOME=/home/renato",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};
	
	char *args[] ={
		"cd",
		"/home/renato/minishell/src/tokenizer",
		"/home/renato/minishell/src/echo",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(&my_env, args);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

	cr_assert_str_eq(output, "cd: too many arguments\n", "Erro multiple args diferente");
	//cr_assert_stdout_eq_str("cd: too many arguments\n", "Erro multiple args diferente"); PQ NAO FUNCIONA????

}

// cd nao é um diretório: cd: arquivo.txt: Not a directory
Test(ft_cd, cd_with_no_directory, .init = redirect_all_stdout_cd)
{
	char		*env[] = {
		"HOME=/home/renato",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};
	
	char *args[] ={
		"cd",
		"Dockerfile",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(&my_env, args);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';
	
	printf("------------------------ %s", output);

	cr_assert(0 != ret, "Retorno do erro diferente");
	cr_assert_str_eq(output, "cd: Dockerfile: Not a directory\n", "Erro não é um diretório");
}

// cd diretorio nao existe: cd: pasta_que_nao_existe: No such file or directory
Test(ft_cd, cd_with_inexistent_directory, .init = redirect_all_stdout_cd)
{
	char		*env[] = {
		"HOME=/home/renato",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};
	
	char *args[] ={
		"cd",
		"pasta_que_nao_existe",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(&my_env, args);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';

	cr_assert(0 != ret, "Retorno do erro diferente");
	cr_assert_str_eq(output, "cd: pasta_que_nao_existe: No such file or directory\n", "Erro diretório nao existe");
	
}
/*
// cd sem premissao: cd: diretório_secreto: Permission denied
Test(ft_cd, cd_with_no_permission, .init = redirect_all_stdout_cd)
{
	char		*env[] = {
		"HOME=/home/renato",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};
	
	char *args[] ={
		"cd",
		"test_no_permission",
		NULL
	};

	t_my_env	*my_env = get_env(env);
	int ret = ft_cd(&my_env, args);

	cr_assert(-1 != ret, "Retorno do erro diferente");
	cr_assert_stdout_eq_str("cd: test_no_permission: Permission denied\n", "Erro diretório sem permissao");

}*/