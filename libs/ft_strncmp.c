/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:48:55 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 12:51:04 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO -----------------------------------------------------------
// A função strcmp() compara as duas cadeias de caracteres 's1' e 's2'.
// A localidade não é levada em conta.
// A comparação é feita usando unsigned characters.

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if ((int)n < 0)
		return ((int)n);
	while ((str1[i] || str2[i]) && i < (int)n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int	main(void)
// {
// 	char	s1[] = "test\200";
// 	char	s2[] = "test\0";
// 	size_t	n = 5;

// 	printf("Original: %d\n", strncmp(s1, s2, n));
// 	printf("Criada: %d\n", ft_strncmp(s1, s2, n));
// 	return (0);
// }

// int     main(int ac, char **av)
// {
//     if (ac < 4)
//     {
//         return (printf("\nFalta argumentos :)\n\n"));
//     }
//     //printf("Criada: %d\n", ft_strncmp(av[1], av[2], atoi(av[3])));
//     //printf("Original: %d\n", strncmp(av[1], av[2], atoi(av[3])));
//     return (0);
// }
