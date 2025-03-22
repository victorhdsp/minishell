/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:24:25 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/22 11:44:20 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

int     ft_assert(int input, int expected) {
    int result = 0;

    result = input == expected;
    cr_assert(result);
    return (result);
}

int     ft_assert_str(char *input, char *expected) {
    int     result;

    if (strcmp(input, expected) == 0)
        result = 1;
    else
        result = 0;
    cr_assert(result);
    return (result);
}

int     ft_assert_str_list(char **input, char **expected) {
    int     result;
    int     i;

    i = 0;
    while (input[i] && expected[i]) {
        if (strcmp(input[i], expected[i]) != 0) {
            result = 0;
            break;
        }
        i++;
    }
    if (input[i] == NULL && expected[i] == NULL)
        result = 1;
    else
        result = 0;
    cr_assert(result);
    return (result);
}

void    ft_free_str(char *str) {
    if (str)
        free(str);
}

void    ft_free_str_list(char **str_list) {
    int i;

    i = 0;
    while (str_list[i]) {
        free(str_list[i]);
        i++;
    }
    free(str_list);
}