/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/03 14:08:36 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../sentences/sentences.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

int		ft_heredoc(char *exit);

void	ft_prepare_exec(t_sentence *sentence);
void	ft_use_redirects(t_sentence *sentence);

#endif