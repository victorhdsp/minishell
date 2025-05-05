#include "../../__test/utils.h"
#include "./flow.h"


void suite_setup(void) {
    char		*env[] = {NULL};
	t_system	new_sys;

	new_sys.name = "test";
	new_sys.last_exit_status = 0;
	new_sys.env = env;
	get_system(&new_sys);
}

Test(ambient, set_system_info, .init = suite_setup)
{
	t_system	expected_sys;

	expected_sys = get_system(NULL);
	cr_assert_str_eq(expected_sys.name, "test",
                    "Nome do sistema esperado está incorreto: esperado {test}, recebido {%s}",
					expected_sys.name);
	cr_assert_eq(expected_sys.last_exit_status, 0,
                    "Ultimo exit do sistema esperado está incorreto: esperado {test}, recebido {%d}",
					expected_sys.last_exit_status);
	cr_assert_eq(expected_sys.env[0], NULL,
                    "Env do sistema esperado está incorreto: esperado {(null)}, recebido {%s}",
					expected_sys.env[0]);
}

Test(ambient, change_last_exit, .init = suite_setup)
{
	t_system	expected_sys;

	set_system_exit_status(1);
	expected_sys = get_system(NULL);
	cr_assert_eq(expected_sys.last_exit_status, 1,
                    "Ultimo exit do sistema esperado está incorreto: esperado {1}, recebido {%d}",
					expected_sys.last_exit_status);
}

Test(ambient, change_env, .init = suite_setup)
{
	t_system	expected_sys;
	char		*env[] = {"test=env", NULL};

	set_system_env(env);
	expected_sys = get_system(NULL);
	cr_assert_str_eq(expected_sys.env[0], "test=env",
                    "Env do sistema esperado está incorreto: esperado {test=env}, recebido {%s}",
					expected_sys.env[0]);
}

Test(ambient, get_env_var, .init = suite_setup)
{
	char		*expected_value;
	char		*env[] = {"test=env", NULL};

	set_system_env(env);
	expected_value = get_system_env("test");
	cr_assert_str_eq(expected_value, "env",
                    "O retorna da variável esperado está incorreto: esperado {env}, recebido {%s}",
					expected_value);
}
