/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:53:44 by rpassos-          #+#    #+#             */
/*   Updated: 2025/06/27 14:25:56 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_prompt(void)
{
	char	*pwd;
	char	*user;
	char	*result;
	char	*tmp;

	user = get_system(NULL).username;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	tmp = ft_strnstr(pwd, user, ft_strlen(pwd));
	if (!tmp)
		tmp = pwd;
	else
		tmp += ft_strlen(user);
	result = ft_strjoin(":~", tmp);
	tmp = ft_strjoin(user, result);
	free(result);
	result = ft_strjoin(tmp, "$ ");
	set_system_name(result);
	free(tmp);
	free(pwd);
}

void	disable_ctrl_backslash(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	read_entrys(void)
{
	char		*line;
	t_system	system;

	system = get_system(NULL);
	signal_handler();
	disable_ctrl_backslash();
	while (1)
	{
		set_prompt();
		system = get_system(NULL);
		line = readline(system.name);
		if (line == NULL)
		{
			printf("exit\n");
			free_all_system();
			rl_clear_history();
			exit(0);
		}
		if (line[0])
		{
			add_history(line);
			minishell_flow(line);
		}
		free(line);
	}
}
