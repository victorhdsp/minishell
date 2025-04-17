#include "./minishell.h"

int main(int ac, char **av)
{
    char		*envv[] = {
		"HOME=/root",
		"PWD=",
		"OLDPWD=",
		NULL
	};
	
	char *args[] ={
		"cd",
		"no_permission",
		NULL
	};

	int ret;

	t_my_env	*my_env = get_env(envv);


    if (av[1] && (ft_strcmp(av[1], "cd") == 0))
	{
        ret = ft_cd(&my_env, args);
	}
    
	printf("----------:%d", ret);

    ft_lstclear_env(&my_env); //lembrar de limpar a env na main pra nao dar leak
    
    return (ac);
}
