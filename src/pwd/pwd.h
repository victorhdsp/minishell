/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:12:04 by rpassos-          #+#    #+#             */
/*   Updated: 2025/04/17 18:47:37 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PWD_H
# define PWD_H

#include "../ambient/ambient.h"
#include "../env_management/env_management.h"
# include <unistd.h>
# include <stdio.h>
#include <sys/stat.h> 

void    ft_pwd(t_my_env **my_env, char **args);

#endif