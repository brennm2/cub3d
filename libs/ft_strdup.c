/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:46:48 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 12:14:09 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO ---------------------------------------------------------------
// A função strdup() retorna um ponteiro para uma nova cadeia de caracteres
// que é uma duplicata das cadeias de caracteres 's'.
// A memória para a nova cadeia de caracteres é obtida com Malloc(3)

#include "libft.h"

char	*ft_strdup(const char *s)
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = (char *)malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	printf("%s\n", ft_strdup("lol"));
// 	printf("%s\n", strdup("lol"));
// 	return (0);
// }