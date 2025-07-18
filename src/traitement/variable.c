/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:14:22 by vide-sou          #+#    #+#             */
/*   Updated: 2025/06/28 22:14:38 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_new_value(char *key, char *old_value, char *new_value,
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

char	*get_reserved_value(char *key, char *old_value)
{
	char	*var_value;

	if (!ft_strncmp(key, "?", 1))
	{
		var_value = ft_itoa(get_system_exit_status());
		return (get_new_value(key, old_value, var_value, 1));
	}
	return (NULL);
}

char	*get_public_value(char *key, char *old_value)
{
	int		index;
	char	*var_name;
	char	*var_value;

	index = 0;
	if (ft_isalpha(key[index]) || key[index] == '_')
		while (key[index] && (ft_isalnum(key[index]) || key[index] == '_'))
			index++;
	var_name = ft_substr(key, 0, index);
	var_value = get_new_value(key, old_value, get_system_env(var_name), index);
	free(var_name);
	return (var_value);
}

void	change_variable(char *get, char **set, char *key)
{
	char	*value;
	char	*tmp;

	if (key)
	{
		value = get_reserved_value(key + 1, get);
		if (!value)
			value = get_public_value(key + 1, get);
		tmp = ft_substr(*set, 0, ft_strlen(*set) - ft_strlen(key));
		free(*set);
		*set = ft_strjoin(tmp, value);
		free(tmp);
		free(value);
	}
}

// void	variable_traitement(t_lexer_item *args)
// {
// 	int		index;
// 	char	*str;
// 	char	current_quote;

// 	index = -1;
// 	current_quote = '\0';
// 	while (args[++index].value)
// 	{
// 		str = args[index].value;
// 		while (str && *str)
// 		{
// 			if (current_quote == '\0' && (*str == '\'' || *str == '\"'))
// 				current_quote = *str;
// 			if (current_quote != '\"' && *str == '\'')
// 			{
// 				str = ft_memchr(str + 1, '\'', ft_strlen(str));
// 				if (!str)
// 					break;
// 			}
// 			if (*str == '$')
// 			{
// 				change_variable(str, &args[index].value, str);
// 				str = args[index].value;
// 				continue;
// 			}
// 			if (*str++ == current_quote)
// 				current_quote = '\0';
// 		}
// 	}
// }

// static void	skip_single_quotes(char **str)
// {
// 	char	*next;

// 	next = ft_memchr(*str + 1, '\'', ft_strlen(*str));
// 	if (next)
// 		*str = next;
// 	else
// 		*str = NULL;
// }

// static void	handle_dollar(char **str, char **value_ref)
// {
// 	change_variable(*str, value_ref, *str);
// 	*str = *value_ref;
// }

// static void	process_value(t_lexer_item *item)
// {
// 	char	*str = item->value;
// 	char	current_quote = '\0';

// 	while (str && *str)
// 	{
// 		if (current_quote == '\0' && (*str == '\'' || *str == '\"'))
// 			current_quote = *str;
// 		if (current_quote != '\"' && *str == '\'')
// 		{
// 			skip_single_quotes(&str);
// 			if (!str)
// 				break;
// 		}
// 		if (*str == '$')
// 		{
// 			handle_dollar(&str, &item->value);
// 			continue;
// 		}
// 		if (*str++ == current_quote)
// 			current_quote = '\0';
// 	}
// }

// void	variable_traitement(t_lexer_item *args)
// {
// 	int	index = 0;

// 	while (args[index].value)
// 	{
// 		process_value(&args[index]);
// 		index++;
// 	}
// }
