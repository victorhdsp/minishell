/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:35:54 by vide-sou          #+#    #+#             */
/*   Updated: 2025/06/28 22:22:19 by rpassos-         ###   ########.fr       */
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

static char	*find_env_value(char **env, char *tmp, int key_len)
{
	int		i;
	char	*value;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(tmp, env[i], key_len + 1))
		{
			value = ft_memchr(env[i], '=', key_len + 1);
			if (value)
				return (ft_strdup(value + 1));
			break;
		}
		i++;
	}
	return (NULL);
}

char	*get_system_env(char *key)
{
	t_system	system;
	char		*tmp;
	char		*result;

	if (!key || !*key)
		return (NULL);
	system = get_system(NULL);
	tmp = ft_strjoin(key, "=");
	result = find_env_value(system.env, tmp, ft_strlen(key));
	free(tmp);
	return (result);
}



