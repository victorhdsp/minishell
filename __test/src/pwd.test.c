#include "../utils.h"
#include "../../src/env_management/env_management.h"
#include "../../src/cd/cd.h"
#include "../../src/pwd/pwd.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>


/*
pwd - retornar o caminho absoluto atual
pwd sem argumentos
pwd com argumentos
pwd com a PWD deletada
pwd com valor da PWD alterado
pwd em pasta que apagou antes - mostrar o path da pasta que nao existe mais
pwd em pasta que tirou a permissão  - mostrar o path da pasta

*/

// redirecionador de fd
void	redirect_all_stdout_pwd(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

//remover a pasta do docker pós execução do teste
void cleanup_deleted_dir(void)
{
	chdir("..");
	rmdir("pasta_deletada");
}


Test(ft_pwd, functions_with_no_args, .init = redirect_all_stdout_pwd)
{
	char		*env[] = {
		"HOME=/root",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};

	char *args[] = {
		"pwd",
		NULL
	};

	t_my_env	*my_env = get_env(env);

	ft_pwd(&my_env, args);
	fflush(stdout);
	cr_assert_stdout_eq_str("/usr/src/app/__test\n", "Retorno PWD sem argumentos\n");
}

Test(ft_pwd, functions_with_args, .init = redirect_all_stdout_pwd)
{
	char		*env[] = {
		"HOME=/root",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};

	char *args[] = {
		"pwd",
		"aaaa",
		"&81",
		NULL
	};

	t_my_env	*my_env = get_env(env);

	ft_pwd(&my_env, args);
	fflush(stdout);
	cr_assert_stdout_eq_str("/usr/src/app/__test\n", "Retorno PWD com argumentos\n");
}

Test(ft_pwd, functions_with_unseted_pwd, .init = redirect_all_stdout_pwd)
{
	char		*env[] = {
		"HOME=/root",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};
	
	char *args_unset[] = {
		"unset",
		NULL
	};

	char *args[] = {
		"pwd",
		NULL
	};

	t_my_env	*my_env = get_env(env);

	ft_unset(&my_env, args_unset);
	ft_pwd(&my_env, args);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';


	cr_assert_str_eq(output, "/usr/src/app/__test\n", "Retorno PWD unseted: %s", output);

}

Test(ft_pwd, functions_with_modified_pwd, .init = redirect_all_stdout_pwd)
{
	char		*env[] = {
		"HOME=/root",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};

	char *args_export[] = {
		"export",
		"PWD=conteudo_alterado",
		NULL
	};

	char *args[] = {
		"pwd",
		NULL
	};

	t_my_env	*my_env = get_env(env);

	ft_export(&my_env, args_export);
	ft_pwd(&my_env, args);
	fflush(stdout);
	cr_assert_stdout_eq_str("/usr/src/app/__test\n", "Retorno PWD alterada\n");
}

Test(ft_pwd, functions_with_deleted_dir, .init = redirect_all_stdout_pwd, .fini = cleanup_deleted_dir)
{
	char		*env[] = {
		"HOME=/root",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato","./test",
		NULL
	};

	char *args_cd[] = {
		"cd",
		"./pasta_deletada",
		NULL
	};

	char *args[] = {
		"pwd",
		NULL
	};

	t_my_env	*my_env = get_env(env);

	mkdir("pasta_deletada", 0700);
	ft_cd(&my_env, args_cd);
	rmdir(".");
	ft_pwd(&my_env, args);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';


	cr_assert_str_eq(output, "/usr/src/app/__test/pasta_deletada\n", "Retorno PWD deleted dir: %s\n", output);
}

Test(ft_pwd, functions_with_no_permission_dir, .init = redirect_all_stdout_pwd)
{
	char		*env[] = {
		"HOME=/root",
		"PWD=/usr/src/app/__test",
		"OLDPWD=/home/renato",
		NULL
	};

	char *args_cd[] = {
		"cd",
		"./test_no_permission",
		NULL
	};

	char *args[] = {
		"pwd",
		NULL
	};

	t_my_env	*my_env = get_env(env);

	mkdir("test_no_permission", 0700);
	ft_cd(&my_env, args_cd);
	chmod("../test_no_permission", 000);
	ft_pwd(&my_env, args);

	fflush(stdout);
	FILE *fp = cr_get_redirected_stdout(); 
	char output[4096];
	size_t bytes = fread(output, 1, sizeof(output) - 1, fp);
	output[bytes] = '\0';


	cr_assert_str_eq(output, "/usr/src/app/__test/test_no_permission\n", "Retorno PWD dir sem permissão: %s\n", output);
	
}
