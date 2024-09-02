/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:05:08 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 13:06:50 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO --------------------------------------------
// Se c for uma letra minúscula, toupper() retornará seu
// equivalente em maiúsculas.

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
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
        printf("%c\n", ft_toupper(*av[i]));
        i++;
    }
    return (0);
}*/
