/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:14:22 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/16 16:30:06 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_new_value(char *key, char *old_value, char *new_value,
		int index)
{
	char	*tmp;
	char	*tmp2;
	char	*result;

	tmp = ft_substr(old_value, 0, key - old_value - 1);
	tmp2 = new_value;
	result = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	tmp = result;
	tmp2 = ft_strdup(key + index);
	result = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	return (result);
}

static char	*get_reserved_value(char *key, char *old_value)
{
	char	*var_value;

	if (!ft_strncmp(key, "?", 1))
	{
		var_value = ft_itoa(get_system_exit_status());
		return (get_new_value(key, old_value, var_value, 1));
	}
	return (NULL);
}

static char	*get_public_value(char *key, char *old_value)
{
	int		index;
	char	*var_name;

	index = 0;
	if (ft_isalpha(key[index]) || key[index] == '_')
		while (key[index] && (ft_isalnum(key[index]) || key[index] == '_'))
			index++;
	var_name = ft_substr(key, 0, index);
	return (get_new_value(key, old_value, get_system_env(var_name), index));
}

void	variable_traitement(t_lexer_item *args)
{
	int		index;
	char	*str;
	char	*key;
	char	*tmp;

	index = -1;
	while (args[++index].value)
	{
		str = args[index].value;
		if (str[0] != '\'')
		{
			if (str[0] == '\"')
				str++;
			key = ft_memchr(str, '$', ft_strlen(str));
			if (key)
			{
				tmp = get_reserved_value(key + 1, args[index].value);
				if (!tmp)
					tmp = get_public_value(key + 1, args[index].value);
				free(args[index].value);
				args[index].value = tmp;
				continue ;
			}
		}
	}
}
