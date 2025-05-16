/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:35:54 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/16 14:48:54 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_system	get_system(t_system *new_system)
{
	static t_system	system;

	if (new_system)
		system = *new_system;
	return (system);
}

int	get_system_exit_status(void)
{
	t_system	new_system;

	new_system = get_system(NULL);
	return (new_system.last_exit_status);
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
