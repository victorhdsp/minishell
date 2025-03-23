#ifndef TOKENIZER_H
# define TOKENIZER_H

#include "../minishell.h"

enum            e_type_sentence_item
{
    infile,
    outfile,
    divider,
    parenthesis,
    word
};

enum            e_fn_sentence_item
{
    input,
    insert,
    output,
    append,
    pipe,
    and_if,
    and_or
};

typedef struct s_sentence_item
{
    char                        *value;
    enum e_type_sentence_item   type;
    enum e_fn_sentence_item     fn;
}                   t_sentence_item;

char                **word_breaker(const char *str);
t_sentence_item     *lexer(char *strs);

#endif