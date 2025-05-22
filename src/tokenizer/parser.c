/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:47:15 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/22 12:58:59 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_redirect(t_lexer_item *cmds, int index, int *result)
{
	if (cmds[index].type == type_infile || cmds[index].type == type_outfile)
	{
		if (cmds[index + 1].type != type_word)
			*result = index + 1;
		return (1);
	}
	return (0);
}

static int	ft_logic(t_lexer_item *cmds, int index, int *result, int *has_cmd)
{
	if (cmds[index].type == type_logic)
	{
		if (index == 0)
			*result = index + 1;
		else if (cmds[index - 1].type == type_logic)
			*result = index + 1;
		if (*result == 0)
			*has_cmd = 0;
		return (1);
	}
	return (0);
}

static int	ft_parenthesis(t_lexer_item *cmds, int index, int *result,
		int *has_open_parenthesis)
{
	if (cmds[index].fn == fn_open_parenthesis)
	{
		if (cmds[index + 1].type == type_logic)
			*result = index + 1;
		*has_open_parenthesis = *has_open_parenthesis + 1;
		return (1);
	}
	if (cmds[index].fn == fn_close_parenthesis)
	{
		if (cmds[index - 1].type != type_word)
			*result = index + 1;
		*has_open_parenthesis = *has_open_parenthesis - 1;
		if (*has_open_parenthesis < 0)
			*result = index + 1;
		return (1);
	}
	return (0);
}

static int	ft_command(t_lexer_item **cmds, int *has_open_parenthesis)
{
	int	index;
	int	result;
	int	has_cmd;

	index = 0;
	result = 0;
	has_cmd = 0;
	while ((*cmds)[index].value)
	{
		if ((*cmds)[index].type == type_word && has_cmd == 0)
		{
			(*cmds)[index].fn = fn_cmd;
			has_cmd = 1;
		}
		index += ft_redirect(*cmds, index, &result);
		ft_logic(*cmds, index, &result, &has_cmd);
		ft_parenthesis(*cmds, index, &result, has_open_parenthesis);
		if (result != 0)
			break ;
		index++;
	}
	return (result);
}

int	ft_parser(t_lexer_item **cmds)
{
	int		result;
	int		has_open_parenthesis;
	char	*err_message;

	if (!*cmds)
		return (1);
	has_open_parenthesis = 0;
	result = ft_command(cmds, &has_open_parenthesis);
	if (result != 0 || has_open_parenthesis > 0)
	{
		err_message = "(";
		errno = 2;
		if (result != 0)
			err_message = (*cmds)[result - 1].value;
		print_error("syntax error near unexpected token `", err_message, "\'\n",
			NULL);
		return (2);
	}
	return (0);
}
