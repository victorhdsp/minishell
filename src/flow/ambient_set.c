/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:35:54 by vide-sou          #+#    #+#             */
/*   Updated: 2025/06/26 12:27:05 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_system_exit_status(int exit_status)
{
	t_system	new_system;

	new_system = get_system(NULL);
	new_system.last_exit_status = exit_status;
	get_system(&new_system);
}

void	set_system_exit_request(int exit_status)
{
	t_system	new_system;

	new_system = get_system(NULL);
	new_system.exit_requested = exit_status;
	get_system(&new_system);
}

void	set_system_name(char *name)
{
	t_system	new_system;

	new_system = get_system(NULL);
	if (new_system.name)
		free(new_system.name);
	new_system.name = name;
	get_system(&new_system);
}

void	set_system_env(char **env)
{
	t_system	new_system;

	new_system = get_system(NULL);
	if (new_system.env && new_system.env[0])
		free_arr_with_null(new_system.env, get_arr_size(new_system.env));
	new_system.env = env;
	get_system(&new_system);
}
