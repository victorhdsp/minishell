/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:24:25 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/21 19:43:40 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

int ft_assert(int input, int expected) {
    if (input == expected) {
        cr_assert(1);
        return (1);
    }
    else {
        cr_assert(0);
        return (0);
    }
}

int    ft_assert_str(char *input, char *expected) {
    int     index;

    index = 0;
    while (index)
    {
        if (!ft_assert(input[index], expected[index]))
            return (0);
        index++;
    }
    return (1);
}

int    ft_assert_str_list(char **input, char **expected) {
    int     index;

    index = 0;
    while (index)
    {
        if (!ft_assert_str(input[index], expected[index]))
            return (0);
        index++;
    }
    return (1);
}