/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:38:23 by molapoug          #+#    #+#             */
/*   Updated: 2025/11/12 15:20:32 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **result)
{
	int	j;

	j = 0;
	if (!result)
		return ;
	while (result[j])
	{
		free(result[j]);
		j++;
	}
	free(result);
}

char	*find_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*tmp;
	char	*full;
	char	*path_env;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_env(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
			return (ft_free_split(paths), full);
		(free(full), (i++));
	}
	return (ft_free_split(paths), NULL);
}
