/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordbreaker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:47:15 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/26 18:25:23 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int  is_breaker(char first, char second)
{
    static char breakers[8] = {'(', ')', ' ', '>', '<', '|', '&'};
    int     index;
    int     result;

    index = 0;
    result = 0;
    while (breakers[index])
    {
        if (breakers[index] == first)
            result++;
        index++;
    }
    index = 3;
    if (first == second)
        while (breakers[index])
        {
            if (breakers[index] == second)
                result++;
            index++;
        }
    return (result);
}

static void     ft_get_first_word(const char *str, int *result)
{
    int         has_open_quote;
    int         index;

    has_open_quote = 0;
    result[0] = 0;
    result[1] = 0;
    while (str[result[0]] == ' ')
        result[0]++;
    index = result[0] + result[1];
    while (str[index])
    {
        if (result[1] == 0)
            result[1] += is_breaker(str[result[0]], str[result[0] + 1]);
        if (is_breaker(str[index], 0) && has_open_quote == 0)
            break;
        if ((str[index] == '\'' || str[index] == '\"') && has_open_quote == 0)
            has_open_quote = 1;
        else if ((str[index] == '\'' || str[index] == '\"') && has_open_quote == 1)
            has_open_quote = 0;
        result[1]++;
        index = result[0] + result[1];
    }
    if (has_open_quote == 1)
        result[1] = -1;
}

static int      ft_get_sentence_size(const char *str)
{
    const char  *tmp;
    int         word_cut[2];
    int         size;

    size = 0;
    tmp = str;
    ft_get_first_word(tmp, word_cut);
    while (word_cut[1])
    {
        if (word_cut[1] == -1)
        {
            ft_putstr_fd("Error: unclosed quotes\n", 2);
            return (-1);
        }
        tmp += word_cut[0] + word_cut[1];
        ft_get_first_word(tmp, word_cut);
        size++;
    }
    return (size);
}

static int      ft_populate_words(const char *str, char **result)
{
    int         index;
    const char  *tmp;
    int         word_cut[2];

    tmp = str;
    index = 0;
    ft_get_first_word(tmp, word_cut);
    while (word_cut[1])
    {
        result[index] = ft_substr(tmp, word_cut[0], word_cut[1]);
        if (!result[index])
            return (-1);
        tmp += word_cut[0] + word_cut[1];
        ft_get_first_word(tmp, word_cut);
        index++;
    }
    return (1);
}

char    **word_breaker(const char *str)
{
    char        **result;
    int         size;

    size = ft_get_sentence_size(str);
    if (size == -1 || size == 0)
        return (NULL);
    result = ft_calloc(size + 1, sizeof(char *));
    if (!result)
        return (NULL);
    result[size] = NULL;
    if (ft_populate_words(str, result) == -1)
        return (NULL);
    return (result);
}
