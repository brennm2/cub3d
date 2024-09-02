/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 09:54:06 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 12:07:52 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO -----------------------------------------------------------
// Gera a cadeia de caracteres 's' para o descritor de arquivo fornecido
// seguido por uma nova linha.

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
/* 

int	main(void)
{
    ft_putendl_fd("Vasco da Gama", 1);
    return (0);
} */