/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:45:06 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/30 11:45:08 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_builtin(char **args, t_env **envp)
{
    char    cwd[1024];
    t_env   *current;

    current = *envp;
    if (!args[0])
        return (0);
    if (ft_strcmp(args[0], "cd") == 0)
        return (ft_cd(args, envp));
    if (ft_strcmp(args[0], "echo") == 0)
        return (ft_echo(args));
    if (ft_strcmp(args[0], "pwd") == 0)
    {
        if (getcwd(cwd, sizeof(cwd)))
        {
            write(1, cwd, ft_strlen(cwd));
            write(1, "\n", 1);
        }
        else
            perror("pwd");
        return (0);
    }
    if (ft_strcmp(args[0], "unset") == 0)
        return (ft_unset(args, envp));
    if (ft_strcmp(args[0], "env") == 0)
        return (ft_env(args, envp));
    if (ft_strcmp(args[0], "export") == 0)
        return (ft_export(args, envp));
    if (ft_strcmp(args[0], "exit") == 0)
    {
        ft_dprintf(1, "\e[46mfin de l'experience utilisateur\e[0m\n");
        free_args(args);
        free_env_list(*envp);
        exit(0);
    }
    //IMPORTANT : la valeur -1 n'est pas un builtin
    return (-1);
}

char    **conv_env_envp(t_env *env_list)
{
    int     count;
    int     i;
    int     len;
    t_env   *current;
    char    **envp;

    current = env_list;
    i = 0;
    count = 0;
    while (current)
    {
        count++;
        current = current->next;
    }
    envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
        return (NULL);
    current = env_list;
    while (current && i < count)
    {
        len = ft_strlen(current->key) + ft_strlen(current->value) + 2;
        envp[i] = malloc(len);
        if (envp[i])
        {
            ft_strcpy(envp[i], current->key);
            ft_strcat(envp[i], "=");
            ft_strcat(envp[i], current->value);
        }
        current = current->next;
        i++;
    }
    return (envp[i] = NULL, envp);
}

void    free_envp(char **envp)
{
    int i;

    i = 0;
    if (!envp)
        return ;
    while (envp[i])
        free(envp[i++]);
    free(envp);
}

int execute_external(char **args, t_env *env_list)
{
    pid_t pid;
    int status;
    char **envp;
    
    envp = conv_env_envp(env_list);
    if (!envp)
        return (1);
    pid = fork();
    if (pid == 0)
    {
        if (execve(args[0], args, envp) == -1)
        {
            perror(args[0]);
            free_envp(envp);
            exit(127);
        }
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        free_envp(envp);
        return (WEXITSTATUS(status));
    }
    else
    {
        perror("fork");
        free_envp(envp);
        return (1);
    }
    return (0);
}
