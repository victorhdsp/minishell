/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:53:44 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/05 18:48:28 by rpassos-         ###   ########.fr       */
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

	user = get_system_env("USER");
	pwd = get_system_env("PWD");
	result = ft_strnstr(pwd, user, ft_strlen(pwd));
	if (!result)
		result = pwd;
	tmp = ft_strjoin(":~", result);
	result = ft_strjoin(user, tmp);
	set_system_name(result);
	free(tmp);
	free(user);
	free(pwd);
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