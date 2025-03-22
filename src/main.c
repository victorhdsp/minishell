#include "./minishell.h"

int     main(void)
{
    word_breaker("comando argumento1 argumento2");
    word_breaker("comando \"argumento com espaços\" argumento2");
    word_breaker("comando1|comando2 > output.txt=e");
    word_breaker("|>>|>|<||");
    word_breaker("comando \"argumento não fechado");
    return (1);
}
