/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/05 16:43:30 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../include/libft/libft.h"
#include "./tokenizer/tokenizer.h"
#include "./sentences/sentences.h"
#include "./env/env.h"
#include "./env_management/env_management.h"
#include "./echo/echo.h"
#include "./cd/cd.h"
#include "./flow/flow.h"
//#include <readline/readline.h>
//#include <readline/history.h>
//#include <term.h>
# include <dirent.h>
# include <sys/types.h>

int     ft_count_dir(char *dir_path);
char	*ft_correct_path(char *path);

#endif