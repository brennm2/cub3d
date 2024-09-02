/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:37:48 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 11:56:57 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO: -----------------------------------------
// A função memcmp() compara os primeiros n bytes
// (cada um interpretado como unsigned char)
// das áreas de memória s1 e s2.

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n - 1)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}
/* 
#include <stdio.h>
#include <string.h>

int	main(void)
{
	unsigned int	n = 7;
	unsigned char	s1[] = "abcdefghij";
	unsigned char	s2[] = "abcdefgxyz";

	printf("Criada: %d\n", ft_memcmp(s1, s2, n));
	printf("Original: %d\n", memcmp(s1, s2, n));
	return (0);
} */