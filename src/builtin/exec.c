/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:15:31 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/05 16:04:34 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env_management/env_management.h"
#include "../flow/flow.h"
#include "../env/env.h"
#include "../cd/cd.h"

// Add save in ambient variable
int export_builtin(char **args)
{
    t_system    system;
    t_my_env    *list_env;
    int         result;
    char        **arr_env;

    system = get_system(NULL);
    list_env = get_env(system.env);
    result = ft_export(&list_env, args);
    set_system_env(arr_env);
    return (result);
}

int unset_builtin(char **args)
{
    t_system    system;
    t_my_env    *list_env;
    int         result;
    char        **arr_env;

    system = get_system(NULL);
    list_env = get_env(system.env);
    result = ft_unset(&list_env, args);
    arr_env = get_env_arr(list_env);
    set_system_env(arr_env);
    return (result);
}

int env_builtin()
{
    t_system    system;
    t_my_env    *list_env;
    int         result;

    system = get_system(NULL);
    list_env = get_env(system.env);
    result = print_env(list_env);
    return (result);
}

int cd_builtin(char **args)
{
    t_system    system;
    t_my_env    *list_env;
    int         result;
    char        **arr_env;

    system = get_system(NULL);
    list_env = get_env(system.env);
    result = ft_cd(&list_env, args);
    set_system_env(arr_env);
    return (result);
}