/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/01 13:38:10 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../minishell.h"

int     ft_input(char *path)
{
    int             fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        exit(EXIT_FAILURE);
    }
    return (fd);
}

int     ft_heredoc(char *exit)
{
    int             files_count;
    char            *filename;
    int             fd;
    char            *content;

    files_count = ft_count_dir("/home/vide-sou/projetos/pessoal/rank3/minishell/local/heredoc/");
    content = ft_itoa(files_count);
    filename = ft_strjoin("/home/vide-sou/projetos/pessoal/rank3/minishell/local/heredoc/heredoc_", content);
    free(content);
    fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    free(filename);
    content = ft_get_next_line(0);
    while (ft_strncmp(content, exit, ft_strlen(exit)))
    {
        ft_putstr_fd(content, fd);
        free(content);
        content = ft_get_next_line(0);
    }
    free(content);
    return (fd);
}

void    ft_use_redirects(t_lexer_item *items)
{
    int     index;
    int     fd;

    index = 0;
    fd = -1;
    while (items[index].value)
    {

        if (items[index].fn == fn_output)
            fd = open(items[index + 1].value, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
        else if (items[index].fn == fn_append)
            fd = open(items[index + 1].value, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
        else if (items[index].fn == fn_input)
            fd = ft_input(items[index + 1].value);
        else if (items[index].fn == fn_heredoc)
            fd = ft_heredoc(items[index + 1].value);
        if (fd != -1)
            items[index + 1].value = &fd;
        fd = -1;
        index++;
    }
}

void    ft_check_cmd_path(t_lexer_item *items)
{
    int     index;

    index = 0;
    while (items[index].value && items[index].fn != fn_cmd)
        index++;
}