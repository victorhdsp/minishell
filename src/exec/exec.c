/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/02 13:09:15 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exec.h"

static char	*ft_get_extern_cmd(t_lexer_item *items)
{
	char	*path_var;
	char	*result;
	char	*tmp;
	char	**path_var_items;
	int		index;

	result = NULL;
	path_var = "/home/vide-sou/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/vide-sou/.local/bin";
	// Substituir por uma "get_path" ou algo nesse sentido.
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
	return (NULL);
}

static int	ft_exec_builtin(t_lexer_item *items)
{
	int	index;

	index = 0;
	while (items[index].value && items[index].fn != fn_cmd)
		index++;
	if (!items[index].value)
		return (-1);
	if (!ft_strncmp(items[index].value, "echo", 4))
		return (0);
	else if (!ft_strncmp(items[index].value, "cd", 2))
		return (0);
	else if (!ft_strncmp(items[index].value, "pwd", 3))
		return (0);
	else if (!ft_strncmp(items[index].value, "export", 6))
		return (0);
	else if (!ft_strncmp(items[index].value, "unset", 5))
		return (0);
	else if (!ft_strncmp(items[index].value, "env", 3))
		return (0);
	else if (!ft_strncmp(items[index].value, "exit", 4))
		return (0);
	return (-1);
}

static void	ft_prepare_exec_child(t_sentence sentence)
{
	int		result;
	char	*cmd;
	char	**env;

	cmd = NULL;
	env = ft_calloc(1, sizeof(char *));
	ft_use_redirects(sentence.items);
	result = ft_exec_builtin(sentence.items);
	if (result >= 0)
		exit(result);
	cmd = ft_get_extern_cmd(sentence.items);
	if (cmd)
		result = execve(cmd, sentence.args, env);
	exit(EXIT_SUCCESS);
}

void	ft_prepare_exec(t_sentence *sentence)
{
	int	index;
	int	*pid;

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
