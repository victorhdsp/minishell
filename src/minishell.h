/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/02 13:05:28 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../include/libft/libft.h"
# include "./exec/exec.h"
# include "./sentences/sentences.h"
# include "./tokenizer/tokenizer.h"
# include <dirent.h>
# include <sys/types.h>
//#include <readline/readline.h>
//#include <readline/history.h>
//#include <term.h>

int     ft_count_dir(char *dir_path);
char	*ft_correct_path(char *path);

#endif