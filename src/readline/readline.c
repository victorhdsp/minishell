/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:53:44 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/12 10:35:03 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../flow/flow.h"
#include "../signals_handler/signals_handler.h"
#include "my_readline.h"

void	set_prompt(void)
{
	char	*pwd;
	char	*user;
	char	*result;
	char	*tmp;

	user = get_system(NULL).username;
	pwd = get_system_env("PWD");
	tmp = ft_strnstr(pwd, user, ft_strlen(pwd));
	if (!tmp)
		tmp = pwd;
	else
		tmp += ft_strlen(user);
	result = ft_strjoin(":~", tmp);
	tmp = ft_strjoin(user, result);
	free(result);
	result = ft_strjoin(tmp, "$ ");
	set_system_name(result);
	free(tmp);
	free(pwd);
}

void	read_entrys(void)
{
	char		*line;
	t_system	system;

	system = get_system(NULL);
	signal_handler();
	while (1)
	{
		set_prompt();
		system = get_system(NULL);
		line = readline(system.name);
		if (line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (line && line[0])
		{
			add_history(line);
			minishell_flow(line);
		}
		free(line);
	}
}
