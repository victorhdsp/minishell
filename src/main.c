#include "./minishell.h"

int main(int ac, char **av, char **env)
{
    t_my_env *my_env = get_env(env);

    if (av[1] && (ft_strcmp(av[1], "env") == 0))
        print_env(my_env);
    if (av[1] && (ft_strcmp(av[1], "export") == 0))
    {   
       // print_env(my_env);
        ft_export(&my_env, av[2]);
        print_env(my_env);
    }
    printf("--------------------------%s", av[2]);

    return (ac);
}
