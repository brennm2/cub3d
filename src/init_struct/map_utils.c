/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsousa-d <bsousa-d@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:57:30 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/24 14:58:13 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*remove_all_spaces(char *str)
{
	int i;
	int j;
	char *result;

	i = 0;
	j = 0;
	result = (char *) malloc(ft_strlen(str) + 1);
	if (result == NULL)
		return (NULL);
	while (str[i] != ' ' && !ft_isalpha(str[i]))
		i++;
	while (ft_isalpha(str[i]))
		i++;
	while (str[i]) {
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	str = ft_strdup(result);
	free(result);
	return (str);
}
