/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:23:32 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 17:27:41 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO: -------------------------------------------------------
// Exclui e libera o node fornecido e todos os sucessores desse node,
// usando a função 'del' e free(3). Finalmente, o ponteiro para a
// lista deve ser definido como NULL.

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*templist;
	t_list	*templist2;

	if (!*lst)
		return ;
	templist = *lst;
	while (templist)
	{
		templist2 = templist->next;
		ft_lstdelone(templist, del);
		templist = templist2;
	}
	*lst = NULL;
}
