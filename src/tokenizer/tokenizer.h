/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:12:50 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/16 14:52:52 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

enum							e_type_sentence_item
{
	type_infile,
	type_outfile,
	type_logic,
	type_parenthesis,
	type_word,
	type_null
};

enum							e_fn_sentence_item
{
	fn_null,
	fn_input,
	fn_heredoc,
	fn_output,
	fn_append,
	fn_pipe,
	fn_and,
	fn_or,
	fn_open_parenthesis,
	fn_close_parenthesis,
	fn_cmd
};

typedef struct s_lexer_item
{
	char						*value;
	int							fd;
	enum e_type_sentence_item	type;
	enum e_fn_sentence_item		fn;
}								t_lexer_item;

char							**word_breaker(const char *str);
t_lexer_item					*lexer(char **strs);
int								ft_parser(t_lexer_item **cmds);

#endif