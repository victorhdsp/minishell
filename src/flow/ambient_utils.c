/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:35:54 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/12 10:34:23 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../env_management/env_management.h"
#include "flow.h"

void	free_all_system(void)
{
	t_system	system;

	system = get_system(NULL);
	if (system.env)
		ft_clean_arr(system.env);
	if (system.name)
		free(system.name);
	if (system.username)
		free(system.username);
}
