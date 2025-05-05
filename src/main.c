#include "./minishell.h"
#include "./traitement/traitement.h"
#include "./flow/flow.h"
#include <readline/readline.h>

int main(int ac, char **av, char **env)
{
    char        *cmd;
    t_system    system;

    (void) ac;
    (void) av;
    system_flow(env, ft_strdup("minishell"));
    cmd = readline("minishel: ");
    //cmd = ft_strdup("< ls > teste << VASCO");
    //cmd = ft_strdup("ls | cat -e > c");
    //cmd = ft_strdup("< c");
    minishell_flow(cmd);
    free(cmd);
    free_all_system();
    return (0);
}