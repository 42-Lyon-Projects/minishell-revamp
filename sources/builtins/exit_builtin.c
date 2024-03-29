/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:39 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/24 17:39:38 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "minishell.h"

static t_boolean	has_only_digits(char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (!ft_is_digit(str[index]) && ((str[index] != '-'
					&& index != 0) || (str[index] != '+' && index != 0)))
			return (_false);
		index++;
	}
	return (_true);
}

static char	*skip_chars(char *str)
{
	size_t	index;
	char	*copy;

	index = 0;
	copy = str;
	while ((str[index] == '0' && str[index + 1] && str[index + 1] == '0') || \
		ft_is_whitespace(str[index]))
	{
		index++;
		copy++;
	}
	return (copy);
}

void	exit_with_args(t_minishell *shell, t_commands *command,
	int *code, t_boolean *exit)
{
	char	*args;

	args = NULL;
	if (ft_get_arguments_amount(command) > 1)
	{
		args = command->arguments[1];
		args = skip_chars(args);
		if (!has_only_digits(args))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			env_map_replace_or_add(shell->env_map, "?", "2");
			*code = 2;
		}
		else if (has_only_digits(args) && ft_get_arguments_amount(command) > 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			env_map_replace_or_add(shell->env_map, "?", "1");
			*exit = _false;
		}
		else
			*code = ft_atoi(args);
	}
}

void	exec_exit(t_minishell *shell, t_commands *command)
{
	t_env_map	*env_map;
	int			exit_code;
	char		*result;
	t_boolean	must_exit;

	must_exit = _true;
	printf("exit\n");
	exit_with_args(shell, command, &exit_code, &must_exit);
	if (ft_get_arguments_amount(command) == 1)
	{
		env_map = env_map_find_node(shell->env_map, "?");
		if (env_map != NULL)
			exit_code = ft_atoi(env_map->value);
	}
	if (must_exit == _false)
		return ;
	result = ft_itoa(exit_code % 256);
	if (result == NULL)
		return ;
	env_map_replace_or_add(shell->env_map, "?", result);
	shell->is_running = _false;
	free(result);
}
