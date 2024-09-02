/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:41:07 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 15:57:44 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO: ---------------------------
// Conta o número de nodes em uma lista.

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	listsize;

	listsize = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		listsize++;
	}
	return (listsize);
}
