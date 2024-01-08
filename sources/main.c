/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:27:22 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/08 10:42:03 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

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
		shell->sended_line = line;
		parse_input(shell);
		//exec_simple_cmd(minishell, NULL);
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
	rl_clear_history();
	rl_clear_message();
	rl_clear_visible_line();
	rl_clear_pending_input();
	return (0);
}
