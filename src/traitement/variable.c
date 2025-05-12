/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:14:22 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/18 07:20:06 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./traitement.h"

static char	*get_new_value(char *key, char *old_value)
{
	int		index;
	char	*var_name;
	char	*tmp;
	char	*tmp2;
	char	*result;

	index = 0;
	while (key[index] && (ft_isalnum(key[index]) || key[index] == '_'))
		index++;
	var_name = ft_substr(key, 0, index);
	tmp = ft_substr(old_value, 0, key - old_value - 1);
	tmp2 = get_system_env(var_name);
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

void	variable_traitement(t_lexer_item *args)
{
	int		index;
	char	*str;
	char	*key;
	char	*tmp;

	index = 0;
	while (args[index].value)
	{
		str = args[index].value;
		if (str[0] != '\'')
		{
			if (str[0] == '\"')
				str++;
			key = ft_memchr(str, '$', ft_strlen(str));
			if (key)
			{
				tmp = get_new_value(key + 1, args[index].value);
				free(args[index].value);
				args[index].value = tmp;
				continue ;
			}
		}
		index++;
	}
}
