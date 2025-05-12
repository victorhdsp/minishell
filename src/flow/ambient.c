/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:35:54 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/12 17:43:12 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../env_management/env_management.h"
#include "flow.h"

t_system	get_system(t_system *new_system)
{
	static t_system	system;

	if (new_system)
		system = *new_system;
	return (system);
}

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

char	*get_system_env(char *key)
{
	t_system	system;
	int			index;
	char		*tmp;
	char		*result;
	int			key_len;

	system = get_system(NULL);
	index = 0;
	result = NULL;
	key_len = ft_strlen(key);
	while (key && key[0] && system.env[index])
	{
		if (!ft_strncmp(key, system.env[index], key_len))
		{
			tmp = ft_memchr(system.env[index], '=', key_len + 1);
			result = ft_strdup(tmp + 1);
		}
		index++;
	}
	return (result);
}
