/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:35:54 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/15 15:59:59 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ambient.h"

t_system    get_system(t_system *new_system)
{
    static t_system     system;

    if (new_system)
        system = *new_system;
    return (system);
}

void        set_system_exit_status(int exit_status)
{
    t_system    new_system;

    new_system = get_system(NULL);
    new_system.last_exit_status = exit_status;
    get_system(&new_system);
}

void        set_system_env(char **env)
{
    t_system    new_system;

    new_system = get_system(NULL);
    new_system.env = env;
    get_system(&new_system);
}
