/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:29:52 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/15 15:58:25 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIENT_H
# define AMBIENT_H

# include "../../include/libft/libft.h"

typedef struct      s_system
{
	char            *name;
    int             last_exit_status;
    char            **env;
}					t_system;

t_system    get_system(t_system *new_system);
void        set_system_exit_status(int exit_status);
void        set_system_env(char **env);

#endif