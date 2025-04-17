/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:24:22 by rpassos-          #+#    #+#             */
/*   Updated: 2025/04/08 11:24:23 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_management.h"

static void	set_node(t_my_env **ordered_head, char *env_arr)
{
	t_my_env	*new_node;
	t_my_env	*tmp;

	new_node = ft_lstnew_env(env_arr);
	if (ft_strcmp(new_node->key, (*ordered_head)->key) < 0)
	{
		new_node->next = *ordered_head;
		*ordered_head = new_node;
	}
	else
	{
		tmp = *ordered_head;
		while (tmp->next && ft_strcmp(tmp->next->key, new_node->key) < 0)
			tmp = tmp->next;
		new_node->next = tmp->next;
		tmp->next = new_node;
	}
}

static void	order(t_my_env *my_env)
{
	t_my_env	*ordered_head;
	char		**env_arr;
	int			index;

	index = 0;
	if (!my_env)
		return ;
	env_arr = get_env_arr(my_env);
	ordered_head = ft_lstnew_env(env_arr[index]);
	my_env = my_env->next;
	index++;
	while (my_env)
	{
		set_node(&ordered_head, env_arr[index]);
		index++;
		my_env = my_env->next;
	}
	print_lst(ordered_head);
	ft_clean_arr(env_arr);
	ft_lstclear_env(&ordered_head);
}

static int	check_valid_name(char *word)
{
	int	index;

	index = 1;
	if (!word)
		return (0);
	if (word[0] != '_' && !ft_isalpha(word[0]))
	{
		printf("export: `%s': not a valid identifier\n", word);
		return (0);
	}
	while (word[index] != '\0' && word[index] != '=')
	{
		if (word[index] != '_' && !ft_isalnum(word[index]))
		{
			printf("export: `%s': not a valid identifier\n", word);
			return (0);
		}
		index++;
	}
	return (1);
}

static int	check_overwriting(t_my_env *my_env, char *word)
{
	char	*value;
	char	*key;

	value = ft_strchr(word, '=');
	if (!value)
		value = word + ft_strlen(word);
	key = ft_calloc(value - word + 1, sizeof(char));
	key = ft_memmove(key, word, value - word);
	while (my_env)
	{
		if (my_env && ft_strncmp(my_env->key, key, value - word) == 0)
		{
			free(my_env->value);
			my_env->value = ft_strdup(value + 1);
			free(key);
			return (0);
		}
		my_env = my_env->next;
	}
	free(key);
	return (1);
}

int	ft_export(t_my_env **my_env, char **word)
{
	t_my_env	*new_node;
	int			index;
	int			return_value;

	return_value = 0;
	index = 1;
	if (!word[index])
	{
		order(*my_env);
		return (0);
	}
	while (word[index] != NULL)
	{
		if (!check_valid_name(word[index]))
			return_value = 1;
		else if (check_overwriting(*my_env, word[index]))
		{
			new_node = ft_lstnew_env(word[index]);
			ft_lstadd_back_env(&(*my_env), new_node);
		}
		index++;
	}
	return (return_value);
}
