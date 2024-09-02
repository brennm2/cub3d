/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:37:02 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 12:08:24 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO ----------------------------------------------------------
// Gera a saída do caractere 'c' para o descritor de arquivo fornecido.

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
/* 
#include <stdio.h>

int	main(void)
{
    ft_putstr_fd("Vasco da Gama", 1);
    return (0);
} */