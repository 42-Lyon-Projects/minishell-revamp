/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:43:18 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/08 10:41:28 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "stdlib.h"

t_env_map	*env_map_add_back(t_env_map **env_map, t_env_map *new_node, int is_immutable)
{
	t_env_map	*tmp;

	tmp = *env_map;
	if (is_immutable)
		new_node->is_immutable = 1;
	if (tmp->key == NULL && tmp->value == NULL)
	{
		free(*env_map);
		*env_map = new_node;
		return (*env_map);
	}
	while (tmp->next_node)
		tmp = tmp->next_node;
	tmp->next_node = new_node;
	return (*env_map);
}

t_env_map	*env_map_remove_back(t_env_map *env_map)
{
	t_env_map	*tmp;
	t_env_map	*last_node;

	if (!env_map)
		return (NULL);
	if (!env_map->next_node)
	{
		free(env_map);
		return (NULL);
	}
	tmp = env_map;
	while (tmp->next_node->next_node)
		tmp = tmp->next_node;
	last_node = tmp->next_node;
	tmp->next_node = NULL;
	free(last_node);
	return (env_map);
}

t_env_map	*env_map_remove_from_key(t_env_map *env_map, char *key)
{
	t_env_map	*tmp;
	t_env_map	*last_node;

	if (!env_map)
		return (NULL);
	tmp = env_map;
	while (tmp->next_node->next_node)
	{
		if (ft_str_equals(tmp->next_node->key, key))
		{
			last_node = tmp->next_node;
			tmp->next_node = tmp->next_node->next_node;
			free(last_node);
			return (env_map);
		}
		tmp = tmp->next_node;
	}
	return (env_map);
}

t_env_map	*env_map_replace(t_env_map *env_map, char *key, char *value)
{
	t_env_map	*tmp;

	if (!env_map)
		return (NULL);
	tmp = env_map;
	while (tmp)
	{
		if (ft_str_equals(tmp->key, key))
		{
			tmp->value = value;
			return (env_map);
		}
		tmp = tmp->next_node;
	}
	return (NULL);
}
