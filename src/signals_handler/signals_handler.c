/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:18:26 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/15 07:27:29 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals_handler.h"
#include "../flow/flow.h"
#include <termios.h>

void	handler_ctrl(int sig)
{	
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		set_system_exit_status(130);
	}
	else if (sig == SIGQUIT)
		return;
}

void	signal_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler_ctrl;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("SIGINT error");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror("SIGQUIT error");
}
