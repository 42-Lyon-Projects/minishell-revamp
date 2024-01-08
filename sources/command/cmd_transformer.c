/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_transformer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:48:42 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/08 09:49:52 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/string_utils.h"
#include "../../dependencies/libft/.includes/char_utils.h"
#include <stdlib.h>
#include "../../dependencies/libft/.includes/ft_printf.h"

static void	ft_delete_cmd_space(t_minishell *shell, size_t space_before, size_t space_after, size_t index)
{
	char		*cmd;
	t_boolean	used;

	cmd = shell->commands.latest_command;
	used = _false;
	while (cmd[index])
	{
		if (ft_is_whitespace(cmd[index]) && !used)
			space_before++;
		if (!ft_is_whitespace(cmd[index++]) && !used)
			used = _true;
	}
	used = _false;
	index = ft_strlen(cmd);
	while (cmd[index])
	{
		if (ft_is_whitespace(cmd[index]) && !used)
			space_after++;
		if (!ft_is_whitespace(cmd[index--]) && !used)
			used = _true;
	}
	cmd = ft_substr(cmd, space_before, ft_strlen(cmd) - space_after);
	free(shell->commands.latest_command);
	shell->commands.latest_command = cmd;
}

static int ft_cmd_valid_quotes(t_minishell *shell, size_t start)
{
	if (ft_index_is_in_quote(shell->commands.latest_command, start, '"'))
		return (1);
	if (ft_index_is_in_quote(shell->commands.latest_command, start, '\''))
		return (0);
	return (1);
}

static int ft_cmd_contains_valid_key(t_minishell *shell, char *key, size_t *start)
{
	size_t starting_s = *start;
	if (!ft_str_contains(shell->commands.latest_command, key, start, starting_s))
		return 0;
	if (!ft_cmd_valid_quotes(shell, *start))
		return 0;
	if (!(*start == 0 || (start > 0 && shell->commands.latest_command[*start -1] != '$' &&\
	shell->commands.latest_command[*start + 1] != '$')))
		return 0;
	return 1;
}

static size_t	ft_strlen_until(char *str, char delimiter)
{
	size_t index;
	if (!str)
		return (0);
	index = 0;
	while (str[index])
	{
		if (str[index] == delimiter || str[index] == '"' || str[index] == '\'')
			return (index);
		index++;
	}
	return (index);
}

static void replace_valid_keys(t_minishell *shell, char *key, char *value, size_t *cmd_index)
{
	char	*before_key;
	char	*after_key;
	char	*keyed;

	if (ft_cmd_contains_valid_key(shell, key, cmd_index))
	{
		before_key = ft_substr(shell->commands.latest_command, 0, *cmd_index);
		after_key = ft_strdup(shell->commands.latest_command + (*cmd_index + ft_strlen(key)));
		if (after_key[0] != ' ' && after_key[0] != '"' &&\
		after_key[0] != '\'' && after_key[0] != '\0')
		{
			free(after_key);
			free(before_key);
			return;
		}
		keyed = ft_strjoin(before_key, value);
		free(shell->commands.latest_command);
		shell->commands.latest_command = ft_strjoin(keyed, after_key);
		free(before_key);
		free(keyed);
	}
}

static void replace_invalid_keys(t_minishell *shell, size_t *cmd_index)
{
	char	*before_key;
	char	*after_key;
	char	*invalid_key;
	char	*final;

	while (ft_cmd_contains_valid_key(shell, "$", cmd_index))
	{
		before_key = ft_substr(shell->commands.latest_command, 0, *cmd_index);
		invalid_key = ft_substr(shell->commands.latest_command, *cmd_index, ft_strlen_until(shell->commands.latest_command + *cmd_index, ' '));
		after_key = ft_strdup(shell->commands.latest_command + (*cmd_index + ft_strlen(invalid_key)));

		free(shell->commands.latest_command);
		final = ft_strjoin(before_key, "");

		shell->commands.latest_command = ft_strjoin(final, after_key);
		free(before_key);
		free(after_key);
		free(invalid_key);
		free(final);
	}
}

static void	ft_cmd_transform_env(t_minishell *shell)
{
	size_t		index;
	size_t		cmd_index;
	size_t		usless;
	t_env_map	*env;
	char		*key;

	index = 0;
	while (env_map_get_key(shell->env_map, index))
	{
		cmd_index = 0;
		env = env_map_find_node(shell->env_map, env_map_get_key(shell->env_map, index++));
		key = ft_strjoin("$", env->key);
		if (ft_str_contains(shell->commands.latest_command, key, &usless, 0))
		{
			while (shell->commands.latest_command[cmd_index])
			{
				replace_valid_keys(shell, key, env->value, &cmd_index);
				cmd_index++;
			}
		}
		free(key);
		index++;
	}
	cmd_index = 0;
	size_t t = ft_strlen(shell->commands.latest_command);
	while (t--)
	{
		replace_invalid_keys(shell, &cmd_index);
		cmd_index++;
	}
}

void	ft_post_command(t_minishell *shell)
{
	char	last;
	char	*tmp;

	ft_delete_cmd_space(shell, 0, 0, 0);
	last = ft_get_last_char_iw(shell->commands.latest_command);
	if (last == '|')
	{
		tmp = ft_strdup(shell->commands.latest_command);
		free(shell->commands.latest_command);
		shell->commands.latest_command = ft_substr(tmp, 0, ft_strlen(tmp) -1);
		free(tmp);
	}
	ft_cmd_transform_env(shell);
}
