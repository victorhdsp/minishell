/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/15 12:38:25 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exec.h"
#include <signal.h>
#include <sys/wait.h>

static int	ft_exec_command(t_sentence sentence)
{
	char	*cmd;
	int		fd;
	int		result;

	cmd = NULL;
	result = ft_exec_builtin(sentence.items, sentence.args);
	if (result != -1)
		return (result);
	cmd = ft_get_extern_cmd(sentence.items);
	fd = fork();
	if (fd < 0)
		exit(EXIT_FAILURE);
	if (fd == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (cmd && cmd[0])
			execve(cmd, sentence.args, get_system(NULL).env);
		exit(EXIT_SUCCESS);
	}
	waitpid(fd, &result, 0);
	return (result);
}

void	create_commands_without_pipe(t_sentence sentence)
{
	int		stdin_backup;
	int		stdout_backup;
	int		exec_return;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	prepare_redirects(&sentence);
	dup2(sentence.infile, STDIN_FILENO);
	dup2(sentence.outfile, STDOUT_FILENO);
	exec_return = ft_exec_command(sentence);
	if (WIFEXITED(exec_return))
		set_system_exit_status(WEXITSTATUS(exec_return));
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
}
