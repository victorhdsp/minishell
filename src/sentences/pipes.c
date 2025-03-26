/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:59:02 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/26 12:51:57 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./sentences.h"

static  void ft_count_pipes(t_sentence_item *items, int *sentences_index)
{
    int     index;

    index = 0;
    *sentences_index = 1;
    while (items[index].value)
    {
        if (items[index].type == type_divider && items[index].fn != fn_pipe)
            break;
        if (items[index].fn == fn_pipe)
            *sentences_index = *sentences_index + 1;
        index++;
    }
}

static  void ft_count_words(t_sentence_item *items, int *words_index, int index)
{
    *words_index = 0;
    while (items[index].value)
    {
        if (items[index].type == type_divider)
            break;
        if (items[index].type == type_infile || items[index].type == type_outfile)
            index++;
        else if (items[index].type == type_word)
            *words_index = *words_index + 1;
        index++;
    }
}

static  void ft_create_sentence(t_sentence *sentence, t_sentence_item *items, int *index)
{
    int         words_index;

    ft_count_words(items, &words_index, *index);
    sentence->args = ft_calloc(words_index + 1, sizeof(char *));
    words_index = 0;
    while (items[*index].type != type_divider && items[*index].value)
    {
        if (items[*index].type == type_infile)
        {
            sentence->infile = items[*index + 1].value;
            *index = *index + 1;
        }
        else if (items[*index].type == type_outfile)
        {
            sentence->outfile = items[*index + 1].value;
            *index = *index + 1;
        }
        else if (items[*index].type == type_word)
        {
            sentence->args[words_index] = items[*index].value;
            words_index++;
        }
        *index = *index + 1;
    }
}

t_sentence  *ft_pipes(t_sentence_item *items)
{
    t_sentence  *sentences;
    int         sentences_total;
    int         sentences_index;
    int         items_index;
    
    sentences_index = 0;
    items_index = 0;
    ft_count_pipes(items, &sentences_total);
    sentences = ft_calloc(sentences_total + 1, sizeof(t_sentence));
    while (sentences_index < sentences_total)
    {
        sentences[sentences_index].infile = NULL;
        sentences[sentences_index].outfile = NULL;
        sentences[sentences_index].args = NULL;
        ft_create_sentence(&sentences[sentences_index], items, &items_index);
        items_index++;
        sentences_index++;
    }
    return (sentences);
}
