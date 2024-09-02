/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:46:07 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 13:01:41 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO ----------------------------------------------------------------
// A função strrchr() retorna um ponteiro para o última ocorrência do
// caractere 'c' nas cadeias de caracteres 's'.

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (unsigned char)c)
			return ((char *)&s[len]);
		len--;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[len]);
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int main (void)
{
    const char    str[] = "pepe y cparlos";
    int    c = 'c';

	//strrchr(str, c);
    printf("%s \n", strrchr(str, c));
    printf("%s \n", ft_strrchr(str, c));
    return (0);
}*/
