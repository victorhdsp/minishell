/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:24:37 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/14 15:23:29 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../../include/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct my_env
{
	char			*key;
	char			*equal;
	char			*value;
	struct my_env	*next;
}					t_my_env;

t_my_env			*get_env(char **env);
char				**get_env_arr(t_my_env *my_env);
t_my_env			*ft_lstnew_env(char *content);
int					ft_lstsize_env(t_my_env *lst);
int					ft_count_arr_size(char **arr);
int					print_env(t_my_env *my_env, char **args);
void				ft_lstadd_back_env(t_my_env **lst, t_my_env *new);

#endif