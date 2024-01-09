/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:27:22 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/09 15:21:27 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../dependencies/libft/.includes/string_utils.h"
#include "../dependencies/libft/.includes/ft_printf.h"

int	g_status_code;

static void	ft_shell_loop(t_minishell *shell)
{
	char	*line;

	while (shell->is_running)
	{
		line = readline(shell->messages.minishell_prefix);
		if (!line || !ft_has_valid_history(line))
			continue ;
		ft_replace_whitespace(line, ' ');
		add_history(line);
		shell->sended_line = ft_strtrim(line, " ");
		parse_input(shell);
		if (ft_str_contains(shell->sended_line, "|", 0, 0) || ft_str_contains(shell->sended_line, "<", 0, 0) || ft_str_contains(shell->sended_line, ">", 0, 0) || !in_builtins(shell->sended_line))
			exec_cmd(shell, shell->sended_line);
		else
			exec_builtin(shell, shell->sended_line);
		free(line);
		free(shell->sended_line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	shell;

	(void) argc;
	(void) argv;
	shell.is_running = 1;
	shell.messages = ft_init_messages();
	shell.env_map = env_map_init(env);
	ft_shell_loop(&shell);
	env_map_flush(shell.env_map);
	ft_flush_tokens(shell.parsing_cmd.tokens);
	rl_clear_history();
	rl_clear_message();
	rl_clear_visible_line();
	rl_clear_pending_input();
	return (0);
}
