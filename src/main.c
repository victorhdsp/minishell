#include "./minishell.h"

int main(int ac, char **av, char **env)
{
    t_my_env *my_env = get_env(env);
    char *ret;

     char    *param[] = {
        "export",
        "#RENATO",
        NULL};

    if (av[1] && (ft_strcmp(av[1], "env") == 0))
        print_env(my_env);
    if (av[1] && (ft_strcmp(av[1], "export") == 0))
    {   
        ft_export(&my_env, av);
        ft_export(&my_env, param);
        //order(my_env);
    }
    if (av[1] && (ft_strcmp(av[1], "unset") == 0))
    {   
        ft_export(&my_env, av);
        ft_export(&my_env, param);
        //order(my_env);
    }
    if (av[1] && (ft_strcmp(av[1], "echo") == 0)) 
 {
    //       ft_echo(ac, av);  
        ret = ft_echo(ac, av);
        printf("\n%s", ret);
}
    ft_lstclear_env(&my_env); //lembrar de limpar a env na main pra nao dar leak
    
    return (ac);
}
