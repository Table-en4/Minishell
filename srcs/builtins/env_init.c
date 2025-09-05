/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:45:17 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/05 10:34:42 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env   *init_env(char **envp)
{
    t_env   *env_list;
    char    *key;
    char    *value;
    char    *pos;
    int     i;

    env_list = NULL;
    i = 0;
    while (envp[i])
    {
        pos = ft_strchr(envp[i], '=');
        if (pos)
        {
            *pos = '\0';
            key = envp[i];
            value = pos + 1;
            set_env_value(&env_list, key, value);
            *pos = '=';
        }
        i++;
    }
    return (env_list);
}

char **pasrse_line(char *line)
{
    char **args;
    char *token;
    int i;

    args = malloc(64 * sizeof(char *));
    if (!args)
        return (NULL);
    i = 0;
    token = ft_strtok(line, " \t\n");
    while (token && i < 63)
    {
        args[i] = ft_strdup(token);
        token = ft_strtok(NULL, " \t\n");
        i++;
    }
    args[i] = NULL;
    return (args);
}

void    free_args(char **args)
{
    int i;

    i = 0;
    if (!args)
        return ;
    while (args[i])
        free(args[i++]);
    free(args);
}
