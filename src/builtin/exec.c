/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:15:31 by vide-sou          #+#    #+#             */
/*   Updated: 2025/06/23 12:58:01 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_builtin(char **args)
{
	t_system	system;
	t_my_env	*list_env;
	int			result;
	char		**arr_env;

	system = get_system(NULL);
	list_env = get_env(system.env);
	result = ft_export(&list_env, args);
	arr_env = get_env_arr(list_env);
	set_system_env(arr_env);
	ft_lstclear_env(&list_env);
	return (result);
}

int	unset_builtin(char **args)
{
	t_system	system;
	t_my_env	*list_env;
	int			result;
	char		**arr_env;

	system = get_system(NULL);
	list_env = get_env(system.env);
	result = ft_unset(&list_env, args);
	arr_env = get_env_arr(list_env);
	set_system_env(arr_env);
	ft_lstclear_env(&list_env);
	return (result);
}

int	env_builtin(char **args)
{
	t_system	system;
	t_my_env	*list_env;
	int			result;

	system = get_system(NULL);
	list_env = get_env(system.env);
	result = print_env(list_env, args);
	ft_lstclear_env(&list_env);
	return (result);
}

int	cd_builtin(char **args)
{
	t_system	system;
	t_my_env	*list_env;
	int			result;
	char		**arr_env;

	system = get_system(NULL);
	list_env = get_env(system.env);
	result = ft_cd(&list_env, args);
	arr_env = get_env_arr(list_env);
	set_system_env(arr_env);
	ft_lstclear_env(&list_env);
	return (result);
}
