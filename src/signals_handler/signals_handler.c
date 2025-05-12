/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:18:26 by rpassos-          #+#    #+#             */
/*   Updated: 2025/04/24 13:02:35 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals_handler.h"

void	handler_ctrl(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
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
