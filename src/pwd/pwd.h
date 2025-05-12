/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:12:04 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/05 19:20:39 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PWD_H
# define PWD_H

# include "../env_management/env_management.h"
# include "../flow/flow.h"
# include <stdio.h>
# include <sys/stat.h>
# include <unistd.h>

int	ft_pwd(void);

#endif