/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:15:47 by vide-sou          #+#    #+#             */
/*   Updated: 2024/10/13 15:05:36 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (nmemb == 0 || nmemb == 0)
		return (malloc(0));
	if ((nmemb * size) % nmemb)
		return (NULL);
	result = malloc(nmemb * size);
	if (!result)
		return (NULL);
	ft_memset(result, 0, nmemb * size);
	return (result);
}
