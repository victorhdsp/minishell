/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:42:45 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/21 18:01:09 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_free(char **arr)
{
	free(arr[1]);
	free(arr);
}

char *set_final_path(char **arr, char **args, char *final_path)
{
	char	*tmp;
	
	if (args[1][0] == '/')
		return(ft_strdup(args[1]));
	final_path = ft_strjoin(arr[1] + 7, "/");
	tmp = final_path;
	final_path = ft_strjoin(final_path, args[1]);
	free(tmp);
	tmp = final_path;
	final_path = normalize_path(final_path);
	free(tmp);
	if (!final_path && final_path[0] == '\0')
		final_path = ft_strdup("/");
	return (final_path);
}

int	chdir_fail(char **arr, char **args, char *final_path)
{
	cd_print_error(args[1]);
	cd_free(arr);
	free(final_path);
	return (1);
}

char *check_home_path_arg(char **arr, char **args, char *final_path)
{
	if (!args[1])
		final_path = ft_strdup("");
	else
		final_path = set_final_path(arr, args, final_path);
	return (final_path);
}

void	 free_arr_with_null(char **arr, int splitted_arr_size)
{
	int	index;

	index = 0;
	while (index < splitted_arr_size)
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
