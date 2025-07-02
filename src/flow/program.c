/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 08:46:27 by vide-sou          #+#    #+#             */
/*   Updated: 2025/07/02 15:24:09 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	system_flow(char **env, char *name)
{
	t_system	new_system;
	t_my_env	*list_env;
	char		*username;

	new_system.last_exit_status = 1;
	new_system.name = ft_strdup(name);
	new_system.username = ft_strdup("user");
	new_system.exit_requested = -1;
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

bool	check_command_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*temp;
	char	*full_path;

	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK) == 0)
		{
			free(full_path);
			return (true);
		}
		free(full_path);
	}
	return (false);
}

static int	execute_and_cleanup(t_lexer_item *lexed_cmd)
{
	t_sentence *sentence_cmd;
	
	prepare_heredoc(lexed_cmd);
	variable_traitement(lexed_cmd);
	prepare_redirects(lexed_cmd);
	quote_traitement(lexed_cmd);
	sentence_cmd = create_pipes(lexed_cmd);
	if (sentence_cmd[1].args)
		create_commands_with_pipe(sentence_cmd, lexed_cmd);
	else
		create_commands_without_pipe(sentence_cmd[0], lexed_cmd);
	free_program(lexed_cmd, sentence_cmd);
	return (get_system(NULL).last_exit_status);
}

int	minishell_flow(char *cmd)
{
	t_lexer_item *lexed_cmd;
	char **splited_cmd;

	splited_cmd = word_breaker(cmd);
	if (!validate_first_token(splited_cmd))
		return (get_system(NULL).last_exit_status);
	if (!is_built_in_or_invalid(splited_cmd[0])
		&& !ft_get_extern_cmd_not_found(splited_cmd[0]))
		return (handle_cmd_not_found(splited_cmd));
	lexed_cmd = lexer(splited_cmd);
	free(splited_cmd);
	if (ft_parser(&lexed_cmd) != 0)
		return (parser_error_cleanup(lexed_cmd));
	return (execute_and_cleanup(lexed_cmd));
}
