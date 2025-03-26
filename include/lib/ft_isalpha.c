/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:26:49 by vide-sou          #+#    #+#             */
/*   Updated: 2024/10/14 20:36:32 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_islower(int c)
{
	return (c >= 97 && c <= 122);
}

static int	ft_isupper(int c)
{
	return (c >= 65 && c <= 90);
}

int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}
