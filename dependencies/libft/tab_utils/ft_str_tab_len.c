/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 02:17:59 by jbadaire          #+#    #+#             */
/*   Updated: 2023/11/19 12:55:34 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_str_tab_len(char **tab)
{
	size_t	index;

	index = 0;
	while (tab && tab[index])
		index++;
	return (index);
}
