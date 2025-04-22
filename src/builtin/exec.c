/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:15:31 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/22 11:30:09 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env_management/env_management.h"
#include "../flow/flow.h"
#include "../env/env.h"
#include "../cd/cd.h"

int export_builtin(char **args)
{
    t_system    system;
    t_my_env    *list_env;

    system = get_system(NULL);
    list_env = get_env(system.env);
    return (ft_export(&list_env, args));
}

int unset_builtin(char **args)
{
    t_system    system;
    t_my_env    *list_env;

    system = get_system(NULL);
    list_env = get_env(system.env);
    return (ft_unset(&list_env, args));
}

int env_builtin()
{
    t_system    system;
    t_my_env    *list_env;

    system = get_system(NULL);
    list_env = get_env(system.env);
    return (print_env(&list_env));
}

int cd_builtin(char **args)
{
    t_system    system;
    t_my_env    *list_env;

    system = get_system(NULL);
    list_env = get_env(system.env);
    return (ft_cd(&list_env, args));
}