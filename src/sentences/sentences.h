#ifndef SENTENCES_H
# define SENTENCES_H

#include "../tokenizer/tokenizer.h"

typedef struct s_sentence
{
    char        *infile;
    char        *outfile;
    char        **args;
}                   t_sentence;

t_sentence  *ft_pipes(t_sentence_item *itens);

#endif