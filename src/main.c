#include "./minishell.h"

int main(int argc, char **argv, char **env)
{
    t_my_env *my_env = get_env(env);

    ft_export(my_env, NULL);
    
    return (0);
}
