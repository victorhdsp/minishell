/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:50:40 by vide-sou          #+#    #+#             */
/*   Updated: 2025/07/02 10:23:35 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	system_flow(env, "minishell > ");
	read_entrys();
	free_all_system();
	rl_clear_history();
	return (0);
}
