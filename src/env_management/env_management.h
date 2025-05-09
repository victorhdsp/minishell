/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:24:26 by rpassos-          #+#    #+#             */
/*   Updated: 2025/04/08 11:24:27 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MANAGEMENT_H
# define ENV_MANAGEMENT_H

# include "../../include/libft/libft.h"
# include "../env/env.h"
# include <stdio.h>
# include <stdlib.h>

char	**ft_clean_arr(char **result);
void	ft_lstclear_env(t_my_env **lst);
int		ft_export(t_my_env **my_env, char **word);
int		ft_strcmp(char *s1, char *s2);
int		ft_unset(t_my_env **my_env, char **word);
void	print_lst(t_my_env *ordered_head);

#endif