/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:50:05 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/14 15:27:34 by vide-sou         ###   ########.fr       */
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
		print_error("unexpected error on close dir\n", NULL, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	free(path);
	return (index);
}

void	print_error(char *str1, char *str3, char *str2, char *str4)
{
	if (str1)
		ft_putstr_fd(str1, 2);
	if (str2)
		ft_putstr_fd(str2, 2);
	if (str3)
		ft_putstr_fd(str3, 2);
	if (str4)
		ft_putstr_fd(str4, 2);
	set_system_exit_status(errno);
}