/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by vide-sou          #+#    #+#             */
/*   Updated: 2025/06/26 16:24:07 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../include/libft/libft.h"

# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>

# include "./traitement/traitement.h"
# include "./tokenizer/tokenizer.h"
# include "./signals_handler/signals_handler.h"
# include "./sentences/sentences.h"
# include "./readline/my_readline.h"
# include "./pwd/pwd.h"
# include "./flow/flow.h"
# include "./exit/exit.h"
# include "./exec/exec.h"
# include "./env_management/env_management.h"
# include "./env/env.h"
# include "./echo/echo.h"
# include "./cd/cd.h"
# include "./builtin/builtin.h"

int		ft_count_dir(char *dir_path);
char	*ft_correct_path(char *path);
void	free_program(t_lexer_item *lexed_cmd, t_sentence *sentence_cmd);
void	print_error(char *str1, char *str2, char *str3, int error_status);

#endif