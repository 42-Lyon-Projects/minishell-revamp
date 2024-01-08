/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:32:12 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/08 09:03:24 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "stdlib.h"

t_tokens	*ft_create_token(char token, t_token_type token_type)
{
	t_tokens	*tokens;

	tokens = malloc(sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->value = token;
	tokens->type = token_type;
	tokens->next = 0;
	return (tokens);
}

void	ft_add_black_token(t_tokens **tokens_list, t_tokens *token)
{
	t_tokens	*tmp;

	tmp = *tokens_list;
	if (!tmp || tmp->type == 0)
	{
		(*tokens_list)->type = token->type;
		(*tokens_list)->value = token->value;
		free(token);
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
}

void	ft_flush_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	if(!tokens || ft_get_tokens_amount(tokens) < 0)
		return;
	while (tokens)
	{
		tmp = (tokens)->next;
		free(tokens);
		tokens = tmp;
	}
}