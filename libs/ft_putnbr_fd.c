/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:13:35 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 12:07:57 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO ----------------------------------------------------
// Gera a saída do int 'n' para o descritor de arquivo fornecido.

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int long	i;

	i = n;
	if (i < 0)
	{
		ft_putchar_fd('-', fd);
		i = i * -1;
	}
	if (i >= 10)
		ft_putnbr_fd((i / 10), fd);
	ft_putchar_fd(i % 10 + '0', fd);
}
/* 
int	main(void)
{
    ft_putnbr_fd(2, 1);
    return (0);
} */