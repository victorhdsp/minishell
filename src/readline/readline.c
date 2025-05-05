/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:53:44 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/05 19:37:05 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_readline.h"
#include "../signals_handler/signals_handler.h"
#include "../flow/flow.h"

void	set_prompt()
{
	char	*pwd;
	char	*user;
	char	*result;
	char 	*tmp;

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
	while(1)
	{
		set_prompt();
		system = get_system(NULL);
		line = readline(system.name);
		if (line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		minishell_flow(line);
		free(line);
	}
}