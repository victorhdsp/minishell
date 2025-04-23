#include "./minishell.h"
#include "./traitement/traitement.h"

int main(int ac, char **av, char **env)
{
    /*char *input = "\"comando\" \"$PATH\"";
    char **breaked = word_breaker(input);

    t_lexer_item *lexed = lexer(breaked);
    variable_traitement(lexed);
    quote_traitement(lexed);*/
    t_system system;
    system.name = "victor";
    system.last_exit_status = 0;
    system.env = env;
    get_system(&system);
  
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
