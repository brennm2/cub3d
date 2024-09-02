/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:41:35 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 13:06:10 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO --------------------------------------------
// Se c for uma letra maiúscula, tolower() retornará seu
// equivalente em minúsculas.

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}
/*
#include <stdio.h>

int	main(int ac, char **av)
{
    int i;

    i = 1;
    while (ac > 1 && av[i])
    {
        printf("%c\n", ft_tolower(*av[i]));
        i++;
    }
    return (0);
}*/