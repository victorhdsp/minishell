/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:50:43 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/20 17:21:46 by rpassos-         ###   ########.fr       */
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

int	get_arr_size(char **arr)
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
	while (!splitted[index] || index != 0)
	{
		index--;
		if (splitted[index])
		{
			free(splitted[index]);
			splitted[index] = NULL;
			break;
		}
	}
}

char *normalize_path(char *path)
{
	char	**splitted;
	char	*final_path;
	char	*tmp;
	int		index;
	int		size;

	splitted = ft_split(path, '/');
	if (!splitted)
   		return NULL;
	final_path = NULL;
	index = 0;
	while (splitted[index])
	{
		if (strcmp(splitted[index], "..") == 0)   //"/home/rpassos-/test/..   /outro/.  /pasta_2/pasta_3/..  /.."
		{
			if (index > 0 && splitted[index - 1] == NULL)
				find_previous_null(splitted, index);  //"/home/rpassos-/null/null/outro/null/pasta_2/null   /null/null"
			free(splitted[index - 1]);
			splitted[index - 1] = NULL;
			free(splitted[index]);
			splitted[index] = NULL;
		}
		else if (strcmp(splitted[index], ".") == 0)
		{
			free(splitted[index]);
			splitted[index] = NULL;
		}	
		index++;
	}
	size = index;
	index = 0;
	while (index < size)
	{
		if (splitted[index])
		{
			tmp = final_path;
			final_path = ft_strjoin(final_path, "/");
			free(tmp);
		}
		tmp = final_path;
		final_path = ft_strjoin(final_path, splitted[index]);
		free(tmp);
		index++;
	}
	free_arr(splitted);
	return (final_path);
}

int	ft_cd(t_my_env **my_env, char **args)
{
	char	**arr;
	char	*tmp;
	char	*final_path;

	if (!args[1])
		return (check_home(my_env));
	if (get_arr_size(args) > 2)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	arr = set_arr_for_export("OLDPWD=");
	final_path = ft_strjoin(arr[1] + 7, "/");
	tmp = final_path;
	final_path = ft_strjoin(final_path, args[1]);
	free(tmp);
	tmp = final_path;
	final_path = normalize_path(final_path);
	free(tmp);
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
		free(final_path);
		return (1);
	}
	free(final_path);
	return (0);
}
