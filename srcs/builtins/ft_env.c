#include "minishell.h"

int env_value(t_env **env, char *arg)
{
    t_blt   *blt;

    blt = NULL;
    blt->pos = ft_strchr(arg, '=');
    if (!blt->pos)
        return (0);
    *(blt->pos) = '\0';
    blt->key = arg;
    blt->value = blt->pos + 1;
    if (!valide_id(blt->key))
    {
        *(blt->pos) = '=';
        return (ft_dprintf(2, "env: '%s': not valid", arg), 1);
    }
    blt->copy = ft_strdup(blt->copy);
    *(blt->pos) = '=';
    set_env_value(env, blt->copy, blt->value);
    return (free(blt->copy), 0);
}

int    unset_env(t_env **envp, char *key)
{
    t_env   *current;
    t_env   *prev;

    if (!envp || !*envp || !key)
        return (1);
    current = *envp;
    prev = NULL;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *envp = current->next;
            free_env_node(current);
            return (1);
        }
        prev = current;
        current = current->next;
    }
    return (0);
}

t_env   *duplic_env(t_env *ori)
{
    t_env   *new;
    t_env   *current;

    new = NULL;
    current = ori;
    while (current)
    {
        set_env_value(&new, current->key, current->value);
        current = current->next;
    }
    return (new);
}

int env_exec(char **args, t_env *env)
{
    pid_t   pid;
    int     status;
    char    **envp;

    envp = conv_env_envp(env);
    if (!env)
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
        //coder la fonction wexitstatus
        return (WEXITSTATUS(status));
    }
    return (0);
}

int ft_env(char **args, t_env **envp)
{
    int     i;
    t_env   *env;
    t_env   *current;
    //int     ignore_env;
    char    **commad;
    int     command_start;
    int     result;

    i = 1;
    env = NULL;
    //ignore_env = 0;
    commad = NULL;
    command_start = -1;
    if (!args[1])
    {
        current = *envp;
        while (current)
        {
            ft_dprintf(1, "%s=%s\n", current->key, current->value);
            current = current->next;
        }
        return (0);
    }
    env = duplic_env(*envp);
    while (args[i])
    {
        if (ft_strcmp(args[i], "-i") == 0)
        {
            //ignore_env = 1;
            free_env_list(env);
            env = NULL;
        }
        else if (ft_strcmp(args[i], "-u") == 0)
        {
            i++;
            if (!args[i])
            {
                ft_dprintf(2, "env: option requires argument -- u\n");
                return (free_env_list(env), 1);
            }
            unset_env(&env, args[i]);
        }
        else if (ft_strchr(args[i], '='))
        {
            if (export_no_value(&env, args[i]) != 0)
                return (free_env_list(env), 1);
        }
        else
        {
            command_start = i;
            break ;
        }
        i++;
    }
    if (command_start == -1)
    {
        current = env;
        while (current)
        {
            ft_dprintf(1, "%s=%s\n", current->key, current->value);
            current = current->next;
        }
        return (free_env_list(env), 0);
    }
    commad = &args[command_start];
    result = env_exec(commad, env);
    return (free_env_list(env), result);
}
