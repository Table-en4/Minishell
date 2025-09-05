/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:37:11 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/05 10:53:32 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valide_unset(char *name)
{
    int i;

    if (!name || !name[0])
        return (0);
    i = 0;
    while (name[i])
    {
        if (name[i] == '=' || name[i] == '-')
            return (0);
        i++;
    }
    return (valide_id(name));
}

int ft_unset(char **args, t_env **envp)
{
    int i;
    int error_count;

    if (!args[1])
        return (0);
    error_count = 0;
    i = 1;
    while (args[i])
    {
        if (args[i][0] == '-' && args[i][1] != '\0')
        {
            if (ft_strcmp(args[i], "-v") == 0)
            {
                i++;
                unset_env(envp, args[i]);
                i++;
                continue;
            }
            else if (ft_strcmp(args[i], "-f") == 0)
            {
                ft_dprintf(2, "unset: -f option not supported\n");
                error_count++;
                i++;
                continue;
            }
            else if (ft_strcmp(args[i], "--") == 0)
            {
                i++;
                continue;
            }
            else
            {
                ft_dprintf(2, "unset: '%s' invalid option\n", args[i]);
                ft_dprintf(2, "unset: usage: unset [-v] [name]\n");
                return (2);
            }
        }
        else
        {
            if (!is_valide_unset(args[i]))
            {
                ft_dprintf(2, "unset: '%s' invalid id\n", args[i]);
                error_count++;
                i++;
                continue;
            }
            if (ft_strcmp(args[i], "PWD") == 0 ||
                ft_strcmp(args[i], "OLDPWD") == 0 ||
                ft_strcmp(args[i], "PATH") == 0)
                ft_dprintf(2, "unset: warning: unsetting '%s'\n", args[i]);
        }
        i++;
    }
    if (error_count > 0)
        return (1);
    return (0);
}
