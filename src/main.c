/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:30:53 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/09 15:31:13 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(void)
{/*
	t_sentence		*result;
	t_lexer_item	input[] = {
		{.value = ">", .type = type_outfile, .fn = fn_output},
		{.value = "local/tmp", .type = type_word, .fn = fn_null},
		{.value = "cat", .type = type_word, .fn = fn_cmd},
		{.value = "Makefile", .type = type_word, .fn = fn_null},
		{.value = NULL}
	};
	result = ft_pipes((t_lexer_item *)input);
	ft_prepare_exec(result);
*/
/*
	char      *filename = "/home/vide-sou/projetos/pessoal/rank3/minishell/local/tmp/test_output.txt";
    t_lexer_item    input[] = {
		{.value = ">", .type = type_outfile, .fn = fn_output},
		{.value = filename, .type = type_word, .fn = fn_null},
		{.value = NULL}
	};
    t_sentence *sentence = ft_pipes((t_lexer_item *)input);
    ft_use_redirects(sentence);
    int result = access(filename, F_OK);
*/
char *heredoc_content = "test heredoc content\n";
char *heredoc_delimiter = "EOF\n";
t_lexer_item input[] = {
	{.value = "<<", .type = type_infile, .fn = fn_heredoc},
	{.value = heredoc_delimiter, .type = type_word, .fn = fn_null},
	{.value = NULL}
};
t_sentence *sentence = ft_pipes((t_lexer_item *)input);

int fd = fork();
if (fd == 0)
{
	ft_use_redirects(sentence);
} else 
{
	fflush(0);
	write(0, heredoc_content, strlen(heredoc_content));
	write(0, heredoc_delimiter, strlen(heredoc_delimiter));
	waitpid(fd, NULL, 0);
}
}
