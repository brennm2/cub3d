/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:06:37 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 11:56:39 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Description: ---------------------------------------------------
// A função atoi() converte a parte inicial da string *s para int.

#include "libft.h"

int	ft_atoi(const char *s)
{
	int	i;
	int	sinal;
	int	numero;

	i = 0;
	sinal = 1;
	numero = 0;
	while (((char *)s)[i] == 32 ||
			(((char *)s)[i] >= 9 && ((char *)s)[i] <= 13))
		i++;
	while (((char *)s)[i] == '+' || ((char *)s)[i] == '-')
	{
		if (((char *)s)[i] == '-')
			sinal = sinal * -1;
		if (((char *)s)[i + 1] == '-' || ((char *)s)[i + 1] == '+')
			return (0);
		i++;
	}
	while (((char *)s)[i] >= '0' && ((char *)s)[i] <= '9')
	{
		numero = numero * 10;
		numero = numero + (((char *)s)[i] - '0');
		i++;
	}
	return (numero = numero * sinal);
}

/* 
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    //char escape[] = {9, 10, 11, 12, 13, 0};

    printf("Criada: %d\n", ft_atoi("-225"));
    printf("Original: %d\n", atoi("-225"));
    return (0);
}  */