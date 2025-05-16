/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:50:40 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/16 14:55:28 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	system_flow(env, "minishell");
	read_entrys();
	free_all_system();
	rl_clear_history();
	return (0);
}
