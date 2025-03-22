/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordbreaker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:47:15 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/22 11:51:31 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char    **word_breaker(const char *str)
{
    char    **result;
    result = ft_calloc(2, sizeof(char *));
    result[0] = ft_strdup("test");
    result[1] = NULL;
    
    return (result);
}