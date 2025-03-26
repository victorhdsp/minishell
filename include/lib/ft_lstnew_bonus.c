/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:46:06 by vide-sou          #+#    #+#             */
/*   Updated: 2024/10/14 20:41:59 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*result;

	result = (t_list *)ft_calloc(1, sizeof(t_list));
	if (result == NULL)
		return (NULL);
	result->content = content;
	result->next = NULL;
	return (result);
}
