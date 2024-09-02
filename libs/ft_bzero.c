/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:35:35 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 11:56:40 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO: -------------------------------------------------------------
// A função bzero() apaga os dados nos n bytes do início da memória no local
// apontado por s, escrevendo zeros (bytes contendo '\0') naquela área.

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}
/*
#include <stdio.h>

int	main(void)
{
    char    str[] = "Vasco";
    size_t  n = 42;

    ft_bzero(str, n);
    printf("%s\n", str);
    return (0); 
}*/