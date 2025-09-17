/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:44:57 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/30 11:44:59 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_array(t_env *env)
{
	t_env	*current;
	char	**array;
	int		count;
	int		i;
	char	*tmp;

	count = 0;
	current = env;
	while (current)
		1 && (count++, current = current->next);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		tmp = ft_strjoin(current->key, "=");
		array[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		if (!array[i])
			return (ft_free_split(array), NULL);
		1 && (i++, current = current->next);
	}
	return (array[i] = NULL, array);
}
