/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:58:20 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 12:00:36 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO -----------------------------------------------
// A função memset() preenche os primeiros n bytes
// da área de memória apontada por s com a constante byte c.

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (str);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
    char    str[] = "Vasco da Gama";
    int     c = '-';
    size_t  n = 2;
    char    *put;
	//char	*put2;
    put = ft_memset(str, c, n);
	//put2 = memset(str, c, n);

	//printf("%s\n", put2);
	printf("%s\n", put);
    return (0);
}*/
