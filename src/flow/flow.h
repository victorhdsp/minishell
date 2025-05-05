/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:29:52 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/05 17:32:01 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOW_H
# define FLOW_H

# include "../../include/libft/libft.h"

typedef struct      s_system
{
	char            *name;
    int             last_exit_status;
    char            **env;
}					t_system;

t_system    get_system(t_system *new_system);
void        set_system_exit_status(int exit_status);
void        set_system_name_status(char *name);
void        set_system_env(char **env);
char        *get_system_env(char *key);
void        free_all_system(void);

void        system_flow(char **env, char *name);
int         minishell_flow(char *cmd);

#endif