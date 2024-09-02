/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:19:45 by bde-souz          #+#    #+#             */
/*   Updated: 2024/01/16 14:03:45 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sup_x(unsigned long long int x, int i)
{
	if (x == 0)
	{
		i = ft_is_c('0', i);
		return (i);
	}
	if (x >= 16)
	{
		i = ft_sup_x(x / 16, i);
		i = ft_sup_x(x % 16, i);
	}
	else
	{
		if (x <= 9)
			i = ft_is_c(x + '0', i);
		else
			i = ft_is_c(x + 'a' - 10, i);
	}
	return (i);
}

int	ft_is_ptr(void *ptr, int i)
{
	unsigned long long int	t_ptr;

	if (!ptr)
		return (ft_is_s("(nil)", i));
	t_ptr = (unsigned long long int)ptr;
	i = ft_is_s("0x", i);
	i = ft_sup_x(t_ptr, i);
	return (i);
}
