/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:12:05 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/02 10:55:21 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_redirect_token(char *token)
{
	return (
		ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0
		|| ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0
	);
}

bool	ft_get_extern_cmd_not_found(char *cmd)
{
	char	**paths;
	char	*path_var;
	bool	found;

	if (is_redirect_token(cmd))
		return (true);
	path_var = get_system_env("PATH");
	if (!path_var)
		return (print_cmd_not_found(cmd));
	paths = ft_split(path_var, ':');
	free(path_var);
	found = check_command_in_paths(paths, cmd);
	free_arr_with_null(paths, get_arr_size(paths));
	if (!found && !is_redirect_token(cmd))
		print_error(cmd, ": command not found\n", NULL, 127);
	return (found);
}

bool	validate_first_token(char **cmds)
{
	if (!cmds || !cmds[0])
		return (false);
	if (is_redirect_token(cmds[0]))
		return (true);
	if ((cmds[0][0] == '.' && ft_strcmp(cmds[0], "./minishell") != 0)
	|| cmds[0][0] == '/' || cmds[0][0] == '\\')
	{
		print_error(cmds[0], ": command not found\n", NULL, 127);
		free_arr_with_null(cmds, get_arr_size(cmds));
		return (false);
	}
	return (true);
}

bool	is_built_in_or_invalid(char *cmd)
{
	if (ft_strcmp(cmd, "./minishell") == 0)
		return (true);
	if (is_redirect_token(cmd))
		return (true);
	if (cmd[0] == '.' || cmd[0] == '/')
		return (false);
	return (
		ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
	);
}
