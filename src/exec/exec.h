/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by vide-sou          #+#    #+#             */
/*   Updated: 2025/07/03 11:43:32 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define FD_NOT_CREATED -2

# include "../tokenizer/tokenizer.h"
# include "../sentences/sentences.h"

void	create_commands_with_pipe(t_sentence *sentences, t_lexer_item	*lexed_cmd);
void	create_commands_without_pipe(t_sentence sentence, t_lexer_item	*lexed_cmd);
void	free_all_child(t_sentence *sentences, int **tube, t_lexer_item *lexed_cmd);
int		ft_exec_builtin(t_lexer_item *items, char **args);
void	prepare_heredoc(t_lexer_item	*items);
char	*ft_get_extern_cmd(t_lexer_item *items);
void	prepare_redirects(t_lexer_item *items);

#endif