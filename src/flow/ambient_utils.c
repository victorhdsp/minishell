/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:35:54 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/05 16:14:12 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flow.h"
#include "../env/env.h"
#include "../env_management/env_management.h"

void	free_all_system(void)
{
	t_system	system;

	system = get_system(NULL);
	if (system.env)
		ft_clean_arr(system.env);
	if (system.name)
		free(system.name);
}