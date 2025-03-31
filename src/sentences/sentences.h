/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sentences.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:12:53 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/31 09:13:08 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SENTENCES_H
# define SENTENCES_H

# include "../../include/libft/libft.h"
# include "../tokenizer/tokenizer.h"

typedef struct s_redirect
{
	char					*word;
	enum e_fn_sentence_item	fn;
}							t_redirect;

typedef struct s_sentence
{
	t_redirect				*infile;
	t_redirect				*outfile;
	char					**args;
}							t_sentence;

t_sentence					*ft_pipes(t_lexer_item *items);

#endif