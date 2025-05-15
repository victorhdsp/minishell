/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:50:43 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/15 08:49:55 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exit.h"

static int	get_arr_size(char **arr)
{
	int	index;

	index = 0;
	while (arr[index] != NULL)
		index++;
	return (index);
}

static int	return_value_traitement(char *value)
{
	int		index;
	int		result;

	index = 0;
	while (value[index])
	{
		if (!ft_isdigit(value[index]))
			return error__numeric_argument_required;
		index++;
	}
	result = ft_atoi(value);
	if (result >= 255)
		result %= 256;
	return (result);
}

int	exit_builtin(char **args)
{
	int		return_value;

	return_value = no_error;
	if (get_arr_size(args) > 2)
	{
		print_error("exit: too many arguments\n", NULL, NULL, NULL);
		return (1);
	}
	if (args && args[1] && args[1][0])
	{
		return_value = return_value_traitement(args[1]);
		if (return_value == error__numeric_argument_required)
		{
			print_error("exit: ", args[1], ": numeric argument required\n", NULL);
			exit (2);
		}
	}
	exit(return_value);
	return (return_value);
}
