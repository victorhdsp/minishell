/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:44:35 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/21 17:48:33 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "../../include/libft/libft.h"
# include "../env/env.h"
# include "../env_management/env_management.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

void	cd_free(char **arr);
void	cd_print_error(char *arg);
int		get_arr_size(char **arr);
char    *normalize_path(char *path);
int		ft_cd(t_my_env **my_env, char **args);
void	free_arr_with_null(char **arr, int splitted_arr_size);
int		chdir_fail(char **arr, char **args, char *final_path);
char	*set_final_path(char **arr, char **args, char *final_path);
char    *check_home_path_arg(char **arr, char **args, char *final_path);

#endif