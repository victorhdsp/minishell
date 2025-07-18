/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:29:52 by vide-sou          #+#    #+#             */
/*   Updated: 2025/07/02 10:18:16 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOW_H
# define FLOW_H

# include "../../include/libft/libft.h"
# include "../sentences/sentences.h"

typedef struct s_system
{
	char	*name;
	int		last_exit_status;
	int		exit_requested;
	char	**env;
	char	*username;
}			t_system;

t_system	get_system(t_system *new_system);
int			get_system_exit_status(void);
char		*get_system_env(char *key);
void		set_system_exit_status(int exit_status);
void		set_system_name(char *name);
void		set_system_env(char **env);
void		set_system_exit_request(int exit_status);

bool		check_command_in_paths(char **paths, char *cmd);
int			parser_error_cleanup(t_lexer_item *lexed_cmd);
void		free_sentence(t_sentence *sentences);
int			handle_cmd_not_found(char **cmds);
void		free_lexer(t_lexer_item *lexer);
bool		print_cmd_not_found(char *cmd);
void		free_all_system(void);

bool		ft_get_extern_cmd_not_found(char *cmd);
void		system_flow(char **env, char *name);
bool		is_built_in_or_invalid(char *cmd);
bool		validate_first_token(char **cmds);
int			minishell_flow(char *cmd);

#endif