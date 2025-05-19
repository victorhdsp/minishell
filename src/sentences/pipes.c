/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:59:02 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/19 11:53:51 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	ft_count_words(t_lexer_item *items, int *words_index, int index)
{
	*words_index = 0;
	while (items[index].value)
	{
		if (items[index].type == type_logic)
			break ;
		if (items[index].type == type_infile
			|| items[index].type == type_outfile)
			index++;
		else if (items[index].type == type_word)
			*words_index = *words_index + 1;
		index++;
	}
}

static void	ft_create_sentence(t_sentence *sentence, t_lexer_item *items,
		int *index)
{
	int	words_index;

	ft_count_words(items, &words_index, *index);
	sentence->args = ft_calloc(words_index + 1, sizeof(char *));
	words_index = 0;
	while (items[*index].type != type_logic && items[*index].value)
	{
		if (items[*index].type == type_infile)
		{
			*index = *index + 1;
		}
		else if (items[*index].type == type_outfile)
		{
			*index = *index + 1;
		}
		else if (items[*index].type == type_word)
		{
			sentence->args[words_index] = items[*index].value;
			words_index++;
		}
		*index = *index + 1;
	}
}

static void	ft_save_items(t_sentence *sentence, t_lexer_item *items,
		int items_index)
{
	int	index;

	index = items_index;
	while (items[index].type != type_logic && items[index].value)
		index++;
	sentence->items = ft_calloc(index + 1, sizeof(t_lexer_item));
	index = 0;
	while (items[items_index].type != type_logic && items[items_index].value)
	{
		sentence->items[index] = items[items_index];
		if (items[items_index].type == type_infile)
			sentence->infile = items[items_index + 1].fd;
		if (items[items_index].type == type_outfile)
			sentence->outfile = items[items_index + 1].fd;
		index++;
		items_index++;
	}
}

t_sentence	*create_pipes(t_lexer_item *items)
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
		sentences[sentences_index].infile = STDIN_FILENO;
		sentences[sentences_index].outfile = STDOUT_FILENO;
		sentences[sentences_index].args = NULL;
		sentences[sentences_index].items = NULL;
		ft_save_items(&sentences[sentences_index], items, items_index);
		ft_create_sentence(&sentences[sentences_index], items, &items_index);
		items_index++;
		sentences_index++;
	}
	return (sentences);
}
