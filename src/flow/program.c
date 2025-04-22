/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 08:46:27 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/22 11:41:04 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"
#include "../traitement/traitement.h"
#include "../exec/exec.h"
#include "./flow.h"

int minishell_flow(char *cmd)
{
    char            **splited_cmd;
    t_lexer_item    *lexed_cmd;
    t_sentence      *sentence_cmd;
    
    splited_cmd = word_breaker(cmd);
    lexed_cmd = lexer(splited_cmd);
    set_system_exit_status(ft_parser(&lexed_cmd));
    variable_traitement(lexed_cmd);
    quote_traitement(lexed_cmd);
    sentence_cmd = create_pipes(lexed_cmd);
    exec_command(sentence_cmd);
    return(get_system(NULL).last_exit_status);
}
