/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:50:40 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/20 17:16:05 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	/*char		*path = "/home/rpassos-/test/renato/../outro/./pasta_2/pasta_3/../..";
	char *result;

	result = normalize_path(path);

	printf("-------- %s\n", result);
	free(result);*/
	
	system_flow(env, "minishell > ");
	read_entrys();
	free_all_system();
	rl_clear_history();
	return (0);
}
