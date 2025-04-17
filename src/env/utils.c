/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:24:34 by rpassos-          #+#    #+#             */
/*   Updated: 2025/04/08 11:24:35 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_my_env	*ft_lstnew_env(char *content)
{
	t_my_env	*result;
	char		*value;

	result = (t_my_env *)ft_calloc(1, sizeof(t_my_env));
	if (result == NULL)
	{
		return (NULL);
	}
	value = ft_strchr(content, '=');
	if (!value)
		value = content + ft_strlen(content);
	result->key = ft_calloc(value - content + 1, sizeof(char));
	result->key = ft_memmove(result->key, content, value - content);
	result->next = NULL;
	result->equal = NULL;
	result->value = NULL;
	if (value && value[0])
	{
		result->equal = "=";
		result->value = ft_strdup(value + 1);
	}
	return (result);
}

int	ft_lstsize_env(t_my_env *lst)
{
	int			count;
	t_my_env	*current;

	count = 0;
	current = lst;
	while (current)
	{
		current = current->next;
		count++;
	}
	return (count);
}
