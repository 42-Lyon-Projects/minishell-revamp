/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:10:16 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/21 14:39:18 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

void	error_msg(char *string)
{
	perror(string);
	exit(EXIT_FAILURE);
}

void	free_and_exit(t_minishell *shell, t_pipex *pipex, int code)
{
	t_env_map	*node;
	int			status_code;

	node = env_map_find_node(shell->env_map, "?");
	if (code != -1)
		status_code = code;
	else
		status_code = ft_atoi(node->value);
	ft_flush_command_list(shell->commands);
	ft_flush_tokens(shell->parsing_cmd.tokens);
	if (shell && shell->env_map)
		env_map_flush(shell->env_map);
	if (pipex && pipex->envp)
		ft_free_split(pipex->envp);
	if (pipex && pipex->pid)
		free(pipex->pid);
	if (shell && shell->sended_line)
		free(shell->sended_line);
	exit(status_code);
}
