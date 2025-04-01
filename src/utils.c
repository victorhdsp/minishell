/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:50:05 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/01 12:18:09 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_count_dir(char *dir_path)
{
    DIR             *dir;
    struct dirent   *files;
    int             index;

    dir = opendir(dir_path);
    if (!dir)
    {
        ft_putstr_fd("unexpected error on open dir\n", 2);
        exit(EXIT_FAILURE);
    }
    files = readdir(dir);
    while (files)
    {
        files = readdir(dir);
        index++;
    }
    if (closedir(dir))
    {
        ft_putstr_fd("unexpected error on close dir\n", 2);
        exit(EXIT_FAILURE);
    }
    return index - 2;
}