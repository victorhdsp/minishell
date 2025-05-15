/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:44:35 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/15 12:33:23 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include "../minishell.h"

enum	e_error_exit
{
	no_error = EXIT_SUCCESS,
	error__numeric_argument_required = -1,
	error__too_many_arguments = -2,
};

int		exit_builtin(char **args);

#endif