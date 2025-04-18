/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:14:22 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/18 01:37:54 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./traitement.h"

void    quote_traitement(t_lexer_item *args)
{
    int     index;
    char    *str;
    char    *tmp;
    int     str_size;

    index = 0;
    while (args[index].value)
    {
        str = args[index].value;
        if (str[0] == '\'' || str[0] == '\"')
        {
            str_size = ft_strlen(str + 1) - 1;
            tmp = ft_calloc(str_size, sizeof(char));
            ft_memmove(tmp, str + 1, str_size);
            free(args[index].value);
            args[index].value = tmp;
        }
        index++;
    }
}
