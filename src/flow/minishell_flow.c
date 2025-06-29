/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:34:20 by rpassos-          #+#    #+#             */
/*   Updated: 2025/06/28 22:39:08 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static bool	validate_first_token(char **cmds)
// {
// 	if (!cmds || !cmds[0])
// 	return (false);
// 	if ((cmds[0][0] == '.' && ft_strcmp(cmds[0], "./minishell") != 0)
// 	|| cmds[0][0] == '/' || cmds[0][0] == '\\')
// 	{
// 		print_error(cmds[0], ": command not found\n", NULL, 127);
// 		free_arr_with_null(cmds, get_arr_size(cmds));
// 		return (false);
// 	}
// 	return (true);
// }

// static int	handle_cmd_not_found(char **cmds)
// {
// 	printf("---------ENTROU\n");
// 	free_arr_with_null(cmds, get_arr_size(cmds));
// 	return (get_system(NULL).last_exit_status);
// }

// static int	parser_error_cleanup(t_lexer_item *lexed_cmd)
// {
// 	if (lexed_cmd)
// 	free_lexer(lexed_cmd);
// 	return (EXIT_FAILURE);
// }

// static int	execute_and_cleanup(t_lexer_item *lexed_cmd)
// {
// 	t_sentence *sentence_cmd;

// 	sentence_cmd = create_pipes(lexed_cmd);
// 	prepare_heredoc(lexed_cmd);
// 	variable_traitement(lexed_cmd);
// 	prepare_redirects(lexed_cmd);
// 	quote_traitement(lexed_cmd);
// 	if (sentence_cmd[1].args)
// 		create_commands_with_pipe(sentence_cmd, lexed_cmd);
// 	else
// 		create_commands_without_pipe(sentence_cmd[0], lexed_cmd);
// 	free_program(lexed_cmd, sentence_cmd);
// 	return (get_system(NULL).last_exit_status);
// }

// int	minishell_flow(char *cmd)
// {
// 	char			**splited_cmd;
// 	t_lexer_item	*lexed_cmd;

// 	splited_cmd = word_breaker(cmd);
// 	lexed_cmd = lexer(splited_cmd);
// 	if (!validate_first_token(splited_cmd))
// 		return (get_system(NULL).last_exit_status);
// 	if (!is_built_in_or_invalid(splited_cmd[0]) && !ft_get_extern_cmd_not_found(splited_cmd[0]))
// 		return (handle_cmd_not_found(splited_cmd));
// 	free(splited_cmd);
// 	if (ft_parser(&lexed_cmd) != 0)
// 		return (parser_error_cleanup(lexed_cmd));
// 	return (execute_and_cleanup(lexed_cmd));
// }