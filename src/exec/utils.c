/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/16 15:23:59 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_super_path(char **super_path)
{
	int		index;

	index = 0;
	while (super_path[index])
	{
		free(super_path[index]);
		index++;
	}
	free(super_path);
}

static char	**create_super_path(void)
{
	char	**result;
	char	*path_var;
	char	*tmp;
	char	*pwd;

	path_var = get_system_env("PATH");
	tmp = ft_strjoin(path_var, ":");
	free(path_var);
	pwd = getcwd(NULL, 0);
	path_var = ft_strjoin(tmp, pwd);
	free(tmp);
	free(pwd);
	result = ft_split(path_var, ':');
	free(path_var);
	return (result);
}

static char *search_in_path(char *path, char *program)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(path, "/");
	result = ft_strjoin(tmp, program);
	free(tmp);
	if (access(result, R_OK) == 0)
		return (result);
	free(result);
	return (NULL);
}

char	*ft_get_extern_cmd(t_lexer_item *items)
{
	char	*result;
	char	**path_var_items;
	int		index;

	result = NULL;
	path_var_items = create_super_path();
	index = 0;
	while (items[index].value && items[index].fn != fn_cmd)
		items++;
	index = 0;
	while (path_var_items[index] && (*items).value)
	{
		result = search_in_path(path_var_items[index], (*items).value);
		if (result)
			break;
		index++;
	}
	if (!result && (*items).value)
		print_error((*items).value, ": command not found\n", NULL, NULL);
	free_super_path(path_var_items);
	return (result);
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
		return (exit_builtin(args));
	return (-1);
}
