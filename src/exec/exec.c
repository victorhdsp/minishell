/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/23 11:51:35 by vide-sou         ###   ########.fr       */
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
	path_var = get_system_env("PATH");
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
	printf("%s: command not found\n", (char *)(*items).value);
	return (NULL);
}

static int	ft_exec_builtin(t_lexer_item *items, char **args)
{
	int	index;

	index = 0;
	// Adicionar built-ins
	while (items[index].value && items[index].fn != fn_cmd)
		index++;
	if (!items[index].value)
		return (-1);
	if (!ft_strncmp(items[index].value, "echo", 4))
		return (ft_echo(args));
	else if (!ft_strncmp(items[index].value, "cd", 2))
		return (cd_builtin(args));
	else if (!ft_strncmp(items[index].value, "pwd", 3))
		return (0);
	else if (!ft_strncmp(items[index].value, "export", 6))
		return (export_builtin(args));
	else if (!ft_strncmp(items[index].value, "unset", 5))
		return (unset_builtin(args));
	else if (!ft_strncmp(items[index].value, "env", 3))
		return (env_builtin());
	else if (!ft_strncmp(items[index].value, "exit", 4))
		return (0);
	return (-1);
}

static void	ft_exec_command_child(t_sentence sentence)
{
	int			result;
	char		*cmd;
	t_system	system;

	cmd = NULL;
	system = get_system(NULL);
	prepare_redirects(&sentence);
	dup2(sentence.outfile, STDOUT_FILENO);
	dup2(sentence.infile, STDIN_FILENO);
	result = ft_exec_builtin(sentence.items, sentence.args);
	if (result >= 0)
		exit(result);
	cmd = ft_get_extern_cmd(sentence.items);
	if (cmd)
		set_system_exit_status(execve(cmd, sentence.args, system.env));
	exit(EXIT_FAILURE);
}

static void	prepare_child(t_sentence *sentences, int *tube[2], int index, int size)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (index != size - 1 && sentences[index].outfile == STDOUT_FILENO)
			sentences[index].outfile = tube[index][1];
		if (index != 0 && sentences[index].infile == STDIN_FILENO)
			sentences[index].infile = tube[index - 1][0];
		ft_exec_command_child(sentences[index]);
	}
	else
	{
		if (index != 0)
			close(tube[index - 1][0]);
		if (index != size - 1)
			close(tube[index][1]);
		waitpid(pid, NULL, 0);
	}
}

void	exec_command(t_sentence *sentences)
{
	int	index;
	int	size;
	int	**tube;

	size = 0;
	while (sentences[size].args)
		size++;
	tube = ft_calloc(size, sizeof(int *));
	index = 0;
	while (index < size)
	{
		tube[index] = ft_calloc(2, sizeof(int));
		if (pipe(tube[index]) == -1)
			exit(EXIT_FAILURE);
		index++;
	}
	index = 0;
	while (sentences[index].args)
	{
		prepare_child(sentences, tube, index, size);
		index++;
	}
	close(tube[index - 1][0]);
	close(tube[index - 1][1]);
}
