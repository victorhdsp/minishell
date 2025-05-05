/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/05 16:47:53 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../builtin/builtin.h"
# include "../sentences/sentences.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

void	exec_command(t_sentence *sentence);
void	prepare_redirects(t_sentence *sentence);
char	*ft_get_extern_cmd(t_lexer_item *items);
int		ft_exec_builtin(t_lexer_item *items, char **args);

#endif