/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/06/23 16:05:05 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_simple_redirect(char *path, enum e_fn_sentence_item fn)
{
	int	fd;

	fd = FD_NOT_CREATED;
	if (fn == fn_input)
		fd = open(path, O_RDONLY);
	else if (fn == fn_output)
		fd = open(path, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	else if (fn == fn_append)
		fd = open(path, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	if (fd < 0)
		print_error(path, ": ", strerror(errno), errno);
	return (fd);
}

static int	ft_heredoc(char *exit, char *filename)
{
	char	*content;
	int		fd;

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	content = readline("> ");
	while (ft_strncmp(content, exit, ft_strlen(exit) + 1))
	{
		ft_putendl_fd(content, fd);
		free(content);
		content = readline("> ");
	}
	close(fd);
	fd = open(filename, O_RDWR);
	free(content);
	return (fd);
}

void	prepare_heredoc(t_lexer_item *items)
{
	int		index;
	int		fd;
	char	*content;
	char	*tmp;
	char	*filename;

	index = 0;
	fd = FD_NOT_CREATED;
	while (items[index].value)
	{
		if (items[index].fn == fn_heredoc)
		{
			content = ft_itoa(ft_count_dir("./"));
			tmp = ft_correct_path("./heredoc_");
			filename = ft_strjoin(tmp, content);
			free(tmp);
			free(content);
			fd = ft_heredoc(items[index + 1].value, filename);
			free(filename);
		}
		if (fd != FD_NOT_CREATED)
			items[index + 1].fd = fd;
		fd = FD_NOT_CREATED;
		index++;
	}
}

void	prepare_redirects(t_lexer_item *items)
{
	int	fd;
	int	index;

	index = 0;
	fd = FD_NOT_CREATED;
	while (items[index].value)
	{
		if (items[index].fn == fn_output)
			fd = ft_simple_redirect(items[index + 1].value, fn_output);
		else if (items[index].fn == fn_append)
			fd = ft_simple_redirect(items[index + 1].value, fn_append);
		else if (items[index].fn == fn_input)
			fd = ft_simple_redirect(items[index + 1].value, fn_input);
		if (fd != FD_NOT_CREATED)
			items[index + 1].fd = fd;
		fd = FD_NOT_CREATED;
		index++;
	}
}
