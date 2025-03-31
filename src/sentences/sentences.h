/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sentences.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:12:53 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/31 09:56:06 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SENTENCES_H
# define SENTENCES_H

#include "../tokenizer/tokenizer.h"
#include "../../include/libft/libft.h"

typedef struct s_sentence
{
    char        	*infile;
    char        	*outfile;
    char        	**args;
	t_lexer_item	*items;
}                   t_sentence;

t_sentence  *ft_pipes(t_lexer_item *items);

#endif