/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:39:12 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/20 18:05:00 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	 free_arr_with_null(char **arr)
{
	int	index;

	index = 0;
	while (index < get_arr_size(arr))
	{
		if (!arr[index])
			index++;
		else
		{
			free(arr[index]);
			index++;
		}
	}
	free(arr);
}

static void	find_previous_null(char **splitted, int index)
{
	while (!splitted[index] || index != 0)
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

char	*normalize_path(char *path)
{
	char	**splitted;
	char	*final_path;
	int		index;

	splitted = ft_split(path, '/');
	if (!splitted)
   		return NULL;
	final_path = NULL;
	index = -1;
	while (splitted[++index])
	{
		if (strcmp(splitted[index], "..") == 0)   //"/home/rpassos-/test/..   /outro/.  /pasta_2/pasta_3/..  /.."
		{
			if (index > 0 && splitted[index - 1] == NULL)
				find_previous_null(splitted, index);  //"/home/rpassos-/null/null/outro/null/pasta_2/null   /null/null"
			clear_index_content(splitted, index - 1);
			clear_index_content(splitted, index);
		}
		else if (strcmp(splitted[index], ".") == 0)
			clear_index_content(splitted, index);
	}
	final_path = set_correct_path(splitted, final_path, index);
	free_arr_with_null(splitted);
	return (final_path);
}
