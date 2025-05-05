/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:12:04 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/05 16:40:53 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PWD_H
# define PWD_H

#include "../flow/flow.h"
#include "../env_management/env_management.h"
# include <unistd.h>
# include <stdio.h>
#include <sys/stat.h> 

void    ft_pwd(t_my_env **my_env, char **args);

#endif