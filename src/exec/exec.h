/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/19 12:12:29 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define FD_NOT_CREATED -2

# include "../tokenizer/tokenizer.h"
# include "../sentences/sentences.h"

void	create_commands_with_pipe(t_sentence *sentences, t_lexer_item	*lexed_cmd);
void	create_commands_without_pipe(t_sentence sentence, t_lexer_item	*lexed_cmd);
void	prepare_heredoc(t_lexer_item	*items);
void	prepare_redirects(t_lexer_item *items);
char	*ft_get_extern_cmd(t_lexer_item *items);
int		ft_exec_builtin(t_lexer_item *items, char **args);

#endif