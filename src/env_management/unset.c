/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:25:22 by rpassos-          #+#    #+#             */
/*   Updated: 2025/04/08 11:36:46 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_management.h"

void	print_lst(t_my_env *ordered_head)
{
	while (ordered_head)
	{
		printf("declare -x %s", ordered_head->key);
		if (ordered_head->equal && *ordered_head->equal)
		{
			printf("=\"%s\"", ordered_head->value);
		}
		printf("\n");
		ordered_head = ordered_head->next;
	}
}

static void	clear_node(t_my_env *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

static void	check_envs(t_my_env **my_env, char *word)
{
	t_my_env	*current;
	t_my_env	*prev;
	t_my_env	*tmp;

	current = *my_env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, word) == 0)
		{
			tmp = current;
			if (prev == NULL)
				*my_env = current->next;
			else
				prev->next = current->next;
			current = current->next;
			clear_node(tmp);
			break ;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

int	ft_unset(t_my_env **my_env, char **word)
{
	int	index;

	index = 1;
	if (!word[1])
		return (0);
	while (word[index] != NULL)
	{
		check_envs(my_env, word[index]);
		index++;
	}
	return (0);
}
