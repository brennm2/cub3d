/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:22:47 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 11:56:51 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO: ----------------------------------------------
// A função itoa() converte o int n em uma cadeia de string.

#include "libft.h"

static int	ft_is_positive(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	ft_n_size(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*str;

	size = ft_n_size(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (0);
	str[size] = '\0';
	if (n == 0)
		str[size - 1] = '0';
	if (n < 0)
		str[0] = '-';
	while (n != 0)
	{
		str[size - 1] = ft_is_positive(n % 10) + '0';
		n = n / 10;
		size--;
	}
	return (str);
}

// #include <stdio.h>

// int main(void)
// {
// 	printf("%s\n", ft_itoa(125));
// 	printf("%s\n", ft_itoa(-125));
// 	printf("%s\n", ft_itoa(-2147483648));
// 	printf("%s\n", ft_itoa(2147483647));
// 	printf("%s\n", ft_itoa(0));
// }