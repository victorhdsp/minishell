/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:53:44 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/05 17:04:28 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_readline.h"
#include "../signals_handler/signals_handler.h"
#include "../ambient/ambient.h"

char	*set_prompt()
{
	char	*pwd;
	char	*user;
	char	*result;

	user = get_system_env("USER");
	pwd = get_system_env("PWD");
	result = ft_strnstr(pwd, user, ft_strlen(pwd));
	if (!result)
		return (pwd);
	return (result);
}

void	read_entrys(void)
{
	char		*line;
	t_system	system;
	
	signal_handler();
	while(1)
	{
		system = get_system(NULL);
		set_prompt();
		line = readline(system.name);
		if (line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		printf("%s\n", line);
		//começa a executar a cadeia de comandos
		free(line);
	}
}