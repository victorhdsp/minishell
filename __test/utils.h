/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/21 19:43:03 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <criterion/criterion.h>

int ft_assert(int input, int expected);
int ft_assert_str(char *input, char *expected);
int ft_assert_str_list(char **input, char **expected);

#endif