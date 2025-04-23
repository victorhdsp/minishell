/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/23 12:06:16 by vide-sou         ###   ########.fr       */
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

static void	free_exec(t_sentence *sentences, int **tube)
{
	int	sent_index;
	int	item_index;

	sent_index = 0;
	item_index = 0;
	while (sentences[sent_index].args)
	{
		while (sentences[sent_index].items[item_index].value)
		{
			if (sentences[sent_index].items[item_index].type == type_infile
				|| sentences[sent_index].items[item_index].type == type_outfile)
				close(*(int *)sentences[sent_index].items[item_index].value);
			item_index++;
		}
		free(sentences[sent_index].items);
		free(sentences[sent_index].args);
		free(tube[sent_index]);
		sent_index++;
	}
	free(sentences);
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
	close(tube[index - 1][0]);
	close(tube[index - 1][1]);
	free_exec(sentences, tube);
}
