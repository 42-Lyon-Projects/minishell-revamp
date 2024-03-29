/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 03:16:57 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/09 14:08:25 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "char_utils.h"
#include "string_utils.h"
#include <stdlib.h>

static void	ft_pre_process_token_type(t_tokens *tmp)
{
	while (tmp)
	{
		if (ft_str_equals(tmp->value, "\'"))
			tmp->type = SIMPLE_QUOTE;
		else if (ft_str_equals(tmp->value, "\""))
			tmp->type = DOUBLE_QUOTE;
		else if (ft_str_equals(tmp->value, "|"))
			tmp->type = PIPE;
		else if (ft_str_equals(tmp->value, ">"))
			tmp->type = REDIRECT_OUT;
		else if (ft_str_equals(tmp->value, "<"))
			tmp->type = REDIRECT_IN;
		else if (ft_is_whitespace(tmp->value[0]))
			tmp->type = _SPACE;
		else if (ft_str_equals(tmp->value, "?"))
			tmp->type = INTERO;
		else
			tmp->type = WORD;
		tmp = tmp->next;
	}
}

static t_boolean	ft_token_is_in_quote(t_minishell *shell,
	char *rebuilded_string, size_t token_pos)
{
	size_t	len;

	len = get_index_from_token(shell, token_pos);
	if (len == 0)
		return (_false);
	return (ft_index_is_in_quotes(rebuilded_string, len));
}

static void	post_process_redirections(t_tokens **head, t_tokens *tmp)
{
	if (tmp->type == REDIRECT_OUT && tmp->next && \
		tmp->next->type == REDIRECT_OUT)
	{
		free(tmp->next->value);
		tmp->next->value = NULL;
		ft_delete_token(head, tmp->next);
		free(tmp->value);
		tmp->value = ft_strdup(">>");
		tmp->type = REDIRECT_OUT_DOUBLE;
	}
	else if (tmp->type == REDIRECT_IN && tmp->next && \
		tmp->next->type == REDIRECT_IN)
	{
		free(tmp->next->value);
		tmp->next->value = NULL;
		ft_delete_token(head, tmp->next);
		free(tmp->value);
		tmp->value = ft_strdup("<<");
		tmp->type = REDIRECT_IN_DOUBLE;
	}
}

static void	ft_post_process_token_type(t_tokens *tmp, t_minishell *shell)
{
	char	*rebuilded;

	rebuilded = rebuild_string_from_token(shell);
	while (tmp)
	{
		post_process_redirections(&shell->parsing_cmd.tokens, tmp);
		if (ft_token_is_in_quote(shell, rebuilded, get_current_token_pos(tmp)))
		{
			tmp->type = QUOTED;
		}
		tmp = tmp->next;
	}
	if (rebuilded)
		free(rebuilded);
}

void	tokenize_input(t_minishell *shell)
{
	shell->parsing_cmd.tokens = ft_create_token(0, 0);
	ft_split_to_tokens(shell, 0, 0);
	ft_pre_process_token_type(shell->parsing_cmd.tokens);
	ft_post_process_token_type(shell->parsing_cmd.tokens, shell);
}
