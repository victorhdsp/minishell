/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:50:05 by vide-sou          #+#    #+#             */
/*   Updated: 2025/06/26 12:54:44 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_correct_path(char *path)
{
	char	*root;
	char	*result;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (path[0] == '/')
		return (ft_strdup(path));
	root = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = path;
	while (!ft_strncmp(tmp, "../", 3))
		tmp += 3;
	result = ft_strjoin(root, tmp);
	free(root);
	return (result);
}

int	ft_count_dir(char *dir_path)
{
	DIR				*dir;
	char			*path;
	struct dirent	*files;
	int				index;

	path = ft_correct_path(dir_path);
	dir = opendir(path);
	index = 0;
	if (dir)
	{
		files = readdir(dir);
		while (files)
		{
			files = readdir(dir);
			index++;
		}
		index -= 2;
	}
	if (!dir || closedir(dir) == -1)
	{
		print_error("unexpected error on close dir\n", NULL, NULL, 1);
		exit(EXIT_FAILURE);
	}
	free(path);
	return (index);
}

void	print_error(char *str1, char *str2, char *str3, int error_status)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(str1, str2);
	result = ft_strjoin(temp, str3);
	free(temp);
	ft_putstr_fd(result, 2);
	free(result);
	set_system_exit_status(error_status);
}

void	free_program(t_lexer_item *lexed_cmd, t_sentence *sentence_cmd)
{
	t_system	system;

	system = get_system(NULL);
	free_sentence(sentence_cmd);
	free_lexer(lexed_cmd);
	if (system.exit_requested == 1)
	{
		free(system.name);
		ft_clean_arr(system.env);
		free(system.username);
		exit(system.last_exit_status);
	}
}
