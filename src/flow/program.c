/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 08:46:27 by vide-sou          #+#    #+#             */
/*   Updated: 2025/06/23 12:30:19 by rpassos-         ###   ########.fr       */
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

void	system_flow(char **env, char *name)
{
	t_system	new_system;
	t_my_env	*list_env;
	char		*username;

	new_system.last_exit_status = 1;
	new_system.name = ft_strdup(name);
	new_system.username = ft_strdup("user");
	list_env = get_env(env);
	new_system.env = get_env_arr(list_env);
	get_system(&new_system);
	username = get_system_env("USER");
	if (username)
	{
		free(new_system.username);
		new_system.username = username;
		get_system(&new_system);
	}
	ft_lstclear_env(&list_env);
}

int	minishell_flow(char *cmd)
{
	char			**splited_cmd;
	t_lexer_item	*lexed_cmd;
	t_sentence		*sentence_cmd;

	splited_cmd = word_breaker(cmd);
	lexed_cmd = lexer(splited_cmd);
	free(splited_cmd);
	if (ft_parser(&lexed_cmd) != 0)
	{
		if (lexed_cmd)
			free_lexer(lexed_cmd);
		return (EXIT_FAILURE);
	}
	prepare_heredoc(lexed_cmd);
	variable_traitement(lexed_cmd);
	prepare_redirects(lexed_cmd);
	quote_traitement(lexed_cmd);
	sentence_cmd = create_pipes(lexed_cmd);
	if (sentence_cmd[1].args)
		create_commands_with_pipe(sentence_cmd, lexed_cmd);
	else
		create_commands_without_pipe(sentence_cmd[0], lexed_cmd);
	free_sentence(sentence_cmd);
	free_lexer(lexed_cmd);
	return (get_system(NULL).last_exit_status);
}
