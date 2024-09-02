/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:24:41 by bde-souz          #+#    #+#             */
/*   Updated: 2023/10/19 11:56:52 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO: -------------------------------
// Adiciona um node 'novo' no início da lista.

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
