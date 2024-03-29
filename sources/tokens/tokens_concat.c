/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_concat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:35:26 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/20 15:33:19 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include <stdlib.h>

/**
 * @brief Rebuilds a string from the tokens stored in the minishell struct.
 *
 * This function append the V of tokens in the minishell's parsing command
 * to reconstruct the original command string.
 *
 * @param shell A pointer to the minishell structure.
 * @return A dynamically allocated str contains the reconstructed command.
 *         The caller is responsible for freeing memory for the str.
 */
char	*rebuild_string_from_token(t_minishell *shell)
{
	t_tokens	*tokens;
	char		*str_1;
	char		*str_2;

	tokens = shell->parsing_cmd.tokens;
	str_1 = ft_strdup("");
	while (tokens && tokens->value)
	{
		str_2 = ft_strjoin(str_1, tokens->value);
		free(str_1);
		str_1 = ft_strdup(str_2);
		free(str_2);
		tokens = tokens->next;
	}
	return (str_1);
}

void	append_token(t_tokens *appended, t_tokens *to_append)
{
	char	*joined;
	char	*def;

	if ((!appended || !appended->value) || (!to_append || !to_append->value))
		return ;
	def = NULL;
	if (appended->type == ENV_VALUE && to_append->type == ENV_VALUE)
		def = ft_strjoin(appended->value, "");
	if (def != NULL)
		joined = ft_strjoin(def, to_append->value);
	else
		joined = ft_strjoin(appended->value, to_append->value);
	if (appended->value)
		free(appended->value);
	if (def)
		free(def);
	appended->value = ft_strdup(joined);
	if (joined != NULL)
		free(joined);
}

void	append_quoted(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp && tmp->next)
	{
		if ((tmp->type == QUOTED || tmp->type == SIMPLE_QUOTE || \
			tmp->type == DOUBLE_QUOTE || tmp->type == WORD || \
			tmp->type == ENV_VALUE) && \
			(tmp->next->type == QUOTED || tmp->next->type == SIMPLE_QUOTE || \
				tmp->next->type == DOUBLE_QUOTE || tmp->next->type == WORD || \
				tmp->next->type == ENV_VALUE))
		{
			append_token(tmp, tmp->next);
			ft_delete_token(tokens, tmp->next);
			tmp = *tokens;
			continue ;
		}
		tmp = tmp->next;
	}
}
