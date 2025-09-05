/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:04:38 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/02 10:19:13 by molapoug         ###   ########.fr       */
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
    t_cd    val;

    if (!args[1])
    {
        val.home = get_home(*envp);
        if (!val.home)
            return (ft_putstr_fd("cd : HOME does not set\n", 2), 1);
        val.go_dir = val.home;
    }
    else if (ft_strcmp(args[1], "-") == 0)
    {
        val.old_pwd = get_oldpwd(*envp);
        if (!val.old_pwd)
            return (ft_putstr_fd("cv : OLDPWD does not set\n", 2), 1);
        val.go_dir = val.old_pwd;
        ft_dprintf(1, "%s\n", val.go_dir);
    }
    else
        val.go_dir = args[1];
    if (chdir(val.go_dir) == -1)
        return (ft_dprintf(1, "cd: %s: %s\n", val.go_dir, strerror(errno)), 1);
    if (ft_update_pwd(envp) != 0)
        return (1);
    return (0);
}
