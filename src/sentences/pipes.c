/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:59:02 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/28 15:34:11 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./sentences.h"

static void	ft_count_pipes(t_lexer_item *items, int *sentences_index)
{
	int	index;

	index = 0;
	*sentences_index = 1;
	while (items[index].value)
	{
		if (items[index].type == type_logic && items[index].fn != fn_pipe)
			break ;
		if (items[index].fn == fn_pipe)
			*sentences_index = *sentences_index + 1;
		index++;
	}
}

static void	ft_count_words(t_lexer_item *items, int lexer_index[3], int index)
{
	lexer_index[0] = 0;
	lexer_index[1] = 0;
	lexer_index[2] = 0;
	while (items[index].value)
	{
		if (items[index].type == type_logic)
			break ;
		else if (items[index].type == type_infile)
		{
			lexer_index[1] = lexer_index[1] + 1;
			index++;
		}
		else if (items[index].type == type_outfile)
		{
			lexer_index[2] = lexer_index[2] + 1;
			index++;
		}
		else if (items[index].type == type_word)
			lexer_index[0] = lexer_index[0] + 1;
		index++;
	}
}

static void	ft_save_sentence_item(t_sentence *sentence, t_lexer_item *items,
		int lexer_index[3], int *index)
{
	if (items[*index].type == type_infile)
	{
		sentence->infile[lexer_index[1]].fn = items[*index].fn;
		sentence->infile[lexer_index[1]].word = items[*index + 1].value;
		lexer_index[1]++;
		*index = *index + 1;
	}
	else if (items[*index].type == type_outfile)
	{
		sentence->outfile[lexer_index[2]].fn = items[*index].fn;
		sentence->outfile[lexer_index[2]].word = items[*index + 1].value;
		lexer_index[2]++;
		*index = *index + 1;
	}
	else if (items[*index].type == type_word)
	{
		sentence->args[lexer_index[0]] = items[*index].value;
		lexer_index[0]++;
	}
	*index = *index + 1;
}

static void	ft_create_sentence(t_sentence *sentence, t_lexer_item *items,
		int *index)
{
	int	lexer_index[3];

	ft_count_words(items, lexer_index, *index);
	sentence->args = ft_calloc(lexer_index[0] + 1, sizeof(char *));
	sentence->infile = ft_calloc(lexer_index[1] + 1, sizeof(char *));
	sentence->outfile = ft_calloc(lexer_index[2] + 1, sizeof(char *));
	lexer_index[0] = 0;
	lexer_index[1] = 0;
	lexer_index[2] = 0;
	while (items[*index].type != type_logic && items[*index].value)
	{
		ft_save_sentence_item(sentence, items, lexer_index, index);
	}
}

t_sentence	*ft_pipes(t_lexer_item *items)
{
	t_sentence	*sentences;
	int			sentences_total;
	int			sentences_index;
	int			items_index;

	sentences_index = 0;
	items_index = 0;
	ft_count_pipes(items, &sentences_total);
	sentences = ft_calloc(sentences_total + 1, sizeof(t_sentence));
	while (sentences_index < sentences_total)
	{
		sentences[sentences_index].infile = NULL;
		sentences[sentences_index].outfile = NULL;
		sentences[sentences_index].args = NULL;
		ft_create_sentence(&sentences[sentences_index], items, &items_index);
		items_index++;
		sentences_index++;
	}
	return (sentences);
}
