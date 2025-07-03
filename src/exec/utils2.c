/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:42:03 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/03 11:43:15 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_all_child(t_sentence *sentences, int **tube, t_lexer_item *lexed_cmd)
{
	free_sentence(sentences);
	free_all_system();
	free_lexer(lexed_cmd);
	free(tube[0]);
	free(tube[1]);
	free(tube);
}