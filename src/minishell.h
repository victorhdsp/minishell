/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by vide-sou          #+#    #+#             */
/*   Updated: 2025/05/14 14:35:09 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../include/libft/libft.h"
# include "./cd/cd.h"
# include "./echo/echo.h"
# include "./env/env.h"
# include "./env_management/env_management.h"
# include "./flow/flow.h"
# include "./pwd/pwd.h"
# include "./sentences/sentences.h"
# include "./tokenizer/tokenizer.h"
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>

int		ft_count_dir(char *dir_path);
char	*ft_correct_path(char *path);
void	print_error(char *str1, char *str3, char *str2, char *str4);

#endif