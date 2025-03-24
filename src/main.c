#include "./minishell.h"

int     main(void)
{
    //word_breaker("comando argumento1 argumento2");
    //word_breaker("comando \"argumento com espaços\" argumento2");
    //word_breaker("comando1|comando2 > output.txt=e");
    //word_breaker("|>>|>|<||");
    //word_breaker("comando \"argumento não fechado");
    //word_breaker("");
    //word_breaker(" ");

    //char *input[] = {"comando1", "|", "comando2", "&&", "comando3", ">", "\"output file.txt\"", NULL};
    //char *input[] = {"|", ">", "<", "&&", "||", NULL};
    //char *input[] = {"comando1", "|", "comando2", ">", "output.txt", "=", "e", NULL};
    //lexer(input);

    /*char **input = word_breaker("comando argumento1 argumento2");
    t_sentence_item *cmds = lexer(input);
    int result = ft_parser(&cmds);
    
    int     index;
    index = 0;
    printf("input!\n");
    while (input[index])
    {
        printf("    %s\n", input[index]);
        index++;
    }
    index = 0;
    printf("lexer!\n");
    while (cmds[index].value)
    {
        printf("    value: %s\n", cmds[index].value);
        printf("    type: %d\n", cmds[index].type);
        printf("    fn: %d\n", cmds[index].fn);
        index++;
    }
    printf("parser!\n");
    printf("    result: %d\n", result);*/
    char *cmd[] = {"(", "comando1", "&&", "comando2", "||", "comando3", NULL};
    t_sentence_item *input = lexer((char **)cmd);

    int             expected = 2;
    int             result = ft_parser((t_sentence_item **)&input);
    return (1);
}
