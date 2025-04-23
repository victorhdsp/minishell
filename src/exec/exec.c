/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/23 12:59:36 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exec.h"

static void	ft_exec_command_child(t_sentence sentence)
{
	int			result;
	char		*cmd;
	t_system	system;

	cmd = NULL;
	system = get_system(NULL);
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
	prepare_redirects(&sentences[index]);
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

static void	free_tubes(int size, int **tube)
{
	int	index;

	index = 0;
	while (index < size)
	{
		close(tube[index][0]);
		close(tube[index][1]);
		free(tube[index]);
		index++;
	}
	free(tube);
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
	free_tubes(size, tube);
}
