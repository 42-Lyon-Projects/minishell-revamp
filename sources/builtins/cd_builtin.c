/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:57 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/24 17:42:50 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string_utils.h"
#include "put_utils.h"

void	err_msg(t_minishell *shell, char *msg)
{
	if (!msg)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putendl_fd("No such file or directory\n", 2);
	}
	else
		ft_putendl_fd(msg, 2);
	env_map_replace(shell->env_map, "?", "1");
}

static char	*get_cwd_for_cd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_strdup(cwd));
	else
		return (NULL);
}

void	exec_cd(t_minishell *shell, t_commands *command)
{
	t_env_map	*node;
	t_env_map	*oldpwd;
	char		*tmp;

	env_map_replace_or_add(shell->env_map, "?", "0");
	node = env_map_find_node(shell->env_map, "HOME");
	if (command->arguments_amount > 2)
		err_msg(shell, "cd: too many arguments");
	else if (node != NULL && command->arguments_amount == 1
		&& chdir(node->value) != 0)
		err_msg(shell, NULL);
	else if (command->arguments[1])
	{
		if (chdir(command->arguments[1]) != 0 || !get_pwd())
			err_msg(shell, NULL);
	}
	oldpwd = env_map_find_node(shell->env_map, "PWD");
	if (oldpwd)
		env_map_replace_or_add(shell->env_map, "OLDPWD", oldpwd->value);
	tmp = get_cwd_for_cd();
	env_map_replace_or_add(shell->env_map, "PWD", tmp);
	if (tmp)
		free(tmp);
}
