/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sentences.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:12:53 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/16 14:51:03 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SENTENCES_H
# define SENTENCES_H

# include "../tokenizer/tokenizer.h"

typedef struct s_sentence
{
	int				infile;
	int				outfile;
	char			**args;
	t_lexer_item	*items;
}					t_sentence;

t_sentence			*create_pipes(t_lexer_item *items);

#endif