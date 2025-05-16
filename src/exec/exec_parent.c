/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/16 16:33:59 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_ambient(char *cmd, t_sentence sentence,
		t_lexer_item *lexed_cmd)
{
	int	index;

	index = 0;
	while (sentence.items[index].value)
	{
		if (sentence.items[index].type == type_infile
			|| sentence.items[index].type == type_outfile)
			close(sentence.items[index + 1].fd);
		index++;
	}
	free(sentence.items);
	free(sentence.args);
	free_all_system();
	free_lexer(lexed_cmd);
	free(cmd);
}

static int	ft_exec_command(t_sentence sentence, t_lexer_item *lexed_cmd)
{
	char	*cmd;
	int		fd;
	int		result;

	cmd = NULL;
	result = ft_exec_builtin(sentence.items, sentence.args);
	if (result != -1)
		return (result);
	fd = fork();
	if (fd < 0)
		exit(EXIT_FAILURE);
	if (fd == 0)
	{
		cmd = ft_get_extern_cmd(sentence.items);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (cmd)
			execve(cmd, sentence.args, get_system(NULL).env);
		free_ambient(cmd, sentence, lexed_cmd);
		exit(EXIT_SUCCESS);
	}
	waitpid(fd, &result, 0);
	return (result);
}

void	create_commands_without_pipe(t_sentence sentence,
		t_lexer_item *lexed_cmd)
{
	int		stdin_backup;
	int		stdout_backup;
	int		exec_return ;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	prepare_redirects(&sentence);
	dup2(sentence.infile, STDIN_FILENO);
	dup2(sentence.outfile, STDOUT_FILENO);
	exec_return = ft_exec_command(sentence, lexed_cmd);
	if (WIFEXITED(exec_return))
		set_system_exit_status(WEXITSTATUS(exec_return));
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
}
