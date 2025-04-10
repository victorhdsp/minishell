#include "./minishell.h"

int main(int ac, char **av)
{
    char		*envv[] = {
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

	t_my_env	*my_env = get_env(envv);


    if (av[1] && (ft_strcmp(av[1], "cd") == 0))
        ft_cd(my_env, args);
    

    ft_lstclear_env(&my_env); //lembrar de limpar a env na main pra nao dar leak
    
    return (ac);
}
