/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:44:35 by rpassos-          #+#    #+#             */
/*   Updated: 2025/04/09 17:17:31 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "../env_management/env_management.h"
# include "../../include/libft/libft.h"
# include "../env/env.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

int	ft_cd(t_my_env **my_env, char **args);

#endif