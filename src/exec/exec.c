/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/05 20:02:52 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exec.h"

static void	ft_exec_command_child(t_sentence sentence, int *tube[2], int size)
{
	int			result;
	char		*cmd;
	t_system	system;
	int			index;

	cmd = NULL;
	system = get_system(NULL);
	cmd = ft_get_extern_cmd(sentence.items);
	dup2(sentence.infile, STDIN_FILENO);
	dup2(sentence.outfile, STDOUT_FILENO);
	index = 0;
	while (index <= size)
	{
		close(tube[index][0]);
		close(tube[index][1]);
		index++;
	}
	if (cmd && cmd[0])
		set_system_exit_status(execve(cmd, sentence.args, system.env));
	exit(EXIT_FAILURE);
}

static void	prepare_child(t_sentence *sentences, int *tube[2], int index, int size)
{
	pid_t		pid;
	int			result;
	prepare_redirects(&sentences[index]);
	
	result = ft_exec_builtin(sentences[index].items, sentences[index].args);
	if (result >= 0)
		set_system_exit_status(result);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (index < size - 1 && sentences[index].outfile == STDOUT_FILENO)
			sentences[index].outfile = tube[index][1];
		else if (index > 0 && sentences[index].infile == STDIN_FILENO)
			sentences[index].infile = tube[index - 1][0];
		if (result == -1)
			ft_exec_command_child(sentences[index], tube, index);
	}
	else if (index > 0)
	{	
		close(tube[index - 1][0]);
		close(tube[index - 1][1]);
	}
}

void	exec_command(t_sentence *sentences)
{
	int		index;
	int		size;
	int		**tube;

	size = 0;
	while (sentences[size].args)
		size++;
	tube = ft_calloc(size, sizeof(int *));
	index = 0;
	while (tube && index < size)
	{
		tube[index] = ft_calloc(2, sizeof(int));
		if (pipe(tube[index]) == -1)
			exit(EXIT_FAILURE);
		prepare_child(sentences, tube, index, size);
		index++;
	}
	index = 0;
	while (index < size)
	{
		wait(NULL);
		free(tube[index]);
		index++;
	}
	free(tube);
}
