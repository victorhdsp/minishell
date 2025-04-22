/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:24:12 by rpassos-          #+#    #+#             */
/*   Updated: 2025/04/22 11:37:22 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

static int	check_consecutive_n(char *word)
{
	int	index;

	index = 1;
	while (word[index] != '\0')
	{
		if (word[index] != 'n')
			return (0);
		index++;
	}
	return (1);
}

static int	check_args(char **data, int *flag_beginning, int *index,
		int *flag_check)
{
	if (!ft_strncmp(data[*index], "-n", 2) && !*flag_beginning)
	{
		while (data[*index] && !ft_strncmp(data[*index], "-n", 2))
		{
			if (!check_consecutive_n(data[*index]))
			{
				printf("%s ", data[*index]);
				(*index)++;
				break ;
			}
			(*index)++;
			*flag_check = 1;
		}
	}
	*flag_beginning = 1;
	if (!data[*index])
		return (0);
	printf("%s", data[*index]);
	return (1);
}

int	ft_echo(char **data)
{
	int	flag_not_at_beginning;
	int	flag_check;
	int	index;

	index = 1;
	flag_check = 0;
	flag_not_at_beginning = 0;
	while (data[index] != NULL)
	{
		if (!check_args(data, &flag_not_at_beginning, &index, &flag_check))
			break ;
		if (data[index + 1])
			printf(" ");
		index++;
	}
	if (!flag_check)
		printf("\n");
	return (0);
}
