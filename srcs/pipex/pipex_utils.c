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

char *find_path(char *cmd, t_env *env)
{
    char **paths;
    char *tmp;
    char *full;
    int i;

    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
    paths = ft_split(get_env("PATH", env), ':');
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i++])
    {
        tmp = ft_strjoin(paths[i], "/");
        full = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(full, X_OK) == 0)
            return (free_split(paths), full);
        free(full);
    }
    return (free_split(paths), NULL);
}
