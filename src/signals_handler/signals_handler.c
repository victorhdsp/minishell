/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:18:26 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/16 14:52:10 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_ctrl(int signal, siginfo_t *info, void *notused)
{
	(void)notused;
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		if (info->si_uid)
			rl_redisplay();
		set_system_exit_status(130);
	}
	else if (signal == SIGQUIT)
		return ;
}

void	signal_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handler_ctrl;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("SIGINT error");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror("SIGQUIT error");
}
