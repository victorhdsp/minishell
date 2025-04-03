/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:47:07 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/03 14:09:02 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exec.h"

static int	ft_simple_redirect(char *path, enum e_fn_sentence_item fn) //Resolver caso passe uma pasta
{
	int	fd;

	fd = -1;
	if (fn == fn_input)
		fd = open(path, O_RDONLY);
	else if (fn == fn_output)
		fd = open(path, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	else if (fn == fn_append)
		fd = open(path, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	if (fd < 0)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	ft_heredoc(char *exit)
{
	int		files_count;
	char	*filename;
	char	*tmp;
	int		fd;
	char	*content;

	files_count = ft_count_dir("../../local/heredoc/");
	content = ft_itoa(files_count);
	tmp = ft_correct_path("../../local/heredoc/heredoc_");
	filename = ft_strjoin(tmp, content);
	free(tmp);
	free(content);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	free(filename);
	content = ft_get_next_line(0);
	while (ft_strncmp(content, exit, ft_strlen(exit)))
	{
		ft_putstr_fd(content, fd);
		free(content);
		content = ft_get_next_line(0);
	}
	free(content);
	return (fd);
}

static void ft_save_redirects(t_sentence *sentence, int index, int fd)
{
	sentence->items[index + 1].value = &fd;
	if (sentence->items[index].type == type_infile)
		sentence->infile = fd;
	if (sentence->items[index].type == type_outfile)
		sentence->outfile = fd;
}

void	ft_use_redirects(t_sentence *sentence)
{
	int				fd;
	int				index;
	t_lexer_item	*items;

	index = 0;
	fd = -1;
	items = sentence->items;
	while (items[index].value)
	{
		if (items[index].fn == fn_output)
			fd = ft_simple_redirect(items[index + 1].value, fn_output);
		else if (items[index].fn == fn_append)
			fd = ft_simple_redirect(items[index + 1].value, fn_append);
		else if (items[index].fn == fn_input)
			fd = ft_simple_redirect(items[index + 1].value, fn_input);
		else if (items[index].fn == fn_heredoc)
			fd = ft_heredoc(items[index + 1].value);
		if (fd != -1)
			ft_save_redirects(sentence, index, fd);
		fd = -1;
		index++;
	}
}

void	ft_check_cmd_path(t_lexer_item *items)
{
	int	index;

	index = 0;
	while (items[index].value && items[index].fn != fn_cmd)
		index++;
}
