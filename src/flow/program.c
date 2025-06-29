/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 08:46:27 by vide-sou          #+#    #+#             */
/*   Updated: 2025/06/28 22:39:01 by rpassos-         ###   ########.fr       */
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

bool	is_built_in_or_invalid(char *cmd)
{
	if (ft_strcmp(cmd, "./minishell") == 0)
		return (true);
	if (cmd[0] == '.' || cmd[0] == '/')
		return (false);
	return (
		ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
	);
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

bool	print_cmd_not_found(char *cmd)
{
	print_error(cmd, ": command not found\n", NULL, 127);
	return (false);
}

bool	ft_get_extern_cmd_not_found(char *cmd)
{
	char	**paths;
	char	*path_var;
	bool	found;

	path_var = get_system_env("PATH");
	if (!path_var)
		return (print_cmd_not_found(cmd));

	paths = ft_split(path_var, ':');
	free(path_var);

	found = check_command_in_paths(paths, cmd);
	free_arr_with_null(paths, get_arr_size(paths));

	if (!found)
		print_error(cmd, ": command not found\n", NULL, 127);
	return (found);
}


bool	validate_first_token(char **cmds)
{
	if (!cmds || !cmds[0])
	return (false);
	if ((cmds[0][0] == '.' && ft_strcmp(cmds[0], "./minishell") != 0)
	|| cmds[0][0] == '/' || cmds[0][0] == '\\')
	{
		print_error(cmds[0], ": command not found\n", NULL, 127);
		free_arr_with_null(cmds, get_arr_size(cmds));
		return (false);
	}
	return (true);
}

int	handle_cmd_not_found(char **cmds)
{
	printf("---------ENTROU\n");
	free_arr_with_null(cmds, get_arr_size(cmds));
	return (get_system(NULL).last_exit_status);
}

int	parser_error_cleanup(t_lexer_item *lexed_cmd)
{
	if (lexed_cmd)
	free_lexer(lexed_cmd);
	return (EXIT_FAILURE);
}

int	execute_and_cleanup(t_lexer_item *lexed_cmd)
{
	prepare_heredoc(lexed_cmd);
	variable_traitement(lexed_cmd);
	prepare_redirects(lexed_cmd);
	quote_traitement(lexed_cmd);
	t_sentence *sentence_cmd = create_pipes(lexed_cmd);
	if (sentence_cmd[1].args)
		create_commands_with_pipe(sentence_cmd, lexed_cmd);
	else
	create_commands_without_pipe(sentence_cmd[0], lexed_cmd);
	free_program(lexed_cmd, sentence_cmd);
	return (get_system(NULL).last_exit_status);
}

int	minishell_flow(char *cmd)
{
	char **splited_cmd = word_breaker(cmd);
	if (!validate_first_token(splited_cmd))
		return (get_system(NULL).last_exit_status);
	if (!is_built_in_or_invalid(splited_cmd[0]) && !ft_get_extern_cmd_not_found(splited_cmd[0]))
		return (handle_cmd_not_found(splited_cmd));
	t_lexer_item *lexed_cmd = lexer(splited_cmd);
	free(splited_cmd);
	if (ft_parser(&lexed_cmd) != 0)
		return (parser_error_cleanup(lexed_cmd));
	return (execute_and_cleanup(lexed_cmd));
}
