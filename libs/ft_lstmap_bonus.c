/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:17:22 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/20 20:50:16 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO: --------------------------------------------------------------
// Itera a lista 'lst' e aplica a função 'f' no conteúdo de cada node.
// Cria um novo Lista resultante das sucessivas aplicações de a função 'f'.
// A função 'del' é usada para excluir o conteúdo de um node, se necessário.

#include "libft.h"

static void	*ft_clear(t_list *lst, void *content, void (*del)(void *))
{
	if (content && del)
		del(content);
	ft_lstclear(&lst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newnode;
	void	*content;

	if (!lst || !f)
		return (NULL);
	newlst = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (!content)
			return (ft_clear(newlst, content, del));
		newnode = ft_lstnew(content);
		if (!newnode)
			return (ft_clear(newlst, content, del));
		ft_lstadd_back(&newlst, newnode);
		lst = lst->next;
	}
	return (newlst);
}
