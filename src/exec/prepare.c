/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/15 12:50:41 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exec.h"

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
	{
		print_error(path, ": ", strerror(errno), NULL);
		set_system_exit_status(errno);
	}
	return (fd);
}

static int	ft_heredoc(char *exit, char *filename)
{
	char	*content;
	int		fd;

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	ft_putstr_fd("> ", 0);
	content = ft_get_next_line(0);
	while (ft_strncmp(content, exit, ft_strlen(exit)))
	{
		ft_putstr_fd(content, fd);
		free(content);
		ft_putstr_fd("> ", 0);
		content = ft_get_next_line(0);
	}
	close(fd);
	fd = open(filename, O_RDWR);
	free(content);
	return (fd);
}

static void	ft_save_redirects(t_sentence *sentence, int index, int fd)
{
	sentence->items[index + 1].fd = fd;
	if (sentence->items[index].type == type_infile)
		sentence->infile = fd;
	if (sentence->items[index].type == type_outfile)
		sentence->outfile = fd;
}

static void	first_heredoc(t_sentence *sentence)
{
	int		index;
	int		fd;
	char	*content;
	char	*tmp;
	char	*filename;

	index = 0;
	fd = FD_NOT_CREATED;
	while (sentence->items[index].value)
	{
		if (sentence->items[index].fn == fn_heredoc)
		{
			content = ft_itoa(ft_count_dir("../../local/heredoc/"));
			tmp = ft_correct_path("../../local/heredoc/heredoc_");
			filename = ft_strjoin(tmp, content);
			free(tmp);
			free(content);
			fd = ft_heredoc(sentence->items[index + 1].value, filename);
			free(filename);
		}
		if (fd != FD_NOT_CREATED)
			ft_save_redirects(sentence, index, fd);
		fd = FD_NOT_CREATED;
		index++;
	}
}

void	prepare_redirects(t_sentence *sentence)
{
	int				fd;
	int				index;
	t_lexer_item	*items;

	index = 0;
	fd = FD_NOT_CREATED;
	items = sentence->items;
	first_heredoc(sentence);
	while (items[index].value)
	{
		if (items[index].fn == fn_output)
			fd = ft_simple_redirect(items[index + 1].value, fn_output);
		else if (items[index].fn == fn_append)
			fd = ft_simple_redirect(items[index + 1].value, fn_append);
		else if (items[index].fn == fn_input)
			fd = ft_simple_redirect(items[index + 1].value, fn_input);
		if (fd != FD_NOT_CREATED)
			ft_save_redirects(sentence, index, fd);
		fd = FD_NOT_CREATED;
		index++;
	}
}
