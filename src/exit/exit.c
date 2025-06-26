/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:50:43 by rpassos-          #+#    #+#             */
/*   Updated: 2025/06/26 12:45:02 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	return_value_traitement(char *value)
{
	int	index;
	int	result;

	index = 0;
	if (value[0] == '+' || value[0] == '-')
		index++;
	while (value[index])
	{
		if (!ft_isdigit(value[index]))
			return (error__numeric_argument_required);
		index++;
	}
	if (index >= 20)
		return (error__numeric_argument_required);
	result = ft_atoi(value);
	if (result >= 255)
		result %= 256;
	return (result);
}

int	exit_builtin(char **args)
{
	unsigned char	return_value;
	
	return_value = no_error;
	if (get_arr_size(args) > 2)
	{
		print_error("exit: too many arguments\n", NULL, NULL, 1);
		return (error__too_many_arguments);
	}
	if (args && args[1] && args[1][0])
	{
		return_value = return_value_traitement(args[1]);
		if (return_value == error__numeric_argument_required
			&& args[1][0] != '2')
		{
			print_error("exit: ", args[1], ": numeric argument required\n", 2);
			exit(2);
		}
	}
	set_system_exit_request(1);
	set_system_exit_status(return_value);
	return (return_value);
}
