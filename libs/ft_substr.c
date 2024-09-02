/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:23:43 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 13:04:44 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO -------------------------------------------------------
// Aloca (com malloc(3)) e retorna uma substring da string 's'.
// A substring começa no índice 'start' e é de tamanho máximo 'len'.

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned char	i;
	unsigned char	j;
	unsigned int	strlen;
	char			*str;

	strlen = ft_strlen(s);
	i = 0;
	j = 0;
	if (start > ft_strlen(s))
		len = 0;
	if (len > strlen - start)
		len = ft_strlen(s + start);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	while (len > i && s[start + i] && ft_strlen(s) > start)
	{
		str[j++] = s[start + i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%s\n", ft_substr("123456", 2, 55555555));
// 	return (0);
// }