/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:24:35 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/21 15:40:29 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_my_env	*get_env(char **env)
{
	int			index;
	t_my_env	*my_env;
	t_my_env	*head;

	if (!env || !*env)
		return (NULL);
	index = 0;
	my_env = ft_lstnew_env(env[index]);
	if (!my_env)
		return (NULL);
	head = my_env;
	index++;
	while (env[index] != NULL)
	{
		my_env->next = ft_lstnew_env(env[index]);
		if (my_env->next == NULL)
			return (NULL);
		my_env = my_env->next;
		index++;
	}
	return (head);
}

static char	*merge_values(t_my_env *my_env)
{
	char	*word;
	char	*tmp;

	word = ft_strjoin(my_env->key, my_env->equal);
	if (my_env->value != NULL)
	{
		tmp = word;
		word = ft_strjoin(word, my_env->value);
		free(tmp);
	}
	return (word);
}

char	**get_env_arr(t_my_env *my_env)
{
	char	**my_env_arr;
	int		size;
	int		index;

	size = ft_lstsize_env(my_env);
	index = 0;
	my_env_arr = (char **)ft_calloc(size + 1, sizeof(char *));
	if (my_env_arr == NULL)
		return (NULL);
	while (my_env)
	{
		my_env_arr[index] = merge_values(my_env);
		index++;
		my_env = my_env->next;
	}
	my_env_arr[index] = NULL;
	return (my_env_arr);
}

int	print_env(t_my_env *my_env, char **args)
{
	if (get_arr_size(args) > 1)
	{
		printf("env: too many arguments\n");
		return (1);
	}
	while (my_env != NULL)
	{
		printf("%s", my_env->key);
		if (my_env->equal)
		{
			printf("%s", my_env->equal);
			printf("%s", my_env->value);
		}
		printf("\n");
		my_env = my_env->next;
	}
	return (0);
}
