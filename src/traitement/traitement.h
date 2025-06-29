/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traitement.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by vide-sou          #+#    #+#             */
/*   Updated: 2025/06/28 22:03:28 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAITEMENT_H
# define TRAITEMENT_H

#include "../tokenizer/tokenizer.h"

void	quote_traitement(t_lexer_item *args);
void	variable_traitement(t_lexer_item *args);
char	*get_public_value(char *key, char *old_value);
char	*get_reserved_value(char *key, char *old_value);
void	change_variable(char *get, char **set, char *key);
char	*get_new_value(char *key, char *old_value, char *new_value, int index);

#endif