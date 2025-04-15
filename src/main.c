#include "./minishell.h"
#include "./ambient/ambient.h"

int main(int ac, char **av, char **env)
{
    t_system    system;

    system.name = "victor";
    system.last_exit_status = 0;
    system.env = env;

    get_system(&system);
    set_system_exit_status(1);

    char		*param[] = {
		"export",
		"RENATO=TESTE",
		NULL};

	t_my_env	*my_env = get_env(env);
    ft_export(&my_env, param);
    set_system_env(get_env_arr(my_env));

    get_system(NULL);
}