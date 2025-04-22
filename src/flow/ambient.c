/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:35:54 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/22 10:05:41 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flow.h"
#include "../env/env.h"

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
	t_system		system;
	int				index;
	char			*tmp;
	char			*result;
	int				key_len;

	system = get_system(NULL);
	index = 0;
	result = NULL;
	key_len = ft_strlen(key);
	while (system.env[index])
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

void	system_flow(char **env, char *name)
{
	t_system	new_system;
	t_my_env	*list_env;

	new_system.last_exit_status = -1;
	new_system.name = name;
	list_env = get_env(env);
	new_system.env = get_env_arr(list_env);
	get_system(&new_system);
}