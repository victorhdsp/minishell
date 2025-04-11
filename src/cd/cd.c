/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:50:43 by rpassos-          #+#    #+#             */
/*   Updated: 2025/04/09 17:52:42 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

static char **set_arr_for_export(char *key)
{
	char *cwd_ret;
	char *new_keyvalue;
	char **arr;

	cwd_ret = getcwd(NULL, 0);
	new_keyvalue = ft_strjoin(key, cwd_ret);
	arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = NULL;
	arr[1] = ft_strdup(new_keyvalue);
	arr[2] = NULL;
	free(cwd_ret);
	free(new_keyvalue);
	return (arr);
}

static void cd_free(char **arr)
{
	free(arr[1]);
	free(arr);
}

static void print_error(char *arg)
{
	if (errno == 20)
		printf("cd: %s: Not a directory\n", arg);
	else if (errno == 2)
		printf("cd: %s: No such file or directory\n", arg);
	else if (errno == 13)
		printf("cd: %s: Permission denied\n", arg);
}

static int	get_arr_size(char **arr)
{
	int	index;

	index = 0;
	while (arr[index] != NULL)
		index++;
	return (index);
}

static int check_home(t_my_env **my_env)
{
	t_my_env *current;
	char **arr;

	current = *my_env;
	while (current)
	{
		if (ft_strcmp(current->key, "HOME") == 0)
		{
			arr = set_arr_for_export("OLDPWD=");
			chdir(current->value);
			ft_export(my_env, arr);
			cd_free(arr);
			arr = set_arr_for_export("PWD=");
			ft_export(my_env, arr);
			cd_free(arr);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

int	ft_cd(t_my_env **my_env, char **args)
{
	int	ret;
	char **arr;

	if (!args[1])
	{
		ret = check_home(my_env);
		//printf("funcionou");
		return (ret);
	}
	if (get_arr_size(args) > 2)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	arr = set_arr_for_export("OLDPWD=");
	ret = chdir(args[1]);
	if (ret == 0)
	{
		ft_export(my_env, arr);
		cd_free(arr);
		arr = set_arr_for_export("PWD=");
		ft_export(my_env, arr);
		cd_free(arr);
	}
	else
	{
		print_error(args[1]);
		cd_free(arr);
		return (ret);
	}
	return (ret);
}
