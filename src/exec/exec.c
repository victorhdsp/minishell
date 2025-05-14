/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/14 15:19:19 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exec.h"

static void	ft_exec_command_child(t_sentence sentence, int *tube[2], int size)
{
	int		result;
	char	*cmd;
	int		index;

	cmd = NULL;
	dup2(sentence.infile, STDIN_FILENO);
	dup2(sentence.outfile, STDOUT_FILENO);
	result = ft_exec_builtin(sentence.items, sentence.args);
	index = 0;
	while (tube && index <= size)
	{
		close(tube[index][0]);
		close(tube[index][1]);
		index++;
	}
	if (result > -1)
	{
		set_system_exit_status(result);
		exit(EXIT_SUCCESS);
	}
	cmd = ft_get_extern_cmd(sentence.items);
	if (cmd && cmd[0])
		set_system_exit_status(execve(cmd, sentence.args,
				get_system(NULL).env));
	exit(EXIT_FAILURE);
}

static void	prepare_child(t_sentence *sentences, int *tube[2], int index,
		int size)
{
	pid_t	pid;

	prepare_redirects(&sentences[index]);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if ((index < size - 1 && sentences[index].outfile == STDOUT_FILENO))
			sentences[index].outfile = tube[index][1];
		if ((index > 0 && sentences[index].infile == STDIN_FILENO))
			sentences[index].infile = tube[index - 1][0];
		if (sentences[index].outfile == -1)
			sentences[index].outfile = tube[index][1];
		ft_exec_command_child(sentences[index], tube, index);
	}
	else if (index > 0)
	{
		close(tube[index - 1][0]);
		close(tube[index - 1][1]);
	}
}

void	exec_command_in_parent(t_sentence *sentences)
{
	int		stdin_backup;
	int		stdout_backup;
	int		result;
	char	*cmd;
	int		fd;
	
	cmd = NULL;
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	prepare_redirects(&sentences[0]);
	dup2(sentences[0].infile, STDIN_FILENO);
	dup2(sentences[0].outfile, STDOUT_FILENO);
	result = ft_exec_builtin(sentences[0].items, sentences[0].args);
	if (result == -1)
	{
		cmd = ft_get_extern_cmd(sentences[0].items);
		fd = fork();
		if (fd == 0 && cmd && cmd[0])
			set_system_exit_status(execve(cmd, sentences[0].args, get_system(NULL).env));
		if (fd == 0)
			exit(EXIT_SUCCESS);
		waitpid(fd, NULL, 0);
	}
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
}

void	exec_command_in_childs(t_sentence *sentences)
{
	int	index;
	int	size;
	int	**tube;

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
