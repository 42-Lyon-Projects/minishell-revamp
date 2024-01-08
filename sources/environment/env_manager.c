/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:43:45 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/08 10:25:39 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "stdlib.h"

t_env_map	*env_map_init(char **envp)
{
	t_env_map	*env_map;

	env_map = malloc(sizeof(t_env_map));
	if (!env_map)
		return (NULL);
	env_map->is_system = 0;
	env_map->has_equal = 0;
	env_map->is_immutable = 0;
	env_map->key = NULL;
	env_map->value = NULL;
	env_map->next_node = NULL;
	env_array_to_map(&env_map, envp);
	return (env_map);
}

t_env_map	*ft_create_env_node(char *key, char *value, int has_equals, int is_system)
{
	t_env_map	*new_node;

	new_node = malloc(sizeof(t_env_map));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->has_equal = has_equals;
	new_node->is_system = is_system;
	new_node->is_immutable = 0;
	new_node->next_node = NULL;
	return (new_node);
}

void	env_map_flush(t_env_map *env_map)
{
	t_env_map	*tmp;

	while (env_map)
	{
		tmp = env_map->next_node;
		if (env_map->key)
			free(env_map->key);
		if (env_map->value)
		{
			free(env_map->value);
			env_map->value = NULL;
		}
		free(env_map);
		env_map = tmp;
	}
}
