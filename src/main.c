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

    char *input = strdup("");
    char *expected = "";
    char **breaked = word_breaker(input);
    t_lexer_item *lexed = lexer(breaked);
    quote_traitement(lexed);
}
