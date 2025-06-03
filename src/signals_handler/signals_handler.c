/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:18:26 by rpassos-          #+#    #+#             */
/*   Updated: 2025/06/03 16:26:18 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_ctrl(int signal, siginfo_t *info, void *notused)
{
	(void)notused;
	if (signal == SIGINT)
	{
		if (info->si_uid)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
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
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("SIGINT error");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror("SIGQUIT error");
}
