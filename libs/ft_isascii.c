/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:27:53 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 11:56:48 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO: --------------------------------------------
// Verifica se C é um valor de unsigned char de 7 bits
// que se ajusta no conjunto de caracteres ASCII.

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
    unsigned char    ch = 219;
    printf("%d\n", ft_isascii(ch));
    return (5);
}*/
