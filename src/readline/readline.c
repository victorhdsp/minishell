/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:53:44 by rpassos-          #+#    #+#             */
/*   Updated: 2025/04/24 10:54:44 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_readline.h"

void	read_entrys(void)
{
	char	*line;
	
	//signal_handler();
	while(1)
	{
		line = readline("minishell$: ");
		if (line == NULL)
			exit(0);
		add_history(line);
		printf(line);
		//começa a executar a cadeia de comandos
		free(line);
	}
}