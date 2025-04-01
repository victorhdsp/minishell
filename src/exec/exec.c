/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/01 13:37:16 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../minishell.h"

static void ft_exec_builtin(t_lexer_item *items)
{
    int     index;

    index = 0;
    while (items[index].value && items[index].fn != fn_cmd)
        index++;
    if (ft_strncmp(items[index].value, "echo", 4))
        return;
    else if (ft_strncmp(items[index].value, "cd", 2))
        return;
    else if (ft_strncmp(items[index].value, "pwd", 3))
        return;
    else if (ft_strncmp(items[index].value, "export", 6))
        return;
    else if (ft_strncmp(items[index].value, "unset", 5))
        return;
    else if (ft_strncmp(items[index].value, "env", 3))
        return;
    else if (ft_strncmp(items[index].value, "exit", 4))
        return;
}

static void ft_prepare_exec_child(t_sentence sentence)
{
    ft_use_redirects(sentence.items);
    ft_exec_builtin(sentence.items);
    exit(EXIT_SUCCESS);
}

void    ft_prepare_exec(t_sentence *sentence)
{
    int     index;
    int     *pid;

    index = 0;
    while (sentence[index].args)
        index++;
    pid = ft_calloc(index + 1, sizeof(int));
    index = 0; 
    while (sentence[index].args)
    {
        pid[index] = fork();
        if (pid[index] < 0)
        {
            ft_putstr_fd("unexpected error on create child process", 2);
            exit(EXIT_FAILURE);
        }
        if (pid[index] != 0)
            ft_prepare_exec_child(sentence[index]);
        index++;
    }
    while (sentence[index].args)
    {
        waitpid(pid[index], NULL, 0);
        index++;
    }
}
