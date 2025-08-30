/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:04:38 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/30 02:26:30 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_update_pwd(t_env **envp)
{
    char    *old_pwd;
    char    *new_pwd;
    char    cwd[1024];

    old_pwd = get_env(*envp, "PWD");
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return (perror("getcwd"), 1);
    new_pwd = cwd;
    if (old_pwd)
        set_env_value(envp, "OLDPWD", old_pwd);
    set_env_value(envp, "PWD", new_pwd);
    return (0);
}

int ft_cd(char **args, t_env **envp)
{
    char    *go_dir;
    char    *home;
    char    *old_pwd;

    if (!args[1])
    {
        home = get_home(*envp);
        if (!home)
            return (ft_putstr_fd("cd : HOME does not set\n", 2), 1);
        go_dir = home;
    }
    else if (ft_strcmp(args[1], "-") == 0)
    {
        old_pwd = get_oldpwd(*envp);
        if (!old_pwd)
            return (ft_putstr_fd("cv : OLDPWD does not set\n", 2), 1);
        go_dir = old_pwd;
        ft_dprintf(1, "%s\n", go_dir);
    }
    else
        go_dir = args[1];
    if (chdir(go_dir) == -1)
        return (ft_dprintf(1, "cd: %s: %s\n", go_dir, strerror(errno)), 1);
    if (ft_update_pwd(envp) != 0)
        return (1);
    return (0);
}
