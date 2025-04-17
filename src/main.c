#include "./minishell.h"

int main(int ac, char **av, char **env)
{
    t_my_env *my_env = get_env(env);
    char *input[] = {"echo", NULL};

    char    *envv[] = {
        "GDMSESSION=ubuntu",
        "DISPLAY=:0",
        "SHLVL=1",
        "OLDPWD=/home/rpassos-",
        "MAIL=rpassos-@student.42.rio",
        NULL
        };
    t_my_env *my_env2 = get_env(envv);

    char    *envv2[] = {
        "unset",
        "GDMSESSION",
        "MAIL",
        "OLDPWDA",
        NULL
        };

    char *args_pwd[] = {
		"pwd",
		NULL
	};


    if (av[1] && (ft_strcmp(av[1], "env") == 0))
        print_env(my_env2);
    if (av[1] && (ft_strcmp(av[1], "export") == 0))
    {   
        ft_export(&my_env, av);
        //ft_export(&my_env, param);
        //print_env(my_env);
    }
    if (av[1] && (ft_strcmp(av[1], "unset") == 0))
    {   
        print_env(my_env2);
        ft_unset(&my_env2, envv2);
        printf("==========\n");
        
        print_env(my_env2);
        //order(my_env);
    }
    if (av[1] && (ft_strcmp(av[1], "echo") == 0)) 
    {
    //       ft_echo(ac, av);  
        ft_echo(1, input);
    }
    if (av[1] && (ft_strcmp(av[1], "pwd") == 0)) 
    {
         ft_pwd(args_pwd);
    }
    ft_lstclear_env(&my_env); //lembrar de limpar a env na main pra nao dar leak
    
    return (ac);
}
