/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:39:12 by rpassos-          #+#    #+#             */
/*   Updated: 2025/04/14 13:54:11 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

void	cd_free(char **arr)
{
	free(arr[1]);
	free(arr);
}
