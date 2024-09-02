/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:47:51 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 12:44:07 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO --------------------------------------------------------
// A função strlen() calcula o comprimento da cadeia de caracteres
// apontado por 'str', excluindo o byte nulo de terminação ('\0').

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int		i;
	char	*s;

	s = (char *)str;
	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
#include <stdio.h>

int	main(void)
{
    char    c[]= "Vasco";
    printf("%d\n", ft_strlen(c));
    return (0);
}*/
