/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:42:45 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/20 17:55:51 by rpassos-         ###   ########.fr       */
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
	
	final_path = ft_strjoin(arr[1] + 7, "/");
	tmp = final_path;
	final_path = ft_strjoin(final_path, args[1]);
	free(tmp);
	tmp = final_path;
	final_path = normalize_path(final_path);
	free(tmp);
	return (final_path);
}

int	chdir_fail(char **arr, char **args, char *final_path)
{
	cd_print_error(args[1]);
	cd_free(arr);
	free(final_path);
	return (1);
}
