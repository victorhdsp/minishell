/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:07:57 by rpassos-          #+#    #+#             */
/*   Updated: 2025/04/17 18:52:11 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pwd.h"

void    ft_pwd(t_my_env **my_env, char **args)
{
    char *cwd;
    
    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
        cwd = get_system_env("PWD");
    printf("%s\n", cwd);
    free(cwd);
}