/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:50:40 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/12 10:50:54 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./flow/flow.h"
#include "./minishell.h"
#include "./traitement/traitement.h"
#include <readline/readline.h>

int	main(int ac, char **av, char **env)
{
	char		*cmd;
	t_system	system;

	(void)ac;
	(void)av;
	system_flow(env, "minishell");
	read_entrys();
	free_all_system();
	return (0);
}
