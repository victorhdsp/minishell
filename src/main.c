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

    //t_sentence_item input[] = {
    //    { .value = "comando",    .type = type_word, .fn = fn_null },
    //    { .value = "|",          .type = type_divider, .fn = fn_pipe },
    //    { .value = "argumento1", .type = type_word, .fn = fn_null },
    //    { .value = "argumento2", .type = type_word, .fn = fn_null },
    //    { .value = "&&",         .type = type_divider, .fn = fn_and },
    //    { .value = "comando2",   .type = type_word, .fn = fn_null },
    //    { .value = NULL }
    //};

    t_sentence_item input[] = {
        { .value = "comando",    .type = type_word, .fn = fn_null },
        { .value = "argumento1", .type = type_word, .fn = fn_null },
        { .value = "argumento2", .type = type_word, .fn = fn_null },
        { .value = NULL }
    };

    t_sentence  *result = ft_pipes((t_sentence_item *)input);
    
    return (1);
}
