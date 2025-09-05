/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:34:51 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/05 10:34:52 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_count(t_env *envp)
{
	int		count;
	t_env	*current;

	count = 0;
	current = envp;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	*create_env_string(char *key, char *value)
{
	char	*result;
	int		key_len;
	int		value_len;
	int		i;
	int		j;

	if (!key || !value)
		return (NULL);
	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	result = malloc(key_len + value_len + 2);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (key[i])
		result[j++] = key[i++];
	result[j++] = '=';
	i = 0;
	while (value[i])
		result[j++] = value[i++];
	result[j] = '\0';
	return (result);
}

void	free_env_tab(char **tab, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**env_to_tab(t_env *envp)
{
	char	**tab;
	t_env	*current;
	int		count;
	int		i;

	count = env_count(envp);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	current = envp;
	i = 0;
	while (current)
	{
		tab[i] = create_env_string(current->key, current->value);
		if (!tab[i])
			return (free_env_tab(tab, i), NULL);
		current = current->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
