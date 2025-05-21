/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:39:12 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/21 18:01:01 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*set_correct_path(char	**splitted, char *final_path, int index)
{
	char	*tmp;
	int		size;

	size = index;
	index = 0;
	while (index < size)
	{
		if (splitted[index])
		{
			tmp = final_path;
			final_path = ft_strjoin(final_path, "/");
			free(tmp);
		}
		tmp = final_path;
		final_path = ft_strjoin(final_path, splitted[index]);
		free(tmp);
		index++;
	}
	return (final_path);	
}

static void	clear_index_content(char **splitted, int index)
{
	free(splitted[index]);
	splitted[index] = NULL;
}

static void	find_previous_null(char **splitted, int index)
{
	while (index != 0 && !splitted[index])
	{
		index--;
		if (splitted[index])
		{
			free(splitted[index]);
			splitted[index] = NULL;
			break;
		}
	}
}

void	find_previous_null_and_free(char **splitted, int index)
{
	if (index > 0 && splitted[index - 1] == NULL)
				find_previous_null(splitted, index - 1);
			clear_index_content(splitted, index - 1);
			clear_index_content(splitted, index);
}

char	*normalize_path(char *path)
{
	char	**splitted;
	int		index;
	char	*final_path;
	int		splitted_arr_size;

	splitted = ft_split(path, '/');
	splitted_arr_size = get_arr_size(splitted);
	if (!splitted)
   		return (NULL);
	final_path = NULL;
	index = -1;
	while (splitted[++index])
	{
		if (strcmp(splitted[index], "..") == 0)
			find_previous_null_and_free(splitted, index);
		else if (strcmp(splitted[index], ".") == 0)
			clear_index_content(splitted, index);
	}
	final_path = set_correct_path(splitted, final_path, index);
	free_arr_with_null(splitted, splitted_arr_size);
	return (final_path);
}
