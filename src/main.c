#include "./minishell.h"
#include "./traitement/traitement.h"
#include <readline/readline.h>

int main(int ac, char **av, char **env)
{
    char    *cmd;

    (void) ac;
    (void) av;
    system_flow(env, "minishell");
    cmd = readline("minishel: ");
    //cmd = ft_strdup("ls");
    minishell_flow(cmd);
    return (0);
}
