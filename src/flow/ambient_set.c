/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:35:54 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/15 08:24:28 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../env_management/env_management.h"
#include "flow.h"

void	set_system_exit_status(int exit_status)
{
	t_system	new_system;

	new_system = get_system(NULL);
	new_system.last_exit_status = exit_status;
	get_system(&new_system);
}

void	set_system_name(char *name)
{
	t_system	new_system;

	new_system = get_system(NULL);
	new_system.name = name;
	get_system(&new_system);
}

void	set_system_env(char **env)
{
	t_system	new_system;

	new_system = get_system(NULL);
	if (new_system.env && new_system.env[0])
		free(new_system.env);
	new_system.env = env;
	get_system(&new_system);
}
