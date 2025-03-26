/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:47:15 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/26 18:39:25 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void  ft_redirect(t_lexer_item *cmds, int index, int *result)
{
    if (cmds[index].type == type_infile || cmds[index].type == type_outfile)
    {
        if (cmds[index + 1].type != type_word)
            *result = index + 2;
    }
}

static void  ft_logic(t_lexer_item *cmds, int index, int *result, int *has_cmd)
{
    if (cmds[index].type == type_logic)
    {
        if (index == 0)
            *result = index + 1;
        else if (cmds[index - 1].type == type_logic)
            *result = index + 1;
        if (*result == 0)
            *has_cmd = 0;
    }
}

static void  ft_parenthesis(t_lexer_item *cmds, int index, int *result, int *has_open_parenthesis)
{
    if (cmds[index].fn == fn_open_parenthesis)
    {
        if (cmds[index + 1].type == type_logic)
            *result = index + 1;
        *has_open_parenthesis = *has_open_parenthesis + 1;
    }
    if (cmds[index].fn == fn_close_parenthesis)
    {
        if (cmds[index - 1].type != type_word)
            *result = index + 1;
        *has_open_parenthesis = *has_open_parenthesis - 1;
        if (*has_open_parenthesis < 0)
            *result = index + 1;
    }
}

static int     ft_command(t_lexer_item **cmds, int *has_open_parenthesis)
{
    
    int     index;
    int     result;
    int     has_cmd;

    index = 0;
    result = 0;
    has_cmd = 0;
    while ((*cmds)[index].value)
    {
        ft_redirect (*cmds, index, &result);
        ft_logic (*cmds, index, &result, &has_cmd);
        ft_parenthesis (*cmds, index, &result, has_open_parenthesis);
        if ((*cmds)[index].type == type_word && has_cmd == 0)
        {
            (*cmds)[index].fn = fn_cmd;
            has_cmd = 1;
        }
        if (result != 0)
            break;
        index++;
    }
    return (result);
}

int ft_parser(t_lexer_item **cmds)
{
    int     result;
    int     has_open_parenthesis;
    
    has_open_parenthesis = 0;
    result = ft_command(cmds, &has_open_parenthesis);
    if (result != 0 || has_open_parenthesis > 0)
    {
        ft_putstr_fd("syntax error near unexpected token `", 2);
        if (result != 0)
            ft_putstr_fd((*cmds)[result - 1].value, 2);
        else
            ft_putchar_fd('(', 2);
        ft_putstr_fd("\'\n", 2);
        return (2);
    }
    return (0);
}
