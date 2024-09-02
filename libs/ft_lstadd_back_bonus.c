/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:00:11 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 19:22:42 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO: -----------------------------
// Adiciona o node 'new' no final da lista.

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tempnode;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tempnode = ft_lstlast(*lst);
	tempnode->next = new;
}
