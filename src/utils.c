/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:50:05 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/23 12:01:57 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_correct_path(char *path)
{
	char	*root;
	char	*result;
	char	*tmp;

	//Corrigir essa porra
	tmp = ft_calloc(100, sizeof(char));
	getcwd(tmp, 100);
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
	DIR *dir;
	char *path;
	struct dirent *files;
	int index;

	path = ft_correct_path(dir_path);
	dir = opendir(path);
	index = 0;
	if (!dir)
	{
		ft_putstr_fd("unexpected error on open dir\n", 2);
		exit(EXIT_FAILURE);
	}
	files = readdir(dir);
	while (files)
	{
		files = readdir(dir);
		index++;
	}
	if (closedir(dir))
	{
		ft_putstr_fd("unexpected error on close dir\n", 2);
		exit(EXIT_FAILURE);
	}
	free(path);
	return (index - 2);
}