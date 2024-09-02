/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:49:19 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 12:50:59 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO -------------------------------------------------------------
// Aplica a função 'f' a cada caractere da string 's', passando seu índice
// como primeiro argumento para criar uma nova cadeia de caracteres
// (com malloc(3)) resultante de aplicações sucessivas de 'f'.

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (0);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

// char	ft_isa(unsigned int n, char c)
// {
// 	if (n < 0)
// 		return (0);
// 	c = 'a';
// 	return (c);
// }

// char addOne(unsigned int i, char c)
// {
// 	return (i + c);
// }

// #include <stdio.h>

// int main (void)
// {
// 	printf("%s\n", ft_strmapi("123", addOne));
// }