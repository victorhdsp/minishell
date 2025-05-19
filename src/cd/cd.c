/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:50:43 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/19 19:25:11 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**set_arr_for_export(char *key)
{
	char	*cwd_ret;
	char	*new_keyvalue;
	char	**arr;

	cwd_ret = getcwd(NULL, 0); //retorna null pois a pasta perdeu a permissão
	if (!cwd_ret)
		cwd_ret = ft_strdup(get_system_env("PWD"));
	new_keyvalue = ft_strjoin(key, cwd_ret);
	arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = NULL;
	arr[1] = ft_strdup(new_keyvalue);
	arr[2] = NULL;
	free(cwd_ret);
	free(new_keyvalue);
	return (arr);
}

static void	cd_print_error(char *arg)
{
	if (ft_strcmp(arg, "HOME") == 0)
		print_error("cd: ", arg, " not set\n", NULL);
	else if (errno == 20)
		print_error("cd: ", arg, ": Not a directory\n", NULL);
	else if (errno == 2)
		print_error("cd: ", arg, ": No such file or directory\n", NULL);
	else if (errno == 13)
		print_error("cd: ", arg, ": Permission denied\n", NULL);
}

static int	get_arr_size(char **arr)
{
	int	index;

	index = 0;
	while (arr[index] != NULL)
		index++;
	return (index);
}

static int	check_home(t_my_env **my_env)
{
	t_my_env	*current;
	char		**arr;

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
	cd_print_error("HOME");
	return (1);
}

void	find_previous_null(char **splitted, int index)
{
	int	splitted_index;

	splitted_index = index;

	while (!splitted[index] || splitted_index != 0)
	{
		index--;
		if (splitted[index])
		{
			splitted[index] = NULL;
			break;
		}
	}
}

char *normalize_path(char *path)
{
	char	**splitted;
	int		index;
	int		size;
	char	*final_path;
	char	*tmp;

	splitted = ft_split(path, '/');
	index = 0;
	while (splitted[index])
	{
		if (strcmp(splitted[index], "..") == 0)   //"/home/rpassos-/test/..   /outro/.  /pasta_2/pasta_3/..  /.."
		{
			if (splitted[index - 1] == NULL)
				find_previous_null(splitted, index);  //"/home/rpassos-/null/null/outro/null/pasta_2/null   /null/null"
			splitted[index - 1] = NULL;
			splitted[index] = NULL;
		}
		else if (strcmp(splitted[index], ".") == 0)
			splitted[index] = NULL;
		index++;
	}
	size = index;
	index = 0;
	while (index < size)
	{
		if (splitted[index])
			final_path = ft_strjoin(final_path, "/");
		tmp = final_path;
		final_path = ft_strjoin(final_path, splitted[index]);
		free(tmp);
		index++;
	}
	return (final_path);
}



int	ft_cd(t_my_env **my_env, char **args)
{
	char	**arr;
	char	*path;
	char	*final_path;

	if (!args[1])
		return (check_home(my_env));
	if (get_arr_size(args) > 2)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	arr = set_arr_for_export("OLDPWD=");
	
	path = ft_strjoin(get_system_env("PWD"), "/");
	
	final_path = ft_strjoin(path, args[1]);
	
	printf("PWD: %s\n", get_system_env("PWD"));
	printf("arg: %s\n", args[1]);
	printf("final path: %s\n", final_path);
	if (chdir(final_path) == 0)
	{
		ft_export(my_env, arr);
		cd_free(arr);
		arr = set_arr_for_export("PWD=");
		ft_export(my_env, arr);
		cd_free(arr);
	}
	else
	{
		cd_print_error(args[1]);
		cd_free(arr);
		return (1);
	}
	return (0);
}