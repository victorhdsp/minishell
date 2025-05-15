/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/15 06:49:26 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exec.h"
#include "../exit/exit.h"

char	*ft_get_extern_cmd(t_lexer_item *items)
{
	char	*path_var;
	char	*result;
	char	*tmp;
	char	**path_var_items;
	int		index;

	path_var = get_system_env("PATH");
	tmp = ft_strjoin(path_var, ":");
	free(path_var);
	path_var = ft_strjoin(tmp, getcwd(NULL, 0));
	path_var_items = ft_split(path_var, ':');
	index = 0;
	while (items[index].value && items[index].fn != fn_cmd)
		items++;
	index = 0;
	while (path_var_items[index] && (*items).value)
	{
		tmp = ft_strjoin(path_var_items[index], "/");
		result = ft_strjoin(tmp, (*items).value);
		free(tmp);
		if (access(result, R_OK) == 0)
			return (result);
		free(result);
		index++;
	}
	if ((*items).value)
		print_error((char *)(*items).value, ": command not found\n", NULL, NULL);
	return (NULL);
}

int	ft_exec_builtin(t_lexer_item *items, char **args)
{
	int	index;

	index = 0;
	while (items[index].value && items[index].fn != fn_cmd)
		index++;
	if (!items[index].value)
		return (0);
	if (!ft_strncmp(items[index].value, "echo", 4))
		return (ft_echo(args));
	else if (!ft_strncmp(items[index].value, "cd", 2))
		return (cd_builtin(args));
	else if (!ft_strncmp(items[index].value, "pwd", 3))
		return (ft_pwd());
	else if (!ft_strncmp(items[index].value, "export", 6))
		return (export_builtin(args));
	else if (!ft_strncmp(items[index].value, "unset", 5))
		return (unset_builtin(args));
	else if (!ft_strncmp(items[index].value, "env", 3))
		return (env_builtin(args));
	else if (!ft_strncmp(items[index].value, "exit", 4))
		return(exit_builtin(args));
	return (-1);
}
