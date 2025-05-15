/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/15 08:56:16 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../builtin/builtin.h"
# include "../sentences/sentences.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define FD_NOT_CREATED -2

void	create_commands_with_pipe(t_sentence *sentences);
void    create_commands_without_pipe(t_sentence sentence);
void	prepare_redirects(t_sentence *sentence);
char	*ft_get_extern_cmd(t_lexer_item *items);
int		ft_exec_builtin(t_lexer_item *items, char **args);

#endif