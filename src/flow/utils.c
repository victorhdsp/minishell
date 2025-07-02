/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:14:40 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/02 15:29:13 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_sentence(t_sentence *sentences)
{
	int	sent_index;
	int	item_index;

	sent_index = 0;
	while (sentences[sent_index].items)
	{
		item_index = 0;
		while (sentences[sent_index].items[item_index].value)
		{
			if (sentences[sent_index].items[item_index].type == type_infile
				|| sentences[sent_index].items[item_index].type == type_outfile)
				close(sentences[sent_index].items[item_index + 1].fd);
			item_index++;
		}
		free(sentences[sent_index].items);
		free(sentences[sent_index].args);
		sent_index++;
	}
	free(sentences);
}

void	free_lexer(t_lexer_item *lexer)
{
	int	index;

	index = 0;
	while (lexer[index].value)
	{
		free(lexer[index].value);
		index++;
	}
	free(lexer);
}

int	handle_cmd_not_found(char **cmds)
{
	free_arr_with_null(cmds, get_arr_size(cmds));
	return (get_system(NULL).last_exit_status);
}

int	parser_error_cleanup(t_lexer_item *lexed_cmd)
{
	if (lexed_cmd)
		free_lexer(lexed_cmd);
	return (EXIT_FAILURE);
}

bool	print_cmd_not_found(char *cmd)
{
	print_error(cmd, ": command not found\n", NULL, 127);
	return (false);
}
