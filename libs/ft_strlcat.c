/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:31:49 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 12:40:30 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO --------------------------------------------------------
// Copia e concatenar cadeias de caracteres respectivamente
// Retorna o tamanho das duas strings contatenadas

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	lenstr;
	size_t	i;
	size_t	templen;

	i = 0;
	lendst = ft_strlen(dst);
	lenstr = ft_strlen((char *)src);
	templen = ft_strlen(dst);
	if (!dst && !src)
		return (0);
	if (size <= lendst)
		return (lenstr + size);
	size = size - lendst;
	while (i < size - 1 && src[i])
	{
		dst[lendst] = src[i];
		i++;
		lendst++;
	}
	dst[lendst] = '\0';
	return (templen + lenstr);
}

// #include <stdio.h>

// //#include <bsd/string.h>
// // use -lbsd
// int	main(void)
// {
// 	// char	dst[14] = "a";
// 	// const char	src[] = "lorem ipsum dolor sit amet";
// 	// size_t	size = 15;

// 	char dst2[14] = "a";
// 	const char src2[] = "lorem ipsum dolor sit amet";
// 	int size2 = -1;

// 	printf("Retorno da ft_criada: %ld\n", ft_strlcat(dst2, src2, size2));
// 	printf("%s\n", dst2);
// 	//printf("%s\n", dst2);
// 	//printf("Retorno da ft_original: %ld\n", strlcat(dst, src, size));
// 	//printf("%s\n%s\n%ld\n", dst, src, size);
// 	//printf("%s\n", dst);
// 	return (0);
// }