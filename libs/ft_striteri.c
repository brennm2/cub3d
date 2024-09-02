/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:22:15 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 12:25:22 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO -----------------------------------------------------------------
// Aplica a função 'f' em cada caractere da cadeia de caracteres passado como
// argumento, passando seu índice como primeiro argumento.
// Cada caractere é passado por endereço para 'f' para ser modificado
// se necessário.

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
// #include <stdio.h>

// void ft_isa (unsigned int n, char *c)
// {
// 	printf("%i %s\n", n, c);
// }

// int main (void)
// {
// 	ft_striteri("Vasco", &ft_isa);
// 	return (0);
// }