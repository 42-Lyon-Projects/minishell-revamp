/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_alpha.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 03:52:15 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 03:52:16 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_alpha(int character)
{
	return ((character >= 'A' && character <= 'Z') || \
	(character >= 'a' && character <= 'z'));
}
