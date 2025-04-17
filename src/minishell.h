/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/17 17:14:14 by rpassos-         ###   ########.fr       */
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
#include "./pwd/pwd.h"
#include "./ambient/ambient.h"
//#include <readline/readline.h>
//#include <readline/history.h>
//#include <term.h>
# include <dirent.h>
# include <sys/types.h>

int     ft_count_dir(char *dir_path);
char	*ft_correct_path(char *path);

#endif