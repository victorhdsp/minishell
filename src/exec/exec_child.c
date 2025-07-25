/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/07/03 11:43:50 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_ambient(t_sentence *sentences, t_lexer_item *lexed_cmd)
{
	free_all_system();
	free_sentence(sentences);
	free_lexer(lexed_cmd);
}

static void	ft_exec_command(t_sentence *sentences, t_sentence sentence, int **tube, int size, t_lexer_item *lexed_cmd)
{
	int		result;
	char	*cmd;
	int		index;

	cmd = NULL;
	dup2(sentence.infile, STDIN_FILENO);
	dup2(sentence.outfile, STDOUT_FILENO);
	result = ft_exec_builtin(sentence.items, sentence.args);
	index = -1;
	while (tube && ++index <= size)
	{
		close(tube[index][0]);
		close(tube[index][1]);
	}
	if (result > -1)
	{
		set_system_exit_status(result);
		free_all_child(sentences, tube, lexed_cmd);
		exit(EXIT_SUCCESS);
	}
	cmd = ft_get_extern_cmd(sentence.items);
	if (cmd && cmd[0])
		set_system_exit_status(execve(cmd, sentence.args,
				get_system(NULL).env));
	exit(EXIT_FAILURE);
}

static void	prepare_child(t_sentence *sentences, int **tube, int index,
		t_lexer_item *lexed_cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if ((sentences[index + 1].args
				&& sentences[index].outfile == STDOUT_FILENO))
			sentences[index].outfile = tube[index][1];
		if ((index > 0 && sentences[index].infile == STDIN_FILENO))
			sentences[index].infile = tube[index - 1][0];
		if (sentences[index].outfile == -1)
			sentences[index].outfile = tube[index][1];
		ft_exec_command(sentences, sentences[index], tube, index, lexed_cmd);
		free_ambient(sentences, lexed_cmd);
	}
	else if (index > 0)
	{
		close(tube[index - 1][0]);
		close(tube[index - 1][1]);
	}
}

void	create_commands_with_pipe(t_sentence *sentences,
		t_lexer_item *lexed_cmd)
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
		prepare_child(sentences, tube, index, lexed_cmd);
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
