/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/22 11:04:20 by vide-sou         ###   ########.fr       */
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

static int	ft_exec_builtin(t_lexer_item *items)
{
	int	index;

	index = 0;
	// Adicionar built-ins
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

static void	ft_exec_command_child(t_sentence sentence)
{
	int			result;
	char		*cmd;
	t_system	system;

	cmd = NULL;
	system = get_system(NULL);
	prepare_redirects(&sentence);
	dup2(sentence.infile, STDIN_FILENO);
	dup2(sentence.outfile, STDOUT_FILENO);
	result = ft_exec_builtin(sentence.items);
	if (result >= 0)
		exit(result);
	cmd = ft_get_extern_cmd(sentence.items);
	if (cmd)
		result = execve(cmd, sentence.args, system.env);
	exit(EXIT_FAILURE);
}

static void	finish_command(int	*pid, t_sentence *sentence)
{
	int				sent_index;
	int				item_index;
	t_lexer_item	item;

	sent_index = 0;
	while (sentence[sent_index].args)
	{
		waitpid(pid[sent_index], NULL, 0);
		item_index = 0;
		while (sentence[sent_index].items[item_index].value)
		{
			item = sentence[sent_index].items[item_index];
			if (item.type == type_infile || item.type == type_outfile)
				close(*(int *)item.value);
			item_index++;
		}
		sent_index++;
	}
}

void	exec_command(t_sentence *sentence)
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
		if (pid[index] == 0)
			ft_exec_command_child(sentence[index]);
		index++;
	}
	finish_command(pid, sentence);
}
