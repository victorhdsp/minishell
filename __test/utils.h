/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/09 13:40:19 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include <criterion/hooks.h>
#include <stdio.h>
#include <setjmp.h>

int     ft_assert(int input, int expected);
int     ft_assert_str(char *input, char *expected);
int     ft_assert_str_list(char **input, char **expected);

void    ft_free_str(char *str);
void    ft_free_str_list(char **str_list);

void    redirect_stdout(void);
void    redirect_stderr(void);
#endif