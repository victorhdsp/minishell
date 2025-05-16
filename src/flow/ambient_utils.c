/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:35:54 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/16 14:49:02 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all_system(void)
{
	int			index;
	t_system	system;

	index = 0;
	system = get_system(NULL);
	if (system.env)
		ft_clean_arr(system.env);
	if (system.name)
		free(system.name);
	if (system.username)
		free(system.username);
}
