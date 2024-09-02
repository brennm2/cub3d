/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:46:04 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 11:56:42 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO: ------------------------------------------------------------------
// The calloc() function allocates memory for an array of n elements of
// size bytes each and returns a pointer to the allocated memory.
// The memory is set to zero. If n or size is 0, then calloc() returns
// a unique pointer value that can later be successfully passed to free().

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*s;

	s = malloc(n * size);
	if (!s)
		return (NULL);
	ft_bzero(s, n * size);
	return (s);
}
/* 
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
    printf("%s\n", (char *)ft_calloc(5, 5));
    printf("%s\n", (char *)calloc(5, 5));
    return (0);
} */