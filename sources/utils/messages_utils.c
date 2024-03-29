/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:38:28 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/25 16:48:21 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define GREEN   "\001\033[0;32m\002"
#define CYAN    "\001 \033[1;36m\002"
#define RESET   "\001 \033[0m\002"

t_message	ft_init_messages(void)
{
	t_message	messages;

	messages.minishell_prefix = GREEN"➜"CYAN"minishell :"RESET;
	messages.pipe_syntax_error = "⛔ Syntax error near unexpected token '|'\n";
	messages.double_pipe_error = "⛔ Syntax error near unexpected token "
		"'||' (Unsupported)\n";
	messages.quote_not_closed = "⛔ Quote is not closed.\n";
	messages.semicolon_detected = "⛔ Syntax error near unexpected token ';'\n";
	messages.whitepipe_error = "⛔ Syntax error near unexpected token "
		"'|'. (WhitePipe) \n";
	messages.other_input_error = "⛔ Syntax error near unexpected token\n";
	return (messages);
}
