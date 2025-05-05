/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 08:46:27 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/23 13:30:29 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"
#include "../traitement/traitement.h"
#include "../exec/exec.h"
#include "./flow.h"

static void free_sentence(t_sentence *sentence)
{
    int sent_index;
    int item_index;

    sent_index = 0;
    while (sentence[sent_index].items)
    {
        item_index = 0;
        while (sentence[sent_index].items[item_index].value)
        {
            if (sentence[sent_index].items[item_index].type == type_infile
                || sentence[sent_index].items[item_index].type == type_outfile)
                close(sentence[sent_index].items[item_index + 1].fd);
            item_index++;
        }
        free(sentence[sent_index].items);
        free(sentence[sent_index].args);
        sent_index++;
    }
    free(sentence);
}

static void free_lexer(t_lexer_item *lexer)
{
    int index;

    index = 0;
    while (lexer[index].value)
    {
        free(lexer[index].value);
        index++;
    }
    free(lexer);
}

void	system_flow(char **env, char *name)
{
	t_system	new_system;
	t_my_env	*list_env;

	new_system.last_exit_status = -1;
	new_system.name = name;
	list_env = get_env(env);
	new_system.env = get_env_arr(list_env);
	get_system(&new_system);
    ft_lstclear_env(&list_env);
}

int minishell_flow(char *cmd)
{
    char            **splited_cmd;
    t_lexer_item    *lexed_cmd;
    t_sentence      *sentence_cmd;
    int             exit_status;
    
    splited_cmd = word_breaker(cmd);
    lexed_cmd = lexer(splited_cmd);
    exit_status = ft_parser(&lexed_cmd);
    if (exit_status != 0)
    {
        free_lexer(lexed_cmd);
        free(splited_cmd);
        return (EXIT_FAILURE);
    }
    variable_traitement(lexed_cmd);
    quote_traitement(lexed_cmd);
    sentence_cmd = create_pipes(lexed_cmd);
    exec_command(sentence_cmd);
    free_sentence(sentence_cmd);
    free_lexer(lexed_cmd);
    free(splited_cmd);
    return(get_system(NULL).last_exit_status);
}
