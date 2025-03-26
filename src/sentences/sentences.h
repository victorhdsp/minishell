#ifndef SENTENCES_H
# define SENTENCES_H

#include "../tokenizer/tokenizer.h"
#include "../../include/libft/libft.h"

typedef struct s_sentence
{
    char        *infile;
    char        *outfile;
    char        **args;
}                   t_sentence;

t_sentence  *ft_pipes(t_lexer_item *items);

#endif