/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/14 14:26:13 by vide-sou         ###   ########.fr       */
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

void	exec_command_in_childs(t_sentence *sentences);
void    exec_command_in_parent(t_sentence *sentences);
void	prepare_redirects(t_sentence *sentence);
char	*ft_get_extern_cmd(t_lexer_item *items);
int		ft_exec_builtin(t_lexer_item *items, char **args);

#endif