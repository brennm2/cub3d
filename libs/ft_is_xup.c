/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_xup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:32:30 by bde-souz          #+#    #+#             */
/*   Updated: 2024/01/16 14:03:53 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_xup(unsigned int x, int i)
{
	if (x == 0)
	{
		i = ft_is_c('0', i);
		return (i);
	}
	if (x >= 16)
	{
		i = ft_is_xup(x / 16, i);
		i = ft_is_xup(x % 16, i);
	}
	else
	{
		if (x <= 9)
			i = ft_is_c(x + '0', i);
		else
			i = ft_is_c(x + 'A' - 10, i);
	}
	return (i);
}
